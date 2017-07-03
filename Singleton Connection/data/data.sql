BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS workers
(
    worker_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    firstname TEXT NOT NULL,
    lastname  TEXT NOT NULL,
    base_rate DOUBLE,
    hire_date DATE,
    position  INTEGER,
    FOREIGN KEY(position) REFERENCES position(position_id)
);

INSERT INTO workers VALUES (NULL, 'Haruhi', 'Suzumiya',  50.00, '2017-06-14', 1);
INSERT INTO workers VALUES (NULL, 'Asuka', 'Langley',    50.00, '2014-03-21', 1);
INSERT INTO workers VALUES (NULL, 'Shana', 'Flame Haze', 50.00, '2013-09-17', 1);
INSERT INTO workers VALUES (NULL, 'Shiki', 'Ryogi',      50.00, '2016-11-29', 2);
INSERT INTO workers VALUES (NULL, 'Kirie', 'Fujou',      50.00, '2011-09-28', 3);
COMMIT;

BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS position
(
    position_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    position    TEXT NOT NULL UNIQUE
);

INSERT INTO position(position) VALUES ('Employee');
INSERT INTO position(position) VALUES ('Manager');
INSERT INTO position(position) VALUES ('Sales');
COMMIT;

BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS subordinates
(
    superior INTEGER NOT NULL,
    inferior INTEGER NOT NULL,
    FOREIGN KEY(superior) REFERENCES workers(worker_id),
    FOREIGN KEY(inferior) REFERENCES workers(worker_id)
);

INSERT INTO subordinates VALUES (5, 1);
INSERT INTO subordinates VALUES (5, 2);
INSERT INTO subordinates VALUES (5, 3);
INSERT INTO subordinates VALUES (4, 5);
COMMIT;