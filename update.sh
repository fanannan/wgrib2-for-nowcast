#!/usr/bin/bash
PATH="$PATH:/bin/:/usr/bin:/usr/local/bin:"
DIR="/home/nowcast250/data"
OUT_DIR="${DIR}/recent"

# Clean up the old bin files
cd $OUT_DIR
PREV_05_FILE="`ls -lt ./*_NOWC_GPV_Ggis0p25km_Prr05lv_Aper5min_FH0000-0030_grib2.bin | head -n 1 | gawk '{print $9}'`"
PREV_60_FILE="`ls -lt ./*_NOWC_GPV_Ggis0p25km_Pri60lv_Aper5min_FH0000-0030_grib2.bin | head -n 1 | gawk '{print $9}'`"
if [ -f ${PREV_05_FILE} ]; then
    rm $PREV_05_FILE
fi
if [ -f ${PREV_60_FILE} ]; then
    rm $PREV_60_FILE
fi

# Find the latest gz file
cd $DIR
LATEST_05_ARCHIVE_FILE="`ls -lt ./*_NOWC_GPV_Ggis0p25km_Prr05lv_Aper5min_FH0000-0030_grib2.bin.gz | head -n 1 | gawk '{print $9}'`"
LATEST_60_ARCHIVE_FILE="`ls -lt ./*_NOWC_GPV_Ggis0p25km_Pri60lv_Aper5min_FH0000-0030_grib2.bin.gz | head -n 1 | gawk '{print $9}'`"

# Extract the lates bin files
LATEST_05_FILE="`echo ${LATEST_05_ARCHIVE_FILE} | sed 's/\.gz//'`"
LATEST_60_FILE="`echo ${LATEST_60_ARCHIVE_FILE} | sed 's/\.gz//'`"
if [ ! -f $OUT_DIR/$LATEST_05_FILE ]; then
        gzip -c -d $DIR/$LATEST_05_ARCHIVE_FILE > $OUT_DIR/$LATEST_05_FILE
fi
if [ ! -f $OUT_DIR/$LATEST_60_FILE ]; then
        gzip -c -d $DIR/$LATEST_60_ARCHIVE_FILE > $OUT_DIR/$LATEST_60_FILE
fi

# Parse the nowcast data
cd $OUT_DIR
TIME="`echo ${LATEST_05_FILE} | sed 's/.*RJTD_//' | sed 's/00_.*//'`"
CSV_05_FILE="nowcast_${TIME}_05_1.csv"
if [ ! -f $OUT_DIR/$CSV_05_FILE ]; then
        echo "processing ${LATEST_05_FILE}"
        wgrib2 ${LATEST_05_FILE} -csv_nz ${CSV_05_FILE} 1.0 1>/dev/null
fi
TIME="`echo ${LATEST_60_FILE} | sed 's/.*RJTD_//' | sed 's/00_.*//'`"
CSV_60_FILE="nowcast_${TIME}_60_1.csv"
if [ ! -f $OUT_DIR/$CSV_60_FILE ]; then
        echo "processing ${LATEST_60_FILE}"
        wgrib2 ${LATEST_60_FILE} -csv_nz ${CSV_60_FILE}  1.0 1>/dev/null
fi

# Clean up the old csv files
find $OUT_DIR -mtime +1 -name "*.csv"  | xargs rm


