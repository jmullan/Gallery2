��    n      �  �   �      P	  *   Q	  (   |	  %   �	  �   �	    �
  
   �     �     �     �  D   �  �   4     0     >     D     K  "   S  	   v  	   �     �  |   �          -     ;     I  U   W     �  Y   �  2   &  
   Y  �   d     �     �       a        u  �  �     &  '   3     [     u  A   �  ?   �     
  �   #     �     �  >   �  D  :  A        �  �   �     ~     �     �     �     �     �     �     �     �               (     9  "   G      j  *   �  	   �     �     �     �    �  "        *     9  '   M     u     |     �     �     �     �     �          
  @     >   S     �  %   �  C   �  B     ?   G  -   �     �     �  -   �       	     1     \   M  
   �     �     �     �     �  �   �  $   �  $   �  I   �  �  D  B      ?   E   2   �   �   �   3  �!     �"     �"     �"     #  G   #    b#     u$     �$     �$  
   �$     �$     �$     �$     �$  {   �$     f%     %     �%     �%  P   �%     �%  N   &  C   ]&     �&  �   �&     c'  
   j'     u'  d   |'     �'  �  �'     �)  2   �)     *     )*  :   <*  F   w*     �*  �   �*     �+     �+  D   �+  e  ,  R   |-     �-  �   �-     �.     �.     �.     �.     �.     �.     �.     /     /     /     ,/     B/     Q/     e/  *   ~/  )   �/     �/     �/     �/     0    0      11     R1     d1  .   �1     �1     �1     �1  #   �1     2     32     O2     `2     g2  @   o2  K   �2  
   �2      3  C   (3  A   l3  P   �3  $   �3     $4     94  )   Q4     {4     �4  A   �4  ]   �4     /5     ;5     O5     a5     x5  �   �5  ,   W6  %   �6  ?   �6             C      .   U   c       8   A       1   3   T   V   d       =   $   ?              0   '             4       e   
   7   >   H                 	              i       k   5          2   Z   W       m   ;   %      j   f   \   L                 [   9   F          E                    <   &   6       :      )   ^                   (         !          B   Y   R   *          N   /      b       S       l      J   n   _   g   "          I   K      ,       @   D       G   h   ]           P   +   a                         `      M   X   O   #       -      Q    %sSummary%s was truncated for %sitem %d%s. %sTitle%s was truncated for %sitem %d%s. (Default to summary value if not set) <b>Note:</b> Before you import any data you should make sure your Gallery 1 is installed correctly by adding a photo through the Gallery 1 web interface.  Make sure you resolve any errors you see there first. Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories. Note that these redirects are not active until the G1 images are actually removed or moved. Omit the !-f line shown below to redirect anyway. Album Name Album Notes Album Title Albums to import: An album already exists with this name.  This album will be renamed. Any hidden albums or items will be imported with restricted view permissions. Activate the Hidden Items module before migration to import these as "hidden" which means they are invisible to guest users until accessed by the direct URL for those items. Base filename Blank Cancel Caption Character Encoding of Source Text: Check All Clear All Confirm Migration Copy all or part of an existing Gallery 1 installation into your Gallery 2.  It won't modify your Gallery 1 data in any way. Creating thumbnails Custom Field: Custom field: Custom fields Custom fields imported into item fields above will not be duplicated as custom fields Custom fields will be imported Custom fields will not be imported.  Activate Custom Fields module to enable this option. Default to same as summary if custom field not set Delete All Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries? Description Description: %s Destination: Do not create Gallery 2 custom fields for fields selected above for title, summary or description Download .htaccess file Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. Remove G1 rewrite rules from an existing file. Redirects will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be. However, if you also use the G2 URL Rewrite module then activate the G1 redirect rule in that module instead of using the block shown below. Encoding: %s Ensure the %s Apache module is enabled. Enter a custom field name Error importing %s Error while importing %d album. Errors while importing %d albums. Error while importing %d user. Errors while importing %d users. Example: /var/www/albums G1 URL redirect. Use only if G2 is installed where G1 used to be and you have run a G1 import with the URL redirect option selected. Otherwise follow instructions in %sMigrate Site Admin%s. G1 path G1-&gt;G2 Mapping G1-&gt;G2 mappings will be recorded for use in URL Redirection Gallery 2 has the following fields for all items and albums: title, summary text shown with thumbnails and description text shown in item or album view. G1 albums already have these three items (though the names of summary and description are reversed). G1 items have only a filename and caption. For items imported into G2: Gallery can redirect old Gallery1 URLs to the new Gallery2 pages. Hidden Items If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file "gallery_remote2.php" file before you can use Gallery Remote to upload images to G2. Import Import %s now. Import Albums Import Complete Import Users Import custom fields Import from Gallery 1 Import more data Imported %s Importing Photos Importing Users Invert Selection Item captions Item fields will be imported from: Map entries deleted successfully Migrate your Gallery 1 albums to Gallery 2 Migration No albums imported. No available users No users imported. Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster. Path to Gallery 1 albums directory Prepare Import Recently Used Paths Record G1-&gt;G2 mappings during import Select Select Albums and Users Select the albums to migrate Select the users to migrate Set description from: Set summary from: Set title from: Set: Source: Successfully imported %d album. Successfully imported %d albums. Successfully imported %d user. Successfully imported %d users. Summary The path that you entered is invalid. There is one G1-&gt;G2 map entry There are %d G1-&gt;G2 map entries These users are already in your gallery, and will not be imported: This album has an illegal name and will be renamed to <i>%s</i> This album's owner (%s) hasn't been imported. Thumbnail %d of %d Thumbnail generation Thumbnails will be generated during migration Title Title: %s To enable URL Redirection under Apache webserver: Top level albums and albums whose parents are not selected will be imported into this album: Truncated: URL Redirection Username Users to import: You did not enter a path. You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the %sModules%s page to activate a Graphics Toolkit. You must choose something to import! You must specify a custom field name Your Gallery 1 will be converted from this character encoding into UTF-8: Project-Id-Version: Gallery: Migration 1.0.10
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2006-12-20 07:46-0800
PO-Revision-Date: 2007-03-11 11:38+0200
Last-Translator: Jyrki Heinonen <jyrki.heinonen@gmail.com>
Language-Team: Finnish <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 %3$sKohteen %4$d%5$s %1$syhteenveto%2$s jouduttiin lyhentämään. %3$sKohteen %4$d%5$s %1$sotsikko%2$s jouduttiin lyhentämään. (Oletuksena yhteenvedon arvo, jos ei ole asetettu) <b>Huomioi:</b>Ennen kuin tuot mitään dataan, sinun pitää varmistua siitä, että Gallery1 on asennettu oikein lisäämällä kuva Gallery1:n webbikäyttöliittymän kautta. Selvitä kaikki mahdolliset virheet ensin siltä puolelta. Lisää sama <tt>.htaccess</tt> lohko Gallery1 albumien kansioon jos haluat uudelleenohjaukset myös kuviin ja albumien kansioihin. Huomioi, että nämä uudelleenohjaukset eivät tule voimaan ennen kuin G1 kuvat ovat poistettu tai siirretty. Jätä pois alla näkyvä !-f rivi, jos haluat kuitenkin ohjata. Albumin Nimi Albumin Kommentit Albumin Otsikko Tuotavat albumit: Saman niminen albumi on jo olemassa. Tämä albumi uudelleennimetään. Piilotetut albumit ja kohteet tuodaan rajoitetuilla katseluoikeuksilla. Aktivoi piilotetut kohteet moduuli ennen migraatiota tuodaksesi nämä kohteet /"piilotettuina"/, joka tarkoittaa sitä, että ne ovat näkymättömiä vieraille ennenkuin niihin menee suoralla URL:lla. Tiedostonimi Tyhjä Peruuta Kuvateksti Lähteen Merkistö (Encoding): Valitse Kaikki Poista Valinnat Vahvista Siirto Kopioi kaikki tai osa olemassaolevasta Gallery1:n asennuksesta Gallery2:een. Se ei muokkaa Gallery1:stä millään tavalla. Luomassa Esikatselukuvia Lisäkenttä: Lisäkentät: Lisäkentät Ylläoleviin kohteen kenttiin tuodut lisäkentät eivät kopioidu lisäkentiksi. Lisäkentät tuodaan Lisäkenttiä ei tuoda. Aktivoi lisäkenttämoduuli mahdollistaaksesi tämän. Oletuksena sama kuin yhteenveto, jos lisäkenttää ei ole asetettu Poista kaikki Ohjausmerkintöjen poistaminen aiheuttaa sen, että vanhat G1 URLit tuottavat 'sivua ei löytynyt' virheen, eivätkä ohjaudu oikeille G2 sivuille. Poistetaanko kaikki merkinnät? Kuvaus Kuvaus: %s Kohde: Älä luo Gallery 2 lisäkenttiä yläpuolella valituille otsikolle, yhteenvedolle tai selitykselle. Lataa .htaccess-tiedosto Muokka tai luo tiedosto nimeltä <tt>.htaccess</tt> Gallery1 kansioon ja lisää allaoleva siihen allaoleva teksti. Poista G1 uudelleenkirjoitussäännöt olemassaolevasta tiedostosta. Uudelleenohjaukset toimivat myös Gallery2:n kansiosta, jos se on sama missä G1 aikaisemmin oli. Kuitenkin, jos kuitenkin käytät myös G2:n URL uudelleenkirjoitusmoduulia, aktivoi G1:n uudelleenohjaussäännöt siinä moduulissa sen sijaan, että käyttäisit alla olevaa lohkoa. Merkistö: %s Varmista, että Apachen moduuli %s on käytössä. Syötä lisäkentän nimi Virhe tuotaessa %s Virhe tuotaessa yhtä albumia. Virhe tuotaessa %d albumia. Virhe tuotaessa yhtä käyttäjää. Virhe tuotaessa %d käyttäjää. Esimerkki: /var/www/albums G1 URL uudelleenohjaus. Käytä vain jos G2 on asennettu paikkaan jossa G1 oli ennen ja olet ajanut G1 tuonnin URL uudelleenohjausoptio valittuna. Muussa tapauksessa seuraa ohjeita sivulla %sSiirron Sivuston Ylläpito%s. G1 polku G1-&gt;G2 Muunnos G1-&gt;G2 ohjausmerkinnät tallennetaan URL uudelleenohjausta varten Gallery2:ssa on seuraavat kentät kaikille kohteille ja albumeille: otsikko, yhteenveto esikatselukuville ja selitys näkyvissä joko kohde- tai albuminäkymässä. G1 albumeilla on jo nämä kolme (vaikkakin yhteenvedon ja selityksen tekstit ovat toisinpäin). G1:n kohteilla on ainoastaan tiedostonnimi ja kuvateksti. Kohteilla, jotka siirretään G2:een: Galleria voi uudelleenohjata vanhan gallery1:n URL:it uusille Gallery2:n sivuille. Piilotetut kohteet Jos G2 on asennettu samaan polkuun, missä G1 sijaitsi, sinun täytyy poistaa G1:n tiedosto "gallery_remote2.php" ennen kuin voit käyttää Gallery Remotea kuvien siirtämiseen G2:een. Tuo Tuo %s nyt. Tuo Albumit Tuonti Valmis Tuo Käyttäjät Tuo kustomoidut kentät Tuo Gallery 1:sta Tuo lisää tietoa Tuotu %s Tuomassa Kuvia Tuomassa Käyttäjiä Vaihda Valitut Kohteiden otsakkeet Kohteen kentät tuodaan: Ohjausmerkinnät poistettiin onnistuneesti Siirtä Gallery 1:n albumit Gallery 2:een Siirto Albumeja ei tuotu. Ei käyttäjiä saatavilla Käyttäjiä ei tuotu. Yleensä Galleria tekee esikatselukuvat kun ensimmäistä kertaa katsot niitä ja samalla tallentaa ne seuraavia kertoja varten. Jos valitset tämän toiminnon, luomme esikatselukuvat jo siirron aikana. Siirto kestää pitempään, mutta albumin katselu tapahtuu nopeammin. Polku Gallery 1:n albumikansioon Valmistele Tuonti Lähiaikoina käytetyt polut Tallenna G1-&gt;G2 kohdistukset tuonnin aikana Valitse Valitse Albumit ja Käyttäjät Valitse siirrettävät albumit Valitse siirrettävät käyttäjät Aseta kuvaus täältä: Aseta yhteenveto täältä: Aseta otsikoksi: Aseta: Lähde: Onnistuneesti tuotu yksi albumi. Onnistuneesti tuotu %d albumia. Onnistuneesti tuotu yksi käyttäjä. Onnistuneesti tuotu %d käyttäjää. Yhteenveto Antamasi hakemisto on epäkelpo. On yksi G1-&gt;G2 ohjausmerkintä On %d G1-&gt;G2 ohjausmerkintää Seuraavat käyttäjät ovat jo galleriassa joten niitä ei tuoda: Tällä albumilla on kielletty nimi ja se uudelleennimetään nimellä <i>%s</i> Albumin omistajaa (%s) ei ole tuotu. Esikatselukuva %d/%d Esikatselukuvien luonti Esikatselukuvat luodaan migraation aikana Otsikko Otsikko: %s Mahdollistaaksesi URL uudelleenohjauksen apache web-palvelimella: Ylätason albumit ja albumit, joiden vanhempia ei ole valittu, siirretään tähän albumiin: Lyhennetty: URL Uudelleenohjaus Käyttäjätunnus Tuotavat käyttäjät: Et antanut polkua. Sinulla ei ole yhtän grafiikkatyökalua aktivoituna, joka käsittelisi JPEG-kuvia. Jos tuot kuvat nyt, sinulle ei tule yhtään esikatselukuvaa. Käy %smoduulit%s sivulla aktivoimassa grafiikkatyökalu. Sinun täytyy määritellä jotain tuotavaa! Määrittele kustomoidun kentän nimi Galleria 1 muunnetaan tästä merkistöstä UTF-8 merkistöön: 