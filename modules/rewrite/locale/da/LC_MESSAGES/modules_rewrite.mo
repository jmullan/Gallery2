��    q      �  �   ,      �	     �	     �	     �	     �	     �	  3   �	  (   
     <
     N
     S
  	   `
     j
  "   �
     �
  '   �
     �
     	  1   (  "   Z  5   }  +   �  >   �  3     /   R  '   �     �     �     �  #   �               &     >     V     e     x  A   �     �     �  �   �     �     �  K   �  s   2  y   �           %     5     O  W   l  M   �  I     e   \  W   �          -  a   ;     �     �     �     �     �     �  +     ,   /  >   \  =   �  4   �  A     8   P     �     �  (   �     �     �     �  �   �  	   g  
   q  �   |     *     9     G     Z     b     ~     �     �  
   �     �  )   �  3     <   :  3   w  -   �  �   �  I   �  &   �  "        @  �   T     �     �     �       p         �     �  Z   �     �  A   �  @   A  �  �          #     7     =     R  8   j  '   �     �     �     �     �       %   !     G  +   f     �  #   �  %   �  #   �  @     2   `  O   �  4   �  5      0   N            �   %   �   -   �      �      !     !     )!     A!     V!     h!  ^   �!     �!     �!  �    "     �"     �"  M   �"  �   I#  �   �#     l$     s$  !   �$     �$  b   �$  Z   #%  Y   ~%  a   �%  Y   :&     �&     �&  Y   �&  	   '     '     "'     <'     Z'     w'  2   �'  (   �'  <   �'  I   "(  .   l(  M   �(  2   �(     )     ))  5   8)     n)     u)  
   y)  �   �)      *     ,*  �   C*     �*     	+     +     )+     ,+     ?+      K+     l+  	   �+     �+  -   �+  6   �+  >   ,  5   O,  .   �,  �   �,  T   �-  #   �-     .     (.  �   6.     �.     �.  !   �.     /  p   '/     �/     �/  g   �/     0  @   0  ?   U0     :       p   "             E   ?      q   F   -              C      Z   #   ;                     G       !       Q   g      d   (   @      M   I   &                                 *   T   '           \   .   0   J   =                             A      P          	   /   7   o   c   b   l   Y      <   K   O                 $   j   ^   e      1          +   S   [   i   3   2       m       5      `   f   )   8      L   X   V   W   %       4       6   ,       >   H                               D   9   R   ]       n   N   k                  
   _      U   a   B   h    404 File Not Found 404 File not found Active Additional Keywords Allow empty referer? An error occured while trying to save your settings Apache mod_rewrite and Gallery multisite Approved referers Back Bad keyword. Bad path: Block hotlinked items Block hotlinking is not supported. Cannot read the .htaccess file Cannot read the embedded .htaccess file Cannot read the httpd.ini file Cannot write to httpd.ini file Cannot write to httpd.ini file, please create it. Cannot write to the .htaccess file Cannot write to the .htaccess file, please create it. Cannot write to the embedded .htaccess file Cannot write to the embedded .htaccess file, please create it. Cant write to the httpd.ini file in that directory. Check short style URLs for filesystem conflicts Checked %d items and found %d conflicts Checking item %d of %d Configuration Current language (eg, en or de) Custom Gallery directory test setup Done Download Item Duplicate URL patterns. Embedded .htaccess file Embedded Setup Empty URL pattern. Empty configuration value. Ensures browsers do not use cached version when image has changed Error Error: 404 File Not Found For whatever reason, Gallery did not detect a working mod_rewrite setup. If you are confident that mod_rewrite does work you may override the automatic detection. Please, run these two tests to see for yourself. Force Gallery .htaccess file Gallery did not detect Path Info, please run this thest yourself to verify. Gallery tries to test mod_rewrite in action. For this to work you need to edit each of these two files accordingly: Gallery tries to test mod_rewrite in action. This does not work with multisite since Gallery lacks the complete codebase. Help Httpd.ini path: IIS ISAPI_Rewrite Support ISAPI_Rewrite httpd.ini file If one of the two tests gives you a page with the text PASS_REWRITE you are good to go. If the test gives you a page that says PASS_ISAPI_REWRITE you are good to go. If the test gives you a page that says PASS_PATH_INFO you are good to go. If you add this at the bottom, please make sure that there's atleast one empty line below the section In order to make the test pass you need to add the test rewrite rule in your httpd.ini: Invalid directory. Invalid path. It is recomended that you don't activate the 'Download Item' URL since it will slow down Gallery. Keywords Line 6: No help available No keyword help available PHP Path Info Support PHP Path Info Test Path to an item (eg, /album/image.jpg.html) Please configure the embedded htaccess path. Please create a file in your Gallery directory named .htaccess Please make sure Gallery can read the existing .htaccess file Please make sure Gallery can read the httpd.ini file Please make sure Gallery can write to the existing .htaccess file Please make sure Gallery can write to the httpd.ini file Processing... Public path: Quick and easy way to access Site Admin. Rules Save Setup Short URLs are compiled out of predefined keywords. Modules may provide additional keywords. Keywords are escaped with % (eg: %itemId%). Show Item Site Admin Some rules only apply if the referer (the site that linked to the item) is something other than Gallery itself. Hosts in the list below will be treated as friendly referers. Status: Active Status: Error Status: Not Active Success Successfully saved settings Test Test ISAPI Rewrite Manually Test Path Info Manually Test again Test mod_rewrite manually Testing if %s is supported by the server. Testing if Gallery can write to the .htaccess file. Testing if Gallery can write to the embedded .htaccess file. Testing if Gallery can write to the httpd.ini file. Testing if the server supports PHP Path Info. The Apache mod_rewrite module is installed on most Apache servers by default. If you are unsure of what method you should choose then select this. Gallery will try to detect if your server supports mod_rewrite. The current status may not be accurate, you have forced the test to pass. The general URL for downloading items. The general URL for viewing items. The item file name. This will go through all your Gallery items and check if the short style URL links to an existing file or directory on your webserver. URL Pattern URL Rewrite URL Rewrite Administration URL Rewrite Setup Using Path Info is supported by most systems. With this method Gallery parses the URL itself during the request. View Warning Warning: If you don't allow empty referer users won't be able to download nor play movies. Works mod_rewrite configuration 1 (with global Options +FollowSymlinks) mod_rewrite configuration 2 (with local Options +FollowSymlinks) Project-Id-Version: Gallery: URL Rewrite 1.1.10
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2005-07-25 14:14+0200
PO-Revision-Date: 2006-04-03 11:39+0200
Last-Translator: Bjorn Graabek <bjorn@graabek.com>
Language-Team: Danish <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 404 Fil ikke fundet 404 Fil ikke fundet Aktiv Yderligere Nøgleord Tillad 'empty referer'? En fejl opstod under da dine indstillinger skulle gemmes Apache mod_rewrite og Gallery multisite Godkendte henvisere Tilbage Fokert nøgleord Ugyldig sti: Bloker hotlink'ede objekter Blok hotlinking er ikke understøttet Kan ikke læse .htaccess filen Kan ikke læse den indlejrede .htaccess fil Kan ikke læse httpd.ini filen Kan ikke skrive til .htaccess filen Kan ikke skrive til httpd.ini filen,  Kan ikke skrive til .htaccess filen Kan ikke skrive til .htaccess filen, vær venlig at oprette den. Kunne ikke skrive til den indlejrede .htaccess fil Kunne ikke skrive til den indlejrede .htaccess fil, vær venlig at oprette den. Kan ikke skrive til httpd.ini filen i det bibliotek. Kontroller korte URLer for konflikter med filsystemet Kontrollerede %d objekter og fandt %d konflikter Kontroller objekt %d af %d Konfiguration Nuværende sprog (f.eks. en eller da) Speciel Gallery bibliotekskontrolindstilinger Udført Hent Element Dublerede URL mønstre. Indlejret .htaccess fil Indlejret opsætning Tomt URL mønster Tom konfigurationsværdi. Sikrer at browseren ikke bruger en cachet version af billedet, når billedet er blevet ændret Fejl Fejl: 404 Fil ikke fundet Af en eller anden grund kan Gallery ikke detektere en fungerende mod_rewrite installation. Hvis du er helt sikkert på at mod_rewrite virker kan du tilsidesætte den automatisk detektion. Kør venligst disse to tests selv. Tving Gallery .htaccess fil Gallery kunne ikke finde PathInfo, udfør selv denne test for at efterprøve. Gallery forsøger at prøve mod_rewrite ved at benytte det. For at dette skal virke skal du ændre i disse to filer som følgende: Gallery prøver at kontrollere mod_rewrite ved at bruge det. Dette virker ikke i en "multisite" opsætning, da Gallery ikke har adgang til hele installationen. Hjælp Httpd.ini sti: IIS ISAPI_Rewrite Understøttelse ISAPI_Rewrite httpd.ini fil Hvis en af disse to tests giver dig en side med teksten PASS_REWRITE er du klar til at gå videre. Hvis testen resulterer i side med teksten PASS_ISAPI_REWRITE er du klar til at gå videre. Hvis testen resulterer i en side med teksten PASS_PATH_INFO er du klar til at gå videre. Hvis du tilføjer dette i bunden, sørg da for at der er mindst en tom linje nedenunder sektionen For at få testen til at lykkes, må du tilføje test 'rewrite' reglen i httpd.ini filen: Ugyldigt bibliotek. Ugyldig sti. Det anbefales at 'Download Emne' URL ikke aktiveres da det vil gøre Gallery langsommere. Nøgleord Linie 6: Ingen hjælp tilgængelig Ingen tilgængelige nøgleord PHP PathInfo Understøttelse PHP PathInfo Test Sti til et objekt (f.eks. /album/billede.jpg.html) Konfigurer den indlejrede .htaccess sti. Lav venligst en fil i dit gallery bibliotek kaldet .htaccess Undersøg venligst om galleriet kan læse den eksisterende .htaccess fil. Sørg for at Gallery kan læse .htaccess filen Undersøg venligst om galleriet kan skrive til den eksisterende .htaccess fil Sørg for atUGallery kan skrive til.htaccess filen Behandler... Offentlig sti: Hurtig og nem måde at få adgang til Administration. Regler Gem Opsætning Kort URLer er oversat ud fra prædefinerede nøgleord. Moduler kan stille yderligere nøgleord til rådighed. Nøgleord skrives inde i % (f.eks. %ItemId%). Vis Element Gallery Administration Nogle regler gælder kun hvis henviseren (det sted som henviste til objektet) er noget andet end Gallery selv. Websteder i nedenstående liste vil blive opfattet som venlige henvisere. Staus: Aktiv Status: Fejl Statis: Ikke Aktiv Ok Gemte opsætningen Afprøvning Kontroller ISAPI Rewrite manuelt Test PathInfo Manuelt Test igen Kontroller mod_rewrite manuelt Afprøver om %s er understøttet af serveren. Undersøger om Gallery kan skrive til .htaccess filen. Tester om Gallery kan skrive til den indlejrede .htaccess fil. Undersøger om Gallery kan skrive til .htaccess filen Tester om serveren understøtter PHP PathInfo. Det er normalt at mod_rewrite modulet er installeret på en Apache webserver. Hvis du er i tvivl om hvilken metode du skal vælge, så vælg denne. Gallery vil forsøge at opdage om denne server understøtter mod_rewrite. Den nuværende status er måske ikke korrekt, du har tvunget testen til at godkende. Generel URL for at downloade emner. Generel URL for at se emner. Emne filnavn. Dette vil gå gennem alle dine Gallery objekter og kontrollere om de korte URLer fører til en eksisterende fil eller bibliotek på din webserver. URL Mønster URL Omskrivning Administration af URL omskrivning Indstilling af URL Omskrivning PathInfo er understøttet af de fleste systemer. Med denne metode parser Gallery selv URL'en ved forespørgslen. Vis Advarsel Advarsel: Hvis du ikke tillader 'empty referer', hvil brugere ikke kunne downloade eller afspille film. Virker mod_rewrite konfiguration 1 (med global Options +FollowSymlinks) mod_rewrite konfiguration 2 (med local Options +FollowSymlinks) 