
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryViewCountMap (
  DB_COLUMN_PREFIXitemId
      int(11)
    
      ,
    DB_COLUMN_PREFIXviewCount
      int(11)
    
    , 
  
    UNIQUE KEY (DB_COLUMN_PREFIXitemId)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryViewCountMap',
      1,
      0
      );

  