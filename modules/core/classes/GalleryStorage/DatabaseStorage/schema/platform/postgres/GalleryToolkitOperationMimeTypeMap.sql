
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXTkOperationMimeTypeMap (
  DB_COLUMN_PREFIXoperationName
      VARCHAR(
      
          128
        
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXtoolkitId
      VARCHAR(
      
          128
        
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXmimeType
      VARCHAR(
      
          128
        
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpriority
      INTEGER
    
    NOT NULL
  
    );

  
    CREATE INDEX TkOperationMimeTypeMap_operationName 
    ON DB_TABLE_PREFIXTkOperationMimeTypeMap
    (DB_COLUMN_PREFIXoperationName);

  
    CREATE INDEX TkOperationMimeTypeMap_mimeType 
    ON DB_TABLE_PREFIXTkOperationMimeTypeMap
    (DB_COLUMN_PREFIXmimeType);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'TkOperationMimeTypeMap',
      1,
      0
      );

  