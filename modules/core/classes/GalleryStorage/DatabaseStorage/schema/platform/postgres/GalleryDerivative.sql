
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXDerivative (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeSourceId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeOperations
      VARCHAR(
      
          255
        
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeOrder
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeSize
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeType
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXmimeType
      VARCHAR(
      
          128
        
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpostFilterOperations
      VARCHAR(
      
          255
        
      )
    
    NOT NULL
  
    );

  
    CREATE INDEX DB_TABLE_PREFIXDerivative_843485338 
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeSourceId);

  
    CREATE INDEX DB_TABLE_PREFIXDerivative_397325243 
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeOrder);

  
    CREATE INDEX DB_TABLE_PREFIXDerivative_3011797216 
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeType);

  
    ALTER TABLE DB_TABLE_PREFIXDerivative
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Derivative',
      1,
      0
      );

  