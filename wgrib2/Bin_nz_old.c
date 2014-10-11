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
#include "math.h"
// http://troydhanson.github.io/uthash/userguide.html#_hooks
#include "uthash.h"　
#include "bin_nz.h"

extern int decode, flush_mode;
extern int file_append;
extern int WxText, WxNum;

extern double *lat, *lon;
extern int decode, latlon;

extern struct hash *table;

extern float MIN_LONGTITUDE;
extern float MAX_LONGTITUDE;
extern float MIN_LATITUDE;
extern float MAX_LATITUDE;

extern short int x_size;
extern short int y_size;
extern short int x_offset;
extern short int y_offset;

extern int FT_SNAPSHOT;
extern int FT_FORECAST30m;
extern int FT_FORECAST60m;

struct position_type {
    short int x;
    short int y;
    float value;
  } position;
                     

 
/*
 * HEADER:100:bin_nz_old:output:2:make comma separated file for NZ, X=file (WxText enabled)
 */

int f_bin_nz_old(ARG2) {
        //char new_inv_out[STRING_SIZE];
        char name[100], desc[100], unit[100];
        FILE *out;

        unsigned int j;
        char vt[20],rt[20],et[20];
        int year, month, day, hour, minute, second;
        double min_value = 0.0; //atof(arg2);
        int ft_mode;
        if(strcmp(arg2, "snapshot") == 0){
                ft_mode = FT_SNAPSHOT;
        } else if (strcmp(arg2, "30m") == 0){
                ft_mode = FT_FORECAST30m;
        } else if (strcmp(arg2, "60m") == 0){
                ft_mode = FT_FORECAST60m;
        } else {
               fatal_error("bin_nz: invalid argment %s", arg2);  
        }

        if (!((sizeof(short int) == 2) && (sizeof(float) == 4))){
               fatal_error("bin_nz: binary size not compatibile %s", "");  
        }

        /* initialization phase */
        if (mode == -1) {
                WxText = decode = latlon = 1;
                if ((*local = (void *) ffopen(arg1, file_append ? "a" : "wb")) == NULL)
	                fatal_error("bin_nz: could not open file %s", arg1);  
                 // minimum value to output
                if(min_value < 0.0){
                        fatal_error("bin_nz: arg2 must be a positive number: %s", arg2);
                        return 0;                
                }
                return 0;
        }

        /* cleanup phase */
        if (mode == -2) {
            // free hash table
            delete_all();
            return 0;
        }
        
        /* processing phase */
        if (lat == NULL || lon == NULL) {
                fprintf(stderr,"bin_nz: latitude/longitude not defined, record skipped\n");
                return 0;
        }

        /* Collect runtime and forecast time into vt and rt */
        // sec refers to the array of sections. reftime refers the section 1-13:19)
        reftime(sec, &year, &month, &day, &hour, &minute, &second);
        sprintf(rt, "%4.4d%2.2d%2.2d %2.2d%2.2d", year,month,day,hour,minute); // second is omitted

        // status (section 1-20)
        int status = getStatus(sec);
        if(status != 0){
                fprintf(stderr,"bin_nz: test record skipped\n");
                return 0;
        }

        // parameter name (Section 4-11)
#if DEBUG
        getExtName(sec, mode, NULL, name, desc, unit,".","_");
#endif
        int param= getParamNum(sec);
        if(param != 8 && param != 203 && param != 214){
                fprintf(stderr,"bin_nz: illegal param type (section 4-11), record skipped\n");
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
        //endtime(50011, sec, &year, &month, &day, &hour, &minute, &second);
        //sprintf(et, "%2.2d%2.2d", hour,minute);        

        // stat type (section 4-47) (4.50011)        
        int stat_type = getStatType(sec); // 1, 195, 196
        if(stat_type != 1 && stat_type != 195 && stat_type != 196){
                fprintf(stderr,"bin_nz: illegal stat type (section 4-47), record skipped\n");
                return 0;
        }

        // stat process time (section 4-50:53)
        int stat_process_time = getStatProcessTime(sec);
        if(stat_process_time != 5 && stat_process_time != 60){
                fprintf(stderr,"bin_nz: illegal stat_process_time (section 4-50:53), record skipped\n");
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
/*
        struct pair p1, p2, p3;
        p1.latitude = 1.0;
        p1.longtitude = 2.0;
        p2.latitude = 10.0;
        p2.longtitude = 20.0;
        p3.latitude = 100.0;
        p3.longtitude = 200.0;
        
        add_data(p1, 100.0);
        add_data(p2, 200.0);

        struct hash *h1 = find_data(p1);
        printf("h1: %f\n", h1->value);
        struct hash *h2 = find_data(p2);
        printf("h2: %f\n", h2->value);

        delete_data(h1);
        struct hash *h3 = find_data(p1);
        //printf("h3: %f", h3->value);
        struct hash *h4 = find_data(p2);
        printf("h4: %f\n", h4->value);
        
        add_data(p1, 300.0);
        add_data(p2, 300.0);
        add_data(p1, 1000.0);
        add_data(p2, 2000.0);
        add_data(p3, 3000.0);
        struct hash *h5 = find_data(p1);
        printf("h5: %f\n", h5->value);
        struct hash *h6 = find_data(p2);
        printf("h6: %f\n", h6->value);
        struct hash *current;
        for(current=table; current != NULL; current=(struct hash*)(current->hh.next)){
                printf("%f %f :%f\n",current->id.latitude, current->id.longtitude, current->value);
        }
        fatal_error("","");
*/

        if((ft_mode == FT_SNAPSHOT && sft == -5 ) || 
           (ft_mode == FT_FORECAST30m && sft > -5 && sft <= 25) ||
           (ft_mode == FT_FORECAST60m && sft > -5 && sft <= 55)) {
                for (j = 0; j < ndata; j++) {
                    float value = data[j];
                    if (!UNDEFINED_VAL(data[j]) && value >= min_value && value > 0.0 && (param == 8 || param == 203)) {
                        struct pair *p;
                        p = malloc(sizeof(struct pair));
                        p->longtitude =  lon[j] > 180.0 ?  lon[j]-360.0 : lon[j];
                        p->latitude = lat[j];
                        add_data(p, value);
                        //struct pair p;
                        //p.longtitude =  lon[j] > 180.0 ?  lon[j]-360.0 : lon[j];
                        //p.latitude = lat[j];
                        //add_data(p, value);
                    }
                }
        }
        
        short int x_offset = translate_longtitude_to_index_250m(MIN_LONGTITUDE);
        short int y_offset = translate_latitude_to_index_250m(MIN_LATITUDE);

        /* open output file */
        if((ft_mode == FT_SNAPSHOT && sft == -5 ) || 
           (ft_mode == FT_FORECAST30m && sft == 25) ||
           (ft_mode == FT_FORECAST60m && sft == 55)) {
                out = (FILE *) *local;
                struct hash *current;
                for(current=table; current != NULL; current=(struct hash*)(current->hh.next)){
                        position.value = current->value;
                        float longtitude = current->id->longtitude;
                        float latitude = current->id->latitude;
                        short int flag_1km = check_1km_grid(longtitude, latitude);
                        if(!flag_1km){
                                // 250mメッシュの情報ならそのまま書き込む
                                position.x = translate_longtitude_to_index_250m(longtitude) - x_offset;
                                position.y = translate_latitude_to_index_250m(latitude) - y_offset;
                                fwrite(&position, sizeof(position), 1, out);
                        } else {
                                // 1kmメッシュの場合には、250mメッシュに換算のうえ、となりの座標までの間も同じ値で埋める
                                short int xi = translate_longtitude_to_index_1km(longtitude);
                                short int xx1 = translate_longtitude_to_index_250m(translate_index_to_longtitude_1km(xi-1)) - x_offset;
                                short int xx2 = translate_longtitude_to_index_250m(translate_index_to_longtitude_1km(xi+1)) - x_offset;
                                short int yi = translate_latitude_to_index_1km(latitude);
                                short int yy1 = translate_latitude_to_index_250m(translate_index_to_latitude_1km(yi-1)) - y_offset;
                                short int yy2 = translate_latitude_to_index_250m(translate_index_to_latitude_1km(yi+1)) - y_offset;
                                short int xx, yy;
                                for(xx = xx1; xx < xx2; xx++){
                                        for(yy = yy1; yy < yy2; yy++){                                                
                                                position.x = xx;
                                                position.y = yy;
                                                position.value += 10000.0; // 1kmメッシュの情報の場合は、既に情報がある場合は書き込まない
                                                fwrite(&position, sizeof(position), 1, out);
                                        }
                                }
                        }
                }
                if (flush_mode) fflush(out);
        }
        return 0;
}

        
