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

INSERT INTO workers VALUES (NULL, 'Haruhi', 'Suzumiya', 50.49, '2017-06-14', 1);
INSERT INTO workers VALUES (NULL, 'Asuka', 'Langley', 79.50, '2014-03-21', 1);
INSERT INTO workers VALUES (NULL, 'Shana', 'Flame Haze', 54.19, '2013-09-17', 1);
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
