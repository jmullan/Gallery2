
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXSession (
  DB_COLUMN_PREFIXsessionId
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXuserId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXcreationTime
      INTEGER
    
      ,
    DB_COLUMN_PREFIXlastModificationTime
      INTEGER
    
      ,
    DB_COLUMN_PREFIXsessionData
      TEXT
    
    );

  
    CREATE INDEX Session_userId 
    ON DB_TABLE_PREFIXSession
    (DB_COLUMN_PREFIXuserId);

  
    CREATE INDEX Session_creationTime 
    ON DB_TABLE_PREFIXSession
    (DB_COLUMN_PREFIXcreationTime);

  
    CREATE INDEX Session_lastModificationTime 
    ON DB_TABLE_PREFIXSession
    (DB_COLUMN_PREFIXlastModificationTime);

  
    CREATE UNIQUE INDEX Session_sessionId 
    ON DB_TABLE_PREFIXSession
    (DB_COLUMN_PREFIXsessionId);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Session',
      1,
      0
      );

  