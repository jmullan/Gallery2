��    n      �  �   �      P	  *   Q	  (   |	  %   �	  �   �	    �
  
   �     �     �     �  D   �  �   4     0     >     D     K  "   S  	   v  	   �     �  |   �          -     ;     I  U   W     �  Y   �  2   &  
   Y  �   d     �     �       a        u  �  �     &  '   3     [     u  A   �  ?   �     
  �   #     �     �  ;   �  D  7  A   |     �  �   �     {     �     �     �     �     �     �     �     �               %     6  "   D      g  *   �  	   �     �     �     �    �  "        '     6  $   J     o     v     �     �     �     �     �     �       @     >   M     �  %   �  =   �  B   �  ?   ;  -   {     �     �  -   �     �  	     1     \   A  
   �     �     �     �     �  �   �  $   �  $   �  I   �  �  E  /   
   /   :   :   j   �   �   ~  �!     #     *#     ;#     N#  B   b#  =  �#     �$  	   �$      %     	%  0   %     C%     O%     [%  |   p%     �%      &     &     *&  y   ?&  +   �&  x   �&  M   ^'     �'  �   �'     v(     �(     �(     �(     )  �  <)     8+  ;   J+  +   �+     �+  m   �+  o   4,     �,  �   �,     �-     �-  K   �-  �  .  W   �/     0  �   0     �0     �0     �0     �0     1      1     ?1     X1     l1     y1     �1     �1     �1  0   �1  %   �1  +   2  
   K2     V2     t2     �2  /  �2  /   �3     4     &4  .   E4     t4     �4  !   �4  !   �4  !   �4     5     "5  	   ?5     I5  B   Q5  C   �5     �5  *   �5  >   6  C   J6  A   �6  :   �6     7     7  1   87     j7     r7  D   ~7  r   �7  	   68     @8     T8     f8     {8  �   �8  '   o9  5   �9  K   �9             C      .   U   c       8   A       1   3   T   V   d       =   $   ?                  '             4       e   
   7   >   H                 	              i           0          2   Z   W       m   ;   %      j   M   \   L                     9   F          E                    <   &   6       :      )   ^                   (         !          B   Y   R   *          N   /      b   [   S   5   l      J   n   _   g   "          I   K      ,       @   D       G   h   ]       k   P   +   a                         `      f   X   O   #       -      Q    %sSummary%s was truncated for %sitem %d%s. %sTitle%s was truncated for %sitem %d%s. (Default to summary value if not set) <b>Note:</b> Before you import any data you should make sure your Gallery 1 is installed correctly by adding a photo through the Gallery 1 web interface.  Make sure you resolve any errors you see there first. Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories. Note that these redirects are not active until the G1 images are actually removed or moved. Omit the !-f line shown below to redirect anyway. Album Name Album Notes Album Title Albums to import: An album already exists with this name.  This album will be renamed. Any hidden albums or items will be imported with restricted view permissions. Activate the Hidden Items module before migration to import these as "hidden" which means they are invisible to guest users until accessed by the direct URL for those items. Base filename Blank Cancel Caption Character Encoding of Source Text: Check All Clear All Confirm Migration Copy all or part of an existing Gallery 1 installation into your Gallery 2.  It won't modify your Gallery 1 data in any way. Creating thumbnails Custom Field: Custom field: Custom fields Custom fields imported into item fields above will not be duplicated as custom fields Custom fields will be imported Custom fields will not be imported.  Activate Custom Fields module to enable this option. Default to same as summary if custom field not set Delete All Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries? Description Description: %s Destination: Do not create Gallery 2 custom fields for fields selected above for title, summary or description Download .htaccess file Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. Remove G1 rewrite rules from an existing file. Redirects will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be. However, if you also use the G2 URL Rewrite module then activate the G1 redirect rule in that module instead of using the block shown below. Encoding: %s Ensure the %s Apache module is enabled. Enter a custom field name Error importing %s Error while importing %d album. Errors while importing %d albums. Error while importing %d user. Errors while importing %d users. Example: /var/www/albums G1 URL redirect. Use only if G2 is installed where G1 used to be and you have run a G1 import with the URL redirect option selected. Otherwise follow instructions in %sMigrate Site Admin%s. G1 path G1-&gt;G2 Mapping G1->G2 mappings will be recorded for use in URL Redirection Gallery 2 has the following fields for all items and albums: title, summary text shown with thumbnails and description text shown in item or album view. G1 albums already have these three items (though the names of summary and description are reversed). G1 items have only a filename and caption. For items imported into G2: Gallery can redirect old Gallery1 URLs to the new Gallery2 pages. Hidden Items If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file "gallery_remote2.php" file before you can use Gallery Remote to upload images to G2. Import Import %s now. Import Albums Import Complete Import Users Import custom fields Import from Gallery 1 Import more data Imported %s Importing Photos Importing Users Invert Selection Item captions Item fields will be imported from: Map entries deleted successfully Migrate your Gallery 1 albums to Gallery 2 Migration No albums imported. No available users No users imported. Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster. Path to Gallery 1 albums directory Prepare Import Recently Used Paths Record G1->G2 mappings during import Select Select Albums and Users Select the albums to migrate Select the users to migrate Set description from: Set summary from: Set title from: Set: Source: Successfully imported %d album. Successfully imported %d albums. Successfully imported %d user. Successfully imported %d users. Summary The path that you entered is invalid. There is one G1->G2 map entry There are %d G1->G2 map entries These users are already in your gallery, and will not be imported: This album has an illegal name and will be renamed to <i>%s</i> This album's owner (%s) hasn't been imported. Thumbnail %d of %d Thumbnail generation Thumbnails will be generated during migration Title Title: %s To enable URL Redirection under Apache webserver: Top level albums and albums whose parents are not selected will be imported into this album: Truncated: URL Redirection Username Users to import: You did not enter a path. You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the <a href="%s">Modules</a> page to activate a Graphics Toolkit. You must choose something to import! You must specify a custom field name Your Gallery 1 will be converted from this character encoding into UTF-8: Project-Id-Version: Gallery: Migration 1.0.8
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2006-10-28 16:34+0200
PO-Revision-Date: 2007-01-23 16:49+0100
Last-Translator: Oscar Garcia Amor <oscar.garcia@moire.org>
Language-Team: Spanish <gallery-translations@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 El %sResumen%s del %selemento %d%s fue truncado El %sTítulo%s del %selemento %d%s fue truncado (Por defecto el valor del resumen si no está establecido) <b>Nota:</b> Antes de importar cualquier dato deberías asegurarte de que tu Gallery 1 está instalado correctamente añadiendo una foto a través de la interfaz web de Gallery 1. Cerciorarte de resolver primero cualquier error que veas allí. Añade el mismo bloque <tt>.htaccess</tt> en los directorios de los álbumes de Gallery1 si también quieres redirigir los enlaces a los ficheros de imagen y a los directorios de los álbumes. Nota que estas redirecciones no serán activadas hasta que las imágenes de G1 no se muevan o eliminen realmente. Omite la línea !-f mostrada a continuación para redirigir de todos modos. Nombre del Álbum Notas del Álbum Título del Álbum Álbums a importar: Ya existe un álbum con este nombre.  Este álbum sera renombrado. Cualquier álbum o elemento oculto será importado con los permisos de visualización restingidos. Activa el modulo de Elementos Ocultos antes de la migración para importar estos cómo "ocultos" lo que significa que serán invisibles a los usuarios anónimos a no ser que se acceda a ellos directamente desde la URL. Nombre del fichero En Blanco Cancelar Etiqueta Codificación de Caracteres del Texto de Origen: Marcar Todo Borrar Todo Confirmar Migración Copia todo o parte de una instalación existente de G1 en tu Gallery 2.  No modifica los datos de Gallery 1 en ningún caso. Creando miniaturas Campo Personalizado: Campo personalizado: Campos pesonalizados Los campos personalizados importados en los campos del elemento de arriba no serán duplicados como campos personalizados Los campos personalizados serán importados Los campos personalizados no serán importados.  Actica el módulo de Campos Personalizados para habilitar esta opción. Por defecto lo mismo que el resumen si no se establece un campo personalizado Borrar todo El borrado de las entradas mapeadas causará que las viejas URLs de G1 produzcan errores de HTTP No Encontrado en lugar de redirigir a las páginas de G2. &iquest;Borrar todas las entradas? Descripción Descripción: %s Destino: No crear campos personalizados en Gallery 2 para los campos seleccionados a continuacion para el título, resumen o descipción Descargar el archivo .htaccess Edita o crea un archivo llamado <tt>.htaccess</tt> en el directorio de tu Gallery1 y añade el texto mostrado a continuación al archivo. Elimina las reglas de reescritura de G1 del fichero existente. Las redirecciones funcionarán también en tu directorio de Gallery2 si G2 está instalado en la ruta donde estaba G1. Sin embargo si también utilizas el módulo de reescritura de URL de G2 entonces activa la regla de redirección de G1 en dicho módulo en vez de usar el bloque mostrado a continuación.  Codificación: %s Asegúrate de que el módulo de Apache %s esté habilitado. Introduce el nombre del campo personalizado Error importando %s Ha ocurrido un error mientras se importaba %d álbum. Han ocurrido errores mientras se importaba %d álbumes. Ha ocurrido un error mientras se importaba %d usuario. Han ocurrido errores mientras se importaban %d usuarios. Ejemplo: /var/www/albums Redirigir a la URL de G1. Usar solo si G2 esta instalado donde estaba G1 y puedes ejecutar una importación de G1 con la opción de redirección de URL seleccionada. Si no sigue las instrucciones en %sAdministrador del Sitio de Migración%s Ruta G1 Mapeo G1-&gt;G2 Los mapeos G1->G2 serán reordenados para usar en la redirección de la URL Gallery 2 tiene los siguiente campos para todos los elementos y álbumes: el título, el resumen mostrado con las miniaturas y la descripción mostrada en la vista de un elemento o álbum. Los álbumes de G1 ya tienen estos tres elementos (aunque los nombres del resumen y la descipción estan invertidos). Los elementos de G1 solo tienen un nombre de fichero y una etiqueta. Para elementos importados en G2: Gallery puede redirigir las viejas URLs de Gallery 1 a las nuevas páginas de Gallery 2 Elementos Ocultos Si G2 está instalado en la ruta donde estaba G1, necesitarás antes eliminar el archivo de G1 "gallery_remote2.php" para que puedas usar Gallery Remote para subir imágenes a G2. Importar Importar %s ahora. Importar Álbumes Imporatación Completa Importar Usuarios Importar campos personalizados Importar desde Gallery 1 Importar más datos %s importado Importando Fotos Importando Usuarios Invertir Seleccion Etiquetas del elemento Los campos del elemento serán importados desde: Entradas mapeadas borradas con éxito Migra tus Álbumes de Gallery 1 a Gallery 2 Migración No se han importado álbumes. No hay usuarios disponibles No se han importado usuarios. Normalmente Gallery generará miniaturas la pimera vez que las veas y las guardara para las subsiguientes visitas.  Si marcas esta opción, las miniaturasse crearán en el momento de la importación.  La migración se tomará más tiempo, pero la primera vez que visites un álbum ira mucho mas rápido. Ruta al directorio de los álbumes de Gallery 1 Peparar la Importación Rutas Utilizadas Recientemente Grabar mapeados G1->G2 durante la importación Seleccionar Seleccionar Álbums y Usuarios Seleccionar los álbumes a migrar Seleccionar los usuarios a migrar Establecer la descripción desde: Establecer el resumen desde: Establecer el título desde: Asignado: Origen: Importado %d álbum con éxito. Importados %d álbumes con éxito. Importado %d usuario con éxito. Importados %d usuarios con éxito. Resumen La ruta que has introducido no es válida. Hay una entrada mapeada G1->G2 Hay %d entradas mapeadas G1->G2 Estos usuarios están ya en tu galería y no pueden ser importados: Este álbum tiene un nombre ilegal y será renombrado a <i>%s</i> El propietario de este álbum (%s) no puede ser importado. Miniatura %d de %d Generación de miniaturas La miniaturas se generarán durante la migración Título Título: %s Para habilitar la redirección de URL's bajo el servidor web Apache: Los álbumes de nivel superior y los álbumes cuyos padres no sean seleccionados serán importados en este álbum: Truncado: Redirección de URL Nombre de Usuario Usuarios a importar: No has introducido una ruta. No tienen ninguna Herramienta Gráfica activada para manejar imágenes JPEG.  Si importas ahora, no tendrás ninguna miniatura.  Visita la página de <a href="%s">Módulos</a> para activar una Herramienta Gráfica. &iexcl;Debes elegir algo para importar! Debes especificar el nombre de un campo personalizado Tu Gallery 1 será convertida desde su codificación de caracteres a UTF-8: 