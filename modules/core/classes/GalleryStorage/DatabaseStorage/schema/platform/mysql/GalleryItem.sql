
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXItem (
  DB_COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXcanContainChildren
      int(1)
    
      ,
    DB_COLUMN_PREFIXdescription
      text
    
      ,
    DB_COLUMN_PREFIXkeywords
      varchar(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXorderBy
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXorderDirection
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXownerId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXsummary
      varchar(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXtheme
      varchar(
      
          32
        
      )
    
      ,
    DB_COLUMN_PREFIXtitle
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXviewedSinceTimestamp
      int(11)
    
    NOT NULL
  
    , 
  
    INDEX (DB_COLUMN_PREFIXid)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXkeywords)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXownerId)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXsummary)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXtitle)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Item',
      1,
      0
      );

  