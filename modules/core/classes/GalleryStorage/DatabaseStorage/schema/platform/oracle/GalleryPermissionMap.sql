
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXPermissionMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXuserId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXgroupId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXpermission
      INTEGER
    
    NOT NULL
  
    );

  
    CREATE INDEX PermissionMap_I1
    ON DB_TABLE_PREFIXPermissionMap
    (DB_COLUMN_PREFIXitemId);

  
    CREATE INDEX PermissionMap_I2
    ON DB_TABLE_PREFIXPermissionMap
    (DB_COLUMN_PREFIXuserId);

  
    CREATE INDEX PermissionMap_I3
    ON DB_TABLE_PREFIXPermissionMap
    (DB_COLUMN_PREFIXgroupId);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'PermissionMap',
      1,
      0
      );

  