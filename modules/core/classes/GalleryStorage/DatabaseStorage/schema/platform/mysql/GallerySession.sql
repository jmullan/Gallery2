
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXSession (
  DB_COLUMN_PREFIXsessionId
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXuserId
      int(11)
    
      ,
    DB_COLUMN_PREFIXcreationTime
      int(11)
    
      ,
    DB_COLUMN_PREFIXlastModificationTime
      int(11)
    
      ,
    DB_COLUMN_PREFIXsessionData
      text
    
    , 
  
    UNIQUE KEY (DB_COLUMN_PREFIXsessionId)
    
    , 
  
    INDEX (DB_COLUMN_PREFIXcreationTime)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXlastModificationTime)
    

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

  