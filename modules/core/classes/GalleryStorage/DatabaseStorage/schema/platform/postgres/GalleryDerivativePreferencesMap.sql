
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

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'DerivativePreferencesMap',
      1,
      0
      );

  