
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE TABLE_PREFIXLock (
  COLUMN_PREFIXlockId
      int(11)
    
      ,
    COLUMN_PREFIXreadEntityId
      int(11)
    
      ,
    COLUMN_PREFIXwriteEntityId
      int(11)
    
      ,
    COLUMN_PREFIXrequest
      int(11)
    
    , 
  
    INDEX (COLUMN_PREFIXlockId)
    

    ) TYPE=MyISAM;

    INSERT INTO TABLE_PREFIXSchema (
      COLUMN_PREFIXname,
      COLUMN_PREFIXmajor,
      COLUMN_PREFIXminor
      ) VALUES (
      'Lock',
      1,
      0
      );

  