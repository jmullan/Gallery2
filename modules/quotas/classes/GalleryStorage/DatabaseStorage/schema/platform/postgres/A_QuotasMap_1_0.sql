
      DROP INDEX DB_TABLE_PREFIXQuotasMap_48775;
    
      ALTER TABLE DB_TABLE_PREFIXQuotasMap
      ADD COLUMN DB_COLUMN_PREFIXuserOrGroupIdTemp
  
      INTEGER
    
      ;

      UPDATE DB_TABLE_PREFIXQuotasMap SET
      DB_COLUMN_PREFIXuserOrGroupIdTemp
   = CAST(DB_COLUMN_PREFIXuserOrGroupId AS 
      INTEGER
    )
      ;

      ALTER TABLE DB_TABLE_PREFIXQuotasMap
      DROP DB_COLUMN_PREFIXuserOrGroupId
      ;

      ALTER TABLE DB_TABLE_PREFIXQuotasMap
      RENAME DB_COLUMN_PREFIXuserOrGroupIdTemp
   to DB_COLUMN_PREFIXuserOrGroupId
      ;

      
	ALTER TABLE DB_TABLE_PREFIXQuotasMap
	ALTER DB_COLUMN_PREFIXuserOrGroupId SET NOT NULL
	;
      
      ALTER TABLE DB_TABLE_PREFIXQuotasMap
          ADD PRIMARY KEY (DB_COLUMN_PREFIXuserOrGroupId)
        
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='QuotasMap' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  