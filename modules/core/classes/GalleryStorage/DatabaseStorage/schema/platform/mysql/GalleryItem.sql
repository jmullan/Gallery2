
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryItem (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXdescription
      text
    
      ,
    COLUMN_PREFIXlayout
      varchar(
      
          32
        
      )
    
      ,
    COLUMN_PREFIXkeywords
      varchar(
      
          255
        
      )
    
      ,
    COLUMN_PREFIXorderBy
      varchar(
      
          128
        
      )
    
      ,
    COLUMN_PREFIXorderDirection
      varchar(
      
          128
        
      )
    
      ,
    COLUMN_PREFIXorderWeight
      int(11)
    
      ,
    COLUMN_PREFIXownerId
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXsummary
      varchar(
      
          128
        
      )
    
    NOT NULL
  
      ,
    COLUMN_PREFIXtheme
      varchar(
      
          32
        
      )
    
      ,
    COLUMN_PREFIXtitle
      varchar(
      
          128
        
      )
    
    NOT NULL
  
      ,
    COLUMN_PREFIXviewedSinceTimestamp
      int(11)
    
    NOT NULL
  
    , 
  
    INDEX (COLUMN_PREFIXid)
    
      ,
    
    INDEX (COLUMN_PREFIXdescription
          (255)
          )
    
      ,
    
    INDEX (COLUMN_PREFIXkeywords)
    
      ,
    
    INDEX (COLUMN_PREFIXownerId)
    
      ,
    
    INDEX (COLUMN_PREFIXsummary)
    
      ,
    
    INDEX (COLUMN_PREFIXtitle)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryItem',
      1,
      0
      );

  