
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryPhotoItem (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXwidth
      INTEGER
    
      ,
    DB_COLUMN_PREFIXheight
      INTEGER
    
    );

  
    CREATE INDEX GalleryPhotoItem_id 
    ON DB_TABLE_PREFIXGalleryPhotoItem
    (DB_COLUMN_PREFIXid);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryPhotoItem',
      1,
      0
      );

  