��    X      �     �      �     �     �     �  4   �     �          !  	   .     8  *   N  +   y  /   �  '   �     �  #   	     8	     =	     K	     c	  %   {	     �	     �	  %   �	  A   �	     +
     1
  {   K
  �   �
     �     �  s   �  �   .  �   �  X   X     �  )   �     �  I   �  W   9  �   �  U   _     �     �     �     �     �  q        x     �  +   �  >   �  =     A   M  Z   �     �     �                 �     	   �  �   �     W     f     t     �     �  $   �     �     �     �          !     2  '   L  ^   t  �   �     Z     j     v     �     �     �     �     �     �  H   �  �  $     �  	   �     �  ,        >     Q     d       b   �  !   �  +     D   @  3   �     �  8   �               (     ?  /   ^     �     �  +   �  T   �     :     @  t   \  �   �     �     �  i   �  �   4  r     X   t  
   �  @   �       U   +  [   �  �   �  O   �      $!     9!  *   J!     u!  
   �!  �   �!     "  1   6"  /   h"  >   �"  M   �"  V   %#  f   |#  
   �#     �#     �#     $  
   $  �   $     �$  �   �$     �%     �%     �%     �%     �%      &     #&  )   ,&  *   V&  '   �&     �&     �&  )   �&  Q   '  �   U'     �'     �'     �'     
(  !   (     A(     \(  
   e(     p(  N   x(     
          '   1   S   T   8       $       Q             G   V   2       F                  (   0                   6   A   .   H           R      7      J       "             #          3   :   P      =           O      @   )      !           <              &   B                 K       >                      X          I          ?      /       ;   	   4       %               M       D   C   *       N   9      L       W                +   ,   U   5       E      -        404 File Not Found Active Additional Keywords An error occured while trying to save your settings: Apache mod_rewrite Approved referers Bad keyword. Bad path: Block hotlinked items Cannot write to the Gallery .htaccess file Cannot write to the embedded .htaccess file Check short style URLs for filesystem conflicts Checked %d items and found %d conflicts Checking item %d of %d Custom Gallery directory test setup Done Download Item Duplicate URL patterns. Embedded .htaccess file Embedded .htaccess file is up to date Embedded Setup Empty URL pattern. Enables short URLs using mod_rewrite. Ensures browsers do not use cached version when image has changed Error Error: 404 File Not Found For URL Rewrite to work in an embedded environment you need to set up an extra htaccess file to hold the mod_rewrite rules. For whatever reason, Gallery did not detect a working mod_rewrite setup. If you are confident that mod_rewrite does work you may override the automatic detection. Please, run these two tests to see for yourself. Gallery Gallery .htaccess file Gallery tries to test mod_rewrite in action. For this to work you need to edit each of these two files accordingly: Gallery's URL rewriting works by creating a new file in your gallery directory called <b>.htaccess</b> which contains rules for how short urls should be interpreted. Go to the <a href="%s">Gallery phpinfo page</a> and look for Loaded Modules. You should see mod_rewrite in the list if it's loaded. Go to the <a href=%s>Setup</a> page where you will be able to further probe mod_rewrite. Help How can I check if mod_rewrite is loaded? Htaccess path: I know mod_rewrite is loaded, why is Gallery telling me it's not working? If one of the two tests gives you a page with the text PASS_REWRITE you are good to go. If you are the server admin make sure the Gallery directory has the proper AllowOverride rights. Gallery needs to be able to override FileInfo and Options. Put this at the end of your Apache configuration: In order for this Gallery module to work you need %s enabled with your Apache server. Invalid directory. Invalid path. Item file name (eg, image.jpg) Keywords Line 6: My Gallery is password protected using Apache mod_auth. I know mod_rewrite works, why doesnt Gallery detect this? No help available No keyword help available Path to an item (eg, /album/image.jpg.html) Please create a file in your Gallery directory named .htaccess Please make sure Gallery can read the existing .htaccess file Please make sure Gallery can write to the existing .htaccess file Please update your rules while in embedded mode. Hit the Save button should be sufficient. Processing... Public path: Rules Save Setup Short URLs are compiled out of predefined keywords. Modules may provide additional keywords. Keywords are escaped with % (eg: %itemId%). Show Item Some rules only apply if the referer (the site that linked to the item) is something other than Gallery itself. Hosts in the list below will be treated as friendly referers. Status: Active Status: Error Status: Not Active Success Successfully saved URL styles Successfully saved the configuration Test Test .htaccess File Again Test .htaccess Files Again Test Webserver Again Test mod_rewrite Test mod_rewrite manually Test mod_rewrite with Options directive This checks if the content in your embedded .htaccess file is equal to the standalone version. This will go through all your Gallery items and check if the short style URL links to an existing file or directory on your webserver. Troubleshooting URL Pattern URL Rewrite URL Rewrite Administration URL Rewrite System Checks Unit test module View Warning Works You need a <b>.htaccess</b> file in the embedded access point directory. Project-Id-Version: Gallery: Rewrite 1.0
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2005-06-11 18:26+0200
PO-Revision-Date: 2005-08-09 14:08+0200
Last-Translator: Jan Korbel <jackc@teptin.net>
Language-Team: Czech <cs@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);
 404 Soubor nenalezen Aktivovat Dodatečná klíčová slova Při ukládání nastavení došlo k chybě: Apache mod_rewrite Schválené zdroje Špatné klíčové slovo. Špatná cesta: Blokovat přímý přístup k položkám (položky je možné zobrazit pouze v html kódu Galerie) Nelze zapsat do souboru .htaccess Nelze zapsat soubor .htaccess pro embedding Kontrola krátkých URL z důvodů konfliktů v souborovém systému Zkontrolováno %d položek a nalezeno %d konfliktů Kontroluji položku %d z %d Uživatelské nastavení testovacího adresáře Galerie Hotovo Stáhnout položku Zdvojená URL schéma. Soubor .htaccess pro embedding Soubor .htaccess pro vnořování je aktuální Nastavení embedded Prázdná URL schéma. Aktivace krátkých URL pomocí mod_rewrite Zajišťuje aby prohlížeče nepoužívali nacachovanou verzi změněného obrázku Chyba Chyba: 404 Soubor nenalezen Pro fungující přepis URL v embedded prostředí je potřeba zvláštní htaccess soubor pro mod_rewrite pravidla. Z nějakého důvodu se nepodařilo najít funkční nastavení pro mod_rewrite. Pokud jste přesvědčeni, že mod_rewrite funguje, můžete potlačit automatickou detekci. Mohou Vám pomoci i následující testy. Galerie Soubor Galerie .htaccess Galerie se pokusí otestovat mod_rewrite v akci. Pokud to má fungovat, musíte upravit tyto dva soubory: Pro přepis URL Galerie je potřeba vytvořit ve Vašem hlavním adresáři Galerie nový soubor <b>.htaccess</b>, který bude obsahovat pravidla, podle kterých budou interpretovány krátké URL adresy. Jděte na stránku <a href="%s">Gallery phpinfo</a> a hledejte Loaded Modules. Měl by tam být modul mod_rewrite. Jděte na stránku <a href=%s>Nastavení</a>, kde můžete více vyzkoušet mod_rewrite. Nápověda Jak mohu zkontrolovat, zda je Apache modul mod_rewrite aktivní? Cesta k htaccess: Vím, že je modul mod_rewrite aktivní, proč mi ale Galerie říká, že nefunguje? Pokud se u jednoho z těchto dvou testů objeví text PASS_REWRITE, zdá se že to funguje. Pokud jste správce serveru, přesvědčte se zda má hlavní adresář Galerie správná AllowOverride práva. Galerie potřebuje aby mohla definovat vlastní FileInfo a Options. Na konec Vaší konfigurace Apache serveru vložte následující: Pokud má tento modul fungovat, musí být ve Vašem Apache serveru zapnuto %s. Neplatný adresář. Neplatná cesta. Jméno souboru položky (např. image.jpg) Klíčová slova Řádka 6: Moje Galerie používá Apache modul mod_auth pro zabezpečení heslem. Vím, že mod_rewrite funguje, tak proč ho Galerie nedetekuje? Nápověda není k dispozici Nápověda ke klíčovým slovům není dostupná Cesta k položce (např. /album/image.jpg.html) Prosím vytvořte v adresáři Vaší Galerie soubor .htaccess Prosím ujistěte se, zda Galerie může číst existující soubor .htaccess Prosím ujistěte se, zda Galerie může zapisovat do existujícího souboru .htaccess Prosím zaktualizujte pravidla pro mód vnořování. Mělo by stačit kliknout na tlačítko Uložit. Pracuji... Veřejná cesta: Pravidla Uložit Nastavení Krátká URL se skládají z přednastavených klíčových slov. Moduly mohou poskytovat dodatečná klíčová slova. Klíčová slova jsou escapována znakem % (např.: %itemId%). Zobrazit položku Některá pravidla jsou aplikována pouze v případě, kdy zdrojem není Galerie sama (zdroj je stránka která ukazuje na položku). Počítače na seznamu níže budou považovány za přátelské zdroje. Stav: Aktivní Stav: Chyba Stav: Neaktivní OK Úspěšně uloženy styly URL Konfigurace úspěšně uložena Zkouška Ještě jednou otestovat soubor .htaccess Ještě jednou otestovat soubory .htaccess Ještě jednou otestovat webový server Test mod_rewrite Vyzkoušet mod_rewrite ručně Zkouška mod_rewrite s direktivou Options Tyto kontroly testují, zda obsah souboru .htaccess odpovídá samostatné verzi. Tato kontrola projde všechny položky Galerie a zkontroluje zda krátké URL odkazují na existující adresář na Vašem webovém serveru. Hledání chyb URL schéma Přepis URL Správa přepisu URL Systémové kontroly přepisu URL Modul jednotky testování Zobrazit Varování Funguje Potřebujete soubor <b>.htaccess</b> v přístupovém adresáři vnořování. 