
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryDerivativePreferencesMap (
  DB_COLUMN_PREFIXitemId
      INTEGER
    
      ,
    DB_COLUMN_PREFIXorder
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeType
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeCommands
      VARCHAR(
      
          255
        
      )
    
    );

  
    CREATE INDEX GalleryDerivativePreferencesMap_itemId 
    ON DB_TABLE_PREFIXGalleryDerivativePreferencesMap
    (DB_COLUMN_PREFIXitemId);

  
    CREATE INDEX GalleryDerivativePreferencesMap_order 
    ON DB_TABLE_PREFIXGalleryDerivativePreferencesMap
    (DB_COLUMN_PREFIXorder);

  
    CREATE INDEX GalleryDerivativePreferencesMap_derivativeType 
    ON DB_TABLE_PREFIXGalleryDerivativePreferencesMap
    (DB_COLUMN_PREFIXderivativeType);

  
    CREATE INDEX GalleryDerivativePreferencesMap_derivativeCommands 
    ON DB_TABLE_PREFIXGalleryDerivativePreferencesMap
    (DB_COLUMN_PREFIXderivativeCommands);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryDerivativePreferencesMap',
      1,
      0
      );

  