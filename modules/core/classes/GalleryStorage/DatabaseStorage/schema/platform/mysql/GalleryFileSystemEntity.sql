
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryFileSystemEntity (
  DB_COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpathComponent
      varchar(
      
          32
        
      )
    
    , 
  
    INDEX (DB_COLUMN_PREFIXid)
    
      ,
    
    INDEX (DB_COLUMN_PREFIXpathComponent)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryFileSystemEntity',
      1,
      0
      );

  