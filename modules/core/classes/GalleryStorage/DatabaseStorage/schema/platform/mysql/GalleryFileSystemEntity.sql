
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_GalleryFileSystemEntity (
  
    g_id
      int(11)
    
    NOT NULL
  
    ,
  
    g_pathComponent
      varchar(
      
          32
        
      )
    
    , 
  
    INDEX (
    g_id
    )
    
      ,
    
    INDEX (
    g_pathComponent
    )
    
    ) TYPE=MyISAM;

    INSERT INTO g2_Schema (
      g_name,
      g_major,
      g_minor
      ) VALUES (
      'GalleryFileSystemEntity',
      1,
      0
      );

  