CREATE TABLE DB_TABLE_PREFIXMaintenanceMap(
 DB_COLUMN_PREFIXrunId int(11) NOT NULL,
 DB_COLUMN_PREFIXtaskId varchar(128) NOT NULL,
 DB_COLUMN_PREFIXtimestamp int(11),
 DB_COLUMN_PREFIXsuccess int(1),
 DB_COLUMN_PREFIXdetails text,
 INDEX DB_TABLE_PREFIXMaintenanceMap_21687(DB_COLUMN_PREFIXtaskId),
 PRIMARY KEY(DB_COLUMN_PREFIXrunId)
) TYPE=DB_TABLE_TYPE;
INSERT INTO DB_TABLE_PREFIXSchema (
 DB_COLUMN_PREFIXname,
 DB_COLUMN_PREFIXmajor,
 DB_COLUMN_PREFIXminor
) VALUES('MaintenanceMap', 1, 0);

