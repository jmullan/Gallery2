
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
    
      ,
    DB_COLUMN_PREFIXderivativeOrder
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeSize
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeType
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeMimeType
      VARCHAR(
      
          128
        
      )
    
    );

  
    CREATE INDEX Derivative_id 
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXid);

  
    CREATE INDEX Derivative_derivativeSourceId 
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeSourceId);

  
    CREATE INDEX Derivative_derivativeOrder 
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeOrder);

  
    CREATE INDEX Derivative_derivativeType 
    ON DB_TABLE_PREFIXDerivative
    (DB_COLUMN_PREFIXderivativeType);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Derivative',
      1,
      0
      );

  