
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryUserGroupMap (
  COLUMN_PREFIXuserId
      int(11)
    
      ,
    COLUMN_PREFIXgroupId
      int(11)
    
    , 
  
    INDEX (COLUMN_PREFIXuserId)
    
      ,
    
    INDEX (COLUMN_PREFIXgroupId)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryUserGroupMap',
      1,
      0
      );

  