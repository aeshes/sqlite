BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS employee
(
    id        INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    firstname TEXT NOT NULL,
    lastname  TEXT NOT NULL,
    base_rate DOUBLE,
    hire_date DATE,
    position  INTEGER NOT NULL,
	superior  INTEGER,
	
    FOREIGN KEY(position) REFERENCES position(id),
	FOREIGN KEY(superior) REFERENCES employee(id)
);

INSERT INTO employee VALUES (NULL, 'Haruhi', 'Suzumiya',  50.00, '2017-06-14', 1, 4);
INSERT INTO employee VALUES (NULL, 'Asuka', 'Langley',    50.00, '2014-03-21', 1, 4);
INSERT INTO employee VALUES (NULL, 'Shana', 'Flame Haze', 50.00, '2013-09-17', 1, 5);
INSERT INTO employee VALUES (NULL, 'Shiki', 'Ryogi',      50.00, '2016-11-29', 2, NULL);
INSERT INTO employee VALUES (NULL, 'Kirie', 'Fujou',      50.00, '2011-09-28', 3, NULL);
COMMIT;

BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS position
(
    id       INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    position TEXT NOT NULL UNIQUE
);

INSERT INTO position(position) VALUES ('Employee');
INSERT INTO position(position) VALUES ('Manager');
INSERT INTO position(position) VALUES ('Sales');
COMMIT;
