
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXModuleMap (
  DB_COLUMN_PREFIXmoduleName
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXactive
      int(1)
    
    , 
  
    UNIQUE KEY (DB_COLUMN_PREFIXmoduleName)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ModuleMap',
      1,
      0
      );

  