
      ALTER TABLE DB_TABLE_PREFIXAlbumItem
      DROP (
	DB_COLUMN_PREFIXlayout
      )
    
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='AlbumItem' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  