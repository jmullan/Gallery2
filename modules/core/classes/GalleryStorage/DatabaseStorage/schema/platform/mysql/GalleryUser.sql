
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_GalleryUser (
  
    g_id
      int(11)
    
    NOT NULL
  
    ,
  
    g_username
      varchar(
      
          32
        
      )
    
    NOT NULL
  
    ,
  
    g_fullname
      varchar(
      
          128
        
      )
    
    ,
  
    g_password
      varchar(
      
          32
        
      )
    
    ,
  
    g_email
      varchar(
      
          128
        
      )
    
    ,
  
    g_isAdmin
      int(1)
    
    , 
  
    UNIQUE KEY (
    g_username
    )
    
      ,
    
    UNIQUE KEY (
    g_email
    )
    
    , 
  
    INDEX (
    g_id
    )
    
      ,
    
    INDEX (
    g_username
    )
    
    ) TYPE=MyISAM;

    INSERT INTO g2_Schema (
      g_name,
      g_major,
      g_minor
      ) VALUES (
      'GalleryUser',
      1,
      0
      );

  