
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXComment (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXcommenterId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXhost
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXcomment
      TEXT
    
      ,
    DB_COLUMN_PREFIXdate
      TIMESTAMP
    
    );

  
    CREATE INDEX Comment_id 
    ON DB_TABLE_PREFIXComment
    (DB_COLUMN_PREFIXid);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Comment',
      1,
      0
      );

  