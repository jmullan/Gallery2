��    �      ,  �   <      �
     �
               =  5   ]     �     �     �     �     �     �               #     1     ?     K  �   W  �      �   �  u   R  �   �  �   c     �          '     .     C  	   R    \     b  F   y     �     �     �  R   �  p   F  �   �  �   �  �   q  !   �           2     F     S     f     �     �     �     �     �  t   �  �   )     �  }   �     x     ~     �      �  	   �     �     �     �       	             +  +   <  �   h     0  
   =     H     f     n     �  !   �  �   �  �   �     `     f    m     ~  	   �     �  %   �     �     �  $        A     ^     z     �  S   �               +     8  *   F  #   q  "   �     �  �   �     �  !   �     �     �  (  �    !  M  "  �   e#  �   /$  �   �$  �   �%  4   }&     �&     �&  3   �&  G   '  '   V'  �   ~'  l   (  �   |(  �   )     �)     �)     �)     *     *     2*  �  >*  "   �+     �+  #   �+  $   #,  :   H,     �,     �,  %   �,     �,     �,     �,     -     -     5-     F-     V-     _-  �   n-  �   U.  �   /  e   �/  �   0  �   �0     31     G1     g1     t1     �1  	   �1  >  �1     �2  J   3     Z3     _3     o3  R   �3  f   �3    H4  �   ]5  �   ,6  )   �6     �6     �6     7      7  %   <7     b7     ~7     �7     �7     �7  �   �7  �   ?8     "9  |   :9     �9     �9     �9  "   �9  
   :     :     5:     I:     _:     k:     x:     �:  :   �:  �   �:     �;     �;      �;     �;  "   �;     <  1   -<  �   _<  �   0=     �=     �=    �=     ?     "?     1?  !   Q?      s?     �?     �?     �?     �?  "   @     '@  `   G@  	   �@     �@     �@     �@  5   �@  *   5A  '   `A     �A  �   �A     �B  &   �B     �B     �B  E  �B  �   ?D  >  2E  �   qF  �   WG  �   %H  �   �H  5   �I     �I  &   	J  :   0J  _   kJ  (   �J  �   �J  b   �K  �   �K  �   �L     \M     xM     �M     �M     �M  
   �M     )   M                   U   |   
       <      B       *                   p   K   h       Q       �       !       r          9           "   >                {   @      I       5       =   �   G   0   L       c   z   '       S      g   q   ]   J   ^       Y   ?   4   P   Z          F   8          3          b       R   l      %   	   6      s      o             a   e   O   y      \       i             k      m   +   (       C                 1   T              u      x   X   d      $   [   7   V              #   j   n   W       w      /   &   :   `   v          t      f   D       ;       ,   _   -   E   N   .   ~       2   H          A   }   �        %s module needs configuration (un)check all <b>Error:</b> invalid password. <b>Error:</b> missing password. An error occurred while upgrading Gallery Core Module Authenticate Authenticate Me Authentication successful! Begin Upgrade Config.php upgrade Continue to Step %d&raquo; Current Currently installed Debug Output: Delete Caches Description Empty Cache Error: Gallery 2 requires PHP version 4.3.0 or newer or 5.0.4 or newer. You have PHP version %s installed. Contact your webserver administrator to request an upgrade, available at the %sPHP website%s. Error: Some files and or directories in your storage directory are not writeable by the webserver user. Run chown -R webserverUser %s OR run chmod -R 777 %s. Error: Your PHP is configured without support for %sPerl Compatible Regular Expressions%s. You must enable these functions before Gallery will run. Error: Your version of PHP is configured with safe mode enabled.  You must disable safe mode before Gallery will run. Error: your PHP __FILE__ directive is not functioning correctly. Please file a support request with your webserver administrator or in the Gallery forums. Even though there were errors, you can still continue.  Or, you can try deleting these directories yourself and then click the <b>Try Again</b> link below. FILE Directive FILE directive supported Failed File uploads allowed Finish Upgrade Finished! Gallery creates temporary copies of some of your data on your hard drive.  This helps it to run faster.  But when you upgrade, some of these files might be out of date so it's a good idea to get rid of them now.  Gallery will create them again as it needs them. Gallery file integrity Gallery: <strong>your photos</strong> on <strong>your website</strong> Go Go to my Gallery! Go to the Gallery 2 Installer If you actually want to run the Gallery 2 installer, please follow the link below. If you are using Apache, create a file named .htaccess in the main Gallery directory with the following content: If you have a busy site, consider putting your Gallery in maintenance mode. This gives visitors a message that the site is temporarily offline, rather than showing everybody this upgrade page. Edit your config.php file to activate maintenance mode. If you want to upgrade from Gallery 1, you first need to install Gallery 2 and then use the import module to import your data from Gallery 1. Please follow the link below to install Gallery 2. If you've lost your config.php file when replacing the Gallery 2 files in the preparation for this upgrade, please restore it and try again. Manifest missing or inaccessible. Maximum POST size Maximum upload size Memory limit Missing files (%d) Missing or invalid config.php Modified files (%d) Module Name New New version Note: You're running Gallery from SVN, so recently removed files may appear here.  It might be safe to ignore these. Note: You're running Gallery from SVN, so some modified files are to be expected.  You can probably ignore these, but to be safe you should make sure that you do 'svn update' before continuing. Old files (%d) Once the upgrade has begun, please be patient.  If you cancel or reload the page, you may interfere with the upgrade process. Other Output buffering disabled PHP Version PHP version >= 4.3.0 or >= 5.0.4 Password: Recheck config.php Redo this step Regular expressions Required Safe Mode Safe mode disabled Select Language: Skip Upgrade and Continue to Step %d&raquo; Something went wrong when we tried to upgrade the core module.  In the boxes below you can find some debug information.  Report this in the %sGallery Forums%s and we'll help you diagnose the problem. Stack Trace: Start Over Storage Directory Permissions Success Successfully cleaned caches. System Checks Test skipped due to other errors. The Gallery Core Module is the heart of the Gallery application.  You can upgrade most other modules using the Site Administration interface, but this module must be handled separately in order for the upgrade to go smoothly. The installed version is newer than the version you are trying to upgrade to. You cannot downgrade G2. Please replace the gallery2 files with files from the currently installed version or later. Theme Themes These files are no longer part of Gallery. They probably won't cause any problems but it is a good idea to remove them to keep your install clean.  Gallery can't remove these files for you, but you can download and run %s in your gallery2 directory to delete them for you. Translation support Try Again Unable to clear the page cache Unable to commit database transaction Unable to get the module list Unable to get the theme list Unable to initialize Gallery session Unable to load the %s module Unable to load the %s theme Unable to upgrade the %s module Unable to upgrade the %s theme Unable to write to config.php in your %s directory.  Please change its permissions. Unknown Upgrade %d%% complete Upgrade Core Upgrade Steps Upgraded Gallery Core Module successfully. Upgraded the %s module successfully Upgraded the %s theme successfully Upgrader Help Upgrading Gallery 2 requires %d steps. This upgrade tool will guide you through these steps and provide assistance along the way if additional steps are required. Please read the %sHelp File%s before proceeding. Upgrading modules Upgrading the Gallery Core Module Upgrading themes Warning Warning: The exec() function is disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini. You won't be able to use modules that require external binaries (e.g. ImageMagick, NetPBM or Ffmpeg). This can only be set server-wide, so you will need to change it in the global php.ini. Warning: The putenv() function is disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini.  Gallery can function with this setting, but on some rare systems Gallery will be unable to run in other languages than the system language and English. Warning: The set_time_limit() function is disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini.  Gallery can function with this setting, but it will not operate reliably.  Any operation that takes longer than %d seconds will fail (and in some cases just return a blank page) possibly leading to data corruption. Warning: Your PHP is configured not to allow file uploads (<b>file_uploads</b> parameter in php.ini). You will need to enable this option if you want to upload files to your Gallery with a web browser. Warning: Your PHP is configured to limit the memory to %sb (<b>memory_limit</b> parameter in php.ini). You should raise this limit to at least <b>%sMB</b> for proper Gallery operation. Warning: Your PHP is configured to limit the post data to a maximum of %sb (<b>post_max_size</b> parameter in php.ini). You should raise this limit to allow uploading bigger files. We were unable to clean the following cache directories.  This is probably ok, but if you notice any weird behaviour, you should try to delete these directories yourself.  It's perfectly safe to get rid of them at any time. We've successfully upgraded the Gallery Core Module. Welcome Welcome to the Gallery Upgrader You can do <i>chmod 666 config.php</i> to fix this. You tried to run the upgrade process but a valid config.php is missing. Your Gallery Core Module is up to date! Your PHP is missing the function %sbind_textdomain_codeset%s. This means Gallery may display extended characters for some languages incorrectly. Your PHP is missing the function %sdngettext%s. This means Gallery will be unable to translate plural forms. Your config.php appears to use the old form of multisite support.  Please see the %sHelp File%s for instructions to update your configuration before proceeding. Your webserver does not support localization. To enable support for additional languages please instruct your system administrator to reconfigure PHP with the %sgettext%s option enabled. Zend compatibility mode exec() allowed no limit putenv() allowed set_time_limit() allowed this script Project-Id-Version: Gallery: Upgrader 2.3
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2006-12-20 09:58-0800
PO-Revision-Date: 2006-05-22 15:45+0200
Last-Translator: 
Language-Team:  <eu@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: KBabel 1.11.2
Plural-Forms: nplurals=2; plural=(n != 1);
 %s moduloak konfiguraketa behar du (des)markatu denak <b> Errorea:</b>okerreko pasahitza. <b> Errorea:</b> pasahitza falta da. errorea gertatu da Galeria muin modulua bertsio berritzean Egiaztapena Egiaztatu iezadazu Autentifikazioa behar bezala egin da! Bertsio berritzea hasi Config.php bertsio berritu Jarraitu %d Urratsera&raquo; Unekoa Dagoeneko instalaturik Arazpen Irteera: Katxeak Ezabatu Azalpena Katxea Garbitu Errorea: Gallery 2 PHP 4.3.0 bertsio edo berriagoa edo 5.0.4 edo berriagoa behar du.Zuk PHP %s bertsioa duzu instalaturik. Harremanetan ipini zerbitzari kudeatzailearekin %sPGP webgunean%s eskuragarri dagoen eguneraketa eskatzeko. Errorea: Zure biltegiratze direktorioko zenbait direktorio eta fitxategi ez dira web zerbitzari erabiltzaileaz idazgarriak. chown -R WebErabiltzailea %s edo chmod -R 777 %s abiarazi. Errorea: Zure PHP-a %sPerl bateragarri diren espresio erregular%s onarpenik gabe konfiguraturik dago. Funtzio hau gaitu behar duzu Gallery abiarazi ahal izateko. Errorea: Zure PHP modu segurua gaiturik du. Modu segurua ezgaitu egin behar duzu Gallery erabiltzeko. Errorea: PHP __FILE__ direktiba ez da behar bezala funtzionatzen ari. Mesedez bete zure web kudeatzailearekin batera Gallery foroan eskaera bat. Nahiz eta erroreak aurkitu, aurrera jarraitu dezakezu.  Edo, direktorio hauek eskuz ezabatu eta <b>Berriz Saiatu</b> lotura klikatu dezakezu. FITXATEGI Direktiba FITXATEGI direktiba onartzen da Huts egin du Fitxategi igoera gaiturik Bertsio berritzea amaitu Amaituta! Gallery-k zure datu batzuen aldiroko kopiak gordetzen ditu disko gogorrean. Honek azkarragoa izaten laguntzen du.  Baina bertsio berritzea, fitxategi hauetako batzuek zaharkiturik geratu zitezkeen beraz ideia ona da fitxategi horiek orain berriz sortzea. Gallery-k fitxategi horiek behar dituenean berriz sortuko ditu. Gallery fitxategi integritatea Galeria: <strong>zure argazkiak </strong> -<strong>zure webgunean</strong> Joan Joan Galeriara! Joan Gallery 2 instalatzailera Orain Gallery 2 instalatzailea abiarazi nahi ezkero, beheko lotura jarraitu ezazu. Apache erabiltzen ari bazara .htaccess izeneko fitxategi bat sortu Galeria direktorioan eduki honekin: Trafiko handiko gune bat baduzu, Galeria mantenu moduan ipintzeko aukeraz pentsa ezazu. Honek bisitariari gune aldi batarako itxita dagoela dioen orrialde bat bistaratzen dio eguneraketa orrialdea bistarazi beharrean. Zure config.php fitxategia editatu mantenu modua gaitzeko. Gallery 1-etik eguneratu nahi izan ezkero, lehenik Gallery 2 instalatu ezazu eta gero inportatze modulua erabili Gallery 1-etik datuak inportatzeko.Mesedez jarraitu behekaldeko lotura Gallery 2 instalatzeko Eguneraketa honetarako Gallery 2 fitxategiak ordezkatzean config.php fitxategia ezabatu baduzu, berreskuratu ezazu eta berriz saia zaitez. Manifestua falta da edo ez da eskuragarri Gehienezko MEZU tamaina Gehienezko igoera tamaina Memoria muga Fitxategiak falta dira (%d) config.php falta da edo baliogabea da Aldatutako fitxategiak (%d) Modulua Izena Berria Bertsio berria Oharra: Zu SVN-ko Gallery erabiltzen ari zara, beraz azken aldian ezabaturiko fitxategi batzu agertu daitezke. Abisuari kasu ez egitea segurua izan daiteke. Oharra: SVN-ko Gallery bertsioa erabiltzen ari zara, beraz zenbait fitxategi aldatu izana posible da. Ziurrenik alde batetara utz ditzakezu baina aurrera jarraitu aurretik <b>svn update</b> egin duzula ziurtatu beharko zenuke. Fitxategi zaharrak (%d) Bein bertsio berritzea hasi dela, mesedez itxoin.  Orrialdea utzi edo freskatuz gero bertsio berritze prozesua apur daiteke. Bestelakoak Irteera buferra ezgaiturik PHP Bertsioa PHP bertsioa >= 4.3.0 edo >= 5.0.4 Pasahitza: Config.php berriz egiaztatu Urrats hau berregin Espresio erregularrak Beharrezkoa Modu Segurua Modu segurua ezgaiturik Hizkuntza Hautatu: Saltatu Bertsio berritzea eta Jarraitu %d Urratsera&raquo; Zerbait oker atera da muin modulua bertsio berritzen saiatzean.  Azpiko kutxetan arazpen informazioa emango zaizu.  Honen berri eman %sGallery Foroetan%s eta arazoa aurkitzen lagunduko zaitugu. Aztarna Pilaketa : Berriz Hasi Biltegiratze Direktorio Baimenak Behar bezala egin da Katxeak behar bezala garbitu dira. Sistema Egiaztapenak Proba beste errore batzugatik alde batetara utzia Gallery muin modulua galeria aplikazioaren bihotza da. Beste edozein modulu Gune Kudeaketa interfazearen bidez egunera dezakezu, baina modulu hau beste alde batetik kudeatu behar da eguneraketa leunki egiteko Instalatutako bertsioa bertsio berritzen saiatzen ari zaren bertsioa baino berriagoa da. Mesedez gallery 2 fitxategiak orain instalaturiko bertsioko fitxategiez edo berriagoz ordezkatu. Gaia Gaiak Fitxategi hauek ez dira hemendik aurrera Gallery-ren zati.  Ziurrenik ez dute arazorik sortuko baina ideia ona izaten da ezabatzea instalazio garbi bat mantentzeko. Gallery2-k ezin ditu fitxategi hauek ezabatu baina %s deskargatu eta gallery2 direktorioan abiaraziaz ezabatuko dira. Itzulpen onarpena Saiatu berriro Ezin da katxe orrialdea garbitu Ezin da datubase transakzioa egin Ezin da modulu zerrenda eskuratu Ezin da gai zerrenda eskuratu Ezin da Gallery saioa abiarazi Ezin da %s modulua kargatu Ezin da %s gaia kargatu Ezin da %s modulua bertsio berritu Ezin da %s gaia bertsio berritu Ezin da zure %s direktorioko config.php fitxategian idatzi.  Mesedez baimenak aldatu iezazkiozu. Ezezaguna %d%% Bertsio berritzea osatua Muina Bertsio berritu Bertsio beritze Urratsak Galeria muin modulua behar bezala bertsio berritu da. %s modulua behar bezala bertsio berritu da %s gaia behar bezala bertsio berritu da Bertsio berritzaile Laguntza Gallery 2 bertsio berritzeko %d urrats bete behar dira. Bertsio berritze tresna honek urrats orrialdeen zehar gidatu eta urrats gehigarririk egin beharko balitz laguntza ematen saiatuko da.  Irakurri %sLaguntza Fitxategia%s jarraitu aurretik. Moduloak bertsio berritzen Galeria Muin Modulua Bertsio berritzeb Gaiak bertsio berritzen Abisua Abisua: exec() funtzioa ezgaiturik dago zure PHP konfigurazioan php.ini fitxategian <b>disabled_functions</b> parametroaz.  Kanpo bitarrik behar duten modulurik (adib ImageMagick, NetPBM edo Ffmpeg) erabili. Hau zerbitzari aldean bakarrik ezarri daiteke, beraz erabili nahi izanez gero php.ini orokorrean aldatu beharko duzu. Abisua: zure putenv()  funtzioa ezgaiturik dago php.ini fitxategiko <b>disabled_functions</b> parametroaren bidez.  Gallery-k ezarpena hauez funtziona dezake baina sistema arraro batzuetan ezin izango da abiarazi ingelesaz beste hizkuntzarik. Abisua: zure set_time_limit() funtzioa ez gaiturik dago php.ini fitxategiko <b>disabled_functions</b> parametroaren bidez.  Gallery-k ezarpena hauez funtziona dezake baina ez behar bezain ondo. %d segundutik gora behar duen edozein eskarik huts egin dezake (kasu batzuetan orri zuri bat itzuliaz) datu apurtze aukeraz. Abisua: Zure PHP fitxategi igoerak ez onartzeko konfiguraturik dago (php.ini fitxategian <b>file_uploads</b> parametroan bidez). Aukera hau gaitu beharko duzu galeriara web nabigatzaile baten bidez argazkiak igo nahi izan ezkero. Abisua: PHP memoria erabilera %sb-ra mugaturik konfiguraturik dago php.ini (<b>memory_limit</b> parametroaz. Muga hau behintzat <b>%sMB</b>-ra handitu beharko zenuke Gallery-k behar bezala funtziona dezan. Abisua: PHP mezu tamaina %sb-ra mugatzeko konfiguraturik dago (php.ini fitxategiko <b>post_max_size</b> parametroaz).  Muga hau handitu beharko zenuke fitxategi handiagoak onartzeko. Ezin dira hurrengo direktorioa hauek garbitu.  Hau ziurrenik ondo dago, baina hauen inguruan arazorik aurkitu ezkero direktorio horiek eskuz ezabatzen saia zaitezke. Guztiz ziurra da ezabatu gabe uztea edo edozein momentuan ezabatzea. Galeria Muin Modulua behar bezala bertsio berritu da. Ongi etorri Ongi etorri Galeria Bertsio berritzera <i>chmod 666 config.php</i> egin dezakezu hau konpontzeko. Bertsio berritze prozesua abiarazten saiatu zara baina baliozko config.php fitxategia falta da. Galeria Muina Modulua eguneraturik dago! Zure PHP-an %sbind_textdomain_codeset%s funtzioa falta da. Honen ondorioz Gallery-k okerreko ikurrak bistaraziko ditu zenbait hizkuntzetako karaktere gehigarrietan. Zure PHP-an %sdngettext%s funtzioa falta da. Honen ondorioz Gallery-k ezingo ditu pluralak itzuli. Zure config.php fitxategiak une anitzeko onarpen zaharkitu erabiltzen duela dirudi. %sLaguntza fitxategia%s begiratu eguneraketa argibideentzat aurrera jarraitu aurretik. Zure web zerbitzariak ez du lokalizaziorik onartzen. Hizkuntza gehigarrien onarpena gaitzeko eskatu sistema kudeatzaileari PHP  %sgettext%s aukera gaiturik duela birkonfiguratzeko. Zend bateragarritasun modua exec() onarturik mugarik gabe putenv() onarturik set_time_limit() onarturik skript hau 