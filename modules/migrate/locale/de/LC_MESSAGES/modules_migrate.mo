��    p      �  �         p	     q	  *   y	  (   �	  %   �	  �   �	    �
  
   �     �     �       D     �   \     X     f     l     s  "   {  	   �  	   �     �  |   �     A     U     c     q  U        �  Y   �  2   N  
   �  �   �               .  a   ;     �  �  �     N  '   [     �     �  A   �  ?   �     2  :   K     �     �  ;   �  	   �  D  �  A   +     m  �   z     *     1     @     N     ^     k     �     �     �     �     �     �     �  "   �        *   7  	   b     l     �     �    �  "   �     �     �  $   �          %     =     Z     v     �     �     �     �  @   �  >   �     ;  %   C  =   i  B   �  ?   �  -   *     X     k  -   �     �  	   �  1   �  \   �  
   M     X     h     q     �  �   �  $   `  $   �  I   �  �  �     �  ;   �  1   �  J   �  
  B   c  M!  	   �"     �"  
   �"     �"  P   �"  7  >#     v$     �$  	   �$     �$  +   �$     �$     �$     �$  �   %     �%     �%     �%     �%  �   �%  %   �&  �   �&  `   0'     �'  �   �'     E(     R(     c(  }   i(     �(  �  )     �*  D   +  >   M+     �+  K   �+  R   �+     J,  R   d,     �,     �,  >   �,  	   -  �  -  F   �.     /  �   /     �/     �/     �/     0     0     *0     I0     ^0     x0     �0     �0     �0     �0  %   �0     �0  5   1  	   R1  !   \1  !   ~1  $   �1  k  �1  "   13     T3     g3  8   ~3     �3  "   �3  %   �3  (   4     54     S4     s4     �4  	   �4  E   �4  L   �4     35  /   C5  E   s5  S   �5  H   6  >   V6     �6     �6  9   �6     �6  	   7  9   7  h   H7     �7     �7     �7     �7     �7  �   8  +   9  D   /9  C   t9             E      /   W   e       :   C   2   3   5   V   X   f       ?   %   A          !       (             6       g      9   @   J                 
              k          1          4   \   Y       o   =   &      l   O   ^   N                      ;   H          G                    >   '   8       <      *   `                   )         "          D   [   T   +          P   0   	   d   ]   U   7   n      L   p   a   i   #          K   M      -       B   F       I   j   _       m   R   ,   c      S                  b      h   Z   Q   $              .    %s (%s) %sSummary%s was truncated for %sitem %d%s. %sTitle%s was truncated for %sitem %d%s. (Default to summary value if not set) <b>Note:</b> Before you import any data you should make sure your Gallery 1 is installed correctly by adding a photo through the Gallery 1 web interface.  Make sure you resolve any errors you see there first. Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories. Note that these redirects are not active until the G1 images are actually removed or moved. Omit the !-f line shown below to redirect anyway. Album Name Album Notes Album Title Albums to import: An album already exists with this name.  This album will be renamed. Any hidden albums or items will be imported with restricted view permissions. Activate the Hidden Items module before migration to import these as "hidden" which means they are invisible to guest users until accessed by the direct URL for those items. Base filename Blank Cancel Caption Character Encoding of Source Text: Check All Clear All Confirm Migration Copy all or part of an existing Gallery 1 installation into your Gallery 2.  It won't modify your Gallery 1 data in any way. Creating thumbnails Custom Field: Custom field: Custom fields Custom fields imported into item fields above will not be duplicated as custom fields Custom fields will be imported Custom fields will not be imported.  Activate Custom Fields module to enable this option. Default to same as summary if custom field not set Delete All Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries? Description Description: %s Destination: Do not create Gallery 2 custom fields for fields selected above for title, summary or description Download .htaccess file Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. Remove G1 rewrite rules from an existing file. Redirects will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be. However, if you also use the G2 URL Rewrite module then activate the G1 redirect rule in that module instead of using the block shown below. Encoding: %s Ensure the %s Apache module is enabled. Enter a custom field name Error importing %s Error while importing %d album. Errors while importing %d albums. Error while importing %d user. Errors while importing %d users. Example: /var/www/albums G1 URL redirect. Use only if G2 is installed where G1 used G1 path G1-&gt;G2 Mapping G1->G2 mappings will be recorded for use in URL Redirection Gallery 1 Gallery 2 has the following fields for all items and albums: title, summary text shown with thumbnails and description text shown in item or album view. G1 albums already have these three items (though the names of summary and description are reversed). G1 items have only a filename and caption. For items imported into G2: Gallery can redirect old Gallery1 URLs to the new Gallery2 pages. Hidden Items If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file "gallery_remote2.php" file before you can use Gallery Remote to upload images to G2. Import Import %s now. Import Albums Import Complete Import Users Import custom fields Import from Gallery 1 Import more data Imported %s Importing Photos Importing Users Invert Selection Item captions Item fields will be imported from: Map entries deleted successfully Migrate your Gallery 1 albums to Gallery 2 Migration No albums imported. No available users No users imported. Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster. Path to Gallery 1 albums directory Prepare Import Recently Used Paths Record G1->G2 mappings during import Select Select Albums and Users Select the albums to migrate Select the users to migrate Set description from: Set summary from: Set title from: Set: Source: Successfully imported %d album. Successfully imported %d albums. Successfully imported %d user. Successfully imported %d users. Summary The path that you entered is invalid. There is one G1->G2 map entry There are %d G1->G2 map entries These users are already in your gallery, and will not be imported: This album has an illegal name and will be renamed to <i>%s</i> This album's owner (%s) hasn't been imported. Thumbnail %d of %d Thumbnail generation Thumbnails will be generated during migration Title Title: %s To enable URL Redirection under Apache webserver: Top level albums and albums whose parents are not selected will be imported into this album: Truncated: URL Redirection Username Users to import: You did not enter a path. You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the <a href="%s">Modules</a> page to activate a Graphics Toolkit. You must choose something to import! You must specify a custom field name Your Gallery 1 will be converted from this character encoding into UTF-8: Project-Id-Version: Gallery: Migrate 1.0
POT-Creation-Date: 2003-10-19 05:10+0200
PO-Revision-Date: 2006-02-05 04:00+0000
Last-Translator: Frederik Kunz <frederik.kunz@web.de>
Language-Team: German <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
X-Generator: KBabel 1.10.1
 %s (%s) %sZusammenfassung%s wurde abgeschnitten bei %sElement %d%s. %sTitel%s wurde abgeschnitten bei %sElement %d%s. (auf Zusammenfassungs-Feld zurückgreifen, falls kein Wert vergeben wurde) <b>Achtung:</b> Bevor sie irgendwelche Daten importieren sollten Sie sicher stellen, dass Ihre Gallery 1 korrekt installiert ist indem Sie ein Photo über die Gallery 1 Weboberfläche hinzufügen.  Beheben Sie unbedingt zuerst alle Fehler die Ihnen hierbei begegnen. Fügen Sie den gleichen <tt>.htaccess</tt>-Block in Ihren Gallery 1 "albums"-Ordner ein, wenn Sie auch Verweise zu Bilddateien und Albenordnern umleiten wollen. Bitte beachten Sie, dass diese Weiterleitungen erst aktiv werden, nach dem die G1-Bilder entfernt oder verschoben wurden. Wenn Sie jedoch die Zeile mit !-f weglassen, wird so oder so umgeleitet. Albumname Album-Hinweise Albumtitel Zu importierende Alben: Es existiert bereits ein Album mit diesem Namen.  Der Name wird daher geändert. Alle versteckten Alben oder Elemente werden mit eingeschränkten Zugriffsrechten importiert. Aktivieren Sie vor der Migration das Modul für versteckte Elemente, um diese als "versteckt" zu importieren. Dies bedeutet, dass sie für Gäste unsichtbar sind, wenn diese sie nicht mittels ihrer URL direkt aufrufen. Basis-Dateiname Leer Abbrechen Beschriftung Zeichenkodierung der ursprünglichen Texte: Alle auswählen Auswahl aufheben Migration bestätigen Vollständige oder teilweise Kopie einer bestehenden Gallery 1 Installation in Ihre Gallery 2. Dies wird Ihre Daten in der Gallery 1 in keinster Weise verändern. Erzeuge Voransichten Individuelles Feld: Individuelles Feld: Individuelle Felder Individuelle Felder, welche in die obrigen Elementfelder importiert werden, werden nicht zusätzlich als individuelle Felder dupliziert Individuelle Felder werden importiert Individualisierte Felder werden nicht importiert. Aktivieren Sie das Modul für Individualisierte Felder, um diese Option zu aktivieren. auf Zusammenfassungs-Feld zurückgreifen, falls für das individuelle Feld nichts vergeben wurde Alle löschen Das Löschen von Einträgen führt dazu, dass alte G1-URLs "Nicht gefunden" Fehlermeldungen erzeugen, anstatt auf die G2-Seiten umzuleiten.  Alle Einträge löschen? Beschreibung Beschreibung: %s Ziel: Erzeuge keine individuellen Gallery-2-Felder für die oben ausgewählten Felder für Titel, Zusammenfassung oder Beschreibung .htaccess Datei herunterladen Verändern oder erzeugen Sie eine Datei namens <tt>.htaccess</tt> in Ihrem Gallery1-Ordner und fügen Sie den unten dargestellten Text in die Datei ein. Entfernen Sie dabei eventuell bereits vorhandene Umleitungs-Regeln.Die Umleitung funktioniert auch in Ihrem Gallery2-Ordner, wenn G2 in dem Ordner installiert wurde, in dem sich zuvor G1 befand. Wenn Sie jedoch das G2-Modul 'kurze URLs' verwenden, dann aktuvieren Sie die G1-Umleitungs-Regel in diesem Modul und nicht den hier dargestellten Block. Kodierung: %s Stellen Sie sicher, dass das %s-Modul in Ihrem Apache aktiviert ist. Geben Sie den Namen eines individuellen Informationsfeldes ein Fehler beim Importieren von %s Fehler beim Importieren eines Albums. Fehler beim Importieren von %d Alben. Fehler beim Importieren eines Benutzers. Fehler beim Importieren von %d Benutzern. Beispiel: /var/www/albums G1-URL-Weiterleitung. Nur verwenden, wenn G2 dort installiert ist, wo zuvor G1 war G1-Pfad G1-&gt;G2 Umleitung G1 -> G2 Einträge werden für die URL-Umleitung aufgezeichnet Gallery 1 Gallery 2 bietet die folgenden Felder für alle Elemente und Alben: Titel, Zusammenfassung (für die Voransicht) und Beschreibung (für die Element-Ansicht oder Alben-Ansicht). G1 Alben enthalten bereits diese drei Elemente (auch wenn hier die Bezeichnung für Zusammenfassung und Beschreibung vertauscht sind). G1 Elemente haben nur einen Dateinamen und eine Beschreibung. Für Elemente, die in G2 importiert werden: Gallery kann alte Gallery1-URLs zu den neuen Gallery2-Seiten umleiten. Versteckte Elemente Falls G2 in den Pfad installiert wird, in dem sich zuvor G1 befand, müssen Sie die G1-Datei  "gallery_remote2.php" entfernen, bevor Sie Gallery Remote zum Upload in G2 verwenen können. Import %s jetzt importieren Importiere Alben Import abgeschlossen Importiere Benutzer Importiere individuelle Felder Import von Gallery 1 Importiere sonstige Daten %s importiert Importiere Photos Importiere Benutzer Auswahl invertieren Element-Beschreibungen Element-Felder werden importiert aus: Einträge erfolgreich entfernt Migrieren Sie Ihre Alben aus Gallery 1 nach Gallery 2 Migration Es wurden keine Alben importiert. Es sind keine Benutzer verfügbar Es wurden keine Benutzer importiert. Normalerweise generiert Gallery die Voransichten, sobald diese zum ersten Mal betrachtet werden und speichert sie für darauffolgende Betrachtungen. Falls sie dieses Kästchen anklicken, werden die Voransichten bereits während der Migration erzeugt. Das bedeutet, dass die Migration länger dauern, jedoch die erste Betrachtung eines Albums schneller gehen wird. Pfad zum Gallery 1 'albums'-Ordner Import vorbereiten Zuletzt benutzte Pfade Zeichne G1 -> G2 Einträge während des Importierens auf Wählen Sie Wählen Sie die Alben und Benutzer Wählen Sie die zu migrierenden Alben Wählen Sie die zu migrierenden Benutzer Beschreibung übernehmen aus: Übernehme Zusammenfassung aus: Übernehme Titel aus: Wählen Sie: Herkunft: Erfolgreicher Import eines Albums. Erfolgreicher Import von %d Alben. Erfolgreicher Import eines Benutzers. Erfolgreicher Import von %d Benutzern. Zusammenfassung Der von Ihnen angegeben Pfad ist nicht gültig. Es existiert ein G1 -> G2 Eintrag Es existieren %d G1 -> G2 Einträge Diese Benutzer sind bereits in Ihrer Gallery vorhanden und werden nicht importiert: Dieses Album hat einen ungültigen Namen und wird umbenannt in <i>%s</i> Der/die Besitzer/in dieses Albums (%s) wurde nicht importiert. Vorschaubild %d von %d Vorschaubilder erzeugen Die Vorschaubilder werden während der Migration erzeugt. Titel Titel: %s Um die URL-Umleitung des Apache-Webservers zu aktivieren: Toplevel-Alben und Unteralben, deren Stammalbum nicht selektiert ist, werden in dieses Album importiert: Abgeschnitten: URL-Umleitung Benutzername Zu importierende Benutzer: Sie haben keinen Pfad angegeben Sie haben noch kein Grafik-Werkzeug für JPEG-Bilder aktiviert. Wenn Sie jetzt den Import fortsetzten, werden keine Vorschaubilder generiert. Besuchen Sie die <a href="%s">Modul-Administration</a>, um ein Graphik-Werkzeug zu aktivieren. Sie müssen etwas zum Migrieren auswählen! Sie müssen den Namen eines individuellen Informationsfeldes angeben Ihre Gallery 1 wird von folgendem Zeichensatz zu UTF-8 konvertiert: 