
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryModuleMap (
  DB_COLUMN_PREFIXmoduleName
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXactive
      SMALLINT
    
    );

  
    CREATE UNIQUE INDEX GalleryModuleMap_moduleName 
    ON DB_TABLE_PREFIXGalleryModuleMap
    (DB_COLUMN_PREFIXmoduleName);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryModuleMap',
      1,
      0
      );

  