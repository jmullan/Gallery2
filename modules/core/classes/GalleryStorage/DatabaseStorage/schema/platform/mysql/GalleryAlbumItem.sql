
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryAlbumItem (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
    ,
  COLUMN_PREFIXbackgroundColor
      varchar(
      
          32
        
      )
    
    ,
  COLUMN_PREFIXbackgroundColor2
      varchar(
      
          32
        
      )
    
    ,
  COLUMN_PREFIXborder
      int(11)
    
    ,
  COLUMN_PREFIXborderColor
      varchar(
      
          32
        
      )
    
    ,
  COLUMN_PREFIXcolumns
      int(11)
    
    ,
  COLUMN_PREFIXdisplayViewCount
      int(1)
    
    ,
  COLUMN_PREFIXfont
      varchar(
      
          32
        
      )
    
    ,
  COLUMN_PREFIXhtmlFooter
      text
    
    ,
  COLUMN_PREFIXhtmlHeader
      text
    
    ,
  COLUMN_PREFIXlayout
      varchar(
      
          32
        
      )
    
    ,
  COLUMN_PREFIXlinkColor
      varchar(
      
          32
        
      )
    
    ,
  COLUMN_PREFIXallowPrinting
      int(1)
    
    ,
  COLUMN_PREFIXchildIntermediateResize
      int(11)
    
    ,
  COLUMN_PREFIXchildThumbSize
      int(11)
    
    ,
  COLUMN_PREFIXrows
      int(11)
    
    ,
  COLUMN_PREFIXshowBreadCrumb
      int(1)
    
    ,
  COLUMN_PREFIXtextColor
      varchar(
      
          32
        
      )
    
    , 
  
    INDEX (
    COLUMN_PREFIXid
    )
    
    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryAlbumItem',
      1,
      0
      );

  