
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXWatermarkImage (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXfileName
      VARCHAR(
      
          128
        
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXmimeType
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXsize
      INTEGER
    
      ,
    DB_COLUMN_PREFIXwidth
      INTEGER
    
      ,
    DB_COLUMN_PREFIXheight
      INTEGER
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXWatermarkImage
    ADD PRIMARY KEY (DB_COLUMN_PREFIXid);
    
    CREATE UNIQUE INDEX DB_TABLE_PREFIXWatermarkImage_2620999259 
    ON DB_TABLE_PREFIXWatermarkImage
    (DB_COLUMN_PREFIXfileName);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'WatermarkImage',
      1,
      0
      );

  