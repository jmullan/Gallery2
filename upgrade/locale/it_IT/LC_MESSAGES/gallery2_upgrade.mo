��    n      �  �   �      P	     Q	     o	     }	     �	  d   �	     "
     /
     ?
  	  Z
     d     r     �     �     �     �     �     �     �  u   �  �   q  �        �     �     �     �     �  	   �    �       F        c     f  p   x  �   �  !   �               1     >     Q     e     k     p     t  t   �     �  }        �     �  	   �  
   �     �     �     �  	   �     �     �  +     �   .     �  
               !   $  �   F  -  (  �   V  	   �  %   �          7     T  S   t     �     �     �     �               .     G     V  *   d  #   �     �  �   �  !   �     �  (  �  M  �  �   8  �     �   �  �   p    (  8   7   �   p   4   P!     �!     �!  3   �!  '   �!  �   	"     �"     �"  6   �"     #     #     0#  |  I#  )   �$     �$  #   %  !   (%  d   J%     �%     �%  %   �%    �%     �&     '     ,'     K'     T'     k'     y'     �'     �'  �   �'  �   9(  �   �(     q)     �)     �)     �)     �)     �)  =  �)      +  C   &+     j+     n+  o   �+    �+  $   -     6-     U-     u-     �-     �-     �-     �-     �-     �-  �   �-     W.  �   h.     /     	/  	   /  
    /     +/     B/     U/  	   b/     l/     �/  6   �/  �   �/     �0     �0     �0     �0  %   �0  �   1  M  2  �   ^3     4  0   4  (   K4  !   t4  #   �4  S   �4     5      5     ;5     N5     c5     y5     �5     �5     �5  /   �5  "   �5     6    (6  (   07     Y7  N  a7  o  �8  �    :  �   �:  �   �;  �   �<  ,  �=  7   �>    �>  :   @  	   =@  '   G@  B   o@  5   �@  �   �@     �A     �A  7   �A     B     B     3B         :   ;   l       %   A   b   R          <             `   h           =   
   c      @   8   '   E       ]   k   X          \      "   n   +      D   /                 M   7   )       Z       W       F              (   C   1       d   I   J   !   K          P           Y      V      6           U   9   	   $       5   [   H      4      g      .   B   j   e   0       ,           -      *          i          >              ?           O   T       S       2   N   3       ^                       &   a      _      m      Q   f          G               L   #    %s module needs configuration (un)check all <b>Error:</b> invalid password. <b>Error:</b> missing password. <b>Reminder</b>: Now check the permissions on config.php and make sure it is not globally writeable. Authenticate Authenticate Me Authentication successful! Before you upgrade, we <b>strongly recommend</b> that you make a backup of your database!  If you fail to make a backup and something goes wrong, there is a strong possibility that we will not be able to help you recover your data!  Refer to the following examples: Begin Upgrade Config.php upgrade Continue to Step %d&raquo; Current Currently installed Debug Output: Delete Cache Directories Description Empty Cache Error: Your version of PHP is configured with safe mode enabled.  You must disable safe mode before Gallery will run. Error: your PHP __FILE__ directive is not functioning correctly. Please file a support request with your webserver administrator or in the Gallery forums. Even though there were errors, you can still continue.  Or, you can try deleting these directories yourself and then click the <b>Try Again</b> link below. FILE Directive FILE directive supported Failed File uploads allowed Finished Finished! Gallery creates temporary copies of some of your data on your hard drive.  This helps it to run faster.  But when you upgrade, some of these files might be out of date so it's a good idea to get rid of them now.  Gallery will create them again as it needs them. Gallery file integrity Gallery: <strong>your photos</strong> on <strong>your website</strong> Go Go to my Gallery! If you are using Apache, create a file named .htaccess in the main Gallery directory with the following content: In order to proceed with the install, we have to verify that you are who you claim.  When you performed the install, you entered a password which went into your config.php.  Type that in now.  Refer to your config.php if you've forgotten what you entered. Manifest missing or inaccessible. Maximum POST size Maximum upload size Memory limit Missing files (%d) Modified files (%d) MySQL Name New New version Note: You're running Gallery from CVS, so recently removed files may appear here.  It might be safe to ignore these. Old files (%d) Once the upgrade has begun, please be patient.  If you cancel or reload the page, you may interfere with the upgrade process. Other PHP Version Password: PostgreSQL Recheck config.php Redo this step Required Safe Mode Safe mode disabled Select Language: Skip Upgrade and Continue to Step %d&raquo; Something went wrong when we tried to upgrade the core module.  In the boxes below you can find some debug information.  Report this in the %sGallery Forums%s and we'll help you diagnose the problem. Stack Trace: Start Over Success System Checks Test skipped due to other errors. The Gallery Core Module is the heart of the Gallery application.  You can upgrade most other modules using the Site Administration interface, but this module must be handled separately in order for the upgrade to go smoothly. The following modules can be automatically upgraded for you.  If you choose not to upgrade them now, you may experience problems with your Gallery.   You can always upgrade or deactivate them on the Site Administration page, or return to this page later so any decision you make here is not permanent. These files are no longer part of Gallery. They probably won't cause any problems but it is a good idea to remove them to keep your install clean. Try Again Unable to commit database transaction Unable to get the module list Unable to load the %s module Unable to upgrade the %s module Unable to write to config.php in your %s directory.  Please change its permissions. Unknown Upgrade %d%% complete Upgrade Core Upgrade Modules Upgrade More Modules Upgrade Other Modules Upgrade Selected Modules Upgrade Status Upgrade Steps Upgraded Gallery Core Module successfully. Upgraded the %s module successfully Upgrader Help Upgrading Gallery 2.0 requires %d steps. This upgrade tool will guide you through these steps and provide assistance along the way if additional steps are required. Please read the %sHelp File%s before proceeding. Upgrading the Gallery Core Module Warning Warning: The exec() function is disabled in your php by the <b>disabled_functions</b> parameter in php.ini. You won't be able to use modules that require external binaries (e.g. ImageMagick, NetPBM or Ffmpeg). This can only be set server-wide, so you will need to change it in the global php.ini. Warning: The set_time_limit() function is disabled in your php by the <b>disabled_functions</b> parameter in php.ini.  Gallery can function with this setting, but it will not operate reliably.  Any operation that takes longer than %d seconds will fail (and in some cases just return a blank page) possibly leading to data corruption. Warning: Your PHP is configured not to allow file uploads (<b>file_uploads</b> parameter in php.ini). You will need to enable this option if you want to upload files to your Gallery with a web browser. Warning: Your PHP is configured to limit the memory to %sb (<b>memory_limit</b> parameter in php.ini). You should raise this limit to at least <b>%sMB</b> for proper Gallery operation. Warning: Your PHP is configured to limit the post data to a maximum of %sb (<b>post_max_size</b> parameter in php.ini). You should raise this limit to allow uploading bigger files. Warning: Your PHP is configured to limit the size of file uploads to %sb (<b>upload_max_filesize</b> parameter in php.ini). You should rise this limit to allow uploading bigger files. Warning: Your PHP is configured with Zend ze1_compatibility_mode which can cause PHP to crash.  Click <a href="%s">here</a> to test your PHP.  If you see "SUCCESS" then your PHP is ok.  If you get an error then you must turn off ze1_compatibility_mode before proceeding. We have successfully cleaned out your cache directories. We were unable to clean the following cache directories.  This is probably ok, but if you notice any weird behaviour, you should try to delete these directories yourself.  It's perfectly safe to get rid of them at any time. We've successfully upgraded the Gallery Core Module. Welcome Welcome to the Gallery Upgrader You can do <i>chmod 666 config.php</i> to fix this. Your Gallery Core Module is up to date! Your config.php appears to use the old form of multisite support.  Please see the %sHelp File%s for instructions to update your configuration before proceeding. Zend compatibility mode exec() allowed mysqldump -u%s -p<i>YourPassword</i> --opt %s > %s.sql no limit pg_dump --format=t %s > %s.sql set_time_limit() allowed Project-Id-Version: Gallery: Upgrader 1.0
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2005-06-01 11:42+0000
PO-Revision-Date: 2005-06-01 12:50+0100
Last-Translator: Ermanno Baschiera <ebaschiera@gmail.com>
Language-Team: Italian <LL@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Poedit-Language: Italian
X-Poedit-Country: ITALY
 Il modulo %s ha bisogno di configurazione (de)seleziona tutto <b>Errore:</b> password non valida. <b>Errore:</b> password mancante. <b>Ricorda</b>: Ora controlla i permessi di config.php e assicurati che non sia scrivibile da tutti. Autenticazione Autenticami Autenticazione avvenuta con successo! Prima di fare l'aggiornamento, <b>ti raccomandiamo caldamente</b> di fare un backup del database! Se non fai il backup e qualcosa va storto, c'&egrave; una forte possibilit&agrave; che non saremo in grado di recuperare i tuoi dati! Fa' riferimento agli esempi seguenti: Inizio Aggiornamento Aggiornamento config.php Continua con la Fase %d&raquo; Corrente Attualmente installato Output Debug: Elimina Cache Directory Descrizione Svuota Cache Errore: La versione di PHP che hai &egrave; configurata con safe mode abilitato. Devi disabilitare safe mode affinch&eacute; Gallery funzioni. Errore: la direttiva __FILE__ di PHP non funziona correttamente. Inoltra una richiesta di supporto all'amministratore del tuo webserver o nei forum di Gallery. Anche se ci sono errori, puoi comunque continuare. Oppure puoi provare a cancellare queste directory e cliccare sul link <b>Prova Ancora</b> qui sotto. Direttiva FILE Direttiva FILE supportata Errore Upload file consentito Finito Finito! Gallery crea copie temporanee di alcuni dati nell'hard disk. Questo la aiuta ad andare pi&ugrave; veloce. Per&ograve; quando fai l'aggiornamento, alcuni di questi file potrebbero essere troppo vecchi, quindi sarebbe una buona idea sbarazzarcene adesso. Gallery li creer&agrave; di nuovo quando ne avr&agrave; bisogno. Integrit&agrave; file di Gallery Gallery: <strong>le tue foto</strong> sul <strong>tuo sito</strong> Vai Vai alla mia Gallery! Se usi Apache, crea un file chiamato .htaccess nella directory principale di Gallery con il seguente contenuto: Per procedere nell'installazione, dobbiamo verificare che tu sia davvero chi dici di essere. Quando hai fatto l'installazione, hai inserito una password che &egrave; stata scritta nel file config.php. Inseriscila adesso. Guarda nel file config.php se non ti ricordi cosa hai inserito. Manifest mancante o non accessibile. Dimensione massima per il POST Dimensione massima per l'upload Limite memoria File Mancanti (%d) File Modificati (%d) MySQL Nome Nuovo Nuova Versione Nota: Stai eseguendo una versione CVS di Gallery, quindi file rimossi di recente potrebbero comparire qui. Puoi tranquillamente ignorarli. File vecchi (%d) Una volta che l'aggiornamento sar&agrave; iniziato, sii paziente. Se annulli o ricarichi la pagina, potresti interferire con il processo di aggiornamento. Altro Versione PHP Password: PostgreSQL Ricontrolla config.php Ripeti questa fase Obbligatorio Safe Mode Safe mode disabilitata Seleziona Lingua: Salta l'Aggiornamento e Continua con la Fase %d&raquo; Qualcosa &egrave; andato storto quando si &egrave; tentato l'aggiornamento del modulo core. Nei riquadri qui sotto puoi trovare qualche informazione di debug. Riportale nei %sGallery Forums%s e ti aiuteremo a capire qual &egrave; il problema. Stack Trace: Ricomincia da Capo OK Controlli del Sistema Test saltato a causa di altri errori. Il Modulo Core di Gallery &egrave; il cuore dell'applicazione Gallery. Puoi aggiornare gli altri moduli usando l'interfaccia Amministrazione Sito, ma questo modulo deve essere gestito separatamente affich&eacute; l'aggiornamento vada liscio. I seguenti moduli possono essere aggiornati automaticamente. Se scegli di non aggiornarli adesso, potresti riscontrare problemi con la tua Gallery. Puoi sempre aggiornarli o disattivarli nella pagina Amministrazione Sito, oppure ritornare a questa pagina pi&ugrave; tardi, cos&igrave; le decisioni che prendi qui non sono permanenti. Questi file non fanno pi&ugrave; parte di Gallery. Probabilmente non creeranno alcun problema ma sarebbe una buona idea quella di cancellarli e tenere pulita l'installazione. Prova Ancora Impossibile compiere la transazione nel database Impossibile ottenere la lista dei moduli Impossibile caricare il modulo %s Impossibile aggiornare il modulo %s Impossibile scrivere in config.php nella directory di %s. Modifica i suoi permessi. Sconosciuto Aggiornamento completato al %d%% Aggiornamento Core Aggiornamento Moduli Aggiorna Altri Moduli Aggiorna Altri Moduli Aggiorna Moduli  Stato Aggiornamento Fasi Aggiornamento Modulo Core di Gallery aggiornato con successo. Modulo %s aggiornato con successo. Help Upgrader L'aggiornamento di Gallery 2 necessita di %d fasi. Questo strumento di aggiornamento ti guider&agrave; attraverso queste fasi e ti dar&agrave; assistenza lungo il cammino se ci sar&agrave; bisogno di ulteriori passi. Leggi il %sFile di Help%s prima di continuare. Aggiornamento del Modulo Core di Gallery Warning Warning: La funzione exec() &egrave; disabilitata in php dal parametro <b>disabled_functions</b> di php.ini. Non sarai in grado di utilizzare moduli che necessitano di binari esterni (ad es. ImageMagick, NetPBM o Ffmpeg). Questo pu&ograve; essere configurato solo a livello di server, quindi dovrai cambiarlo nel file php.ini globale. Warning: La funzione set_time_limit() &egrave; disabilitata in php dal parametro <b>disabled_functions</b> di php.ini. Gallery pu&ograve; funzionare comunque, ma non in maniera affidabile. Ogni operazione che richieder&agrave; pi&ugrave; di %d secondi verr&agrave; interrotta (e in alcuni casi ti ritorner&agrave; una pagina bianca) col rischio di danneggiare i dati. Warning: il tuo PHP &egrave; configurato per non permettere gli upload di file (parametro <b>file_uploads</b> in php.ini). Dovrai attivare questa opzione se vuoi fare l'upload di file in Gallery con un browser. Warning: Il tuo PHP &egrave; configurato per limitare la memoria a %sb (parametro <b>memory_limit</b> in php.ini). Dovresti aumentare questo limite ad almeno <b>%sMB</b> affinch&eacute; Gallery lavori correttamente. Warning: Il tuo PHP &egrave; configurato in modo da limitare i dati di post ad un massimo di %sb (parametro <b>post_max_size</b> in php.ini). Dovresti aumentare questo limite per permettere l'upload di file pi&ugrave; grandi. Warning: Il tuo PHP &egrave; configurato in modo da limitare l'upload ad un massimo di %sb (parametro <b>upload_max_filesize</b> in php.ini). Dovresti aumentare questo limite per permettere l'upload di file pi&ugrave; grandi. Warning: Il tuo PHP &egrave; configurato con ze1_compatibility_mode di Zend che potrebbe causare il crash di PHP. Clicca <a href="%s">qui</a> per fare un test del PHP. Se vedi "SUCCESS" allora il tuo PHP va bene. Se ottieni un errore allora devi disattivare ze1_compatibility_mode prima di procedere. Abbiamo ripulito con successo le directory della cache. Non siamo stati in grado di ripulire le seguenti directory di cache. Questo probabilmente va bene, ma se riscontri qualche comportamento strano, dovresti provare a cancellare queste directory manualmente. Non c'&egrave; alcun rischio a cancellarle in qualsiasi momento. Abbiamo aggiornano con successo il Modulo Core di Gallery. Benvenuto Benvenuto nell'Aggiornamento di Gallery Puoi fare <i>chmod 666 config.php</i> per mettere a posto la cosa. Il Modulo Core della tua Gallery &egrave; aggiornato! Il tuo config.php sembra utilizzare la vecchia gestione del supporto ai siti multipli. Vedi il %sFile di Help%s per le istruzioni su come aggiornare la configurazione prima di procedere. Compatibility mode di Zend exec() concesso mysqldump -u%s -p<i>LaTuaPassword</i> --opt %s > %s.sql nessun limite pg_dump --format=t %s > %s.sql set_time_limit() concesso 