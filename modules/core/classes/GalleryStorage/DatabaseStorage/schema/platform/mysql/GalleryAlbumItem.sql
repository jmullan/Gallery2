
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editting it by hand would be a bad idea.  If 
    -- you want to do something productive, fix the style sheet so that it
    -- formats the SQL attractively.
    --

    CREATE TABLE g2_GalleryAlbumItem (
  
    g_id
      int(11)
    
    NOT NULL
  
    ,
  
    g_backgroundColor
      varchar(
      
          32
        
      )
    
    ,
  
    g_backgroundColor2
      varchar(
      
          32
        
      )
    
    ,
  
    g_border
      int(11)
    
    ,
  
    g_borderColor
      varchar(
      
          32
        
      )
    
    ,
  
    g_columns
      int(11)
    
    ,
  
    g_displayViewCount
      int(1)
    
    ,
  
    g_font
      varchar(
      
          32
        
      )
    
    ,
  
    g_htmlFooter
      text
    
    ,
  
    g_htmlHeader
      text
    
    ,
  
    g_layout
      varchar(
      
          32
        
      )
    
    ,
  
    g_linkColor
      varchar(
      
          32
        
      )
    
    ,
  
    g_allowPrinting
      int(1)
    
    ,
  
    g_childIntermediateResize
      int(11)
    
    ,
  
    g_childThumbSize
      int(11)
    
    ,
  
    g_rows
      int(11)
    
    ,
  
    g_showBreadCrumb
      int(1)
    
    ,
  
    g_textColor
      varchar(
      
          32
        
      )
    
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
      'GalleryAlbumItem',
      1,
      0
      );

  