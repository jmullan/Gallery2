
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXFileSystemEntity (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpathComponent
      VARCHAR(
      
          128
        
      )
    
    );

  
    CREATE INDEX FileSystemEntity_id 
    ON DB_TABLE_PREFIXFileSystemEntity
    (DB_COLUMN_PREFIXid);

  
    CREATE INDEX FileSystemEntity_pathComponent 
    ON DB_TABLE_PREFIXFileSystemEntity
    (DB_COLUMN_PREFIXpathComponent);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'FileSystemEntity',
      1,
      0
      );

  