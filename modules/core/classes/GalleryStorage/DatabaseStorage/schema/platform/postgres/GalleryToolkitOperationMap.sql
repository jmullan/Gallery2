
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXToolkitOperationMap (
  DB_COLUMN_PREFIXname
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXparametersCrc
      VARCHAR(
      
          32
        
      )
    
      ,
    DB_COLUMN_PREFIXoutputMimeType
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXdescription
      VARCHAR(
      
          255
        
      )
    
    );

  
    CREATE UNIQUE INDEX ToolkitOperationMap_name_parametersCrc 
    ON DB_TABLE_PREFIXToolkitOperationMap
    (DB_COLUMN_PREFIXname
        ,
      DB_COLUMN_PREFIXparametersCrc);

  
    CREATE UNIQUE INDEX ToolkitOperationMap_name 
    ON DB_TABLE_PREFIXToolkitOperationMap
    (DB_COLUMN_PREFIXname);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ToolkitOperationMap',
      1,
      0
      );

  