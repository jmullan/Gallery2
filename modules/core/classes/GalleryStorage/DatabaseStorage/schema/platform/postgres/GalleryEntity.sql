
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryEntity (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXcreationTimestamp
      TIMESTAMP
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXmodificationTimestamp
      TIMESTAMP
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXserialNumber
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXentityType
      VARCHAR(
      
          32
        
      )
    
    NOT NULL
  
    );

  
    CREATE INDEX GalleryEntity_id 
    ON DB_TABLE_PREFIXGalleryEntity
    (DB_COLUMN_PREFIXid);

  
    CREATE INDEX GalleryEntity_creationTimestamp 
    ON DB_TABLE_PREFIXGalleryEntity
    (DB_COLUMN_PREFIXcreationTimestamp);

  
    CREATE INDEX GalleryEntity_modificationTimestamp 
    ON DB_TABLE_PREFIXGalleryEntity
    (DB_COLUMN_PREFIXmodificationTimestamp);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryEntity',
      1,
      0
      );

  