Þ    o                 `	     a	  *   i	  (   	  %   ½	  Ð   ã	    ´
  
   Ò     Ý     é     õ  D     û   L     H     V     \     c  "   k  	     	        ¢  |   ´     1     E     S     a  U   o     Å  Y   ä  2   >  
   q     |                 a   +         ¥     >  '   K     s       A      ?   â     "  :   ;     v     ~  ;     D  Ì  A        S  ¯   `               &     4     D     Q     f     |               ª     º     Ë  "   Ù      ü  *     	   H     R     f     y      "        ¼     Ë  $   ß               #     @     \     r                 @   ¡  >   â     !  %   )  =   O  B     ?   Ð  -        >     Q  -   f       	     1   ¤  \   Ö  
   3     >     N     W     h  Ã     $   F  $   k  I       Ú  
   h  2   s  2   ¦  -   Ù  ¿      0  Ç      ø!     "     "     "  6   /"  á   f"     H#     U#     \#     c#     j#     #     #     £#  y   °#     *$     :$     J$     X$  N   e$     ´$  N   Í$  9   %     V%     c%     ñ%  
   þ%     	&  Y   &     s&  ±  &  
   =(  )   H(     r(     (  %    (  %   Æ(     ì(  J   )  	   P)     Z)  8   k)  O  ¤)  I   ô*     >+  ¤   K+     ð+     ÷+     	,     ,     #,     0,     C,     [,     n,     z,     ,     ,     ¡,     ®,     Ë,  1   ä,     -     -     6-     L-  ø   e-  #   ^.     .     .  2   ¥.     Ø.     ß.     õ.     /     '/     @/     S/  	   f/  	   p/     z/     /     ´/     »/  2   ×/  ?   
0  ?   J0  2   0     ½0     Ø0  $   è0     1     1  8    1  U   Y1  	   ¯1     ¹1     Æ1     Ó1     ã1  °   ü1  $   ­2  '   Ò2  <   ú2             D      /   V   d       9   B       2   4   U   W   e       >   %   @          !       (             5       f      8   ?   I                 
              j          1          3   [   X       n   <   &      k   N   ]   M                      :   G          F                    =   '   7       ;      *   _                   )         "          C   Z   S   +          O   0   	   c   \   T   6   m      K   o   `   h   #          J   L      -       A   E       H   i   ^       l   Q   ,   b      R                  a      g   Y   P   $              .    %s (%s) %sSummary%s was truncated for %sitem %d%s. %sTitle%s was truncated for %sitem %d%s. (Default to summary value if not set) <b>Note:</b> Before you import any data you should make sure your Gallery 1 is installed correctly by adding a photo through the Gallery 1 web interface.  Make sure you resolve any errors you see there first. Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories. Note that these redirects are not active until the G1 images are actually removed or moved. Omit the !-f line shown below to redirect anyway. Album Name Album Notes Album Title Albums to import: An album already exists with this name.  This album will be renamed. Any hidden albums or items will be imported with restricted view permissions. Activate the Hidden Items module before migration to import these as "hidden" which means they are invisible to guest users until accessed by the direct URL for those items. Base filename Blank Cancel Caption Character Encoding of Source Text: Check All Clear All Confirm Migration Copy all or part of an existing Gallery 1 installation into your Gallery 2.  It won't modify your Gallery 1 data in any way. Creating thumbnails Custom Field: Custom field: Custom fields Custom fields imported into item fields above will not be duplicated as custom fields Custom fields will be imported Custom fields will not be imported.  Activate Custom Fields module to enable this option. Default to same as summary if custom field not set Delete All Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries? Description Description: %s Destination: Do not create Gallery 2 custom fields for fields selected above for title, summary or description Download .htaccess file Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. Remove G1 rewrite rules from an existing file. Redirects will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be. However, if you also use the G2 URL Rewrite module then activate the G1 redirect rule in that module instead of using the block shown below. Encoding: %s Ensure the %s Apache module is enabled. Enter a custom field name Error importing %s Error while importing %d album. Errors while importing %d albums. Error while importing %d user. Errors while importing %d users. Example: /var/www/albums G1 URL redirect. Use only if G2 is installed where G1 used G1 path G1-&gt;G2 Mapping G1->G2 mappings will be recorded for use in URL Redirection Gallery 2 has the following fields for all items and albums: title, summary text shown with thumbnails and description text shown in item or album view. G1 albums already have these three items (though the names of summary and description are reversed). G1 items have only a filename and caption. For items imported into G2: Gallery can redirect old Gallery1 URLs to the new Gallery2 pages. Hidden Items If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file "gallery_remote2.php" file before you can use Gallery Remote to upload images to G2. Import Import %s now. Import Albums Import Complete Import Users Import custom fields Import from Gallery 1 Import more data Imported %s Importing Photos Importing Users Invert Selection Item captions Item fields will be imported from: Map entries deleted successfully Migrate your Gallery 1 albums to Gallery 2 Migration No albums imported. No available users No users imported. Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster. Path to Gallery 1 albums directory Prepare Import Recently Used Paths Record G1->G2 mappings during import Select Select Albums and Users Select the albums to migrate Select the users to migrate Set description from: Set summary from: Set title from: Set: Source: Successfully imported %d album. Successfully imported %d albums. Successfully imported %d user. Successfully imported %d users. Summary The path that you entered is invalid. There is one G1->G2 map entry There are %d G1->G2 map entries These users are already in your gallery, and will not be imported: This album has an illegal name and will be renamed to <i>%s</i> This album's owner (%s) hasn't been imported. Thumbnail %d of %d Thumbnail generation Thumbnails will be generated during migration Title Title: %s To enable URL Redirection under Apache webserver: Top level albums and albums whose parents are not selected will be imported into this album: Truncated: URL Redirection Username Users to import: You did not enter a path. You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the <a href="%s">Modules</a> page to activate a Graphics Toolkit. You must choose something to import! You must specify a custom field name Your Gallery 1 will be converted from this character encoding into UTF-8: Project-Id-Version: Gallery: Migration 1.0.2
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2005-08-04 17:53-0400
PO-Revision-Date: 2005-08-04 17:53-0400
Last-Translator: Stephen Chu <stephen@ju-ju.com>
Language-Team: Chinese Traditional <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 %sï¼%sï¼ %3$sé ç®%4$d%5$sç%1$sæè¦%2$sè¢«åªç¯äºã %3$sé ç®%4$d%5$sç%1$sä¸»é¡%2$sè¢«åªç¯äºã ï¼å¦æªè¨­å®åé è¨­çºåæè¦ç¸åï¼ <b>æ³¨æï¼</b>å¨å¼é²ä»»ä½è³æä¹åä½ æè©²åéé Gallery 1 çç¶²é çé¢å å¥ä¸åç§çä»¥ç¢ºèªä½ ç Gallery 1 å®è£æ­£å¸¸ãç¢ºå®ä½ è§£æ±ºäºä»»ä½é­éå°çé¯èª¤ã å¦æä½ å¸ææå°åçæªæ¡æç¸ç°¿ç®éçéµæ¥ä¹è½å°æ°çä½ç½®ï¼è«å¨ Gallery 1 ç¸ç°¿ç®éä¸­å ä¸ä¸æ¨£ç <tt>.htaccess</tt> åå¡ãè«æ³¨æéäºéå°éµæ¥å¨ G1 çåçæ²æççåªé¤æç§»åä¹åæ¯æ²æä½ç¨çãæä¸é¢é¡¯ç¤ºç !-f è¡çç¥ä»¥å¼·å¶è½åã ç¸ç°¿åç¨± ç¸ç°¿æ³¨é ç¸ç°¿ä¸»é¡ å¼é²ç¸ç°¿ï¼ ååç¸ç°¿å·²ç¶å­å¨ãéåç¸ç°¿å°è¢«æ¹åã ä»»ä½é±èçç¸ç°¿æé ç®å°ä»¥éå¶è§ççæ¬éå¼é²ãå¨é·ç§»åæéé±èé ç®æ¨¡çµæä½¿éäºé ç®å¼é²æãé±èãï¼è¡¨ç¤ºé¤éç¨ç´æ¥æå°å®åçç¶²åéæ¥ï¼è¨ªå®¢çä¸å°éäºé ç®ã æªæ¡åç¨± ç©ºç½ åæ¶ èªªæ ä¾æºæå­çå­åç·¨ç¢¼ï¼ é¸æå¨é¨ æ¸é¤å¨é¨ ç¢ºèªé·ç§» å°ç¾æ Gallery 1 çå¨é¨æé¨åæªæ¡æ·è²å°ä½ ç Gallery 2 ä¸­ãéå®å¨ä¸ææ´åä½ ç Gallery 1 è³æ. å»ºç«ç¸®ç¥å èªå®æ¬ä½ï¼ èªå®æ¬ä½: èªå®æ¬ä½ å¼é²å°ä¸åé ç®æ¬ä½çèªå®æ¬ä½å°ä¸æè¢«è¤è£½çºèªå®æ¬ä½ã èªå®æ¬ä½å°è¢«å¼é² èªå®æ¬ä½å°ä¸è¢«å¼é²ãåç¨èªå®æ¬ä½æ¨¡çµä»¥åç¨éåé¸é ã å¦ææ²æè¨­å®èªå®æ¬ä½ï¼é è¨­çºåæè¦ç¸å åªé¤å¨é¨ åªé¤å°æ é ç®æä½¿èç Gallery 1 ç¶²åç¢ç HTTP æ¾ä¸å°ç¶²é çé¯èª¤ï¼èä¸æ¯è½å° G2 é é¢ãè¦åªé¤ææé ç®åï¼ è©³ç´°æè¿° æè¿°: %s ç®æ¨ä½ç½®ï¼ è«å¿çºä¸é¢é¸æçä¸»é¡ãæè¦ææè¿°ç­æ¬ä½ç¢ç Gallery 2 çèªå®æ¬ä½ ä¸è¼ .htaccess æªæ¡ è«å¨ Gallery 1 ç®éä¸­ç·¨è¼¯æç¢çä¸ååçº <tt>.htaccess</tt> çæªæ¡ï¼ä¸¦å°ä¸é¢é¡¯ç¤ºçæå­å å¥è©²æªæ¡ä¸­ãåªé¤ç¾ææªæ¡ä¸­ G1 çéå°è¦åãå¦æä½ ç Gallery 2 å®è£å¨åä¾ Gallery 1 çè·¯å¾ä½ç½®ï¼éå°åè½ä¹æå¨ Gallery 2 ç®éä¸­åä½ãä½æ¯å¦æä½ åæä½¿ç¨ G2 çç¶²åæ¹å¯«æ¨¡çµï¼åè«æ G1 çéå°è¦åå å¨é£åæ¨¡çµä¸­ï¼èä¸è¦ä½¿ç¨ä¸é¢çæå­ã ç·¨ç¢¼: %s è«ç¢ºèª %s Apache æ¨¡çµå·²ç¶éåã è¼¸å¥ä¸åèªå®æ¬ä½åç¨± å¼é²%sé¯èª¤ å¼é² %d åç¸ç°¿æç¼çé¯èª¤ã å¼é² %d ä½ç¨æ¶æç¼çé¯èª¤ã ä¾å¦ï¼/var/www/albums G1 ç¶²åéå°ãåªæå¨ G2 æ¯å®è£å¨ G1 åä¾çä½ç½®ä¸æä½¿ç¨ G1 è·¯å¾ G1 å° G2 å°æ  Gallery 1->Gallery 2æ å°å°è¢«è¨éç¨æ¼ç¶²åéå° Gallery 2 çææé ç®åç¸ç°¿é½æä¸åæ¬ä½ï¼ä¸»é¡ãåç¸®ç¥åä¸åé¡¯ç¤ºçæè¦ä»¥ååé ç®æç¸ç°¿ä¸åé¡¯ç¤ºçè©³ç´°æè¿°ãGallery 1 ç¸ç°¿å·²åå«éä¸åæ¬ä½ï¼éç¶æè¦åè©³ç´°æè¿°çåç¨±æ¯ç¸åçï¼ãGallery 1 é ç®åªæä¸åæªæ¡åç¨±åèªªæãè¦å¼é² Gallery 2 ä¸­çé ç®ï¼ ååº«å¯ä»¥æåä¾ç Gallery 1 ç¶²åè½å°æ°ç Gallery 2 é é¢ã é±èé ç® å¦æ G2 aæ¯å®è£å¨åä¾ G1 ç®éä¸­ï¼ä»¥åï¼ä½ å¿éåªé¤ G1 çãgallery_remote2.phpãæªæ¡ï¼æè½ä½¿ç¨ Gallery é ç«¯ä¸å³ä¸å³åçå° G2ã å¼é² é¦¬ä¸å¼é²%sã å¼é²ç¸ç°¿ å¼é²å®æ å¼é²ç¨æ¶ å¼é²èªå®æ¬ä½ å¾ Gallery 1 ä¸­å¼é² å¼é²æ´å¤è³æ å·²å¼é²%s å¼é²ç§ç å¼é²ç¨æ¶ ååé¸æ é ç®èªªæ é ç®æ¬ä½å°è¢«å¼é²èª: å°æ é ç®åªé¤æå æä½ ç Gallery 1 ç¸ç°¿é·ç§»å° Gallery 2 ä¸­ é·ç§» æ²æç¸ç°¿è¢«å¼é²ã æ²æå¯ç¨çç¨æ¶ æ²æç¨æ¶è¢«å¼é²ã ä¸è¬ææ³ä¸ï¼Gallery å°å¨ä½ ç¬¬ä¸æ¬¡è§çæç¢çç¸®ç¥åï¼ç¶å¾ä¿å­ç¸®ç¥åä¾å¾çºä½¿ç¨ãå¦æä½ å¾é¸éåé¸é ï¼ç¸®ç¥åå°å¨é·ç§»æå»ºç«ãé·ç§»ææéç¨é·ä½ä½ ç¬¬ä¸æ¬¡è§çç¸ç°¿æéåº¦å°æå¿«å¾å¤ã å° Gallery 1 ç¸ç°¿ç®éçè·¯å¾ æºåå¼é² æè¿ä½¿ç¨çè·¯å¾ å¨å¼é²æè¨é Gallery 1 -> Gallery 2çæ å° é¸æ é¸æç¸ç°¿åç¨æ¶ é¸æè¦é·ç§»çç¸ç°¿ é¸æè¦é·ç§»çç¨æ¶ è©³ç´°æè¿°è¨­å®çºï¼ æè¦è¨­å®çºï¼ ä¸»é¡è¨­å®çºï¼ è¨­å®ï¼ ä¾æºï¼ æåå¼é² %d åç¸ç°¿ã æåå¼é² %d ä½ç¨æ¶ã æè¦ ä½ è¼¸å¥çè·¯å¾ç¡æã æ %d å Gallery 1 å° Gallery 2 çå°æ é ç® éäºç¨æ¶å·²ç¶å­å¨è Gallery ä¸­ï¼å°ä¸æè¢«å¼é²ï¼ éåç¸ç°¿æä¸åæ³çåå­ï¼å°è¢«éæ¹åçº<i>%s</i> éåç¸ç°¿çææèï¼%sï¼ä¸¦æªè¢«å¼é²ã ç¸®ç¥åç¬¬ %2$d ä¹ %1$d ç¸®ç¥åçæ ç¸®ç¥åå°å¨é·ç§»éç¨ä¸­å»ºç« ä¸»é¡ ä¸»é¡ï¼%s å¨ Apache ç¶²é ä¼ºåå¨ä¸éåç¶²åéå°åè½ï¼ é å±¤ç¸ç°¿åå¶ä»ä¸å±¤ç¸ç°¿æªè¢«é¸æçç¸ç°¿å°è¢«å¼é²å°éåç¸ç°¿ä¸­: åªç¯ï¼ ç¶²åéå° ç¨æ¶åç¨± å¼é²ç¨æ¶ï¼ ä½ ä¸¦æªè¼¸å¥è·¯å¾ã ä½ æ²æéåä»»ä½å¯èç JPEG çåå½¢å·¥å·ãå¦æä½ ç¾å¨å¼é²ï¼å°ä¸æçæä»»ä½ç¸®ç¥åãè«åå¾<a href="%s">æ¨¡çµ</a>é é¢åç¨ä¸ååå½¢å·¥å·ã ä½ å¿éé¸æè¦å¼é²çå§å®¹ï¼ ä½ å¿éæå®ä¸åèªå®æ¬ä½åç¨± ä½ çGallery 1å°æè¢«å¾éåå­åç·¨ç¢¼è½æå°UTF-8: 