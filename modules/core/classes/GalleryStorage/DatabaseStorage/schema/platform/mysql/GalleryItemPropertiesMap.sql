
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryItemPropertiesMap (
  DB_COLUMN_PREFIXitemId
      int(11)
    
      ,
    DB_COLUMN_PREFIXkey
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXvalue
      text
    
    , 
  
    UNIQUE KEY (DB_COLUMN_PREFIXitemId
        ,
      DB_COLUMN_PREFIXkey)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryItemPropertiesMap',
      1,
      0
      );

  