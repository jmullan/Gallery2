
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryUser (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXuserName
      VARCHAR(
      
          32
        
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXfullName
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXhashedPassword
      VARCHAR(
      
          32
        
      )
    
      ,
    DB_COLUMN_PREFIXemail
      VARCHAR(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXlanguage
      VARCHAR(
      
          128
        
      )
    
    );

  
    CREATE INDEX GalleryUser_id 
    ON DB_TABLE_PREFIXGalleryUser
    (DB_COLUMN_PREFIXid);

  
    CREATE UNIQUE INDEX GalleryUser_userName 
    ON DB_TABLE_PREFIXGalleryUser
    (DB_COLUMN_PREFIXuserName);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryUser',
      1,
      0
      );

  