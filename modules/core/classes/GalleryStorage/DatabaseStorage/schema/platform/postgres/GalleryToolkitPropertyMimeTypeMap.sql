
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXTkPropertyMimeTypeMap (
  DB_COLUMN_PREFIXpropertyName
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
  
    );

  
    CREATE INDEX DB_TABLE_PREFIXTkPropertyMimeTypeMap_1900452881 
    ON DB_TABLE_PREFIXTkPropertyMimeTypeMap
    (DB_COLUMN_PREFIXpropertyName);

  
    CREATE INDEX DB_TABLE_PREFIXTkPropertyMimeTypeMap_3639779463 
    ON DB_TABLE_PREFIXTkPropertyMimeTypeMap
    (DB_COLUMN_PREFIXmimeType);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'TkPropertyMimeTypeMap',
      1,
      0
      );

  