��    v      �  �   |      �	     �	     
  '   
     ?
     F
     Z
  3   o
  (   �
     �
     �
     �
  	   �
     �
  "        3  '   R     z     �  1   �  "   �  5     +   C  >   o  3   �  /   �  '        :     Q     _  #        �     �     �     �     �     �  A        W     ]  K   w  �   �     �     �  N   �  J     s   N  y   �     <     V     f     �  W   �  M   �  I   C  f   �  W   �     L     _  a   m     �     �     �     �            +   0  A   \  ,   �  >   �  =   
  4   H  A   }  8   �     �       (        <     B     G  �   M  	   �  
   �  �   �     �     �     �     �     �     �     	  
   !     ,  %   F  )   l  3   �  <   �  3     1   ;  -   m  �   �  I   n  &   �  "   �       >     ;   U  �   �  �   =     �     �  p   �     \     a  Z   i     �  A   �  @     u  M     �     �  3   �     +      2      M   =   h   '   �      �      �      �      !     !     '!  $   >!  /   c!  $   �!  )   �!  A   �!  -   $"  C   R"  8   �"  O   �"  F   #  ;   f#  0   �#     �#     �#     �#  ,   $     J$     P$     f$     �$     �$     �$  ]   �$     #%     (%  V   H%  �   �%     �&     �&  V   �&  U   	'  �   _'  �   �'  "   o(     �(     �(     �(  W   �(  G   >)  K   �)  b   �)  b   5*     �*     �*  f   �*     "+     1+     :+  "   P+     s+     �+  /   �+  ;   �+  (   	,  >   2,  :   q,  ;   �,  C   �,  D   ,-     q-     ~-  8   �-     �-     �-     �-  �   �-     �.     �.  �   �.     |/     �/     �/  	   �/  !   �/     �/     �/     0     0  '   60  .   ^0  H   �0  I   �0  :    1  /   [1  ,   �1  �   �1  G   �2  *   �2  (   3     .3  G   E3  >   �3  �   �3  �   �4     ?5     K5  z   ^5  	   �5     �5  �   �5     q6  @   w6  ?   �6     [          g   U          >   )          "           l      4   I   D   -       k   
   	   s   q       B             c   P   5   a   W      ,         X       A       r                H   v   .       f      ^   :       2       +   (   Q   h       n   $      K           _         o         T           \           '       ;   N               @   0   ?   e         O   !       C   V   <   i   p   #          F                  b   /      7   3       9   ]   G   Z       1       j             m   L       S   u   *   `       d      E   %   R           J          Y   &       M   6   =   8      t    404 File Not Found 404 File not found A pattern may not begin with a keyword. Active Additional Keywords Allow empty referer? An error occured while trying to save your settings Apache mod_rewrite and Gallery multisite Approved referers Back Bad keyword. Bad path: Block hotlinked items Block hotlinking is not supported. Cannot read the .htaccess file Cannot read the embedded .htaccess file Cannot read the httpd.ini file Cannot write to httpd.ini file Cannot write to httpd.ini file, please create it. Cannot write to the .htaccess file Cannot write to the .htaccess file, please create it. Cannot write to the embedded .htaccess file Cannot write to the embedded .htaccess file, please create it. Cant write to the httpd.ini file in that directory. Check short style URLs for filesystem conflicts Checked %d items and found %d conflicts Checking item %d of %d Configuration Current language (eg, en or de) Custom Gallery directory test setup Done Duplicate URL patterns. Embedded .htaccess file Embedded Setup Empty URL pattern. Empty configuration value. Ensures browsers do not use cached version when image has changed Error Error: 404 File Not Found For ISAPI Rewrite to work Gallery needs write access to the httpd.ini file. For whatever reason, Gallery did not detect a working mod_rewrite setup. If you are confident that mod_rewrite does work you may override the automatic detection. Please, run these two tests to see for yourself. Force Gallery .htaccess file Gallery did not detect ISAPI Rewrite, please run this test yourself to verify. Gallery did not detect Path Info, please run this test yourself to verify. Gallery tries to test mod_rewrite in action. For this to work you need to edit each of these two files accordingly: Gallery tries to test mod_rewrite in action. This does not work with multisite since Gallery lacks the complete codebase. How to setup ISAP Rewrite Httpd.ini path: IIS ISAPI_Rewrite Support ISAPI_Rewrite httpd.ini file If one of the two tests gives you a page with the text PASS_REWRITE you are good to go. If the test gives you a page that says PASS_ISAPI_REWRITE you are good to go. If the test gives you a page that says PASS_PATH_INFO you are good to go. If you add this at the bottom, please make sure that there's at least one empty line below the section In order to make the test pass you need to add the test rewrite rule in your httpd.ini: Invalid directory. Invalid path. It is recomended that you don't activate the 'Download Item' URL since it will slow down Gallery. Keywords Line 6: No help available No keyword help available PHP Path Info PHP Path Info Support Path to an item (eg, /album/image.jpg.html) Please configure the correct location of ISAPI_Rewrite httpd.ini. Please configure the embedded htaccess path. Please create a file in your Gallery directory named .htaccess Please make sure Gallery can read the existing .htaccess file Please make sure Gallery can read the httpd.ini file Please make sure Gallery can write to the existing .htaccess file Please make sure Gallery can write to the httpd.ini file Processing... Public path: Quick and easy way to access Site Admin. Rules Save Setup Short URLs are compiled out of predefined keywords. Modules may provide additional keywords. Keywords are escaped with % (eg: %itemId%). Show Item Site Admin Some rules only apply if the referer (the site that linked to the item) is something other than Gallery itself. Hosts in the list below will be treated as friendly referers. Status: Active Status: Error Status: Not Active Success Successfully saved settings Test ISAPI Rewrite Manually Test Path Info Manually Test again Test mod_rewrite manually Test the Rewrite Parser Configuration Testing if %s is supported by the server. Testing if Gallery can write to the .htaccess file. Testing if Gallery can write to the embedded .htaccess file. Testing if Gallery can write to the httpd.ini file. Testing if the server supports IIS ISAPI_Rewrite. Testing if the server supports PHP Path Info. The Apache mod_rewrite module is installed on most Apache servers by default. If you are unsure of what method you should choose then select this. Gallery will try to detect if your server supports mod_rewrite. The current status may not be accurate, you have forced the test to pass. The general URL for downloading items. The general URL for viewing items. The item file name. The parser you have selected does not support a referer check. The selected URL Rewrite Parser does not provide any tests. This method allows for short URLs on IIS servers with ISAPI Rewrite installed. Gallery will try to detect if your server supports this method before activating the module. This will go through all your Gallery items and check if the short style URL links to an existing file or directory on your webserver. URL Pattern URL Rewrite Administration Using Path Info is supported by most systems. With this method Gallery parses the URL itself during the request. View Warning Warning: If you don't allow empty referer users won't be able to download nor play movies. Works mod_rewrite configuration 1 (with global Options +FollowSymlinks) mod_rewrite configuration 2 (with local Options +FollowSymlinks) Project-Id-Version: Gallery: URL Rewrite 1.1.17
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2005-05-12 18:29+0200
PO-Revision-Date: 2006-03-17 15:19+0100
Last-Translator: Buut <buut at users.sourceforge Remove - This dot net>
Language-Team: Dutch <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
 404 Bestand Niet Gevonden 404 Bestand niet gevonden Een patroon kan niet beginnen met een sleutelwoord. Actief Aanvullende Sleutelwoorden Lege referenties toestaan? Er is een fout opgetreden bij het opslaan van uw instellingen Apache mod_rewrite en Gallery multisite Goedgekeurde referenties Terug Onjuist sleutelwoord. Onjuist pad: Blokkeer hotlink items Blokkeer hotlink items Kan het .htaccess bestand niet lezen Kan het ingebouwde .htaceess bestand niet lezen Kan het httpd.ini bestand niet lezen Kan niet naar httpd.ini bestand schrijven Kan niet naar httpd.ini bestande schrijven, maak dit bestand aan. Kan niet naar het .htaccess bestand schrijven Kan nietnaar het .htaccess bestand schrijven, maak dit bestand aan. Kan niet naar het ingebouwde .htaceess bestand schrijven Kan niet naar het ingebouwde .htaceess bestand schrijven, maak dit bestand aan. Gallery kan niet schrijven naar het httpd.ini bestand in die directory Controleer korte stijl URLs voor bestandssysteem conflicten %d items gecontroleerd en %d conflicten gevonden Controleren van item %d van %d Configuratie Huidige taal (bijv. nl of en) Aangepaste Gallery directory test instelling Klaar Dubbele URL partonen. Ingebedde .htaccess bestand Ingebedde Configuratie Leeg URL patroon. Lege configuratie waarde. Zorg ervoor dat browsers niet de gecachte versie gebruiken wanneer de afbeelding is veranderd Fout Fout: 404 Bestand Niet Gevonden ISAPI_Rewrite heeft schrijfrechten nodig op het httpd.ini bestand om te kunnen werken. Om wat voor reden dan ook heeft Gallery geen juiste werkende mod_rewrite instelling kunnen herkennen. Als u er zeker van bent dat mod_rewrite werkt kunt de de automatische deterctie overschrijven. Daar deze twee testen om het zelf te zien. Forceren Gallery .htaccess bestand Gallery heeft geen ISAPI Rewrite gevonden, draai deze test zelf om dit te bevesitigen. Gallery heeft geen Path Info gedetecteerd, draai deze test zelf om dit te bevestigen. Gallery probeert om mod_rewrite in actie te testen. Om dit te laten werken dient u elk van deze twee bestanden als volgt te bewerken: Gallery probeert om mod_rewrite in actie te testen. Dit werkt niet bij multisite, aangezien Gallery niet de complete programmacode bevat. Hoe de ISAPI Rewrite in te stellen Path naar httpd.ini IIS ISAPI_Rewrite ondersteuning ISAPI_Rewrite httpd.ini bestand Als één van de twee tests u een pagina geeft met de text PASS_REWRITE kuntu doorgaan. Als de test U een pagina geeft met de text PASS_REWRITE kuntu doorgaan. Als de test U een pagina geeft met de text PASS_PATH_INFO  kunt U doorgaan. Indien U dit aan het eind toevoegd, controleer dan of er minstens 1 lege regel is onder de sectie. Om deze test met goed gevolg te doorlopen, moet je de test rewrite rule in de httpd.ini toevoegen. Ongeldige directory. Ongeldig pad. Het is niet aan te randen om de 'Download Item' URL te activeren, aangezien het Gallery zal vertragen. Sleutelwoorden Regel 6: Geen help beschikbaar Geen sleutelwoord help beschikbaar PHP Path info PHP Path Info Ondersteuning Pad naar een item (bijv, /album/image.jpg.html) Stel de juiste locatie in voor httpd.ini van ISAPI_Rewrite. Configureer het ingebouwde htaceess pad. Maak een bestand aan in uw Gallery directory genaamd .htaccess Zorg dat Gallery het bestaande .htaccess bestand kan lezen Zorg dat Gallery het bestaande .httpd.ini bestand kan lezen Zorg dat Gallery kan schrijven naar het bestaande .htaccess bestand Zorg dat Gallery kan schrijven naar het bestaande .httpd.ini bestand Verwerken... Publiek pad: Snel en gemakkelijke manier voor toegang to Site Beheer. Regels Opslaan Configuratie Korte URLs zijn samengesteld uit voorgedefinieerde sleutelwoorden. Modules kunnen aanvullende sleutelwoorden aanleveren. Sleutelwoorden zijn omringt met % (bijv: %itemId%). Item Weergeven Site Beheer Sommige regels zijn alleen van toepassing als de referentie (de site die naar het item linkt) iets anders is van Gallery zelf. De hosts in de lijst hieronder zullen behandeld worden als vriendelijke referenties. Status: Actief Status: Fout Status: Niet Actief Succesvol Instellingen succesvol opgeslagen Test ISAPO_Rewrite Handmatig Test Path Info Handmatig Test opnieuw Test mod_rewrite handmatig Teste de Rewrite Verwerker Configuratie Testen als %s word door de server ondersteund. Controleer of Gallery kan schrijven naar het bestaande .htaccess bestand Controleer of Gallery kan schrijven naar het ingebouwde .htaceess bestand Zorg dat Gallery kan schrijven naar het httpd.ini bestand. Test of de IIS server ISAPI_Rewrite ondersteund Test of de server PHP Path Info ondersteund. De Apache module mod_rewrite wordt gewoonlijk geinstalleerd. Mocht U niet zeker zijn welke methode U moet gebruiken, kies dan voor deze methode. Gallery zal proberen uit te zoeken of Uw server mod_rewrite ondersteund. De huidige status kan niet de actuele status zijn, doe de test nogmaals De algemene URL voor downloaden van items. De algemene URL voor weergave van items. Bestandsnaam van item. De door u geselecteerde verwerken ondersteund geen referentie controle. De geselecteerde URL Rewrite parser voorziet niet in een test. Met deze methodiek is het mogelijk om op IIS servers waarop ISAPI_Rewrite is geinstalleerd gebruik te maken van 'short URLS'. Gallery zal proberen om te detecteren of Uw server deze methode ondersteund, voordat deze ingeschakeld wordt. Dit zal al uw Gallery item doorlopen en controleren of de kort stijl URL naar een bestaand bestand of directory op uw webserver linkt. URL Patroon URL Rewrite Beheer Using Path Info wordt door veel systemen ondersteund. Indien dit gebruikt wordt zal Gallery de URL request zelf verwerken. Weergeven Waarschuwing Waarschuwing: Als u geen lege referenties toestaat zullen gebruikers niet in staat zijn om videos te downloaden of af te spelen. Werkt mod_rewrite configuratie 1 (met globale Options +FollowSymlinks) mod_rewrite configuratie 2 (met locale Options +FollowSymlinks) 