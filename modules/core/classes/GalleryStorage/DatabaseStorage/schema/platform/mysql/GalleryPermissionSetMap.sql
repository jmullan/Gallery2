
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryPermissionSetMap (
  DB_COLUMN_PREFIXmodule
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXpermission
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXdescription
      varchar(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXbits
      int(11)
    
      ,
    DB_COLUMN_PREFIXflags
      int(11)
    
    , 
  
    UNIQUE KEY (DB_COLUMN_PREFIXpermission)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryPermissionSetMap',
      1,
      0
      );

  