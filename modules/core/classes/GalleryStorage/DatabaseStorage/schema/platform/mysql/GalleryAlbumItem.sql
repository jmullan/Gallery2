
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXAlbumItem (
  DB_COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXlayout
      varchar(
      
	  32
	
      )
    
      ,
    DB_COLUMN_PREFIXtheme
      varchar(
      
	  32
	
      )
    
      ,
    DB_COLUMN_PREFIXorderBy
      varchar(
      
	  128
	
      )
    
      ,
    DB_COLUMN_PREFIXorderDirection
      varchar(
      
	  32
	
      )
    
    ,
  
      PRIMARY KEY (DB_COLUMN_PREFIXid)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'AlbumItem',
      1,
      0
      );

  