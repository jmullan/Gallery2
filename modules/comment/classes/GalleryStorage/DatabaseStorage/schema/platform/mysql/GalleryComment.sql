
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryComment (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
    ,
  COLUMN_PREFIXcommenterId
      int(11)
    
    ,
  COLUMN_PREFIXhost
      varchar(
      
          128
        
      )
    
    ,
  COLUMN_PREFIXcomment
      text
    
    ,
  COLUMN_PREFIXdate
      datetime
    
    , 
  
    INDEX (
    COLUMN_PREFIXid
    )
    
      ,
    
    INDEX (
    COLUMN_PREFIXcomment
          (255)
          
    )
    
    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryComment',
      1,
      0
      );

  