
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryItemPropertiesMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXkey
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXvalue
      TEXT
    
    );

  
    CREATE UNIQUE INDEX GalleryItemPropertiesMap_itemId_key 
    ON DB_TABLE_PREFIXGalleryItemPropertiesMap
    (DB_COLUMN_PREFIXitemId
        ,
      DB_COLUMN_PREFIXkey);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryItemPropertiesMap',
      1,
      0
      );

  