
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryViewCountMap (
  COLUMN_PREFIXitemId
      int(11)
    
    ,
  COLUMN_PREFIXviewCount
      int(11)
    
    , 
  
    UNIQUE KEY (
    COLUMN_PREFIXitemId
    )
    
    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryViewCountMap',
      1,
      0
      );

  