
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXUserGroupMap (
  DB_COLUMN_PREFIXuserId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXgroupId
      INTEGER
    
    NOT NULL
  
    );

  
    CREATE INDEX UserGroupMap_I1
    ON DB_TABLE_PREFIXUserGroupMap
    (DB_COLUMN_PREFIXuserId);

  
    CREATE INDEX UserGroupMap_I2
    ON DB_TABLE_PREFIXUserGroupMap
    (DB_COLUMN_PREFIXgroupId);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'UserGroupMap',
      1,
      0
      );

  