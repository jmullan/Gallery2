
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryToolkitOperationMap (
  DB_COLUMN_PREFIXname
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXparametersCrc
      varchar(
      
          32
        
      )
    
      ,
    DB_COLUMN_PREFIXoutputMimeType
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXdescription
      varchar(
      
          255
        
      )
    
    , 
  
    UNIQUE KEY (DB_COLUMN_PREFIXname
        ,
      DB_COLUMN_PREFIXparametersCrc)
    
      ,
    
    UNIQUE KEY (DB_COLUMN_PREFIXname)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryToolkitOperationMap',
      1,
      0
      );

  