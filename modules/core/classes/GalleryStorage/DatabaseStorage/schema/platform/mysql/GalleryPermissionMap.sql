
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryPermissionMap (
  COLUMN_PREFIXitemId
      int(11)
    
    ,
  COLUMN_PREFIXuserId
      int(11)
    
    ,
  COLUMN_PREFIXgroupId
      int(11)
    
    ,
  COLUMN_PREFIXpermission
      varchar(
      
          32
        
      )
    
    , 
  
    INDEX (
    COLUMN_PREFIXitemId
    )
    
      ,
    
    INDEX (
    COLUMN_PREFIXuserId
    )
    
      ,
    
    INDEX (
    COLUMN_PREFIXgroupId
    )
    
    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryPermissionMap',
      1,
      0
      );

  