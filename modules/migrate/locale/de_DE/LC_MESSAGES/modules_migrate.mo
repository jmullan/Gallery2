��    d      <  �   \      �     �  %   �  �   �  
   ?	     J	     V	     b	  D   t	     �	  �   �	     m
     s
     z
  "   �
  	   �
  	   �
     �
     �
     �
     �
  2   �
  
   .  �   9     �     �     �     �  �         �  '   �          '  A   :  ?   |  ;   �  	   �  D    A   G  �   �     9     @     O     ]     m     z     �     �     �     �     �     �     �  "   �         *   A  	   l     v     �     �     �    �     �     �     �  $   �          "     :     W     s     �     �     �  @   �  >   �     3  %   ;  =   a  B   �  ?   �  -   "  `   P  �   �  '  8     `     s  -   �     �  	   �  1   �  \   �     U     e     n       �   �  $   ]  $   �  I   �  q  �     c  J   k  �   �  	   a     k  
   z     �  P   �     �  �   �     �  	   �     �  +   �          &     7     M     b     v  `   �     �  �   �     �     �     �     �    �      !  D   !  >   S!     �!  K   �!  R   �!  >   P"  	   �"  �  �"  F   ;$  �   �$     =%     D%     Y%     j%     %     �%     �%     �%     �%     �%     �%     &     &  %   6&     \&  5   {&  	   �&     �&  !   �&  !   �&  $   '  k  6'     �(     �(     �(  8   �(     
)  "   )  %   9)  (   _)     �)     �)     �)  	   �)  E   �)  L   ,*     y*  /   �*  E   �*  S   �*  H   S+  >   �+  y   �+  }   U,  �   �,     �-     �-  9   �-     *.  	   0.  9   :.  h   t.     �.     �.     �.     /  �   3/  +   !0  D   M0  C   �0         6   R       8                         \   I   _           !   T   ]   ;   <      5   `      	   J   [      ^   -   )      N                 G   Y         2   '               &   @              ?              a                  E   >            H   =       X       %   U       Q      B   0   V           A          d       C   S       Z   F      L   
   9   $   "   c   W   7                    b      *       D   1   +       #       :   O   4       /      ,   .   K       (   M                3          P        %s (%s) (Default to summary value if not set) Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories. Album Name Album Notes Album Title Albums to import: An album already exists with this name.  This album will be renamed. Base filename Before you migrate any data you must try adding an album and image through the main gallery interface first.  This will show you if your gallery is correctly set up. Blank Cancel Caption Character Encoding of Source Text: Check All Clear All Confirm Migration Creating thumbnails Custom Field: Custom field: Default to same as summary if custom field not set Delete All Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries? Description Description: %s Destination: Download .htaccess file Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. This will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be. Encoding: %s Ensure the %s Apache module is enabled. Enter a custom field name Error importing %s Error while importing %d album. Errors while importing %d albums. Error while importing %d user. Errors while importing %d users. G1->G2 mappings will be recorded for use in URL Redirection Gallery 1 Gallery 2 has the following fields for all items and albums: title, summary text shown with thumbnails and description text shown in item or album view. G1 albums already have these three items (though the names of summary and description are reversed). G1 items have only a filename and caption. For items imported into G2: Gallery can redirect old Gallery1 URLs to the new Gallery2 pages. If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file "gallery_remote2.php" file before you can use Gallery Remote to upload images to G2. Import Import %s now. Import Albums Import Complete Import Users Import complete Import from Gallery 1 Import more data Imported %s Importing Users Importing photos Invert Selection Item captions Item fields will be imported from: Map entries deleted successfully Migrate your Gallery 1 albums to Gallery 2 Migration Migration Status No albums imported. No available users No users imported. Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster. Path Prepare Import Recently Used Paths Record G1->G2 mappings during import Select Select Albums and Users Select the albums to migrate Select the users to migrate Set description from: Set summary from: Set title from: Source: Successfully imported %d album. Successfully imported %d albums. Successfully imported %d user. Successfully imported %d users. Summary The path that you entered is invalid. There is one G1->G2 map entry There are %d G1->G2 map entries These users are already in your gallery, and will not be imported: This album has an illegal name and will be renamed to <i>%s</i> This album's owner (%s) hasn't been imported. This module is unfinished.  It should not harm your Gallery 1 data, but use it at your own risk. This operation takes data (images, albums, users, etc.) from <strong>Gallery 1</strong> and brings it into <strong>Gallery 2</strong>. This process will copy data from an existing Gallery 1 installation.  It won't modify your Gallery 1 data in any way.  You must enter the path to your Gallery 1 <i>albums</i> directory.  If you enter the wrong path, we'll let you know so it's safe to experiment.  Example: <i>/path/to/albums</i> Thumbnail %d of %d Thumbnail generation Thumbnails will be generated during migration Title Title: %s To enable URL Redirection under Apache webserver: Top level albums and albums whose parents are not selected will be imported into this album: URL Redirection Username Users to import: You did not enter a path. You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the <a href="%s">Modules</a> page to activate a Graphics Toolkit. You must choose something to import! You must specify a custom field name Your Gallery 1 will be converted from this character encoding into UTF-8: Project-Id-Version: Gallery: Migrate 1.0
POT-Creation-Date: 2003-10-19 05:10+0200
PO-Revision-Date: 2005-05-14 13:11+0100
Last-Translator: Frederik Kunz <frederik.kunz@web.de>
Language-Team: German <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 %s (%s) (auf Zusammenfassungs-Feld zurückgreifen, falls kein Wert vergeben wurde) Fügen Sie den gleichen <tt>.htaccess</tt>-Block in Ihr Gallery 1 "albums" Verzeichnis ein, wenn Sie auch Verweise zu Bilddateien und Albenverzeichnissen umleiten willen. Albumname Album-Hinweise Albumtitel Zu importierende Alben: Es existiert bereits ein Album mit diesem Namen.  Der Name wird daher geändert. Basis-Dateiname Bevor sie mit der Migration von Daten beginnen, sollten Sie versuchen, ein Album und ein Bild über die Hauptoberfläche Ihrer Gallery hinzuzufügen. Dies wird zeigen, ob Ihre Gallery richtig aufgesetzt ist. Leer Abbrechen Beschriftung Zeichenkodierung der ursprünglichen Texte: Alle auswählen Auswahl aufheben Migration bestätigen Erzeuge Voransichten Individuelles Feld: Individuelles Feld: auf Zusammenfassungs-Feld zurückgreifen, falls für das individuelle Feld nichts vergeben wurde Alle löschen Das Löschen von Einträgen führt dazu, dass alte G1-URLs "Nicht gefunden" Fehlermeldungen erzeugen, anstatt auf die G2-Seiten umzuleiten.  Alle Einträge löschen? Beschreibung Beschreibung: %s Ziel: .htaccess Datei herunterladen Verändern oder erzeugen Sie eine Datei namens <tt>.htaccess</tt> in Ihrem Gallery1 Verzeichnis und fügen Sie den unten dargestellten Text in die Datei ein. Dies funktioniert auch in Ihrem Gallery2 Verzeichnis, wenn G2 in dem Verzeichnis installiert wurde, in dem sich zuvor G1 befand. Kodierung: %s Stellen Sie sicher, dass das %s-Modul in Ihrem Apache aktiviert ist. Geben Sie den Namen eines individuellen Informationsfeldes ein Fehler beim Importieren von %s Fehler beim Importieren eines Albums. Fehler beim Importieren von %d Alben. Fehler beim Importieren eines Benutzers. Fehler beim Importieren von %d Benutzern. G1 -> G2 Einträge werden für die URL-Umleitung aufgezeichnet Gallery 1 Gallery 2 bietet die folgenden Felder für alle Elemente und Alben: Titel, Zusammenfassung (für die Voransicht) und Beschreibung (für die Element-Ansicht oder Alben-Ansicht). G1 Alben enthalten bereits diese drei Elemente (auch wenn hier die Bezeichnung für Zusammenfassung und Beschreibung vertauscht sind). G1 Elemente haben nur einen Dateinamen und eine Beschreibung. Für Elemente, die in G2 importiert werden: Gallery kann alte Gallery1-URLs zu den neuen Gallery2-Seiten umleiten. Falls G2 in den Pfad installiert wird, in dem sich zuvor G1 befand, müssen Sie die G1-Datei  "gallery_remote2.php" entfernen, bevor Sie Gallery Remote zum Upload in G2 verwenen können. Import %s jetzt importieren Importiere Alben Import abgeschlossen Importiere Benutzer Import abgeschlossen Import von Gallery 1 Importiere sonstige Daten %s importiert Importiere Benutzer Importiere Photos Auswahl invertieren Element-Beschreibungen Element-Felder werden importiert aus: Einträge erfolgreich entfernt Migrieren Sie Ihre Alben aus Gallery 1 nach Gallery 2 Migration Migrations-Status Es wurden keine Alben importiert. Es sind keine Benutzer verfügbar Es wurden keine Benutzer importiert. Normalerweise generiert Gallery die Voransichten, sobald diese zum ersten Mal betrachtet werden und speichert sie für darauffolgende Betrachtungen. Falls sie dieses Kästchen anklicken, werden die Voransichten bereits während der Migration erzeugt. Das bedeutet, dass die Migration länger dauern, jedoch die erste Betrachtung eines Albums schneller gehen wird. Pfad Import vorbereiten Zuletzt benutzte Pfade Zeichne G1 -> G2 Einträge während des Importierens auf Wählen Sie Wählen Sie die Alben und Benutzer Wählen Sie die zu migrierenden Alben Wählen Sie die zu migrierenden Benutzer Beschreibung übernehmen aus: Übernehme Zusammenfassung aus: Übernehme Titel aus: Herkunft: Erfolgreicher Import eines Albums. Erfolgreicher Import von %d Alben. Erfolgreicher Import eines Benutzers. Erfolgreicher Import von %d Benutzern. Zusammenfassung Der von Ihnen angegeben Pfad ist nicht gültig. Es existiert ein G1 -> G2 Eintrag Es existieren %d G1 -> G2 Einträge Diese Benutzer sind bereits in Ihrer Gallery vorhanden und werden nicht importiert: Dieses Album hat einen ungültigen Namen und wird umbenannt in <i>%s</i> Der/die Besitzer/in dieses Albums (%s) wurde nicht importiert. Dieses Modul ist noch nicht fertig. Es sollte Ihre G1-Daten nicht verletzen, die Benutzung ist dennoch auf eigene Gefahr. Dieser Vorgang übernimmt Daten (Bilder, Alben, Benutzer, usw.) aus <strong>Gallery 1</strong> in <strong>Gallery 2</strong>. Dieses Modul wird Ihre G1-Daten importieren. Ihre Gallery1 wird in keiner Weise verändert. Sie müssen den Pfad zum G1 <i>albums</i>-Ordner angeben.  Falls der Pfad falsch ist, erhalten Sie eine Meldung. Beispiel: <i>/pfad/zu/albums</i> Vorschaubild %d von %d Vorschaubilder erzeugen Die Vorschaubilder werden während der Migration erzeugt. Titel Titel: %s Um die URL-Umleitung des Apache-Webservers zu aktivieren: Toplevel-Alben und Unteralben, deren Stammalbum nicht selektiert ist, werden in dieses Album importiert: URL-Umleitung Benutzername Zu importierende Benutzer: Sie haben keinen Pfad angegeben Sie haben noch kein Graphik-Werkzeug für JPEG-Bilder aktiviert. Wenn Sie jetzt den Import fortsetzten, werden keine Vorschaubilder generiert. Besuchen Sie die <a href="%s">Modul-Administration</a>, um ein Graphik-Werkzeug zu aktivieren. Sie müssen etwas zum Migrieren auswählen! Sie müssen den Namen eines individuellen Informationsfeldes angeben Ihre Gallery 1 wird von folgendem Zeichensatz zu UTF-8 konvertiert: 