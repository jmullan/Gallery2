
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryPermissionSetMap (
  DB_COLUMN_PREFIXmodule
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXpermission
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXdescription
      VARCHAR(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXbits
      INTEGER
    
      ,
    DB_COLUMN_PREFIXflags
      INTEGER
    
    );

  
    CREATE UNIQUE INDEX GalleryPermissionSetMap_permission 
    ON DB_TABLE_PREFIXGalleryPermissionSetMap
    (DB_COLUMN_PREFIXpermission);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryPermissionSetMap',
      1,
      0
      );

  