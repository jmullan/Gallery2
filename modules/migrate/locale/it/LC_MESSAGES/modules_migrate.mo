��    k      t  �   �       	  *   !	  (   L	  %   u	  �   �	    l
  
   �     �     �     �  D   �                      "   '  	   J  	   T     ^  |   p     �                 U   +     �  Y   �  2   �  
   -  �   8     �     �     �  a   �     I  �  a     �  '        /     I  A   \  ?   �     �     �     �  ;     D  M  A   �  �   �     �     �     �     �     �     �     �     �                    .     ?  "   M      p  *   �  	   �     �     �     �       "        0     ?  $   S     x          �     �     �     �     �            @     >   V     �  %   �  =   �  B     ?   D  -   �     �     �  -   �       	     1     \   J  
   �     �     �     �     �  �   �  $   �  $   �  I     �  N  <   �  :     7   V  �   �  w  u  
   �   
   �      !     !  Q   $!     v!     �!     �!  
   �!  &   �!     �!     �!     �!  �   �!     �"     �"     �"     �"  j   �"  ,   V#  p   �#  M   �#     B$  �   P$     �$      %     %  p   %     �%  �  �%     �'  5   �'  *   �'  #    (  U   D(  W   �(     �(     )     )  R   +)  �  ~)  ^   $+  �   �+     5,     =,     P,     ^,     v,     �,     �,     �,     �,     �,     �,     �,     -  %   "-  ,   H-  ,   u-  
   �-     �-     �-     �-  K  �-  0   D/     u/     �/  0   �/  	   �/     �/     0     !0     A0     \0     t0  
   �0  	   �0  A   �0  C   �0     "1  1   +1  S   ]1  J   �1  F   �1  B   C2     �2     �2  3   �2     �2  
   �2  @   �2  m   63  	   �3     �3     �3     �3     �3  �   �3  '   �4  1   5  R   35                    ,   R   `       5   >       /   @   Q   S   a       :   #   <                 &             1       b   
   4   ;   E                 	                          .          0   W   T       j   8   $      g   J   Y   I                     6   C          B                    9   %   3       7      (   [                   '   f                 ?   V   O   )          K   -      _   X   P   2   i      G   k   \   d   !          F   H      +       =   A       D   e   Z       h   M   *   ^                         ]      c   U   L   "              N    %sSummary%s was truncated for %sitem %d%s. %sTitle%s was truncated for %sitem %d%s. (Default to summary value if not set) <b>Note:</b> Before you import any data you should make sure your Gallery 1 is installed correctly by adding a photo through the Gallery 1 web interface.  Make sure you resolve any errors you see there first. Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories. Note that these redirects are not active until the G1 images are actually removed or moved. Omit the !-f line shown below to redirect anyway. Album Name Album Notes Album Title Albums to import: An album already exists with this name.  This album will be renamed. Base filename Blank Cancel Caption Character Encoding of Source Text: Check All Clear All Confirm Migration Copy all or part of an existing Gallery 1 installation into your Gallery 2.  It won't modify your Gallery 1 data in any way. Creating thumbnails Custom Field: Custom field: Custom fields Custom fields imported into item fields above will not be duplicated as custom fields Custom fields will be imported Custom fields will not be imported.  Activate Custom Fields module to enable this option. Default to same as summary if custom field not set Delete All Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries? Description Description: %s Destination: Do not create Gallery 2 custom fields for fields selected above for title, summary or description Download .htaccess file Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. Remove G1 rewrite rules from an existing file. Redirects will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be. However, if you also use the G2 URL Rewrite module then activate the G1 redirect rule in that module instead of using the block shown below. Encoding: %s Ensure the %s Apache module is enabled. Enter a custom field name Error importing %s Error while importing %d album. Errors while importing %d albums. Error while importing %d user. Errors while importing %d users. Example: /var/www/albums G1 path G1-&gt;G2 Mapping G1->G2 mappings will be recorded for use in URL Redirection Gallery 2 has the following fields for all items and albums: title, summary text shown with thumbnails and description text shown in item or album view. G1 albums already have these three items (though the names of summary and description are reversed). G1 items have only a filename and caption. For items imported into G2: Gallery can redirect old Gallery1 URLs to the new Gallery2 pages. If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file "gallery_remote2.php" file before you can use Gallery Remote to upload images to G2. Import Import %s now. Import Albums Import Complete Import Users Import custom fields Import from Gallery 1 Import more data Imported %s Importing Photos Importing Users Invert Selection Item captions Item fields will be imported from: Map entries deleted successfully Migrate your Gallery 1 albums to Gallery 2 Migration No albums imported. No available users No users imported. Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster. Path to Gallery 1 albums directory Prepare Import Recently Used Paths Record G1->G2 mappings during import Select Select Albums and Users Select the albums to migrate Select the users to migrate Set description from: Set summary from: Set title from: Set: Source: Successfully imported %d album. Successfully imported %d albums. Successfully imported %d user. Successfully imported %d users. Summary The path that you entered is invalid. There is one G1->G2 map entry There are %d G1->G2 map entries These users are already in your gallery, and will not be imported: This album has an illegal name and will be renamed to <i>%s</i> This album's owner (%s) hasn't been imported. Thumbnail %d of %d Thumbnail generation Thumbnails will be generated during migration Title Title: %s To enable URL Redirection under Apache webserver: Top level albums and albums whose parents are not selected will be imported into this album: Truncated: URL Redirection Username Users to import: You did not enter a path. You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the <a href="%s">Modules</a> page to activate a Graphics Toolkit. You must choose something to import! You must specify a custom field name Your Gallery 1 will be converted from this character encoding into UTF-8: Project-Id-Version: Gallery: Migration 1.0.2
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2005-09-06 17:52+0000
PO-Revision-Date: 2005-09-07 12:39+0100
Last-Translator: Ermanno Baschiera <ebaschiera@gmail.com>
Language-Team: Italian <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n!=1);
 Il %ssommario%s dell'%soggetto %d%s &egrave; stato troncato. Il %stitolo%s dell'%soggetto %d%s &egrave; stato troncato. (Sar&agrave; settato come il sommario se non impostato) <b>Nota:</b> Prima di importare qualsiasi dato dovresti assicurarti che Gallery 1 sia installata correttamente, aggiungendo una foto tramite l'interfaccia web di Gallery 1. Assicurati di risolvere prima tutti gli eventuali errori. Aggiungi lo stesso blocco di <tt>.htaccess</tt> nella cartella degli album di Gallery1 se vuoi redirezionare anche i link ai file delle immagini e alle cartelle degli album. Nota che queste redirezioni non sono attive finch&eacute; le immagini di G1 non saranno effettivamente rimosse o spostate. Non inserire la linea !-f mostrata qui sotto per fare comunque la redirezione. Nome Album Note Album Titolo Album Album da importare: Un album con questo nome esiste gi&agrave;. Questo album verr&agrave; rinominato. Nome del file Vuoto Annulla Didascalia Codifica Caratteri del Testo Sorgente: Seleziona Tutto Deseleziona Tutto Conferma Migrazione Copia tutto o parte di una installazione esistente di Gallery 1 dentro la tua Gallery 2. I dati della tua Gallery 1 non verranno modificati in nessun modo. Creazione anteprime Campo Personalizzato: Campo personalizzato: Campi personalizzati I campi personalizzati importati nei campi oggetto qui sopra non saranno duplicati in campi personalizzati I campi personalizzati non saranno importati I campi personalizzati non saranno importati. Attiva il modulo Campi Personalizzati per attivare questa opzione. Se il campo personalizzato non &egrave; impostato, impostalo come il sommario Elimina Tutto Eliminando le entry della mappatura le vecchie URL di G1 produrranno errori HTTP Not Found invece di redirezionare verso le pagine di G2. Eliminare tutte le entry? Descrizione Descrizione: %s Destinazione: Non creare campi personalizzati in Gallery 2 per i campi selezionati sopra per il titolo, sommario o descrizione Scarica il file .htaccess Modifica o crea un file chiamato <tt>.htaccess</tt> nella cartella della tua Gallery1 e aggiungi al file il testo mostrato qui sotto. Elimina le regole di riscrittura di G1 dal file eventualmente esistente. Le redirezioni funzioneranno anche nella cartella di Gallery2 se G2 &egrave; installata nel percorso dove prima c'era G1. Tuttavia, se vuoi utilizzare anche il modulo di G2 URL Rewrite, allora attiva la regola di redirezione di G1 in quel modulo, invece di usare il blocco di testo mostrato qui sotto. Codifica in corso di: %s Assicurati che il modulo di Apache %s sia installato. Inserisci il nome del campo personalizzato Errore durante l'importazione di %s Errore durante l'importazione di %d album. Errori durante l'importazione di %d album. Errore durante l'importazione di %d utente. Errori durante l'importazione di %d utenti. Esempio: /var/www/albums Percorso G1 Mappatura G1-&gt;G2 La mappatura G1->G2 sar&agrave; memorizzata per l'uso nella redirezione delle URL. Gallery 2 ha i seguenti campi per tutti gli oggetti e gli album: titolo, il testo del sommario, mostrato insieme all'anteprima, e il testo della descrizione, mostrato nella visualizzazione oggetto o album. Gli album di G1 hanno gi&agrave; questi tre oggetti (anche se i nomi del riepilogo e della descrizione sono invertiti). Gli oggetti di G1 hanno solo il nome del file e la didascalia. Per gli oggetti importati in G2: Gallery pu&ograve; redirezionare le vecchie URL di Gallery1 verso le nuove pagine di Gallery2. Se G2 &egrave; installata nel percorso dove prima c'era G1, dovrai rimuovere il file di G1 "gallery_remote2.php" prima di poter usare Gallery Remote per caricare immagini in G2. Importa Importa %s adesso. Importa Album Importazione Completata Importa Utenti Importa campi personalizzati Importa da Gallery 1 Importa altri dati Importato %s Importazione Foto Importazione Utenti Inverti Selezione Didascalie oggetto I campi oggetto saranno importati da: Entry della mappatura eliminate con successo Migra i tuoi album di Gallery 1 in Gallery 2 Migrazione Nessun album importato. Nessun utente disponibile Nessun utente importato. Normalmente Gallery generer&agrave; le anteprime la prima volta che le visualizzi, poi le salver&agrave; per le visualizzazioni seguenti. Se spunti questa casella, le anteprime verranno create durante la migrazione. La migrazione sar&agrave; pi&ugrave; lunga ma la prima volta che vedi un album sar&agrave; molto pi&ugrave; veloce. Percorso della cartella degli album di Gallery 1 Preparazione Importazione Percorsi Utilizzati di Recente Registra mappatura G1->G2 durante l'importazione Seleziona Seleziona Album e Utenti Seleziona gli album da migrare Seleziona gli utenti da migrare Imposta la descrizione da: Imposta il sommario da: Imposta titolo da: Impostati: Sorgente: %d album importato con successo. %d album importati con successo. %d utente importato con successo. %d utenti importati con successo. Sommario Il percorso che hai inserito non &egrave; valido. C'&egrave; una entry nella mappatura G1->G2 Ci sono %d entry nella mappatura G1->G2 Questi utenti sono gi&agrave; nella tua gallery, e non verranno importati: Questo album ha un nome illegale e sar&agrave; rinominato in <i>%s</i> Il proprietario di questo album (%s) non &egrave; stato importato. Anteprima %d di %d Generazione anteprime Le anteprime saranno generate durante la migrazione Titolo Titolo: %s Per attivare la Redirezione delle URL sotto il webserver Apache: Gli album di primo livello e gli album i cui genitori non sono selezionati saranno importati in questo album: Troncati: Redirezione URL Nome Utente Utenti da importare: Non hai inserito un percorso. Non hai attivato alcun Set di Strumenti Grafici che gestisca le immagini JPEG. Se fai l'importazione adesso, non avrai le anteprime. Visita la pagina dei <a href="%s">Moduli</a> per attivare un Set di Strumenti Grafici. Devi selezionare qualcosa da importare! Devi specificare il nome del campo personalizzato La tua Gallery 1 sar&agrave; convertita da questa codifica dei caratteri in UTF-8: 