CREATE TABLE DB_TABLE_PREFIXAnimationItem(
 DB_COLUMN_PREFIXid int(11) NOT NULL,
 DB_COLUMN_PREFIXwidth int(11),
 DB_COLUMN_PREFIXheight int(11),
 PRIMARY KEY(DB_COLUMN_PREFIXid)
) TYPE=DB_TABLE_TYPE;

INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('AnimationItem', 1, 0);


