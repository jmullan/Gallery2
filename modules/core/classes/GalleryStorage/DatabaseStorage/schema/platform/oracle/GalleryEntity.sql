
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXEntity (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXcreationTimestamp
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXisLinkable
      NUMBER(1)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXlinkId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXmodificationTimestamp
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXserialNumber
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXentityType
      VARCHAR2(
      
          32
        
      )
    
    NOT NULL
  
    );

  
    CREATE INDEX Entity_creationTimestamp 
    ON DB_TABLE_PREFIXEntity
    (DB_COLUMN_PREFIXcreationTimestamp);

  
    CREATE INDEX Entity_isLinkable 
    ON DB_TABLE_PREFIXEntity
    (DB_COLUMN_PREFIXisLinkable);

  
    CREATE INDEX Entity_modificationTimestamp 
    ON DB_TABLE_PREFIXEntity
    (DB_COLUMN_PREFIXmodificationTimestamp);

  
    CREATE INDEX Entity_serialNumber 
    ON DB_TABLE_PREFIXEntity
    (DB_COLUMN_PREFIXserialNumber);

  
    ALTER TABLE DB_TABLE_PREFIXEntity
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Entity',
      1,
      0
      );

  