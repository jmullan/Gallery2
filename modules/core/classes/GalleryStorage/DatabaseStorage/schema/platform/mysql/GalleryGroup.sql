
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryGroup (
  DB_COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXgroupType
      int(11)
    
      ,
    DB_COLUMN_PREFIXgroupName
      varchar(
      
          32
        
      )
    
    , 
  
    UNIQUE KEY (DB_COLUMN_PREFIXgroupName)
    
    , 
  
    INDEX (DB_COLUMN_PREFIXid)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryGroup',
      1,
      0
      );

  