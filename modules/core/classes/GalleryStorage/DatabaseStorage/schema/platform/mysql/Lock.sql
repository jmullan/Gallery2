
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_Lock (
  
    g_lockId
      int(11)
    
    ,
  
    g_readEntityId
      int(11)
    
    ,
  
    g_writeEntityId
      int(11)
    
    ,
  
    g_request
      int(11)
    
    ) TYPE=MyISAM;

    INSERT INTO g2_Schema (
      g_name,
      g_major,
      g_minor
      ) VALUES (
      'Lock',
      1,
      0
      );

  