
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXChildEntity (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXparentId
      INTEGER
    
    );

  
    CREATE INDEX ChildEntity_id 
    ON DB_TABLE_PREFIXChildEntity
    (DB_COLUMN_PREFIXid);

  
    CREATE INDEX ChildEntity_parentId 
    ON DB_TABLE_PREFIXChildEntity
    (DB_COLUMN_PREFIXparentId);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ChildEntity',
      1,
      0
      );

  