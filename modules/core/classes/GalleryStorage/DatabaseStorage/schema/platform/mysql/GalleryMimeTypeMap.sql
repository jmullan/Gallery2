CREATE TABLE DB_TABLE_PREFIXMimeTypeMap(
 DB_COLUMN_PREFIXextension varchar(32) NOT NULL,
 DB_COLUMN_PREFIXmimeType varchar(32) NOT NULL,
 DB_COLUMN_PREFIXviewable int(1),
 PRIMARY KEY(DB_COLUMN_PREFIXextension)
) TYPE=DB_TABLE_TYPE;
INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('MimeTypeMap', 1, 0);

