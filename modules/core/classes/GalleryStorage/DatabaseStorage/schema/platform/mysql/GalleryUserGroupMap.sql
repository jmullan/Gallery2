
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_GalleryUserGroupMap (
  
    g_userId
      int(11)
    
    ,
  
    g_groupId
      int(11)
    
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
      'GalleryUserGroupMap',
      1,
      0
      );

  