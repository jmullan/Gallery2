
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryDerivative (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXderivativeSourceId
      int(11)
    
    NOT NULL
  
      ,
    COLUMN_PREFIXderivativeCommands
      varchar(
      
          255
        
      )
    
      ,
    COLUMN_PREFIXderivativeSize
      int(11)
    
      ,
    COLUMN_PREFIXderivativeType
      int(11)
    
      ,
    COLUMN_PREFIXderivativeMimeType
      varchar(
      
          128
        
      )
    
    , 
  
    INDEX (COLUMN_PREFIXid)
    
      ,
    
    INDEX (COLUMN_PREFIXderivativeSourceId)
    
      ,
    
    INDEX (COLUMN_PREFIXderivativeType)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryDerivative',
      1,
      0
      );

  