
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryItem (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXdescription
      TEXT
    
      ,
    DB_COLUMN_PREFIXlayout
      VARCHAR(
      
          32
        
      )
    
      ,
    DB_COLUMN_PREFIXkeywords
      VARCHAR(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXorderBy
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXorderDirection
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXorderWeight
      INTEGER
    
      ,
    DB_COLUMN_PREFIXownerId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXsummary
      VARCHAR(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXtheme
      VARCHAR(
      
          32
        
      )
    
      ,
    DB_COLUMN_PREFIXtitle
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXviewedSinceTimestamp
      INTEGER
    
    NOT NULL
  
    );

  
    CREATE INDEX GalleryItem_id 
    ON DB_TABLE_PREFIXGalleryItem
    (DB_COLUMN_PREFIXid);

  
    CREATE INDEX GalleryItem_keywords 
    ON DB_TABLE_PREFIXGalleryItem
    (DB_COLUMN_PREFIXkeywords);

  
    CREATE INDEX GalleryItem_ownerId 
    ON DB_TABLE_PREFIXGalleryItem
    (DB_COLUMN_PREFIXownerId);

  
    CREATE INDEX GalleryItem_summary 
    ON DB_TABLE_PREFIXGalleryItem
    (DB_COLUMN_PREFIXsummary);

  
    CREATE INDEX GalleryItem_title 
    ON DB_TABLE_PREFIXGalleryItem
    (DB_COLUMN_PREFIXtitle);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryItem',
      1,
      0
      );

  