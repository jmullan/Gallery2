
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXItemAttributesMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXviewCount
      INTEGER
    
      ,
    DB_COLUMN_PREFIXorderWeight
      INTEGER
    
      ,
    DB_COLUMN_PREFIXparentSequence
      VARCHAR(
      
          255
        
      )
    
    NOT NULL
  
    );

  
    CREATE INDEX ItemAttributesMap_parentSequence 
    ON DB_TABLE_PREFIXItemAttributesMap
    (DB_COLUMN_PREFIXparentSequence);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'ItemAttributesMap',
      1,
      0
      );

  