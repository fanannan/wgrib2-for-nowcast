#include <stdio.h>
#include <string.h>
#include "grb2.h"
#include "wgrib2.h"
#include "fnlist.h"

/*
 * 2/2007 Public Domain: Wesley Ebisuzaki
 */

/*
 * HEADER:200:ens:inv:0:ensemble information
 */

int f_ens(ARG0) {
    int type, typefcst, center;
    const char *string;
    if (mode >= 0) {
	typefcst = code_table_4_7(sec);
	type = code_table_4_6(sec);
	center = GB2_Center(sec);
	if (type >= 0) {
	    switch(type) {
	        case 0: sprintf(inv_out,"ENS=hi-res ctl"); break;
	        case 1: sprintf(inv_out,"ENS=low-res ctl"); break;
	        case 2: 
			sprintf(inv_out,"ENS=-%d", perturbation_number(sec)); break;
	        case 3: 
			sprintf(inv_out,"ENS=+%d", perturbation_number(sec)); break;
	        case 4: 
			sprintf(inv_out,"MM-ENS=%d", perturbation_number(sec)); break;
	        default:
			sprintf(inv_out,"ENS=? table4.6=%d pert=%d",type,perturbation_number(sec)); break;
	    }
	    inv_out += strlen(inv_out);
	    if (typefcst >= 0) {
		*inv_out++=' ';
		*inv_out=0;
	    }
	}
	if (typefcst >= 0) {
	    string = "unknown derived fcst";
	    switch(typefcst) {
	        case 0: string = "ens-mean"; break;
	        case 1: string = "wt ens-mean"; break;
	        case 2: string = "std dev"; break;
	        case 3: string = "normalized std dev"; break;
	        case 4: string = "spread"; break;
	        case 5: string = "large anom index"; break;
	        case 6: string = "cluster mean"; break;
	        case 7: string = "25%-75% range"; break;
	        case 8: string = "ens min"; break;
	        case 9: string = "ens max"; break;
	        case 192: if (center == NCEP)  string = "mode"; break;
	        case 193: if (center == NCEP)  string = "10%"; break;
	        case 194: if (center == NCEP)  string = "50%"; break;
	        case 195: if (center == NCEP)  string = "90%"; break;
	    }
	    sprintf(inv_out,"%s", string);
	    inv_out += strlen(inv_out);
	}
    }
    return 0;
}

/*
 * HEADER:200:N_ens:inv:0:number of ensemble members
 */
int f_N_ens(ARG0) {
    unsigned int n;

    if (mode >= 0) {
	n = number_of_forecasts_in_the_ensemble(sec);
	if (n > 0) sprintf(inv_out,"%d ens members", n); 
    }
    return 0;
}
