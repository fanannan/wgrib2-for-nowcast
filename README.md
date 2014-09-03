Modifination to wgrib2, distributed under terms of the GNU General Public License.

An optional parametetr is added to handle JMA's nowcast 250 data. You can use it as follows.

        -csv_nz FILE_PATH min_value
        ex: -csv_nz sample_output.csv 0.25

"min_value" is a lower threshold value to filter the data records. Records for the error information are all omitted.
A record of the output file follows the format described below.

        Reference time, end time, forecast time offset, longtitude, latitude, data value

