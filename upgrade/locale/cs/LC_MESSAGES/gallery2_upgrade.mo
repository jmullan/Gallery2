��    �      d  �   �      �     �     �     �     �  d     5   z     �     �     �  	  �     �             $   .     S     [     o     �     �     �     �  �   �  �   �  �     u   �  �   (  �   �     _     n     �     �     �  	   �    �     �  F   �           2  R   P  p   �  �     �     �   �  )   [  !   �     �     �     �     �     �               &     +     /  t   ;  �   �     r  }   �     �                +  	   L     V     i     x     �  	   �     �     �  +   �  �   �     �  
   �     �     �     �       !      �   B  �   $  �   �     �     �    �     �  	   �     �  %      "   4   !   W      y      �   $   �      �      �      !     0!     M!     m!  S   �!     �!     �!     �!     "     "  *   )"  #   T"  "   x"     �"  �   �"     }#  !   �#     �#     �#  �   �#  �   �$  �   M%  �   &  4   �&     '     '  3   ?'  G   s'  '   �'  �   �'  l   t(  �   �(  �   �)     =*     U*     d*     m*     ~*     �*  �  �*  "   [,     ~,     �,     �,  �   �,  .   S-     �-     �-     �-    �-     �.     �.     �.  $   �.     $/     1/     F/     b/     t/     �/     �/  �   �/  �   [0  �   '1  s   �1  �   62  �   �2     a3     p3     �3     �3     �3     �3    �3     �4  J   �4     95     O5  ]   m5  �   �5    P6  �   S7  j   8  &   y8  .   �8  $   �8     �8     9     9  %   99     _9     z9     �9     �9     �9  �   �9  �   #:     ;  �   /;     �;  &   �;  	   �;      <     #<     *<     H<     \<     p<  	   }<     �<     �<  6   �<  �   �<     �=     �=  &   �=     >     >     ">  -   4>  �   b>  �   ?  �   �?     �@     �@  !  �@     �A     �A     �A  $   B     :B     QB     hB     �B  .   �B     �B     �B     �B     C     8C     UC  W   rC  	   �C     �C     �C     D      D  0   2D  #   cD  $   �D     �D  �   �D     �E  !   �E     �E  
   �E  �   �E  �   �F  �   bG  �   'H  5   �H     I     I  H   <I  H   �I  *   �I  �   �I  t   �J  �   K  �   �K     nL     �L     �L     �L      �L     �L                    q      w   R   �   B   4       c   a   Q   P   J   !                      '       t   M   �      p   W                  m   L   >   C       V   "      +   s   $                0      )                 (          ,   .   F       i   1   ~               S   H   6   y   z          l       [   �   U   G          ?   �       T   @       E      r   �   /       %       v           b           \      �           �   =   ^   u             5   �   7   A   K   X               e   
             �   g   Z   3       Y   `   ;   }           _   {          #   &   :       8   2           h   �   O               	   d      |       -          x         j       N       f   I   o   <   9      D                 ]   *   k   n    %s module needs configuration (un)check all <b>Error:</b> invalid password. <b>Error:</b> missing password. <b>Reminder</b>: Now check the permissions on config.php and make sure it is not globally writeable. An error occurred while upgrading Gallery Core Module Authenticate Authenticate Me Authentication successful! Before you upgrade, we <b>strongly recommend</b> that you make a backup of your database!  If you fail to make a backup and something goes wrong, there is a strong possibility that we will not be able to help you recover your data!  Refer to the following examples: Begin Upgrade Config.php upgrade Continue to Step %d&raquo; Core Module version: %s (Gallery %s) Current Currently installed Deactivated Plugins Debug Output: Delete Caches Description Empty Cache Error: Gallery 2 requires PHP version 4.3.0 or newer or 5.0.4 or newer. You have PHP version %s installed. Contact your webserver administrator to request an upgrade, available at the %sPHP website%s. Error: Some files and or directories in your storage directory are not writeable by the webserver user. Run chown -R webserverUser %s OR run chmod -R 777 %s. Error: Your PHP is configured without support for %sPerl Compatible Regular Expressions%s. You must enable these functions before Gallery will run. Error: Your version of PHP is configured with safe mode enabled.  You must disable safe mode before Gallery will run. Error: your PHP __FILE__ directive is not functioning correctly. Please file a support request with your webserver administrator or in the Gallery forums. Even though there were errors, you can still continue.  Or, you can try deleting these directories yourself and then click the <b>Try Again</b> link below. FILE Directive FILE directive supported Failed File uploads allowed Finish Upgrade Finished! Gallery creates temporary copies of some of your data on your hard drive.  This helps it to run faster.  But when you upgrade, some of these files might be out of date so it's a good idea to get rid of them now.  Gallery will create them again as it needs them. Gallery file integrity Gallery: <strong>your photos</strong> on <strong>your website</strong> Go to my Gallery! Go to the Gallery 2 Installer If you actually want to run the Gallery 2 installer, please follow the link below. If you are using Apache, create a file named .htaccess in the main Gallery directory with the following content: If you have a busy site, consider putting your Gallery in maintenance mode. This gives visitors a message that the site is temporarily offline, rather than showing everybody this upgrade page. Edit your config.php file to activate maintenance mode. If you want to upgrade from Gallery 1, you first need to install Gallery 2 and then use the import module to import your data from Gallery 1. Please follow the link below to install Gallery 2. If you've lost your config.php file when replacing the Gallery 2 files in the preparation for this upgrade, please restore it and try again. Incompatible with this version of Gallery Manifest missing or inaccessible. Maximum POST size Maximum upload size Memory limit Missing files (%d) Missing or invalid config.php Modified files (%d) Module Name New New version Note: You're running Gallery from SVN, so recently removed files may appear here.  It might be safe to ignore these. Note: You're running Gallery from SVN, so some modified files are to be expected.  You can probably ignore these, but to be safe you should make sure that you do 'svn update' before continuing. Old files (%d) Once the upgrade has begun, please be patient.  If you cancel or reload the page, you may interfere with the upgrade process. Other Output buffering disabled PHP Version PHP version >= 4.3.0 or >= 5.0.4 Password: Recheck config.php Redo this step Regular expressions Required Safe Mode Safe mode disabled Select Language: Skip Upgrade and Continue to Step %d&raquo; Something went wrong when we tried to upgrade the core module.  In the boxes below you can find some debug information.  Report this in the %sGallery Forums%s and we'll help you diagnose the problem. Stack Trace: Start Over Storage Directory Permissions Success Successfully cleaned caches. System Checks Test skipped due to other errors. The Gallery Core Module is the heart of the Gallery application.  You can upgrade most other modules using the Site Administration interface, but this module must be handled separately in order for the upgrade to go smoothly. The following plugins were active, but they are missing or incompatible with your current version of Gallery.  They have been deactivated.  Install the latest version of these plugins to reactivate them. The installed version is newer than the version you are trying to upgrade to. You cannot downgrade G2. Please replace the gallery2 files with files from the currently installed version or later. Theme Themes These files are no longer part of Gallery. They probably won't cause any problems but it is a good idea to remove them to keep your install clean.  Gallery can't remove these files for you, but you can download and run %s in your gallery2 directory to delete them for you. Translation support Try Again Unable to clear the page cache Unable to commit database transaction Unable to deactivate the %s module Unable to deactivate the %s theme Unable to get the module list Unable to get the theme list Unable to initialize Gallery session Unable to load the %s module Unable to load the %s theme Unable to query the %s module Unable to query the %s theme Unable to upgrade the %s module Unable to upgrade the %s theme Unable to write to config.php in your %s directory.  Please change its permissions. Unknown Upgrade %d%% complete Upgrade Core Upgrade Plugins Upgrade Steps Upgraded Gallery Core Module successfully. Upgraded the %s module successfully Upgraded the %s theme successfully Upgrader Help Upgrading Gallery 2 requires %d steps. This upgrade tool will guide you through these steps and provide assistance along the way if additional steps are required. Please read the %sHelp File%s before proceeding. Upgrading modules Upgrading the Gallery Core Module Upgrading themes Warning Warning: Your PHP is configured not to allow file uploads (<b>file_uploads</b> parameter in php.ini). You will need to enable this option if you want to upload files to your Gallery with a web browser. Warning: Your PHP is configured to limit the memory to %sb (<b>memory_limit</b> parameter in php.ini). You should raise this limit to at least <b>%sMB</b> for proper Gallery operation. Warning: Your PHP is configured to limit the post data to a maximum of %sb (<b>post_max_size</b> parameter in php.ini). You should raise this limit to allow uploading bigger files. We were unable to clean the following cache directories.  This is probably ok, but if you notice any weird behaviour, you should try to delete these directories yourself.  It's perfectly safe to get rid of them at any time. We've successfully upgraded the Gallery Core Module. Welcome Welcome to the Gallery Upgrader You can do <i>chmod 666 config.php</i> to fix this. You tried to run the upgrade process but a valid config.php is missing. Your Gallery Core Module is up to date! Your PHP is missing the function %sbind_textdomain_codeset%s. This means Gallery may display extended characters for some languages incorrectly. Your PHP is missing the function %sdngettext%s. This means Gallery will be unable to translate plural forms. Your config.php appears to use the old form of multisite support.  Please see the %sHelp File%s for instructions to update your configuration before proceeding. Your webserver does not support localization. To enable support for additional languages please instruct your system administrator to reconfigure PHP with the %sgettext%s option enabled. Zend compatibility mode exec() allowed no limit putenv() allowed set_time_limit() allowed this script Project-Id-Version: Gallery: Upgrader 2.2
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2005-06-11 11:57+0200
PO-Revision-Date: 2006-12-03 23:56+0100
Last-Translator: Martin Štěpán <drewak@gmail.com>
Language-Team: Czech <cs@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);
 Modul %s potřebuje nakonfigurovat (zrušit) výběr všech <b>Chyba:</b> špatné heslo. <b>Chyba:</b> chybí heslo. <b>Nezapomeňte</b>: Nyní zkontrolujte oprávnění pro soubor config.php a ujistěte se, že není zapisovatelný pro všechny. Při aktualizaci modulu jádra došlo k chybě Autentizace Autentizovat Autentizace úspěšná! Před aktualizací <b>důrazně doporučujeme</b> provést zálohu databáze! Pokud tuto zálohu neprovedete a při aktualizaci dojde k chybě, je velmi pravděpodobné, že Vám nebudeme moci pomoci obnovit data! Můžete použít následující příklady: Začít aktualizaci Aktualizace config.php Pokračovat krokem %d&raquo; Verze jádra modulu: %s (Gallery %s) Stávající Nainstalovaná verze Deaktivované rozšíření Ladící výstup: Výmaz cache Popis Výmaz cache Chyba: Galerie 2 vyžaduje PHP verze 4.3.0 a novější nebo 5.0.4 a novější. Vaše PHP je verze %s. Kontaktujte Vašeho správce a požádejte o aktualizaci, která je dostupná na %swebu PHP%s. Chyba: Některé soubory nebo podadresáře v adresáři úložište nejsou zapisovatelné uživatelem, pod kterým je spuštěn webserver. Spusťte 'chown -R uzivatel %s', případně 'chmod -R 777 %s'. Chyba: Vaše PHP je nakonfigurováno bez podpory %sRegulárních výrazů kompatibilních s Perlem%s. Než Galerie poběží, musíte tyto funkce zapnout. Chyba: Vaše PHP je nakonfigurováno se zapnutým Safe módem. Pokud chcete používat Galerii, musíte ho vypnout. Chyba: PHP direktiva __FILE__ nefunguje správně. Prosím požádejte o podporu Vašeho administrátora nebo na fórech Galerie. Přestože se vyskytly nějaké chyby, stále můžete pokračovat. Nebo se můžete pokusit smazat tyto adresáře ručně a pak kliknout na odkaz <b>Zkusit znovu</b>. Direktiva FILE Direktiva FILE je podporována Chyba Upload souborů povolen Dokončit aktualizaci Hotovo! Galerie vytváří na disku dočasné kopie některých dat, čímž urychluje některé operace. Při aktualizaci se mohou některé z těchto souborů stát zastaralými, takže je vhodné je nyní smazat. Galerie si je znovu vytvoří, až je bude potřebovat. Integrita souborů Galerie Galerie: <strong>Vaše fotografie</strong> na <strong>Vašem webu</strong> Jdi na mojí Galerii! Jít na instalátor Galerie 2 Pokud ve skutečnosti chcete spustit instalátor Galerie 2, prosím následujte odkaz níže. Pokud používáte webový server Apache, vytvořte v hlavním adresáři Vaší Galerie soubor .htaccess s následujícím obsahem: Pokud máte velkou návštěvnost, můžete nastavit Galerii do režimu údržby. Tím se všem návštěvníkům zobrazí informace o dočasné odstávce Galerie místo této stránky pro aktualizaci. Pro aktivaci režimu údržby upravte soubor config.php. Pokud chcete aktualizovat Galerii z verze 1, musíte nejdříve nainstalovat verzi 2 a pak použít modul importu dat z Galerie verze 1. Pro instalaci Galerie 2 následujte odkaz níže. Pokud jste při nahrazování souborů Galerie 2 ztratili soubor config.php, obnovte ho a zkuste to znovu. Nekompatibilní s touto verzí Gallery Chybějící nebo nedostupný soubor Manifest. Maximální velikost POST požadavku Maximální velikost uploadu Limit paměti Chybějící soubory (%d) Chybějící nebo špatný config.php Modifikované soubory (%d) Modul Jméno Nová Nová verze Poznámka: Toto je Galerie z CVS, takže se zde mohou vyskytnout nedávno odebrané soubory. Nejspíše lze toto bez problému ignorovat. Poznámka: Toto je Galerie z CVS, která pravděpodobně obsahuje modifikované soubory. Nejspíše lze bez problému ignorovat, ale pokud si chcete být jisti že máte nejnovější verzi, můžete (než budete pokračovat) spustit 'svn update'. Staré soubory (%d) Jakmile aktualizace začne, buďte trpěliví. Pokud přerušíte nebo obnovíte načítání nějaké stránky, možná přerušíte proces aktualizace. Další Vyrovnávací paměť výstupu vypnuta Verze PHP PHP verze >= 4.3.0 nebo >= 5.0.4 Heslo: Znovu zkontrolovat config.php Opakovat tento krok Regulární výrazy Vyžadováno Safe mód Safe mód je vypnutý Vyberte jazyk: Přeskočit aktualizaci a pokračovat krokem %d&raquo; Něco špatného se stalo při aktualizaci modulu jádra. Níže můžete najít nějaké ladící informace. Můžete je zkusit předhodit ve %sFóru Galerie%s a snad Vám pomůžeme zjistit kde je problém. Trasování zásobníku: Začít znovu Oprávnění pro adresář úložište OK Cache úspěšně vymazána. Kontrola systému Zkouška přeskočena z důvodu jiných chyb. Modul jádra Galerie je srdcem této aplikace. Většinu ostatních modulů můžete zaktualizovat v administračním rozhraní, ale tento modul je nutné aktualizovat zvlášť. Následující rozšíření byly aktivní, ale ve Vámi používané verzi Gallery chybí, nebo jsou s ní nekompatibilní. Proto byly vypnuty. Pro jejich aktivaci nainstalujte nejnovější verzi těchto rozšíření. Nainstalovaná verze je novější než verze, na kterou se snažíte aktualizovat. Nelze snížit verzi G2. Prosím nahraďte soubory gallery2 nainstalovanou nebo novější verzí. Téma Témata Tyto soubory už nejsou součástí Galerie. Pravděpodobně nemohou způsobit žádné problémy, ale asi by bylo nejlepší je odstranit a zachovat tak tuto instalaci čistou. Galerie je nemůže smazat sama, ale pro jejich výmaz si můžete stáhnout a spustit %s v adresáři Galerie. Podpora překladu Zkusit znovu Nelze vymazat cache stránek Nelze commitnout transakce databáze Nelze nahrát modul %s Nelze nahrát téma %s Nelze získat seznam modulů Nelze získat seznam témat Nelze zinicializovat sezení (session) Galerie Nelze nahrát modul %s Nelze nahrát téma %s Nelze zaktualizovat modul %s Nelze zaktualizovat téma %s Nelze zaktualizovat modul %s Nelze zaktualizovat téma %s Nelze zapsat do souboru config.php v adresáři %s. Prosím změňte jeho oprávnění. Neznámý Aktualizace z %d%% kompletní Aktualizace jádra Aktualizovat rozšíření Kroky aktualizace Modul jádra Galerie úspěšně zaktualizován. Modul %s úspěšně zaktualizován Téma %s úspěšně zaktualizováno README Aktualizace Galerie 2 vyžaduje %d kroků. Tento aktualizační nástroj Vás těmito kroky provede, stejně jako případnými dalšími kroky, pokud budou potřeba. Před pokračováním si prosím přečtěte %sREADME%s. Aktualizuji moduly Aktualizace modulu jádra Galerie Aktualizuji témata Varování Varování: konfigurace Vašeho PHP nedovoluje upload souborů (parametr <b>file_uploads</b> v php.ini ). Pokud chcete do Galerie uploadovat soubory, musíte tuto možnost povolit. Varování: ve Vašem PHP je nastaveno omezení paměti na %sB (parametr <b>memory_limit</b> v php.ini). Pro bezproblémovou funkci Galerie byste měli zvýšit tento limit alespoň na <b>%sMB</b>. Varování: ve Vašem PHP je nastavena maximální velikost dat v POST požadavku na %sB (parametr <b>post_max_size</b> v php.ini). Pro upload větších souborů byste měli tento limit zvýšit. Nelze vyčistit následující adresáře cache. Pravděpodobně je to v pořádku, ale pokud narazíte na nějaké divné chování, měli byste se pokusit tyto adresáře promazat. Úspěšně jsme zaktualizovali modul jádra Galerie. Vítejte Vítejte v aktualizaci Galerie Pro opravu práv by mělo pomoci něco jako <i>chmod 666 config.php</i>. Snažíte se spustit aktualizaci, ale chybí validní soubor config.php. Modul jádra Vaší Galerie je aktuální! Ve vašem PHP chybí funkce %sbind_textdomain_codeset%s. To znamená, že Galerie může špatně zobrazovat rozšířené znaky některých jazyků. Ve vašem PHP chybí funkce %sdngettext%s. To znamená, že Galerie nebude moci přeložit tvary množného čísla. Váš config.php zřejmě obsahuje starý formát zápisu pro podporu multisite. Prosím přečtěte si %sNápovědu%s pro další instrukce k aktualizaci konfigurace. Váš webový server nepodporuje lokalizace. Pro přidání podpory dalších jazyků požádejte prosím Vašeho systémového správce o změnu konfigurace PHP se zapnutou volbou %sgettext%s. Kompatibilní mód Zendu Funkce exec() povolena bez omezení funkce putenv() povolena Funkce set_time_limit() povolena tento skript 