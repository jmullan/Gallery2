
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryEntity (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXcreationTimestamp
      datetime
    
    NOT NULL
  
      ,
    COLUMN_PREFIXdataVersion
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXmodificationTimestamp
      datetime
    
    NOT NULL
  
      ,
    COLUMN_PREFIXserialNumber
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXentityType
      varchar(
      
          32
        
      )
    
    NOT NULL
  
    , 
  
    INDEX (COLUMN_PREFIXid)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryEntity',
      1,
      0
      );

  