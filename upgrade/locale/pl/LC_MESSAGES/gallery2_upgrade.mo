��    �      t  �   �      �     �     �     �       d   5  5   �     �     �     �  	               �   3     �  $   �                    3     A     O     [  �   g  �   7  �      �   �  u   2  �   �  �   C     �     �               #     9  	   H    R     X     o     r     �  p   �  �         )     !   >     `     r     �     �     �     �     �     �     �     �     �  }        �     �     �      �  	   �     �     �               '  	   0     :     M  +   ^  
   �     �     �     �     �  !   �                   &  	   :     D  %   c  "   �  !   �     �     �  $   	     .     K     g     �     �     �  S   �     5     =     S     `     u     �     �  *   �  #   �  "   �       �   ,         !         4      E   �  M   (  �!    #  M  	$  �   W%  �   !&  �   �&  �   �'    H(  �   f)  4   F*     {*     �*  3   �*  '   �*  �   �*  l   �+  �   �+  �   �,     Y-     q-     �-     �-     �-     �-  �  �-     �/     �/  %   �/     �/  �   0  E   �0     �0  
   �0  !   �0  �   1     �1     2  �   -2     �2  2   �2      3     )3     93     N3     a3     �3      �3  �   �3  �   �4  �   �5  �   W6  r   7  �   �7  �   %8     �8     �8     9     9     19     O9     g9    �9     �:     �:     �:  !   �:  �   �:  1  �;  �   �<  '   �=  !   �=     >  $   >     A>     P>  -   f>     �>     �>     �>     �>     �>     �>  �   �>     �?     �?  
   �?     �?     �?     �?     �?     @     @     /@     8@     H@     d@  2   t@     �@     �@     �@  6   �@     A  &   #A     JA     PA  N  WA     �B     �B  +   �B  1   �B  "   /C  !   RC  "   tC  !   �C  %   �C  !   �C      D     "D     BD  $   aD  #   �D  Y   �D     E     E     (E     HE     fE     }E     �E  ?   �E      �E     F     ,F    @F     DG  )   ]G     �G     �G  �  �G  `  sI  8  �J  �  L  �   �M  �   �N  �   oO  �   KP  e  .Q  �   �R  1   �S     �S      �S  H   �S  (   -T  �   VT  z   �T  �   wU  �   V     �V     �V     �V      W     W     .W             !       n      x       �   B   5       ^   \   O   N   d   $                  h   *       q   K   �      m   R      z           j   J   =   C       ~   %          p   '                1      +                               /   F       t   2   #   f           `   H   7   |             i       V   �   P   -          >               Q   v   E      o   �   0   "   �       w   (   {   ]   }       W      �       s   �   <   Y   r       �      6   G   8   @       S                   
             �   b   U   4   �   T   [   :   �           Z              &   )           9   3           c   �   M   A           	   _             .          y          e       L   u   a   I   l   ;   ?      D                 X   ,   g   k    %s module needs configuration (un)check all <b>Error:</b> invalid password. <b>Error:</b> missing password. <b>Reminder</b>: Now check the permissions on config.php and make sure it is not globally writeable. An error occurred while upgrading Gallery Core Module Authenticate Authenticate Me Authentication successful! Before you upgrade, we <b>strongly recommend</b> that you make a backup of your database!  If you fail to make a backup and something goes wrong, there is a strong possibility that we will not be able to help you recover your data!  Refer to the following examples: Begin Upgrade Config.php upgrade Congratulations! Your Gallery 2 upgrade is complete!  To upgrade any additional Gallery 2 plugins you may use the Site Administrator interface. Continue to Step %d&raquo; Core Module version: %s (Gallery %s) Current Currently installed Deactivated Plugins Debug Output: Delete Caches Description Empty Cache Error: Essential filesystem operations are disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini. You must allow these functions before Gallery will run. These functions are missing: %s. Error: Gallery 2 requires PHP version 4.3.0 or newer or 5.0.4 or newer. You have PHP version %s installed. Contact your webserver administrator to request an upgrade, available at the %sPHP website%s. Error: Some files and or directories in your storage directory are not writeable by the webserver user. Run chown -R webserverUser %s OR run chmod -R 777 %s. Error: Your PHP is configured without support for %sPerl Compatible Regular Expressions%s. You must enable these functions before Gallery will run. Error: Your version of PHP is configured with safe mode enabled.  You must disable safe mode before Gallery will run. Error: your PHP __FILE__ directive is not functioning correctly. Please file a support request with your webserver administrator or in the Gallery forums. Even though there were errors, you can still continue.  Or, you can try deleting these directories yourself and then click the <b>Try Again</b> link below. FILE Directive FILE directive supported Failed File uploads allowed Filesystem Operations Finish Upgrade Finished! Gallery creates temporary copies of some of your data on your hard drive.  This helps it to run faster.  But when you upgrade, some of these files might be out of date so it's a good idea to get rid of them now.  Gallery will create them again as it needs them. Gallery file integrity Go Go to my Gallery! Go to the Gallery 2 Installer If you are using Apache, create a file named .htaccess in the main Gallery directory with the following content: If you have a busy site, consider putting your Gallery in maintenance mode. This gives visitors a message that the site is temporarily offline, rather than showing everybody this upgrade page. Edit your config.php file to activate maintenance mode. In order to proceed with the upgrade process, we have to verify that you are who you claim.  When you performed the install, you entered a password which went into your config.php.  Type that in now.  Refer to your config.php if you've forgotten what you entered. Incompatible with this version of Gallery Manifest missing or inaccessible. Maximum POST size Maximum upload size Memory limit Missing files (%d) Missing or invalid config.php Modified files (%d) Module Name New New version Old files (%d) Once the upgrade has begun, please be patient.  If you cancel or reload the page, you may interfere with the upgrade process. Other Output buffering disabled PHP Version PHP version >= 4.3.0 or >= 5.0.4 Password: Performing system checks Recheck config.php Redo this step Regular expressions Required Safe Mode Safe mode disabled Select Language: Skip Upgrade and Continue to Step %d&raquo; Start Over Storage Directory Permissions Success Successfully cleaned caches. System Checks Test skipped due to other errors. Theme Themes These files are no longer part of Gallery. They probably won't cause any problems but it is a good idea to remove them to keep your install clean.  Gallery can't remove these files for you, but you can download and run %s in your gallery2 directory to delete them for you. Translation support Try Again Unable to clear the page cache Unable to commit database transaction Unable to deactivate the %s module Unable to deactivate the %s theme Unable to get the module list Unable to get the theme list Unable to initialize Gallery session Unable to load the %s module Unable to load the %s theme Unable to query the %s module Unable to query the %s theme Unable to upgrade the %s module Unable to upgrade the %s theme Unable to write to config.php in your %s directory.  Please change its permissions. Unknown Upgrade %d%% complete Upgrade Core Upgrade More Plugins Upgrade Plugins Upgrade Selected Plugins Upgrade Steps Upgraded Gallery Core Module successfully. Upgraded the %s module successfully Upgraded the %s theme successfully Upgrader Help Upgrading Gallery 2 requires %d steps. This upgrade tool will guide you through these steps and provide assistance along the way if additional steps are required. Please read the %sHelp File%s before proceeding. Upgrading modules Upgrading the Gallery Core Module Upgrading themes Warning Warning: Output buffering is enabled in your PHP by the <b>%s</b> parameter(s) in php.ini.  Gallery can function with this setting - downloading files is even faster - but Gallery might be unable to serve large files (e.g. large videos) and run into the memory limit. Also, some features like the progress bars might not work correctly if output buffering is enabled unless ini_set() is allowed. Warning: The exec() function is disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini. You won't be able to use modules that require external binaries (e.g. ImageMagick, NetPBM or Ffmpeg). This can only be set server-wide, so you will need to change it in the global php.ini. Warning: The putenv() function is disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini.  Gallery can function with this setting, but on some rare systems Gallery will be unable to run in other languages than the system language and English. Warning: The set_time_limit() function is disabled in your PHP by the <b>disabled_functions</b> parameter in php.ini.  Gallery can function with this setting, but it will not operate reliably.  Any operation that takes longer than %d seconds will fail (and in some cases just return a blank page) possibly leading to data corruption. Warning: Your PHP is configured not to allow file uploads (<b>file_uploads</b> parameter in php.ini). You will need to enable this option if you want to upload files to your Gallery with a web browser. Warning: Your PHP is configured to limit the memory to %sb (<b>memory_limit</b> parameter in php.ini). You should raise this limit to at least <b>%sMB</b> for proper Gallery operation. Warning: Your PHP is configured to limit the post data to a maximum of %sb (<b>post_max_size</b> parameter in php.ini). You should raise this limit to allow uploading bigger files. Warning: Your PHP is configured to limit the size of file uploads to %sb (<b>upload_max_filesize</b> parameter in php.ini). You should raise this limit to allow uploading bigger files. Warning: Your PHP is configured with Zend ze1_compatibility_mode which can cause PHP to crash.  Click <a href="%s">here</a> to test your PHP.  If you see "SUCCESS" then your PHP is ok.  If you get an error or no response then you must turn off ze1_compatibility_mode before proceeding. We were unable to clean the following cache directories.  This is probably ok, but if you notice any weird behaviour, you should try to delete these directories yourself.  It's perfectly safe to get rid of them at any time. We've successfully upgraded the Gallery Core Module. Welcome Welcome to the Gallery Upgrader You can do <i>chmod 666 config.php</i> to fix this. Your Gallery Core Module is up to date! Your PHP is missing the function %sbind_textdomain_codeset%s. This means Gallery may display extended characters for some languages incorrectly. Your PHP is missing the function %sdngettext%s. This means Gallery will be unable to translate plural forms. Your config.php appears to use the old form of multisite support.  Please see the %sHelp File%s for instructions to update your configuration before proceeding. Your webserver does not support localization. To enable support for additional languages please instruct your system administrator to reconfigure PHP with the %sgettext%s option enabled. Zend compatibility mode exec() allowed no limit putenv() allowed set_time_limit() allowed this script Project-Id-Version: Gallery: Upgrader 2.2
POT-Creation-Date: 2006-02-23 10:15+0100
PO-Revision-Date: 2006-12-06 23:09+0100
Last-Translator: Kappana <kappana@gnoms.net>
Language-Team: Polish <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=3; plural=(n==1 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);
X-Poedit-Language: Polish
X-Poedit-Country: POLAND
 Moduł %s wymaga konfiguracji zaznacz/odznacz wszystko <b>Błąd:</b> nieprawidłowe hasło. <b>Błąd:</b> brak hasła. <b>Przypomienie</b>: Proszę sprawdzić uprawnienia pliku config.php i upewnić się, że nie ma ustawionych globalnych praw zapisu. Wystąpił błąd podczas aktualizowania modułu głównego Gallery 2 Autoryzacja Zautoryzuj Autoryzacja zakończona sukcesem! Przed rozpoczęciem aktualizacji, <b>stanowczo doradzamy</b> zrobienie backupu bazy danych! W przypadku wystąpienia błędu podczas aktualizacji, istnieje ryzyko, że nie będzie możliwe odzyskanie danych! Przykładowe komendy: Zacznij aktualizację Aktualizacja pliku config.php Gratulacje! Aktualizacja Gallery 2 została zakończona! Aby zaktualizować dodatkowe moduły Gallery 2, można w tym celu użyć interfejsu administratora strony. Przejdź do kroku %d&raquo; Wersja modułu głównego galerii: %s (Gallery %s) Aktualny Aktualna wersja Modyły deaktywowane Wynik debugowania: Usuwanie pamięci podręczniej Opis Czyszczenie pamięci podręcznej Błąd: Podstawowe funkcje operacyjne zostały wyłączone w zainstalowanym PHP za pomocą parametru <b>disabled_functions</b> w pliku php.ini. Przed uruchomieniem galerii konieczne jest włączenie następujących brakujących funkcji: %s. Gallery 2 wymaga wersji PHP 4.3.0 lub nowszej albo 5.0.4 lub nowszej. Zainstalowana wersja PHP to %s. Należy skontaktować się z administratorem serwera WWW i poprosić go o aktualizację do nowszej wersji, dostępnej w %switrynie PHP%s. Błąd: Niektóre pliki i/lub katalogi w katalogu głównym galerii nie posiadają praw zapisu dla serwera WWW. Aby to poprawić należy uruchomić komendę chown -R webserverUser %s LUB run chmod -R 777 %s. Błąd: PHP działa z wyłączoną obsługą %sPerl Compatible Regular Expressions%s (wyrażenia regularne zgodne z językiem Perl). Należy ją włączyć przed uruchomieniem galerii. Błąd: Zainstalowana wersja PHP działa w trybie bezpiecznym. Należy go wyłączyć przed uruchomieniem galerii. Dyrektywa __FILE__ w zainstalowanym PHP nie działa poprawnie. Proszę skontaktować się z administratorem serwera WWW lub zgłosić problem na forum Gallery 2. Pomimo występujących błędów, kontynuacja jest możliwa. Można również spróbować usunąć te katalogi własnoręcznie, a następnie kliknąć poniższy link <b>Spróbuj ponownie</b>. Dyrektywa FILE Wspierana dyrektywa FILE Błąd Wysyłanie plików dozwolone Podstawowe funkcje operacyjne Kończenie aktualizacji Aktualizacja zakończona! Aby przyspieszyć działanie, Gallery 2 tworzy tymczasowe kopie pewnych danych na serwerze. Jednakże po zakończonej aktualizacji, niektóre z tych plików mogą się zdeaktualizować, warto więc je teraz usunąć. W razie potrzeby Gallery 2 stworzy je ponownie. Spójność plików galerii Przejdź do Przejdź do mojej galerii! Przejdź do instalatora Gallery 2 Jeśli używany jest Apache, należy stwórzyć plik o nazwie .htaccess i umieścić go w katalogu głównym galerii. W pliku należy zamieścić następujące komendy: Jeśli aktualizowana strona jest często odwiedzana, proszę zastanowić się nad ustawieniem Gallery 2 w trybie remontu. Dzięki temu goście zobaczą komunikat informujący o tymczasowej nieaktywności strony, zamiast strony aktualizatora. Aby aktywować tryb remontu proszę wyedytować plik config.php Aby kontynuować proces instalacji, Gallery 2 zweryfikuje twoje uprawnienia. Proszę podać hasło, które zostało ustawione podczas instalacji Gallery 2. W razie problemów z przypomnieniem hasła, można je sprawdzić w pliku config.php Niekompatybilne z tą wersją Gallery 2 Zaznacz brakujące i niedostępne Maksymalny rozmiar POST Maksymalny rozmiar wysyłanego pliku Limit pamięci Brakujące pliki (%d) Brakujący lub nieprawidłowy plik config.php Zmienione pliki (%d) Moduł Nazwa Nowy Nowa wersja Stare pliki (%d) W czasie aktualizacji, prosimy o cierpliwość. Jeśli aktualizacja zostanie przerwana lub strona zostanie odświeżona, może to spowodować błędy w procesie aktualizacji. Inny Buforowanie wyłączone Wersja PHP Wersja PHP >= 4.3.0 or >= 5.0.4 Hasło: Sprawdzanie systemu Sprawdź ponownie config.php Powtórz ten krok Wyrażenia regularne Wymagane Tryb bezpieczny Tryb bezpieczny wyłączony Wybierz język: Pomiń aktualizację i przejdź do kroku %d&raquo; Zacznij od nowa Uprawnienia do katalogów Sukces Czyszczenie pamięci podręcznej zakończone sukcesem. Sprawdzanie systemu Test pominięty ze względu na błędy Temat Tematy Poniższe pliki nie stanowią już części Gallery 2. Pozostawienie ich nie powinno wpłynąć na działanie Gallery 2, ale warto je usunąć, aby utrzymać czystą instalację. Gallery 2 nie może ich usunąć automatycznie, jednakże możliwe jest pobranie i uruchomienie w katalogu głównym galerii %s, który zrobi to za ciebie. Wsparcie dla lokalizacji Spróbuj ponownie Nie można wyczyścić pamięci podręcznej Nie można ustanowić połączenia z bazą danych Nie można deaktywować modułu %s Nie można deaktywować tematu %s Nie można pobrać listy modułów Nie można pobrać listy tematów Nie można zainicjować sesji galerii Nie można załadować modułu %s Nie można załadować tematu %s Nie można znaleźć modułu %s Nie można znaleźć tematu %s Nie można zaktualizować modułu %s Nie można zaktualizować tematu %s Nie można zapisać do pliku config.php w katalogu %s. Proszę zmienić jego uprawnienia. Nieznany Postęp aktualizacji: %d%% Aktualizacja modułu głównego Zaktualizuj więcej modułów Aktualizacja modułów Aktualizuj wybrane moduły Kroki aktualizacji Aktualizacja modułu głównego Gallery 2 zakończona sukcesem. Moduł %s został zaktualizowany Temat %s został zaktualizowany Pomoc aktualizatora Aktualizacja Gallery 2 wymaga przejścia przez %d kroków. Niniejszy aktualizator poprowadzi przez nie i pomoże jeśli okaże się, że konieczne będą dodatkowe przejścia. Zanim proces aktualizacji zostanie rozpoczęty proszę przeczytać %splik pomocy%s. Aktualizowanie modułów Aktualizacja modułu głównego Gallery 2 Aktualizowanie tematów Ostrzeżenie Ostrzeżenie: Buforowanie zostało wyłaczone w zainstalowanym PHP za pomocą parametru <b>%s</b> w pliku php.ini. Gallery 2 może funkcjonować z tym ustawieniem - pobieranie plików jest wtedy szybsze - jednakże Gallery 2 może mieć problemy z obsługą większych plików (np. filmy video). Jak również, pewne funkcje takie jak pasek postępu może nie działać prawidłowo jeśli buforowanie jest włączone, chyba, że ini_set() jest dozwolony. Ostrzeżenie: Funkcja exec() została wyłączona w zainstalowanym PHP za pomocą parametru <b>disabled_functions</b> w pliku php.ini. W związku z tym nie będzie możliwe używanie modułów wymagających zewnętrznych binariów (np. ImageMagick, NetPBM czy Ffmpeg). Można zmienić te ustawienia dla całego serwera, edytując globalny plik php.ini. Ostrzeżenie: Funkcja putenv() została wyłaczona w zainstalowanym PHP za pomocą parametru <b>disabled_functions</b> w pliku php.ini. Gallery 2 może funkcjonować z tym ustawieniem, ale na pewnych rzadkich systemach Gallery 2 może nie być w stanie przyjąć innego języka niż język systemowy i angielski. Ostrzeżenie: Funkcja set_time_limit() została wyłaczona w zainstalowanym PHP za pomocą parametru <b>disabled_functions</b> w pliku php.ini. Galeria może funkcjonować z tym ustawieniem, ale działanie może nie być stabilne. Żadna operacja zajmująca więcej czasu niż %d sekund(y) nie powiedzie się (w pewnych przypadkach wyświetli pustą stronę), jak również może prowadzić do utraty danych. Ostrzeżenie: Aktualna konfiguracja PHP nie pozwala na wysyłanie plików (parametr <b>file_uploads</b> w pliku php.ini). Aby wysyłanie plików do galerii za pomocą przeglądarki internetowej było możliwe, należy włączyć tę opcję. Ostrzeżenie: Aktualna konfiguracja PHP ogranicza dostępną pamięć do %sb (parametr <b>memory_limit</b> w pliku php.ini). Aby galeria działała poprawnie należy zwiększyć ten limit do co najmniej <b>%sMB</b>. Ostrzeżenie: Aktualna konfiguracja PHP nie pozwala na wysyłanie danych większych niż %sb (parametr <b>post_max_size</b> w pliku php.ini). Należy zwiększyć ten limit, aby umożliwić wysyłanie większych plików. Ostrzeżenie: Aktualna konfiguracja PHP nie pozwala na wysyłanie plików większych niż %sb (parametr <b>upload_max_filesize</b> w pliku php.ini). Aby umożliwić wysyłanie większych plików, należy zwiększyć ten limit. Ostrzeżenie: W aktualnej konfiguracji PHP włączony jest tryb Zend ze1_compatibility_mod, który może powodować błędy w PHP. Kliknij <a href="%s">tutaj</a>, aby sprawdzić PHP. Jeśli pojawi się napis "SUKCES", konfiguracja jest poprawna. Jeśli wyświetli się błąd, należy wyłączyć ze1_compatibility_mode przed przejściem do kolejnego kroku. Nie można wyczyścić katalogów pamięci podręcznej. Prawdopodobnie wszystko jest w porządku, jednakże w razie wystąpienia dziwnego zachowania galerii katalogi te powinny być usunięte własnoręcznie. Można to zrobić w dowolnej chwili. Moduł główny Gallery 2 został zaktualizowany. Wstęp Witaj w aktualizatorze Gallery 2 Możesz to poprawić korzystając z komendy  <i>chmod 666 config.php</i> Moduł główny Gallery 2 jest aktualny! W zainstalowanym PHP brakuje funkcji %sbind_textdomain_codeset%s. Oznacza to, że Gallery może nieprawidłowo wyświetlać znaki diakrytyczne niektórych języków. W zainstalowanym PHP brakuje funkcji %sdngettext%s. Oznacza to, że Gallery nie będzie mogło tłumaczyć liczby mnogiej. Aktualny plik config.php używa starej metody wspierania multisite. Przed kontynuacją, proszę przeczytać %spliki pomocy%s jak zaktualizować konfigurację. Serwer WWW nie wspiera lokalizacji. Aby dodać obsługę dodatkowych języków, należy poprosić administratora systemu o włączenie opcji %sgettext%s w konfiguracji PHP. Tryb komatybilności z Zend exec() dozwolony bez ograniczeń putenv() dozwolony set_time_limit() dozwolony skryptu 