
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryModuleParameterMap (
  COLUMN_PREFIXmoduleName
      varchar(
      
          128
        
      )
    
      ,
    COLUMN_PREFIXparameterName
      varchar(
      
          128
        
      )
    
      ,
    COLUMN_PREFIXparameterValue
      varchar(
      
          255
        
      )
    
    , 
  
    UNIQUE KEY (COLUMN_PREFIXmoduleName
        ,
      COLUMN_PREFIXparameterName)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryModuleParameterMap',
      1,
      0
      );

  