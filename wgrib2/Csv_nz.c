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
 * HEADER:100:csv_nz:output:2:make comma separated file for NZ, X=file (WxText enabled)
 */

int f_csv_nz(ARG2) {

        //char new_inv_out[STRING_SIZE];
        char name[100], desc[100], unit[100];
        FILE *out;

        unsigned int j;
        char vt[20],rt[20],et[20];
        int year, month, day, hour, minute, second;
        double min_value = atof(arg2);

        /* initialization phase */
        if (mode == -1) {
                WxText = decode = latlon = 1;
                if ((*local = (void *) ffopen(arg1, file_append ? "a" : "w")) == NULL)
	                fatal_error("csv could not open file %s", arg1);  
                 // minimum value to output
                if(min_value < 0.0){
                        fatal_error("arg2 must be a positive number: %s", arg2);
                        return 0;                
                }
                return 0;
        }

        /* cleanup phase */
        if (mode == -2) {
            return 0;
        }
        
        /* processing phase */
        if (lat == NULL || lon == NULL) {
                fprintf(stderr,"csv_nz: latitude/longitude not defined, record skipped\n");
                return 0;
        }

        /* Collect runtime and forecast time into vt and rt */
        // sec refers to the array of sections. reftime refers the section 1-13:19)
        reftime(sec, &year, &month, &day, &hour, &minute, &second);
        sprintf(rt, "%4.4d%2.2d%2.2d %2.2d%2.2d", year,month,day,hour,minute); // second is omitted

        // status (section 1-20)
        int status = getStatus(sec);
        if(status != 0){
                fprintf(stderr,"csv_nz: test record skipped\n");
                return 0;
        }

        // parameter name (Section 4-11)
#if DEBUG
        getExtName(sec, mode, NULL, name, desc, unit,".","_");
#endif
        int param= getParamNum(sec);
        if(param != 8 && param != 203 && param != 214){
                fprintf(stderr,"csv_nz: illegal param type (section 4-11), record skipped\n");
                return 0;
        }

        // forecast time  (section 4-19:22)
        vt[0] = 0;
        unsigned int ft = forecast_time_in_units(sec);
        signed int sft = (ft & 0x80000000) ? -((signed int) (ft & 0x7fffffff)) : ((signed int) ft);
        //sprintf(vt, "%x %d", ft, sft);
#if DEBUG
        //printf("reference time: %4.4d-%2.2d-%2.2d %2.2d\n", year,month,day,hour);
        printf("reference time: %4.4d-%2.2d-%2.2d %2.2d:%2.2d", year,month,day,hour,minute);
        printf("forecast time: %d\n", sft);
#endif

        // end time (section 4-35:41)
        endtime(50011, sec, &year, &month, &day, &hour, &minute, &second);
        sprintf(et, "%2.2d%2.2d", hour,minute);        

        // stat type (section 4-47) (4.50011)        
        int stat_type = getStatType(sec); // 1, 195, 196
        if(stat_type != 1 && stat_type != 195 && stat_type != 196){
                fprintf(stderr,"csv_nz: illegal stat type (section 4-47), record skipped\n");
                return 0;
        }

        // stat process time (section 4-50:53)
        int stat_process_time = getStatProcessTime(sec);
        if(stat_process_time != 5 && stat_process_time != 60){
                fprintf(stderr,"csv_nz: illegal stat_process_time (section 4-50:53), record skipped\n");
                return 0;
        }
        
        // num data (section 5-6:9)
        int num_data = getNumData(sec);

        // show attributes
#if DEBUG
	printf("Start processing of %s\n", name);
	printf("Gridpoints in data: %d\n", ndata);
	printf("Num data: %d\n", num_data);
	printf("Description: %s, Unit %s\n", desc, unit);
	printf("Stat type: %d\n", stat_type);
	printf("Stat process time: %d\n",  stat_process_time);	
#endif
        
        /* open output file */
        out = (FILE *) *local;
        for (j = 0; j < ndata; j++) {
            if (!UNDEFINED_VAL(data[j]) && data[j] >= min_value && data[j] >= 0.0 && (param == 8 || param == 203)) {
                //fprintf(out,"\"%s\",\"%s\",%s,\"%s\",%d,%d,%g,%g,%lg\n", rt, et, vt, name, stat_type, stat_process_time, lon[j] > 180.0 ?  lon[j]-360.0 : lon[j], lat[j], data[j]);
                fprintf(out,"\"%s\",\"%s\",%d,%g,%g,%lg\n", rt, et, sft, lon[j] > 180.0 ?  lon[j]-360.0 : lon[j], lat[j], data[j]);
            }
        }
        if (flush_mode) fflush(out);
        return 0;
}

int getStatus(unsigned char **sec){
        return (int)(sec[1][20-1]);
}

int getParamNum(unsigned char **sec){
        return (int)(sec[4][11-1]);
}

int getStatType(unsigned char **sec){
        return (int)(sec[4][47-1]);
}

int getStatProcessTime(unsigned char **sec){
        return int4(sec[4]+50-1);
}

int getNumData(unsigned char **sec){
        return int4(sec[5]+6-1);
}
