
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryUserGroupMap (
  DB_COLUMN_PREFIXuserId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXgroupId
      INTEGER
    
    );

  
    CREATE INDEX GalleryUserGroupMap_userId 
    ON DB_TABLE_PREFIXGalleryUserGroupMap
    (DB_COLUMN_PREFIXuserId);

  
    CREATE INDEX GalleryUserGroupMap_groupId 
    ON DB_TABLE_PREFIXGalleryUserGroupMap
    (DB_COLUMN_PREFIXgroupId);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryUserGroupMap',
      1,
      0
      );

  