
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXGalleryUser (
  COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
    ,
  COLUMN_PREFIXuserName
      varchar(
      
          32
        
      )
    
    NOT NULL
  
    ,
  COLUMN_PREFIXfullname
      varchar(
      
          128
        
      )
    
    ,
  COLUMN_PREFIXpassword
      varchar(
      
          32
        
      )
    
    ,
  COLUMN_PREFIXemail
      varchar(
      
          128
        
      )
    
    , 
  
    UNIQUE KEY (
    COLUMN_PREFIXuserName
    )
    
      ,
    
    UNIQUE KEY (
    COLUMN_PREFIXemail
    )
    
    , 
  
    INDEX (
    COLUMN_PREFIXid
    )
    
      ,
    
    INDEX (
    COLUMN_PREFIXuserName
    )
    
    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'GalleryUser',
      1,
      0
      );

  