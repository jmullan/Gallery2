
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXGalleryDerivative (
  DB_COLUMN_PREFIXid
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeSourceId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeCommands
      VARCHAR(
      
          255
        
      )
    
      ,
    DB_COLUMN_PREFIXderivativeOrder
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeSize
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeType
      INTEGER
    
      ,
    DB_COLUMN_PREFIXderivativeMimeType
      VARCHAR(
      
          128
        
      )
    
    );

  
    CREATE INDEX GalleryDerivative_id 
    ON DB_TABLE_PREFIXGalleryDerivative
    (DB_COLUMN_PREFIXid);

  
    CREATE INDEX GalleryDerivative_derivativeSourceId 
    ON DB_TABLE_PREFIXGalleryDerivative
    (DB_COLUMN_PREFIXderivativeSourceId);

  
    CREATE INDEX GalleryDerivative_derivativeOrder 
    ON DB_TABLE_PREFIXGalleryDerivative
    (DB_COLUMN_PREFIXderivativeOrder);

  
    CREATE INDEX GalleryDerivative_derivativeType 
    ON DB_TABLE_PREFIXGalleryDerivative
    (DB_COLUMN_PREFIXderivativeType);

  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'GalleryDerivative',
      1,
      0
      );

  