
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_GalleryPermissionMap (
  
    g_itemId
      int(11)
    
    ,
  
    g_userId
      int(11)
    
    ,
  
    g_groupId
      int(11)
    
    ,
  
    g_permission
      varchar(
      
          32
        
      )
    
    , 
  
    INDEX (
    g_itemId
    )
    
      ,
    
    INDEX (
    g_userId
    )
    
      ,
    
    INDEX (
    g_groupId
    )
    
    ) TYPE=MyISAM;

    INSERT INTO g2_Schema (
      g_name,
      g_major,
      g_minor
      ) VALUES (
      'GalleryPermissionMap',
      1,
      0
      );

  