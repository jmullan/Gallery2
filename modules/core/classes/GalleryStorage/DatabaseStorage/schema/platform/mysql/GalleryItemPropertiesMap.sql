
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_GalleryItemPropertiesMap (
  
    g_itemId
      int(11)
    
    ,
  
    g_key
      varchar(
      
          128
        
      )
    
    ,
  
    g_value
      text
    
    , 
  
    UNIQUE KEY (
    g_itemId
        ,
      g_key
    )
    
    , 
  
    INDEX (
    g_value
          (255)
          
    )
    
    ) TYPE=MyISAM;

    INSERT INTO g2_Schema (
      g_name,
      g_major,
      g_minor
      ) VALUES (
      'GalleryItemPropertiesMap',
      1,
      0
      );

  