
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXToolkitPropertyMimeTypeMap (
  DB_COLUMN_PREFIXpropertyName
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXtoolkitId
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXmimeType
      VARCHAR(
      
          128
        
      )
    
    );

  
    CREATE INDEX ToolkitPropertyMimeTypeMap_propertyName 
    ON DB_TABLE_PREFIXToolkitPropertyMimeTypeMap
    (DB_COLUMN_PREFIXpropertyName);

  
    CREATE INDEX ToolkitPropertyMimeTypeMap_mimeType 
    ON DB_TABLE_PREFIXToolkitPropertyMimeTypeMap
    (DB_COLUMN_PREFIXmimeType);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ToolkitPropertyMimeTypeMap',
      1,
      0
      );

  