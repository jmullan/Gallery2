
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXEntity (
  DB_COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXcreationTimestamp
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXisLinkable
      int(1)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXlinkId
      int(11)
    
      ,
    DB_COLUMN_PREFIXmodificationTimestamp
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXserialNumber
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXentityType
      varchar(
      
          32
        
      )
    
    NOT NULL
  
    , 
  
      PRIMARY KEY (DB_COLUMN_PREFIXid)
    
    , 
  
    INDEX (DB_COLUMN_PREFIXcreationTimestamp)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXisLinkable)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXmodificationTimestamp)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXserialNumber)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Entity',
      1,
      0
      );

  