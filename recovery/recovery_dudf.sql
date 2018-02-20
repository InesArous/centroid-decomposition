DROP TABLE time_series;
CREATE TABLE time_series(x1 float, x2 float, x3 float, x4 float);
COPY 20 RECORDS INTO time_series FROM '/Users/rkoopmanschap/projects/centroid-decomposition/recovery/sample.txt' USING DELIMITERS ',','\n';
SELECT set_working_directory('/Users/rkoopmanschap/projects/centroid-decomposition/recovery');
SELECT dudf('recovery_dudf.py', 'time_series', 'x1, x2, x3, x4'); 
