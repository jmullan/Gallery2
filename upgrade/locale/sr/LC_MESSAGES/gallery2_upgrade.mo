��    l      |  �   �      0	     1	     O	     ]	     }	  5   �	     �	     �	     �	     
     
     ,
     G
     O
     c
     q
     }
  �   �
  u   '  �   �  �   8     �     �     �       	       "     (  F   ?     �     �     �  R   �  p     �   }  �   >  !   �     �     �                3     Q     e     l     q     u     �  }   �            	         *     =     L     U     h  +   y  �   �     m  
   z     �     �     �  !   �  �   �  �   �     �     �  	   �  %   �     �     �     �          1     Q  S   p     �     �     �     �  *   �  #   (  "   L     o  �   }     Q  !   c     �     �  (  �  M  �  �     �   �  �   �  �   M  4   -     b     j  3   �  G   �  '     �   .     �     �     �     �  �        �!     �!  !   �!  "   �!  8   "     K"     ^"     v"     �"     �"     �"     �"     �"     �"     #     #  �   (#  �   �#  �   x$  �   %     �%     �%  
   �%     �%  
   &  &  &     :'  Q   W'     �'     �'  %   �'  a   �'  x   L(  �   �(  �   �)     O*     o*     �*     �*     �*  %   �*     �*     +     +     "+     '+     4+  �   H+     �+     �+     �+     �+     ,     ,     ,     8,  2   I,    |,     -     �-  $   �-     �-     �-  (   �-  �   .  �   �.     �/     �/     �/  2   �/  #   �/  $   0     80     W0  !   w0  "   �0  h   �0  	   %1     /1     M1     `1  4   s1      �1  !   �1     �1  �   	2     �2  &   3     +3  
   ?3  f  J3  g  �4  �   6  �   �6  �   �7  �   �8  3   �9     �9  #   �9  P   �9  Z   M:  <   �:  �   �:     �;     �;     �;     �;         $   :       h   &   A   a   #          ;                 Y          <   E   b      @       (   F       _   O   U          ^      "       -      f   0   M             Q   7   +       D   k       9   G      T   *   )      2       c   L   N      J              X       [      V      6           K   8   	   %       5   Z   >             g      \   B   j   d   1       .           /          S      ]   
       =               ?           e   I       R       3       4   C   `                !      '   l                     i              H   ,           P   W    %s module needs configuration (un)check all <b>Error:</b> invalid password. <b>Error:</b> missing password. An error occurred while upgrading Gallery Core Module Authenticate Authenticate Me Authentication successful! Begin Upgrade Config.php upgrade Continue to Step %d&raquo; Current Currently installed Debug Output: Description Empty Cache Error: Some files and or directories in your storage directory are not writeable by the webserver user. Run chown -R webserverUser %s OR run chmod -R 777 %s. Error: Your version of PHP is configured with safe mode enabled.  You must disable safe mode before Gallery will run. Error: your PHP __FILE__ directive is not functioning correctly. Please file a support request with your webserver administrator or in the Gallery forums. Even though there were errors, you can still continue.  Or, you can try deleting these directories yourself and then click the <b>Try Again</b> link below. FILE Directive FILE directive supported Failed File uploads allowed Finished! Gallery creates temporary copies of some of your data on your hard drive.  This helps it to run faster.  But when you upgrade, some of these files might be out of date so it's a good idea to get rid of them now.  Gallery will create them again as it needs them. Gallery file integrity Gallery: <strong>your photos</strong> on <strong>your website</strong> Go Go to my Gallery! Go to the Gallery 2 Installer If you actually want to run the Gallery 2 installer, please follow the link below. If you are using Apache, create a file named .htaccess in the main Gallery directory with the following content: If you want to upgrade from Gallery 1, you first need to install Gallery 2 and then use the import module to import your data from Gallery 1. Please follow the link below to install Gallery 2. If you've lost your config.php file when replacing the Gallery 2 files in the preparation for this upgrade, please restore it and try again. Manifest missing or inaccessible. Maximum POST size Maximum upload size Memory limit Missing files (%d) Missing or invalid config.php Modified files (%d) Module Name New New version Old files (%d) Once the upgrade has begun, please be patient.  If you cancel or reload the page, you may interfere with the upgrade process. Other PHP Version Password: Recheck config.php Redo this step Required Safe mode disabled Select Language: Skip Upgrade and Continue to Step %d&raquo; Something went wrong when we tried to upgrade the core module.  In the boxes below you can find some debug information.  Report this in the %sGallery Forums%s and we'll help you diagnose the problem. Stack Trace: Start Over Storage Directory Permissions Success System Checks Test skipped due to other errors. The Gallery Core Module is the heart of the Gallery application.  You can upgrade most other modules using the Site Administration interface, but this module must be handled separately in order for the upgrade to go smoothly. The installed version is newer than the version you are trying to upgrade to. You cannot downgrade G2. Please replace the gallery2 files with files from the currently installed version or later. Theme Themes Try Again Unable to commit database transaction Unable to get the module list Unable to get the theme list Unable to load the %s module Unable to load the %s theme Unable to upgrade the %s module Unable to upgrade the %s theme Unable to write to config.php in your %s directory.  Please change its permissions. Unknown Upgrade %d%% complete Upgrade Core Upgrade Steps Upgraded Gallery Core Module successfully. Upgraded the %s module successfully Upgraded the %s theme successfully Upgrader Help Upgrading Gallery 2 requires %d steps. This upgrade tool will guide you through these steps and provide assistance along the way if additional steps are required. Please read the %sHelp File%s before proceeding. Upgrading modules Upgrading the Gallery Core Module Upgrading themes Warning Warning: The exec() function is disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini. You won't be able to use modules that require external binaries (e.g. ImageMagick, NetPBM or Ffmpeg). This can only be set server-wide, so you will need to change it in the global php.ini. Warning: The set_time_limit() function is disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini.  Gallery can function with this setting, but it will not operate reliably.  Any operation that takes longer than %d seconds will fail (and in some cases just return a blank page) possibly leading to data corruption. Warning: Your PHP is configured not to allow file uploads (<b>file_uploads</b> parameter in php.ini). You will need to enable this option if you want to upload files to your Gallery with a web browser. Warning: Your PHP is configured to limit the memory to %sb (<b>memory_limit</b> parameter in php.ini). You should raise this limit to at least <b>%sMB</b> for proper Gallery operation. Warning: Your PHP is configured to limit the post data to a maximum of %sb (<b>post_max_size</b> parameter in php.ini). You should raise this limit to allow uploading bigger files. We were unable to clean the following cache directories.  This is probably ok, but if you notice any weird behaviour, you should try to delete these directories yourself.  It's perfectly safe to get rid of them at any time. We've successfully upgraded the Gallery Core Module. Welcome Welcome to the Gallery Upgrader You can do <i>chmod 666 config.php</i> to fix this. You tried to run the upgrade process but a valid config.php is missing. Your Gallery Core Module is up to date! Your config.php appears to use the old form of multisite support.  Please see the %sHelp File%s for instructions to update your configuration before proceeding. Zend compatibility mode exec() allowed no limit set_time_limit() allowed Project-Id-Version: Gallery: Upgrader 2.2
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2006-12-20 09:53-0800
PO-Revision-Date: 2005-09-07 12:46+0200
Last-Translator: Jozef Selesi <selesi@gmail.com>
Language-Team: Srpski <en@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: KBabel 1.10
 Modul %s mora da se podesi Obeleži/isključi sve <b>Greška:</b> netačna lozinka. <b>Greška:</b> nedostaje lozinka. Desila se greška prilikom nadogradnje modula sa jezgrom Provera identiteta Proverite moj identitet Provera identiteta uspešna! Počni nadogradnju Nadogradnja config.php Pređi na %d. korak&raquo; Trenutna Trenutno instalirano Izlaz za otklanjanje grešaka: Opis Isprazni keš Greška: Neke datoteke ili direktorijumi u vašem direktorijumu za skladištenje ne mogu biti menjani od strane web server korisnika. Pokrenite 'chown -R webserverUser %s' ili izvršite 'chmod -R 777 %s'. Greška: Vaša verzija PHP-a je konfigurisana sa uključenim safe mode-om. Safe mode mora biti isključen pre pokretanja Galerije. Greška: __FILE__ direktiva vašeg PHP-a ne funkcioniše pravilno. Molimo vas da potražite pomoć od administratora vašeg web servera ili na Galerijinim forumima. Iako je bilo problema, možete nastaviti. Ili, možete pokušati da izbrišete ove direktorijume i zatim kliknuti na link <b>Pokušaj ponovo</b> ispod. FILE direktiva FILE direktiva je podržana Neuspešno Prenos datoteka je dozvoljen Završeno! Galerija na vašem hard disku pravi privremene kopije nekih od vaših podataka. Ovo joj omogućuje da brže radi. Ali, kada izvršite nadogradnju, neke od ovih datoteka će možda biti zastarele, pa je dobra ideja izbrisati ih sada. Galerija će ih ponovo napraviti kada joj budu bile potrebne. Integritet datoteka Galerije Galerija: <strong>vaše fotografije</strong> na <strong>vašem web sajtu</strong> Kreni Idi u moju Galeriju! Pokreni proces instalacije Galerije 2 Ako u stvari želite da pokrene proces instalacije Galerije 2, kliknite na ispod navedenu adresu. Ako koristite Apache, napravite datoteku sa nazivom .htaccess u glavom direktorijumu Galerije 2 sa sledećim sadržajem: Ako želite da nadogradite Galeriju 1, prvo treba da instalirate Galeriju 2, a zatim da iskoristite modul za prenos da biste preneli vaše podatke iz Galerije 1. Molimo vas da kliknete na ispod datu adresu da instalirate Galeriju 2. Ako ste izgubili vašu config.php datoteku kada ste u toku pripreme za nadogradnju zamenjivali Galerijine datoteke, molimo vas da je vratite i pokušate ponovo. Manifest fali ili je nedostupan Maksimalna POST veličina Maksimalna veličina prenosa Ograničenje memorije Nedostajuće datoteke (%d) Nedostaje config.php ili je neipravan Promenjene datoteke (%d) Modul Naziv Nova Nova verzija Stare datoteke (%d) Kada započne proces nadogradnje, budite strpljivi. Ako je otkažete ili ponovo učitate stranu, možete narušiti proces nadogradnje. Drugo PHP verzija Lozinka: Ponovo proveri config.php Ponovi ovaj korak Potrebno Safe mode je onemogućen Izaberite jezik: Preskoči nadogradnju i pređi na %d. korak&raquo; Nešto je pošlo naopako kad smo pokušali da nadogradimo modul sa jezgrom. U poljima ispod možete naći informacije koje će možda pomoći u otklanjanju ove greške. Prenesite ih u %sGalerijine forume%s i pomoći ćemo vam da otkrijete u čemu je problem. Stanje steka: Kreni ispočetka Prava direktorijuma za skladištenje Uspešno Provera sistema Test je preskočen zbog drugih grešaka. Modul sa jezgrom Galerije je njeno srce. Većinu drugih modula možete nadograditi pomoću interfejsa Administracije Galerije, ali ovaj modul se mora posebno nadograditi, kako bi sve prošlo u redu. Instalirana verzija je novija od one na koju želite da nadogradite. Nije moguće instalirate stariju verziju preko nove. Molimo vas da zamenite datoteke Galerije 2 trenutno instaliranom verzijom ili novijom. Izgled Izgledi Pokušaj ponovo Nije moguće potvrditi transakciju u bazi podataka Nije moguće preuzeti spisak modula Nije moguće preuzeti spisak izgleda Modul %s nije moguće učitati Izgled %s nije moguće učitati Modul %s nije moguće nadograditi Izgled %s nije moguće nadograditi Pisanje u config.php datoteku u vašem %s direktorijumu nije moguće. Molimo vas da joj promenite prava. Nepoznato Nadogradnja je %d%% završena Nadogradnja jezgra Koraci nadogradnje Modul sa jezgrom Galerije 2 je uspešno nadograđen. Modul %s je uspešno nadograđen Izgled %s je uspešno nadograđen Pomoć u vezi sa nadogradnjom Nadogradnja Galerije 2 se sastoji iz %d koraka. Proces nadogradnje će vas voditi kroz te korake i pružati vam pomoć usput ako su potrebni dodatni koraci. Molimo vas da pročitate %sUputstvo za upotrebu%s pre nego što nastavite. Nadogradnja modula Nadogradnja modula sa jezgrom Galerije Nadogradnja izgleda Upozorenje Upozorenje: Funkcija exec() je onemogućena u vašoj verziji PHP-a parametrom <b>disabled_functions</b> u datoteci php.ini. Nećete moći da koristite module kojima su potrebne spoljne binarne datoteke (npr. ImageMagick, NetPBM ili Ffmpeg). Ovo se može uraditi samo na nivou servera, pa ćete morati da promenite ovaj parametar u globalnoj php.ini datoteci. Upozorenje: Funkcija set_time_limit() je onemogućena u vašoj verziji PHP-a parametrom <b>disabled_functions</b> u php.ini datoteci. Galerija može da radi sa ovakvim podešavanjima, ali ne pouzdano. Bilo koja radnja koja traje duže od %d sekundi će biti neuspešna (a u nekim slučajevima samo prikazati praznu stranu), uz mogućnost oštećenja podataka. Upozorenje: Vaša verzija PHP-a nije podešena da omogući prenos datoteka na server (parametar <b>file_uploads</b> u php.ini). Ovu mogućnost ćete morati da uključite ako želite da web čitačem prenosite datoteke u Galeriju. Upozorenje: Vaša verzija PHP-a je konfigurisana da ograniči memoriju na %sb (parametar <b>memory_limit</b> u php.ini). Za ispravan rad Galerije, ovo ograničenje bi trebalo da podignete na bar <b>%sMB</b>. Upozorenje: Vaša verzija PHP-a je podešena da ograniči POST podatke na najviše %sb (parametar <b>post_max_size</b> u php.ini). Trebalo bi da povećate ovu vrednost da bi bio moguć prenos većih datoteka. Nismo uspeli da ispraznimo sledeće direktorijume sa kešom. Ovo verovatno ne predstavlja problem, ali ako primetite bilo kakvo čudno ponašanje, trebalo bi da pokušate sami da ih izbrišete. Sasvim je bezbedno izbrisati ih u bilo kom trenutku. Uspešno smo nadogradili modul sa jezgrom Galerije. Dobro došli Dobro došli u nadogradnju Galeriju Ako koristite Unix, možete izvršiti <i>chmod 666 config.php</i> da to uradite. Pokušali smo da pokrenemo proces nadogradnje, ali nedostaje ispravna config.php datoteka. Vaš modul sa jezgrom Galerije nije potrebno nadograđivati! Čini se da vaš config.php koristi stari način višesajtne podrške. Molimo vas da pročitate %sUputstvo za upotrebu%s da bista saznali šta treba da uradite pre nego što nastavite. Režim Zend kompatibilnosti exec() je dozvoljen nema ograničenja set_time_limit() je dozvoljen 