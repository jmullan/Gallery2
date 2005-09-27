CREATE TABLE DB_TABLE_PREFIXMultiLangItemMap(
 DB_COLUMN_PREFIXitemId INTEGER NOT NULL,
 DB_COLUMN_PREFIXlanguage VARCHAR(32) NOT NULL,
 DB_COLUMN_PREFIXtitle VARCHAR(128),
 DB_COLUMN_PREFIXsummary VARCHAR(255),
 DB_COLUMN_PREFIXdescription text
);

ALTER TABLE DB_TABLE_PREFIXMultiLangItemMap ADD PRIMARY KEY (DB_COLUMN_PREFIXitemId, DB_COLUMN_PREFIXlanguage);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('MultiLangItemMap', 1, 0);


