
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryDerivativePreferencesMap (
  COLUMN_PREFIXitemId
      int(11)
    
      ,
    COLUMN_PREFIXorder
      int(11)
    
      ,
    COLUMN_PREFIXderivativeType
      int(11)
    
      ,
    COLUMN_PREFIXderivativeCommands
      varchar(
      
          255
        
      )
    
    , 
  
    INDEX (COLUMN_PREFIXitemId)
    
      ,
    
    INDEX (COLUMN_PREFIXorder)
    
      ,
    
    INDEX (COLUMN_PREFIXderivativeType)
    
      ,
    
    INDEX (COLUMN_PREFIXderivativeCommands)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryDerivativePreferencesMap',
      1,
      0
      );

  