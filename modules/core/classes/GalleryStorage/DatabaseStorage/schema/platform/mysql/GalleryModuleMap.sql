
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryModuleMap (
  COLUMN_PREFIXmoduleName
      varchar(
      
          128
        
      )
    
      ,
    COLUMN_PREFIXactive
      int(1)
    
    , 
  
    UNIQUE KEY (COLUMN_PREFIXmoduleName)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryModuleMap',
      1,
      0
      );

  