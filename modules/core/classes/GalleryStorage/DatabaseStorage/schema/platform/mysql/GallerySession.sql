
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXSession (
  DB_COLUMN_PREFIXsessionId
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXkey
      varchar(
      
          32
        
      )
    
      ,
    DB_COLUMN_PREFIXvalue
      text
    
    , 
  
    INDEX (DB_COLUMN_PREFIXsessionId)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXkey)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Session',
      1,
      0
      );

  