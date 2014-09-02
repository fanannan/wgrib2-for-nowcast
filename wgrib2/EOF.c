#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grb2.h"
#include "wgrib2.h"
#include "fnlist.h"

static FILE *eof_file = NULL;
static int eof_int;
static FILE *err_file = NULL;
static int err_int;

static FILE *eof_str_file = NULL;
static char *eof_str;
static FILE *err_str_file = NULL;
static char *err_str;

extern int file_append;

/*
 * HEADER:100:err_bin:setup:2:send (binary) integer to file upon err exit: X=file Y=integer
 */

int f_err_bin(ARG2) {
    if (mode == -1) {
        if ((err_file = (void *) ffopen(arg1, file_append ? "ab" : "wb")) == NULL) {
            fatal_error("Could not open %s", arg1);
        }
	err_int = atoi(arg2);
    }
    return 0;
}
void err_bin(void) {
    int i;
    /* this routine may called by fatal error and end of processing */
    if (err_file != NULL) {
        i = fwrite(&err_int, sizeof(int), 1, err_file);
        if (i != 1) fprintf(stderr,"ERROR err_bin: write error\n");
    }
    return;
}

/*
 * HEADER:100:err_string:setup:2:send string to file upon err exit: X=file Y=string
 */

int f_err_string(ARG2) {
    if (mode == -1) {
        if ((err_str_file = (void *) ffopen(arg1, file_append ? "ab" : "wb")) == NULL) {
            fatal_error("Could not open %s", arg1);
        }
	err_str = malloc(strlen(arg2) + 1);
	if (err_str == NULL) fatal_error("err_string: memory allocation","");
	strcpy(err_str, arg2);
    }
    return 0;
}

void err_string(void) {
    int i;
    /* this routine may called by fatal error and end of processing */
    if (err_str_file != NULL) {
	i = fwrite(err_str, strlen(err_str), 1, err_str_file);
	if (i != 1) fprintf(stderr,"ERROR err_string: write error\n");
    }
    return;
}



/*
 * HEADER:100:eof_bin:setup:2:send (binary) integer to file upon EOF: X=file Y=integer
 */

int f_eof_bin(ARG2) {
    if (mode == -1) {
        if ((eof_file = (void *) ffopen(arg1, file_append ? "ab" : "wb")) == NULL) {
            fatal_error("Could not open %s", arg1);
        }
	eof_int = atoi(arg2);
    }
    return 0;
}

void eof_bin(void) {
    int i;
    /* this routine may called by fatal error and end of processing */
    if (eof_file != NULL) {
	i = fwrite(&eof_int, sizeof(int), 1, eof_file);
	if (i != 1) fprintf(stderr,"ERROR eof_bin: write eofor\n");
    }
    return;
}

/*
 * HEADER:100:eof_string:setup:2:send string to file upon EOF: X=file Y=string
 */

int f_eof_string(ARG2) {
    if (mode == -1) {
        if ((eof_str_file = (void *) ffopen(arg1, file_append ? "ab" : "wb")) == NULL) {
            fatal_error("Could not open %s", arg1);
        }
        eof_str = malloc(strlen(arg2) + 1);
        if (eof_str == NULL) fatal_error("eof_string: memory allocation","");
        strcpy(eof_str, arg2);
    }
    return 0;
}

void eof_string(void) {
    int i;
    /* this routine may called by fatal rrror and end of processing */
    if (eof_str_file != NULL) {
        i = fwrite(eof_str, strlen(eof_str), 1, eof_str_file);
        if (i != 1) fprintf(stderr,"ERROR eof_string: write error\n");
    }
    return;
}

