/******************************************************************************************
 Copyright (C) 2008 Niklas Sondell, Storm Weather Center
 This file is part of wgrib2 and could be distributed under terms of the GNU General Public License

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grb2.h"
#include "wgrib2.h"
#include "fnlist.h"

extern int decode, flush_mode;
extern int file_append;
extern int WxText, WxNum;

extern double *lat, *lon;
extern int decode, latlon;

/*
 * HEADER:100:csv_nz:output:1:make comma separated file for NZ, X=file (WxText enabled)
 */

int f_csv_nz(ARG1) {

    char new_inv_out[STRING_SIZE];
    char name[100], desc[100], unit[100];
    FILE *out;

    unsigned int j;
    char vt[20],rt[20];
    int year, month, day, hour, minute, second;

    /* initialization phase */
    if (mode == -1) {
        WxText = decode = latlon = 1;
        if ((*local = (void *) ffopen(arg1,file_append ? "a" : "w")) == NULL)
		fatal_error("csv could not open file %s", arg1);  
	return 0;
    }

    /* cleanup phase */
   if (mode == -2) {
            return 0;
    }
        
    /* processing phase */
    if (lat == NULL || lon == NULL) {
	fprintf(stderr,"csv: latitude/longitude not defined, record skipped\n");
	return 0;
    }
    printf("csv: 4\n");	

    /* open output file */
    out = (FILE *) *local;

    /* Collect runtime and validtime into vt and rt */

    // sec refers to the array of sections. reftime refers the section 1.
    reftime(sec, &year, &month, &day, &hour, &minute, &second);
    sprintf(rt, "%4.4d%2.2d%2.2d %2.2d%2.2d", year,month,day,hour,minute); // second is omitted
#if DEBUG
    printf("ref time: %4.4d-%2.2d-%2.2d %2.2d:%2.2d", year,month,day,hour,minute);
#endif

    // forecast time 
    vt[0] = 0;
    unsigned int ft = forecast_time_in_units(sec);
    signed int sft = (ft & 0x80000000 == 0) ? ((signed int) ft) : -((signed int) (ft & 0x7fffffff));
    printf("vertime: %d", sft);
    sprintf(vt, "%d", sft);
    printf("csv: 7\n");	

    /*Get levels, parameter name, description and unit*/

    *new_inv_out = 0;
    f_lev(call_ARG0(new_inv_out,NULL));

    if (strcmp(new_inv_out, "reserved")==0) return 0;
//    getName(sec, mode, NULL, name, desc, unit);
    getExtName(sec, mode, NULL, name, desc, unit,".","_");
//	fprintf(stderr,"Start processing of %s at %s\n", name, new_inv_out);
//	fprintf(stderr,"Gridpoints in data: %d\n", ndata);
//	fprintf(stderr,"Description: %s, Unit %s\n", desc,unit);

        for (j = 0; j < ndata; j++) {
            if (!UNDEFINED_VAL(data[j])) {
                fprintf(out,"\"%s\",%s,\"%s\",\"%s\",%g,%g,%lg\n", rt, vt, name, new_inv_out, lon[j] > 180.0 ?  lon[j]-360.0 : lon[j], lat[j], data[j]);
            }
        }

        if (flush_mode) fflush(out);
        return 0;
}
