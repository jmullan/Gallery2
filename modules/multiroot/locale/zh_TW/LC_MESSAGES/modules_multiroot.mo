Þ          Ä      l      à     á     ö  -   
     8     @  %   O     u  	         6        È     Î    å  Ù  }  ¾  W     
     .
  5   D
  !   z
     
  ·  ©
     a     w  *        ¸     ¿  *   Ì     ÷       ÷     B        O     V  p  l  ¶  Ý  z            +  3   G     {                	                   
                                                                    Alternate guest user Configure Multiroot Define an alternate guest view of the Gallery Display Generate Files Leave blank to define a virtual root. Missing value Multiroot Multiroot allows you to create an alternate URL to view part of the Gallery.  This configuration screen assists in setup and creation of a PHP file for the alternate URL.  This module never activates and is not needed to use multiroot.  There are two options: New user will be created if given name does not exist. Reset Root album of new view The original/real guest user must have view permission for all items accessible by any alternate guest user.  The form below assists in creation of an alternate guest and will assign view permission for the default album and all subalbums/items.  If these albums are already public and can remain that way, no more setup is required.  Setup for mutually exclusive views is more complicated: the original guest user must have access to items in all views, so first setup those permissions.  Then use the tools here to create each alternate view.  Just use the set of alternate URLs.  Keep the original Gallery URL unpublished as it shows the combined set of items. This option defines a default album for this view and adjusts navigation links so that no parent albums above the default are shown.  Both guests and logged in users accessing the alternate URL will see this effect.  However, Gallery permissions are unchanged so modules like imageblock and search, or manually entered URLs, can lead visitors to items outside the default album.  This option is easier to setup as it uses guest permissions already defined for your Gallery. This option defines a new guest view with permissions defined for exactly what this view should display.  Guests using the alternate URL cannot see any items outside those granted permission, by browsing or via any modules or URLs.  Logged in users see whatever their permissions allow, whether accessing the normal or alternate URL.  This option provides greater access control over the alternate view, but requires additional permissions setup: URI for new guest view: URI for this Gallery: User created and permissions assigned on target album Username of alternate guest user: Virtual root Project-Id-Version: Gallery: Multiroot 0.9.0
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2006-09-12 11:50-0700
PO-Revision-Date: 2005-08-24 14:00-0400
Last-Translator: Stephen Chu <stephen@ju-ju.com>
Language-Team: Chinese Traditional <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 ä»£ç¨çè¨ªå®¢ç¨æ¶ è¨­å®å¤éæ ¹ç¸ç°¿ å®ç¾©è¨ªå®¢çå°çä¸å Gallery ç«é¢ é¡¯ç¤º ç¢çæªæ¡ çç©ºè¡¨ç¤ºå®ç¾©ä¸åèæ¬æ ¹ç¸ç°¿ã æ²ææ¸å¼ å¤éæ ¹ç¸ç°¿ å¤éæ ¹ç¸ç°¿è®ä½ ç¢çä¸åä»£ç¨çç¶²åä¾é¡¯ç¤ºé¨åç Galleryãéåè¨­å®ç«é¢æåå©ä½ è¨­å®åç¢çä»£ç¨ç¶²åç¨ç PHP æªãéåæ¨¡çµæ°¸é ä¸æä¹ä¸éè¦åç¨æè½ä½¿ç¨å¤éæ ¹ç¸ç°¿ãéè£¡æå©åé¸æï¼ å¦ææå®çç¨æ¶ä¸å­å¨ï¼æèªåç¢çä¸åæ°ç¨æ¶ã éç½® æ°ç«é¢çæ ¹ç¸ç°¿ å°ææè¦è®ä»£ç¨çè¨ªå®¢ç¨æ¶çå°çé ç®ï¼åå§ï¼çæ­£ï¼çè¨ªå®¢ç¨æ¶å¿éææ¥ççæ¬éãä¸é¢çè¡¨æ ¼æåå©ä½ ç¢çä¸åä»£ç¨çè¨ªå®¢ä¸¦è¨­å®é è¨­ç¸ç°¿åææå­ç¸ç°¿åé ç®çæ¥çæ¬éãå¦æéäºç¸ç°¿å·²ç¶æ¯å¬éï¼å°±ä¸å¿ä½é²ä¸æ­¥çè¨­å®ãç¨ä½çé¡¯ç¤ºè¨­å®æ¯è¼è¤éï¼åå§ï¼çæ­£ï¼çè¨ªå®¢ç¨æ¶å¿éè½å¤ æ¥çææçé¡¯ç¤ºä¸­çé ç®ï¼æä»¥è«åè¨­å®å¥½é£äºæ¬éãåä½¿ç¨éè£¡çå·¥å·ä¾ç¢çåå¥çæ¿ä»£ç«é¢ãç¶å¾åªä½¿ç¨éäºæ¿ä»£ç¶²åãä¸è¦å¬ä½åä¾ Gallery çç¶²åï¼å çºé£æé¡¯ç¤ºææçé ç®ã éåé¸é çºéåé¡¯ç¤ºå®ç¾©ä¸åé è¨­ç¸ç°¿ä¸¦èª¿æ´å°è¦½éæ¥ï¼é±èé è¨­ç¸ç°¿ä»¥ä¸çç¸ç°¿ãä½¿ç¨éåç¶²åçè¨ªå®¢åç»å¥ç¨æ¶é½æçå°éåææãä¸é Gallery çæ¬éä¸¦æ²ææ¹è®ï¼æä»¥ååååå¡åæå°ç­æ¨¡çµææåè¼¸å¥çç¶²åï¼éæ¯å¯ä»¥å°è¨ªå®¢å¸¶å°é è¨­ä¹å¤çç¸ç°¿ãéåé¸é æ¯è¼å®¹æè¨­å®ï¼å çºå®ä½¿ç¨ä½ ç Gallery ä¸­å·²ç¶å®ç¾©å¥½çè¨ªå®¢æ¬éã éåé¸é å®ç¾©ä¸åæ°çè¨ªå®¢ç«é¢åéåç«é¢çé¡¯ç¤ºæ¬éãä½¿ç¨ä»£ç¨ç¶²åçè¨ªå®¢ç¡æ³çå°ä»»ä½ä¸è¢«åè¨±çé ç®ï¼ä¸è«æ¯ç¶ç±å°è¦½æä»»ä½æ¨¡çµæç¶²åãç»å¥çç¨æ¶å¯ä»¥çå°ä»»ä½ä»åçæ¬éåè¨±çé ç®ï¼ä¸è«æ¯ç¶ç±æ­£å¸¸æä»£ç¨çç¶²åãéåé¸é æä¾è¼é«çå­åæ§å¶ï¼ä½æ¯éè¦é¡å¤çæ¬éè¨­å®ï¼ æ°çè¨ªå®¢ç«é¢ç¶²åï¼ éå Gallery çç¶²åï¼ ç¨æ¶å·²ç¢çä¸¦æå®ç®æ¨ç¸ç°¿çä½¿ç¨æ¬é ä»£ç¨çè¨ªå®¢ç¨æ¶åç¨±ï¼ èæ¬æ ¹ç¸ç°¿ 