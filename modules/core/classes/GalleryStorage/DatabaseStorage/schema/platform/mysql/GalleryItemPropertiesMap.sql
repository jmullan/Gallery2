
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryItemPropertiesMap (
  COLUMN_PREFIXitemId
      int(11)
    
    ,
  COLUMN_PREFIXkey
      varchar(
      
          128
        
      )
    
    ,
  COLUMN_PREFIXvalue
      text
    
    , 
  
    UNIQUE KEY (
    COLUMN_PREFIXitemId
        ,
      COLUMN_PREFIXkey
    )
    
    , 
  
    INDEX (
    COLUMN_PREFIXvalue
          (255)
          
    )
    
    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryItemPropertiesMap',
      1,
      0
      );

  