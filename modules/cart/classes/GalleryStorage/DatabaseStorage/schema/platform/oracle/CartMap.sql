
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXCartMap (
  DB_COLUMN_PREFIXsessionId
      VARCHAR2(
       128 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXitemIds
      VARCHAR2(4000)
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXCartMap
      ADD PRIMARY KEY (DB_COLUMN_PREFIXsessionId)
  ;
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'CartMap',
      1,
      0
      );

  