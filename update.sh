#!/usr/bin/bash
PATH="$PATH:/bin/:/usr/bin:/usr/local/bin:"
DIR="../../data"

PREV_05_FILE="`pwd`/`ls -lt $DIR/*_NOWC_GPV_Ggis0p25km_Prr05lv_Aper5min_FH0000-0030_grib2.bin | head -n 1 | gawk '{print $9}'`"
PREV_60_FILE="`pwd`/`ls -lt ../../data/*_NOWC_GPV_Ggis0p25km_Pri60lv_Aper5min_FH0000-0030_grib2.bin | head -n 1 | gawk '{print $9}'`"
if [ -f ${PREV_05_FILE} ]; then
    rm $PREV_05_FILE
fi
if [ -f ${PREV_60_FILE} ]; then
    rm $PREV_60_FILE
fi

LATEST_05_ARCHIVE_FILE="`pwd`/`ls -lt $DIR/*_NOWC_GPV_Ggis0p25km_Prr05lv_Aper5min_FH0000-0030_grib2.bin.gz | head -n 1 | gawk '{print $9}'`"
LATEST_60_ARCHIVE_FILE="`pwd`/`ls -lt $DIR/*_NOWC_GPV_Ggis0p25km_Pri60lv_Aper5min_FH0000-0030_grib2.bin.gz | head -n 1 | gawk '{print $9}'`"
gzip -d $LATEST_05_ARCHIVE_FILE
gzip -d $LATEST_60_ARCHIVE_FILE

LATEST_05_FILE="`pwd`/`ls -lt $DIR/*_NOWC_GPV_Ggis0p25km_Prr05lv_Aper5min_FH0000-0030_grib2.bin | head -n 1 | gawk '{print $9}'`"
LATEST_60_FILE="`pwd`/`ls -lt $DIR/*_NOWC_GPV_Ggis0p25km_Pri60lv_Aper5min_FH0000-0030_grib2.bin | head -n 1 | gawk '{print $9}'`"

echo "processing ${LATEST_05_FILE}"
TIME="`echo ${LATEST_05_FILE} | sed 's/.*RJTD_//' | sed 's/00_.*//'`"
wgrib2 ${LATEST_05_FILE} -csv_nz nowcast_${TIME}_05_1.csv 1.0 1>/dev/null
echo "processing ${LATEST_60_FILE}"
TIME="`echo ${LATEST_60_FILE} | sed 's/.*RJTD_//' | sed 's/00_.*//'`"
wgrib2 ${LATEST_60_FILE} -csv_nz nowcast_${TIME}_60_1.csv 1.0 1>/dev/null


