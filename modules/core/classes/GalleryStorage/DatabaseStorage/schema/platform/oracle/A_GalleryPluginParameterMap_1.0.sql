
      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
    MODIFY (
    DB_COLUMN_PREFIXpluginType
      VARCHAR2(
       32 
      )
    
        ,
      DB_COLUMN_PREFIXpluginId
      VARCHAR2(
       32 
      )
    
    )
  
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
          DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='PluginParameterMap' AND
          DB_COLUMN_PREFIXmajor=1 AND
          DB_COLUMN_PREFIXminor=0;
  