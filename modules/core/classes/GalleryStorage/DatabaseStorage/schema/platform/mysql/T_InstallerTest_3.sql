ALTER TABLE DB_TABLE_PREFIXSchema
  DROP INDEX DB_TABLE_PREFIXSchema_18169;

UPDATE DB_TABLE_PREFIXSchema
  SET DB_COLUMN_PREFIXmajor=1, DB_COLUMN_PREFIXminor=2
  WHERE DB_COLUMN_PREFIXname='Schema' AND DB_COLUMN_PREFIXmajor=1 AND DB_COLUMN_PREFIXminor=1;


