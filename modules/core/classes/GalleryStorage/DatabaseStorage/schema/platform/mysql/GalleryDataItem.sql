
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryDataItem (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXfileExtension
      varchar(
      
          128
        
      )
    
      ,
    COLUMN_PREFIXmimeType
      varchar(
      
          128
        
      )
    
    , 
  
    INDEX (COLUMN_PREFIXid)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryDataItem',
      1,
      0
      );

  