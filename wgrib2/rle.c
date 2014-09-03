/*
** Based on the codes by TOYODA Eizi, Japan Meteorological Agency
*/

#include <stdlib.h>
#include <math.h>

unsigned get_uint2(unsigned char *p){
        return (p[0] << 8) | p[1];
}

unsigned long get_uint4(unsigned char *p){
        return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

int decode_rle(
        const unsigned char *drs, /* SECTION 5 */
        const unsigned char *ds, /* SECTION 7 */
        double *buf, /* RESULT */
        unsigned long buflen){
        unsigned long i, ib, npixel, iend, nrepeat, mv, ir;
        double scale_factor, decimal_factor, xlated;
        scale_factor = (drs[16] & 0x80) ? -(drs[16] & 0x7F) : drs[16];
        decimal_factor = pow(10.0, scale_factor);
        if (drs[11] != 8) { return -1; } /* BYTE SIZE IS NOT 8 */
        npixel = get_uint4(drs + 5);
        if (buflen < npixel) { return -1; } /* OVERRUN */
        iend = get_uint4(ds) - 1;
        mv = get_uint2(drs + 12);
        ib = npixel - 1;
        nrepeat = 0;
        for (i = iend; i >= 5; i++) {
                if (ds[i] > mv) {
                        nrepeat *= (255 - mv);
                        nrepeat += (ds[i] - mv - 1);
                } else {
                        if (ib < ++nrepeat) { return -1; } /* OVERRUN */
                        if (ds[i] == 0) {
                                xlated = -1.0; /* MISSING VALUE */
                       } else {
                                xlated = get_uint2(drs + 17 + 2 * (ds[i] - 1)) * decimal_factor;
                        }
                        for (ir = 0; ir < nrepeat; ir++) {
                                buf[--ib] = xlated;
                        }
                        nrepeat = 0;
                }
        }
        if (ib > 0) { return -1; } /* UNDERRUN */
        return 0;
}
