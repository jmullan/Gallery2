
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXPermissionMap (
  DB_COLUMN_PREFIXitemId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXuserId
      int(11)
    
      ,
    DB_COLUMN_PREFIXgroupId
      int(11)
    
      ,
    DB_COLUMN_PREFIXpermission
      int(11)
    
    NOT NULL
  
    , 
  
    INDEX (DB_COLUMN_PREFIXitemId)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXuserId)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXgroupId)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'PermissionMap',
      1,
      0
      );

  