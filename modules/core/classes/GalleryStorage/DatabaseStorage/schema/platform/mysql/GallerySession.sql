
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGallerySession (
  COLUMN_PREFIXsessionId
      varchar(
      
          128
        
      )
    
      ,
    COLUMN_PREFIXkey
      varchar(
      
          32
        
      )
    
      ,
    COLUMN_PREFIXvalue
      text
    
    , 
  
    INDEX (COLUMN_PREFIXsessionId)
    
      ,
    
    INDEX (COLUMN_PREFIXkey)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GallerySession',
      1,
      0
      );

  