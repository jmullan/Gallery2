
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryChildEntity (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXparentId
      int(11)
    
    , 
  
    INDEX (COLUMN_PREFIXid)
    
      ,
    
    INDEX (COLUMN_PREFIXparentId)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryChildEntity',
      1,
      0
      );

  