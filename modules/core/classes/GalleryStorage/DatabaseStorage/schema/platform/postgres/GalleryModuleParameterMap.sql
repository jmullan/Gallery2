
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryModuleParameterMap (
  DB_COLUMN_PREFIXmoduleName
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXparameterName
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXparameterValue
      VARCHAR(
      
          255
        
      )
    
    );

  
    CREATE UNIQUE INDEX GalleryModuleParameterMap_moduleName_parameterName 
    ON DB_TABLE_PREFIXGalleryModuleParameterMap
    (DB_COLUMN_PREFIXmoduleName
        ,
      DB_COLUMN_PREFIXparameterName);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryModuleParameterMap',
      1,
      0
      );

  