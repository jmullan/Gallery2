
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryGroup (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
    ,
  COLUMN_PREFIXgroupType
      int(11)
    
    ,
  COLUMN_PREFIXgroupName
      varchar(
      
          32
        
      )
    
    , 
  
    UNIQUE KEY (
    COLUMN_PREFIXgroupName
    )
    
    , 
  
    INDEX (
    COLUMN_PREFIXid
    )
    
      ,
    
    INDEX (
    COLUMN_PREFIXgroupName
    )
    
    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryGroup',
      1,
      0
      );

  