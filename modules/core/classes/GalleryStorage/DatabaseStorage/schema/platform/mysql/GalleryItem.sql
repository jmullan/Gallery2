
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_GalleryItem (
  
    g_id
      int(11)
    
    NOT NULL
  
    ,
  
    g_description
      text
    
    ,
  
    g_isHtmlAllowed
      int(1)
    
    ,
  
    g_keywords
      varchar(
      
          255
        
      )
    
    ,
  
    g_orderBy
      varchar(
      
          128
        
      )
    
    ,
  
    g_orderDirection
      varchar(
      
          128
        
      )
    
    ,
  
    g_orderWeight
      int(11)
    
    ,
  
    g_ownerId
      int(11)
    
    NOT NULL
  
    ,
  
    g_title
      varchar(
      
          128
        
      )
    
    NOT NULL
  
    ,
  
    g_viewCount
      int(11)
    
    ,
  
    g_viewedSinceTimestamp
      int(11)
    
    NOT NULL
  
    , 
  
    INDEX (
    g_id
    )
    
      ,
    
    INDEX (
    g_description
          (255)
          
    )
    
      ,
    
    INDEX (
    g_keywords
    )
    
      ,
    
    INDEX (
    g_title
    )
    
    ) TYPE=MyISAM;

    INSERT INTO g2_Schema (
      g_name,
      g_major,
      g_minor
      ) VALUES (
      'GalleryItem',
      1,
      0
      );

  