��    m      �  �   �      @	     A	  *   I	  (   t	  %   �	  �   �	    �
  
   �     �     �     �  D   �     ,     :     @     G  "   O  	   r  	   |     �  |   �          )     7     E  U   S     �  Y   �  2   "  
   U  �   `     �     �       a        q  �  �     "  '   /     W     q  A   �  ?   �               '  ;   9  	   u  D    A   �  �        �     �     �     �     �     �          "     3     ?     P     `     q  "         �  *   �  	   �     �              2  "   ?     b     q  $   �     �     �     �     �               *     :     ?  @   G  >   �     �  %   �  =   �  B   3  ?   v  -   �     �     �  -        :  	   @  1   J  \   |  
   �     �     �     �       �   (  $   �  $     I   6  y  �     �  2     /   5  !   e    �  N  �     �      �      �       !  C   !     ^!     m!     r!  
   z!  :   �!     �!     �!     �!  �   �!     |"     �"     �"     �"  ~   �"  +   b#  �   �#  ?   $     S$  �   b$     0%     <%     R%  �   e%  "   �%    &     &(  1   9(  )   k(     �(  =   �(  I   �(     :)     Y)     h)  ]   �)  	   �)  �  �)  ^   �+  �   ,     �,     �,     	-     -     --  "   G-  "   j-     �-     �-     �-     �-     �-     �-  %   .  =   6.  @   t.  	   �.     �.     �.  %   �.  �   "/  2   0     @0     S0  6   p0     �0  %   �0  "   �0  (   �0      '1     H1     f1     �1     �1  ?   �1  M   �1     22     ;2  s   Y2  `   �2  =   .3  :   l3     �3     �3  5   �3     
4     4  E    4  s   f4     �4     �4     �4     5      .5  �   O5  9   @6  3   z6  U   �6                    -   T   b       7   @   0   1   B   S   U   c       <   $   >                  '             3       d      6   =   G                 
                         /          2   Y   V       l   :   %      i   L   [   K                     8   E          D                    ;   &   5       9      )   ]                   (   h      !          A   X   Q   *          M   .   	   a   Z   R   4   k      I   m   ^   f   "          H   J      ,       ?   C       F   g   \       j   O   +   `                         _      e   W   N   #              P    %s (%s) %sSummary%s was truncated for %sitem %d%s. %sTitle%s was truncated for %sitem %d%s. (Default to summary value if not set) <b>Note:</b> Before you import any data you should make sure your Gallery 1 is installed correctly by adding a photo through the Gallery 1 web interface.  Make sure you resolve any errors you see there first. Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories. Note that these redirects are not active until the G1 images are actually removed or moved. Omit the !-f line shown below to redirect anyway. Album Name Album Notes Album Title Albums to import: An album already exists with this name.  This album will be renamed. Base filename Blank Cancel Caption Character Encoding of Source Text: Check All Clear All Confirm Migration Copy all or part of an existing Gallery 1 installation into your Gallery 2.  It won't modify your Gallery 1 data in any way. Creating thumbnails Custom Field: Custom field: Custom fields Custom fields imported into item fields above will not be duplicated as custom fields Custom fields will be imported Custom fields will not be imported.  Activate Custom Fields module to enable this option. Default to same as summary if custom field not set Delete All Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries? Description Description: %s Destination: Do not create Gallery 2 custom fields for fields selected above for title, summary or description Download .htaccess file Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. Remove G1 rewrite rules from an existing file. Redirects will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be. However, if you also use the G2 URL Rewrite module then activate the G1 redirect rule in that module instead of using the block shown below. Encoding: %s Ensure the %s Apache module is enabled. Enter a custom field name Error importing %s Error while importing %d album. Errors while importing %d albums. Error while importing %d user. Errors while importing %d users. Example: /var/www/albums G1 path G1-&gt;G2 Mapping G1->G2 mappings will be recorded for use in URL Redirection Gallery 1 Gallery 2 has the following fields for all items and albums: title, summary text shown with thumbnails and description text shown in item or album view. G1 albums already have these three items (though the names of summary and description are reversed). G1 items have only a filename and caption. For items imported into G2: Gallery can redirect old Gallery1 URLs to the new Gallery2 pages. If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file "gallery_remote2.php" file before you can use Gallery Remote to upload images to G2. Import Import %s now. Import Albums Import Complete Import Users Import custom fields Import from Gallery 1 Import more data Imported %s Importing Photos Importing Users Invert Selection Item captions Item fields will be imported from: Map entries deleted successfully Migrate your Gallery 1 albums to Gallery 2 Migration No albums imported. No available users No users imported. Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster. Path to Gallery 1 albums directory Prepare Import Recently Used Paths Record G1->G2 mappings during import Select Select Albums and Users Select the albums to migrate Select the users to migrate Set description from: Set summary from: Set title from: Set: Source: Successfully imported %d album. Successfully imported %d albums. Successfully imported %d user. Successfully imported %d users. Summary The path that you entered is invalid. There is one G1->G2 map entry There are %d G1->G2 map entries These users are already in your gallery, and will not be imported: This album has an illegal name and will be renamed to <i>%s</i> This album's owner (%s) hasn't been imported. Thumbnail %d of %d Thumbnail generation Thumbnails will be generated during migration Title Title: %s To enable URL Redirection under Apache webserver: Top level albums and albums whose parents are not selected will be imported into this album: Truncated: URL Redirection Username Users to import: You did not enter a path. You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the <a href="%s">Modules</a> page to activate a Graphics Toolkit. You must choose something to import! You must specify a custom field name Your Gallery 1 will be converted from this character encoding into UTF-8: Project-Id-Version: Gallery: Migrate 1.0
POT-Creation-Date: 2004-11-25 00:04+0100
PO-Revision-Date: 2005-09-29 00:00+0200
Last-Translator: Arnaud MOURONVAL <ArnaudMouronval@yahoo.com>
Language-Team: French <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 %s (%s) %sRésumé%s a été tronqué en %sélément %d%s. %sTitre%s a été tronqué en %sélément %d%s. (Par défaut, la valeur résumé) <b>Note</b>&nbsp;: avant d'importer des données, vous devriez vérifier que Gallery 1 est correctement installé en ajoutant une photo à travers l'interface Web de Gallery 1. Veuillez prendre le temps de corriger toute erreur que vous pourriez rencontrer. Ajouter ce bloc <tt>.htaccess</tt> dans le répertoire des albums de Gallery 1.x si vous souhaitez rediriger les liens vers les images et les répertoires. Note&nbsp;: ces redirections ne sont actives qu'à partir du moment ou les images ne sont plus présentes dans Gallery 1. Supprimez la ligne !-f pour rediriger systématiquement. Nom d'album Notes d'album Titre d'album Albums à importer&nbsp;: Un album portant ce nom existe déjà. Cet album va être renommé. Nom de fichier Vide Annuler Sous-titre Méthode d'encodage des caractères du texte source&nbsp;: Cocher tout Décocher tout Confirmer la migration Copier tout ou partie d'une installation existante de Gallery 1 dans Gallery 2. Ce module ne modifie en rien les données dans Gallery 1. Génération des vignettes Champ personnalisé&nbsp;: Champ personnalisé&nbsp;: Champs personnalisés Les champs personnalisés importés comme des attributs standards ne seront pas dupliqués sous forme de champs personnalisés Les champs personnalisés seront importés. Les champs personnalisés ne seront pas importés. Veuillez activer le module 'Champs personnalisés' pour disposer de cette option. Par défaut, identique au résumé si aucun champ personnalisé Supprimer tout Supprimer la table des correspondance entraîne le non fonctionnement des anciennes URL de Gallery 1.x au lieu de la redirection adéquate vers une page de Gallery 2.x. Supprimer toutes les entrées&nbsp;? Description Description&nbsp;: %s Destination&nbsp;: Ne pas créer de champ personnalisé dans Gallery 2 pour les champs sélectionnés ci-dessus pour le titre, le résumé ou la description Télécharger le fichier .htaccess &Eacute;ditez ou créez un fichier nommé <tt>.htaccess</tt> dans le répertoire de Gallery 1 et ajoutez y le texte suivant. Supprimez les règles de réécriture d'un fichier existant. Les redirections fonctionneront également dans le répertoire de Gallery 2 si Gallery 2 a été installé là où Gallery 1 se trouvait. Cependant, si vous utilisez également le module de réécriture d'URL de Gallery 2, alors activez la règle de réécriture des URL de Gallery 1 dans ce module plutôt que d'utiliser les règles ci-dessous. Encodage&nbsp;: %s Assurez-vous que le module Apache %s est activé. Saisissez le nom d'un champ personnalisé Erreur durant l'import de %s Erreur en important %d album. Erreurs en important %d albums. Erreur en important %d utilisateur. Erreurs en important %d utilisateurs. Exemple&nbsp;: /var/www/albums Chemin vers G1 Correspondance G1-&gt;G2 Les correspondances G1->G2 seront enregistrées pour utilisation dans les URL de redirection. Gallery 1 Gallery 2 dispose des champs suivants pour tous les éléments et albums&nbsp;: titre, texte de résumé affiché avec les vignettes ou texte de résumé affiché avec les éléments. Les albums de Gallery 1 disposent de ces trois informations (bien que les noms des champs résumé et description soient inversés). Les éléments de Gallery 1 ne disposent que d'un nom de fichier et d'un sous-titre. Pour les éléments importés dans Gallery 2&nbsp;: Gallery peut rediriger les anciennes URL de Gallery 1.x vers les nouvelles pages de Gallery 2. Si Gallery 2 est installé là où se trouvait Gallery 1, vous devez supprimer le fichier "gallery_remote2.php" issu de Gallery 1 avant de pouvoir utiliser Gallery Remote  pour télécharger des photos dans Gallery 2. Importer Importer %s maintenant. Importer les albums Import terminé Importer les utilisateurs Importer les champs personnalisés Importer les données de Gallery 1 Importer d'autres données %s importé Import des photos Import des utilisateurs Inverser la sélection Sous-titres des éléments Les champs seront importés de&nbsp;: Entrées de la table de correspondance effacées avec succès Migration des utilisateurs et albums de Gallery 1 vers Gallery 2 Migration Aucun album n'a été importé. Aucun utilisateur disponible Aucun utilisateur n'a été importé. Normalement, Gallery génère les vignettes lors de leur premier accès. Si vous cochez cette case, les vignettes seront crées lors de la migration. La migration sera plus longue mais le premier affichage des albums sera plus rapide. Chemin vers le répertoire des albums de Gallery 1 Préparer l'import Chemins utilisés récemment Enregistrer les correspondances G1->G2 durant l'import Sélectionner Sélection des albums et utilisateurs Sélectionner les albums à migrer Sélectionner les utilisateurs à migrer Prendre la description de&nbsp;: Prendre le résumé de&nbsp;: Prendre le titre de&nbsp;: Sélectionner&nbsp;: Source&nbsp;: %d album importé avec succès %d albums importés avec succès %d utilisateur importé avec succès. %d utilisateurs importés avec succès. Résumé Le chemin saisi est invalide. Il y a une entrée dans la table de correspondance G1->G2 Il y a %d entrées dans la table de correspondance G1->G2 Ces utilisateurs sont déjà présents dans votre installation et ne seront pas importés&nbsp;: Cet album a un nom illégal et va être renommé en <i>%s</i> Le propriétaire de cet album (%s) n'a pas été importé. Vignette %d de %d Génération des vignettes Les vignettes seront générées durant la migration. Titre Titre&nbsp;: %s Pour activer la redirection des URL avec le serveur Web Apache&nbsp;: Les albums racines et les albums dont les parents ne sont pas sélectionnés seront importés dans cet album&nbsp;: Tronqué&nbsp;: Redirection d'URL Nom d'utilisateur Utilisateurs à importer&nbsp;: Vous n'avez pas saisi de chemin. Vous n'avez aucune boîte à outils graphique pour manipuler les images JPEG. Si vous importez les images maintenant, vous n'aurez aucune vignette. Rendez-vous à la page <a href="%s">Modules</a> pour activer une boîte à outils graphique. Vous devez sélectionner quelque chose à importer&nbsp;! Vous devez spécifier un nom de champ personnalisé Les données de votre Gallery 1.x seront converties de cet encodage vers UTF-8&nbsp;: 