
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXPluginParameterMap (
  DB_COLUMN_PREFIXpluginType
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXpluginId
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXitemId
      int(11)
    
      ,
    DB_COLUMN_PREFIXparameterName
      varchar(
      
          128
        
      )
    
      ,
    DB_COLUMN_PREFIXparameterValue
      varchar(
      
          255
        
      )
    
    , 
  
    UNIQUE KEY (DB_COLUMN_PREFIXpluginType
        ,
      DB_COLUMN_PREFIXpluginId
        ,
      DB_COLUMN_PREFIXitemId
        ,
      DB_COLUMN_PREFIXparameterName)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'PluginParameterMap',
      1,
      0
      );

  