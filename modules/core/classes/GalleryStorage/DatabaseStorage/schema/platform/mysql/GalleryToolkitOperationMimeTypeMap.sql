
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryToolkitOperationMimeTypeMap (
  DB_COLUMN_PREFIXoperationName
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXtoolkitId
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXmimeType
      varchar(
      
          128
        
      )
    
    , 
  
    INDEX (DB_COLUMN_PREFIXoperationName)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXmimeType)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryToolkitOperationMimeTypeMap',
      1,
      0
      );

  