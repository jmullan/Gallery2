
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXItem (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXcanContainChildren
      NUMBER(1)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXdescription
      TEXT
    
      ,
    DB_COLUMN_PREFIXkeywords
      VARCHAR2(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXorderBy
      VARCHAR2(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXorderDirection
      VARCHAR2(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXownerId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXsummary
      VARCHAR2(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXtheme
      VARCHAR2(
      
          32
        
      )
    
      ,
    DB_COLUMN_PREFIXtitle
      VARCHAR2(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXviewedSinceTimestamp
      INTEGER
    
    NOT NULL
  
    );

  
    CREATE INDEX Item_keywords 
    ON DB_TABLE_PREFIXItem
    (DB_COLUMN_PREFIXkeywords);

  
    CREATE INDEX Item_ownerId 
    ON DB_TABLE_PREFIXItem
    (DB_COLUMN_PREFIXownerId);

  
    CREATE INDEX Item_summary 
    ON DB_TABLE_PREFIXItem
    (DB_COLUMN_PREFIXsummary);

  
    CREATE INDEX Item_title 
    ON DB_TABLE_PREFIXItem
    (DB_COLUMN_PREFIXtitle);

  
    ALTER TABLE DB_TABLE_PREFIXItem
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Item',
      1,
      0
      );

  