
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_GalleryEntity (
  
    g_id
      int(11)
    
    NOT NULL
  
    ,
  
    g_creationTimestamp
      datetime
    
    NOT NULL
  
    ,
  
    g_dataVersion
      int(11)
    
    NOT NULL
  
    ,
  
    g_modificationTimestamp
      datetime
    
    NOT NULL
  
    ,
  
    g_serialNumber
      int(11)
    
    NOT NULL
  
    ,
  
    g_entityType
      varchar(
      
          32
        
      )
    
    NOT NULL
  
    , 
  
    INDEX (
    g_id
    )
    
    ) TYPE=MyISAM;

    INSERT INTO g2_Schema (
      g_name,
      g_major,
      g_minor
      ) VALUES (
      'GalleryEntity',
      1,
      0
      );

  