CREATE TABLE DB_TABLE_PREFIXCustomFieldMap(
 DB_COLUMN_PREFIXitemId INTEGER NOT NULL,
 DB_COLUMN_PREFIXfield VARCHAR2(128) NOT NULL,
 DB_COLUMN_PREFIXvalue VARCHAR2(255),
 DB_COLUMN_PREFIXsetId INTEGER,
 DB_COLUMN_PREFIXsetType INTEGER
);

CREATE INDEX DB_TABLE_PREFIXCustomFieldMap_75985
   ON DB_TABLE_PREFIXCustomFieldMap(DB_COLUMN_PREFIXitemId);

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('CustomFieldMap', 1, 1);


