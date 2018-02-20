# select the directory that contains your python scripts
SELECT set_working_directory('/Users/rkoopmanschap/projects/centroid-decomposition/cd_monetdb');

# example 1: time_series centroid decomposition
DROP TABLE time_series;
CREATE TABLE time_series(x1 float, x2 float, x3 float, x4 float);
COPY INTO time_series FROM '/Users/rkoopmanschap/projects/centroid-decomposition/cd_monetdb/climate.csv' USING DELIMITERS ',','\n';
SELECT dudf('centroid_decomposition_dudf.py', 'time_series', 'x1, x2, x3, x4');

# example 2: Using views
DROP VIEW time_series5;
DROP TABLE time_series3;
DROP TABLE time_series4;
CREATE TABLE time_series3 (id INTEGER, x1 FLOAT, x2 FLOAT);
CREATE TABLE time_series4 (id INTEGER, x3 FLOAT, x4 FLOAT);
INSERT INTO time_series3 VALUES (1, 0.2, 0.5), (2, 0.7, 0.1);
INSERT INTO time_series4 VALUES (1, 0.6, 0.2), (2, 0.1, 0.9);
CREATE VIEW time_series5 AS (SELECT ts3.x1, ts3.x2, ts4.x3, ts4.x4 FROM time_series3 AS ts3 JOIN time_series4 AS ts4 ON ts3.id = ts4.id);
SELECT dudf('centroid_decomposition_dudf.py', 'time_series5', 'x1, x2, x3, x4');
