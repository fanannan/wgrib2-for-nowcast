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

extern int decode, flush_mode;
extern int file_append;
extern int WxText, WxNum;

extern double *lat, *lon;
extern int decode, latlon;

float MIN_LONGTITUDE = 120.5046875;
float MAX_LONGTITUDE = 149.0078125;
float MIN_LATITUDE = 21.0031;
float MAX_LATITUDE = 46.6719;

short int x_size;
short int y_size;
short int x_offset;
short int y_offset;

float *sum_matrix;
float *new_matrix;
int new_matrix_status = -1;

int FT_SNAPSHOT = 1;
int FT_FORECAST30m = 2;
int FT_FORECAST60m = 3;
int FT_1kmMeshOnly = 4;
int previous_sft = -10000;

struct position_type {
    short int x;
    short int y;
    float value;
  } position;
                        
int max(short int a, short int b) {
	return a>b?a:b;
}

int min(short int a, short int b) {
	return a<b?a:b;
}

void clear_matrix(float *matrix){
        short int x, y;
        for (y=0;y<y_size;y++) {
                for (x=0;x<x_size;x++) {
	                matrix[y * x_size + x] = 0.0;
                }
        }
}

void add_matrix(float *sum_matrix, float *new_matrix){
        short int y, x;
        for (y=0;y<y_size;y++) {
                for (x=0;x<x_size;x++) {
                        long int i = y * x_size + x;
	                sum_matrix[i] = sum_matrix[i] + new_matrix[i];
                }
        } 
}

//round
float rounder(float x, int r){
        int z = 0;
        switch(r){
                case 0: z = 1;  break;
                case 1: z = 10;  break;
                case 2: z = 100;  break;
                case 3: z = 1000;  break;
                case 4: z = 10000; break;
                default:
                        fatal_error("round err", "");
        } 
        return roundf(x*z)/z;
}

// longtitude -> index        
short int translate_longtitude_to_index_250m(float longtitude){
        float x = (longtitude-122.502+0.0004375)/0.003125;
        return (int)(rounder(x, 0));
}

short int translate_longtitude_to_index_1km(float longtitude){
        float i = (longtitude-120.506-0.00025)/0.0125;
        return (int)(rounder(i, 2));
}

// index  -> longtitude
float translate_index_to_longtitude_250m(int index){
        float x = 0.003125*(index)+122.502-0.0004375;
        return rounder(x, 3);
}
                
float translate_index_to_longtitude_1km(int index){
        float x = 0.0125*(index)+120.506+0.00025;
        return rounder(x, 3);
}

// latitude -> index        
short int translate_latitude_to_index_250m(float latitude){
        float y = (latitude-23.6677-0.00001)/0.0020833333;
        return (int)(rounder(y, 1));
}

short int translate_latitude_to_index_1km(float latitude){
        float y = (latitude-21.0042+0.000033333)/0.00833333333;
        return (int)(rounder(y, 2));
}

// index -> latitude
float translate_index_to_latitude_250m(int index){
        float y = 0.0020833333*(index)+23.6677+0.00001;
        return rounder(y, 4);
}

float translate_index_to_latitude_1km(int index){
        float y = 0.00833333333*(index)+21.0042-0.000033333;
        return rounder(y, 4);
}

int check_longtitude_1km(float longtitude){
        short int x_index = translate_longtitude_to_index_1km(longtitude);
        float x_longtitude = translate_index_to_longtitude_1km(x_index);
        //if (longtitude != x_longtitude && fabs(longtitude - x_longtitude) <= 0.00026){ // 0.000244, -0.000259
        int r = (fabs(longtitude - x_longtitude) < 0.00026); 
        //printf("conversion error or grid system differs at x  %i %f %f %f\n", x_index, longtitude, x_longtitude, longtitude - x_longtitude);
        return r;
}

int check_longtitude_250m(float longtitude){
        short int x_index = translate_longtitude_to_index_250m(longtitude);
        float x_longtitude = translate_index_to_longtitude_250m(x_index);
//        int r = (fabs(longtitude - x_longtitude) > 0.00026); // true if 1km
        int r = (longtitude == x_longtitude); 
        return r;
}

// check if the position complies 1km grid conversion
int is_on_250m_grid(float longtitude, float latitude){
        return !check_longtitude_1km(longtitude);
/*
        short int y_index = translate_latitude_to_index_1km(latitude);
        float y_latitude = translate_index_to_latitude_1km(y_index);
         if(latitude != y_latitude){ // && fabs(latitude - y_latitude) <= 0.00003){  //-0.000004
//        if(fabs(latitude - y_latitude) > 0.001068){
//                printf("conversion error or grid system differs at y %i %f %f %f\n", y_index, latitude, y_latitude, latitude - y_latitude);
                return (1==0);
        }
        short int y_index2 = translate_latitude_to_index_250m(latitude);
        float y_latitude2 = translate_index_to_latitude_250m(y_index2);
        if(latitude == y_latitude2){
                return (1==0);
        }
        return (1==1);
*/
}

int check_1km_grid(float longtitude, float latitude){
        return !is_on_250m_grid(longtitude, latitude);
}

/*
 * HEADER:100:bin_nz:output:3:make comma separated file for NZ, X=file (WxText enabled)
 */

int f_bin_nz(ARG3) {
        //char new_inv_out[STRING_SIZE];
        char name[100], desc[100], unit[100];
        FILE *out;
        unsigned int j;
        char vt[20],rt[20],et[20];
        int year, month, day, hour, minute, second;

        int ft_mode;
        if(strcmp(arg2, "snapshot") == 0){
                ft_mode = FT_SNAPSHOT;
        } else if (strcmp(arg2, "30m") == 0){
                ft_mode = FT_FORECAST30m;
        } else if (strcmp(arg2, "60m") == 0){
                ft_mode = FT_FORECAST60m;
        } else if (strcmp(arg2, "1k") == 0){
                ft_mode = FT_1kmMeshOnly;
        } else {
               fatal_error("bin_nz: invalid argment %s", arg2);  
        }
        double min_value = atof(arg3);

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
                x_offset = translate_longtitude_to_index_250m(MIN_LONGTITUDE);
                y_offset = translate_latitude_to_index_250m(MIN_LATITUDE);
                x_size = translate_longtitude_to_index_250m(MAX_LONGTITUDE) - x_offset;
                y_size = translate_latitude_to_index_250m(MAX_LATITUDE) -y_offset;
                long int matrix_size = sizeof(float) * x_size * y_size;
                sum_matrix = malloc(matrix_size);
                clear_matrix(sum_matrix);
                new_matrix = malloc(matrix_size);
                clear_matrix(new_matrix);
                return 0;
        }

        /* cleanup phase */
        if (mode == -2) {
                /* open output file */
                out = (FILE *) *local;
                //fprintf(stderr, "new matrix status: %d\n", new_matrix_status);
                add_matrix(sum_matrix, new_matrix);
                // clear_matrix(new_matrix);
                new_matrix_status = 0;
                short int x, y;
                long int counter = 0;
                for (y=0;y<y_size;y++) {
                        for (x=0;x<x_size;x++) {
		                float value = sum_matrix[y * x_size + x];
		                if(value>0.0){
		                        position.value = value;
                                        position.x = x;
                                        position.y = y_size - y;
                                        fwrite(&position, sizeof(position), 1, out);
                                        counter++;
                                }
                        }
                }
                short int i;
                for(i = 0; i < 16 - (counter % 16); i++) { // padding
                        position.value = 0;
                        position.x = 0; // where no rain data is fiven
                        position.y = 0;
                        fwrite(&position, sizeof(position), 1, out);
                }
                fprintf(stderr, "size: %d %d\n", x_size, y_size);
                fprintf(stderr, "wrote %d records.\n", counter);
                if (flush_mode) fflush(out);
               free(sum_matrix);
               free(new_matrix);
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

        if((ft_mode == FT_SNAPSHOT && sft == -5 ) || 
           (ft_mode == FT_FORECAST30m && sft > -5 && sft <= 25) ||
           (ft_mode == FT_FORECAST60m && sft > -5 && sft <= 55) ||
           (ft_mode == FT_1kmMeshOnly && sft > 30 && sft <=55)){
                if(sft != previous_sft){
                        add_matrix(sum_matrix, new_matrix);
                        clear_matrix(new_matrix);
                        new_matrix_status = 0;
                        previous_sft = sft;
                }
                for (j = 0; j < ndata; j++) {
                    float value = data[j];
                    if (!UNDEFINED_VAL(data[j]) && value >= min_value && value > 0.0 && (param == 8 || param == 203)) {
                        float longtitude = lon[j] > 180.0 ?  lon[j]-360.0 : lon[j];
                        float latitude = lat[j];
                        //int flag_1km = check_1km_grid(longtitude, latitude);
                        int on250m = is_on_250m_grid(longtitude, latitude);
                        new_matrix_status = 1;
                        //if(!flag_1km){
                        if(on250m){
                                // 250mメッシュの情報ならそのまま書き込む
                                short int x = translate_longtitude_to_index_250m(longtitude) - x_offset;
                                short int y = translate_latitude_to_index_250m(latitude) - y_offset;
                                new_matrix[y * x_size + x] = value;
                                //new_matrix[y * x_size + x] = 128.0;
                                /*
                                printf("%d %d %f %f %f %f %f %f\n", x, y, 
                                        longtitude, 
                                        translate_index_to_longtitude_1km( translate_longtitude_to_index_1km(longtitude)),
                                        translate_index_to_longtitude_1km( translate_longtitude_to_index_1km(longtitude)) -longtitude,
                                        latitude, 
                                        translate_index_to_latitude_250m( translate_latitude_to_index_250m(latitude)),
                                        translate_index_to_latitude_250m( translate_latitude_to_index_250m(latitude)) -latitude);
                                        */
                        } else {
                                // 1kmメッシュの場合には、250mメッシュに換算のうえ、となりの座標までの間も同じ値で埋める
                                short int xi = translate_longtitude_to_index_1km(longtitude);
                                short int xx1 = max(0, translate_longtitude_to_index_250m(translate_index_to_longtitude_1km(xi-1)) - x_offset);
                                short int xx2 = min(x_size, translate_longtitude_to_index_250m(translate_index_to_longtitude_1km(xi+1)) - x_offset);
                                short int yi = translate_latitude_to_index_1km(latitude);
                                short int yy1 = max(0, translate_latitude_to_index_250m(translate_index_to_latitude_1km(yi-1)) - y_offset);
                                short int yy2 = min(y_size, translate_latitude_to_index_250m(translate_index_to_latitude_1km(yi+1)) - y_offset);
                                short int x, y;
                                for(x = xx1; x < xx2; x++){
                                        for(y = yy1; y < yy2; y++){                                                
                                                long int index = y * x_size + x;
                                                if (new_matrix[index] <= 0.0){
                                                        if (ft_mode != FT_1kmMeshOnly){
                                                                new_matrix[index] = value;  
                                                                //new_matrix[index] = 2.0;
                                                        } else {
                                                                new_matrix[index] = 8.0;
                                                        }
                                                }
                                        }
                                }
                        }
                    }
                }
        }
        return 0;
}

