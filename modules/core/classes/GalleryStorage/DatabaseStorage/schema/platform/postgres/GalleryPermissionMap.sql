
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryPermissionMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXuserId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXgroupId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXpermission
      BIT(32)
    
    );

  
    CREATE INDEX GalleryPermissionMap_itemId 
    ON DB_TABLE_PREFIXGalleryPermissionMap
    (DB_COLUMN_PREFIXitemId);

  
    CREATE INDEX GalleryPermissionMap_userId 
    ON DB_TABLE_PREFIXGalleryPermissionMap
    (DB_COLUMN_PREFIXuserId);

  
    CREATE INDEX GalleryPermissionMap_groupId 
    ON DB_TABLE_PREFIXGalleryPermissionMap
    (DB_COLUMN_PREFIXgroupId);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryPermissionMap',
      1,
      0
      );

  