
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXDerivativePreferencesMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXorder
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeType
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeOperations
      VARCHAR(
      
          255
        
      )
    
    );

  
    CREATE INDEX DerivativePreferencesMap_itemId 
    ON DB_TABLE_PREFIXDerivativePreferencesMap
    (DB_COLUMN_PREFIXitemId);

  
    CREATE INDEX DerivativePreferencesMap_order 
    ON DB_TABLE_PREFIXDerivativePreferencesMap
    (DB_COLUMN_PREFIXorder);

  
    CREATE INDEX DerivativePreferencesMap_derivativeType 
    ON DB_TABLE_PREFIXDerivativePreferencesMap
    (DB_COLUMN_PREFIXderivativeType);

  
    CREATE INDEX DerivativePreferencesMap_derivativeOperations 
    ON DB_TABLE_PREFIXDerivativePreferencesMap
    (DB_COLUMN_PREFIXderivativeOperations);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'DerivativePreferencesMap',
      1,
      0
      );

  