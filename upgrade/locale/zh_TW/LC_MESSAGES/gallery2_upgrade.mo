Þ    {      ô  §   Ì      h
     i
     
     
     µ
  d   Õ
  5   :     p     }       	  ¨     ²     À     Ó     c     ~               ¨     Á     Í  È   Ù  u   ¢          ³     O     ^     w     ~       	       ¦     ¬  F   Ã     
       p     ÿ     !        ²     Ä     Ø     å     ø                      t   '  Ê        g  }   v     ô     ú        	   '  
   1     <     O     ^  	   g     q       +     Ç   Á       
        ¡     ©  !   ·  á   Ù  -  »  Â   é     ¬     ³  	   F  %   P     v          ±     Î     ê     
  S   )     }               ¨     ¸     Í     ã     ü       *     #   D  "   h       Õ        o  !        £     ´  (  ¼  M  å  É   3!  ¸   ý!  ´   ¶"  ·   k#    #$  8   2%  ß   k%  4   K&     &     &  3   ¨&  '   Ü&      '     ¥'     ½'  6   Ì'     (     (     +(  z  D(     ¿)     Ô)  !   ð)     *  d   1*  3   *     Ê*     Ñ*     ä*  Í   ñ*     ¿+     Ì+  w   Þ+     V,     p,     w,     ,     ,     §,     ´,  »   Á,     }-     ý-     .     	/     /     (/     //     B/     I/  ú   V/     Q0  G   c0     «0     ²0  l   Ê0  Ê   71  $   2     '2     :2     M2     `2     x2     2     2      2  	   §2     ±2  Ò   I3     4     44     ¹4  
   À4  8   Ë4  	   5  
   5     5     .5     A5     N5     [5     q5  (   5  »   ª5     f6     v6     6     6     6  È   ¶6     7      8     .9  q   59     §9     ´9     Ð9     é9     :     :     ,:     A:  X   V:     ¯:     ¶:     È:     Õ:     â:     þ:     ;     $;     1;  $   >;     c;     x;     ;  ´   £;     X<  !   k<     <      <    §<  +  Å=  Ä   ñ>  Å   ¶?  ©   |@  ¯   &A    ÖA  -   ðB  Ø   C  0   ÷C     (D  !   /D  D   QD  0   D     ÇD     JE     \E  6   jE     ¡E     ®E     ÍE        	   t   #            y   <   A   D   Y   l   I       x          S   ^       w   p   )   W   *      R   k       v          U                             L   =          q   g   E   \   B           s           b   i   3   ?   (   m   P   G   8          Z   -           +      e   2   O   J             `   z   /   r       C       a             _   ]      d   j          $       [       >   :           V   '      h   !   f   
   F       1   o   0       9   4          ,                  n   @             6      .   ;       K   %                 &   Q       N   c   T   u   M           "      X                  7   5       {   H        %s module needs configuration (un)check all <b>Error:</b> invalid password. <b>Error:</b> missing password. <b>Reminder</b>: Now check the permissions on config.php and make sure it is not globally writeable. An error occurred while upgrading Gallery Core Module Authenticate Authenticate Me Authentication successful! Before you upgrade, we <b>strongly recommend</b> that you make a backup of your database!  If you fail to make a backup and something goes wrong, there is a strong possibility that we will not be able to help you recover your data!  Refer to the following examples: Begin Upgrade Config.php upgrade Congratulations! Your Gallery 2 upgrade is complete!  To upgrade any additional Gallery 2 modules you may use the Site Administrator interface. Continue to Step %d&raquo; Current Currently installed Debug Output: Delete Cache Directories Description Empty Cache Error: Gallery 2 requires PHP version 4.1.0 or newer or 5.0.4 or newer. You have PHP version %s installed. Contact your webserver administrator to request an upgrade, available at the %sPHP website%s. Error: Your version of PHP is configured with safe mode enabled.  You must disable safe mode before Gallery will run. Error: your PHP __FILE__ directive is not functioning correctly. Please file a support request with your webserver administrator or in the Gallery forums. Even though there were errors, you can still continue.  Or, you can try deleting these directories yourself and then click the <b>Try Again</b> link below. FILE Directive FILE directive supported Failed File uploads allowed Finished Finished! Gallery creates temporary copies of some of your data on your hard drive.  This helps it to run faster.  But when you upgrade, some of these files might be out of date so it's a good idea to get rid of them now.  Gallery will create them again as it needs them. Gallery file integrity Gallery: <strong>your photos</strong> on <strong>your website</strong> Go Go to my Gallery! If you are using Apache, create a file named .htaccess in the main Gallery directory with the following content: In order to proceed with the install, we have to verify that you are who you claim.  When you performed the install, you entered a password which went into your config.php.  Type that in now.  Refer to your config.php if you've forgotten what you entered. Manifest missing or inaccessible. Maximum POST size Maximum upload size Memory limit Missing files (%d) Modified files (%d) MySQL Name New New version Note: You're running Gallery from CVS, so recently removed files may appear here.  It might be safe to ignore these. Note: You're running Gallery from CVS, so some modified files are to be expected.  You can probably ignore these, but to be safe you should make sure that you do <b>cvs update -Pd</b> before continuing. Old files (%d) Once the upgrade has begun, please be patient.  If you cancel or reload the page, you may interfere with the upgrade process. Other PHP Version PHP version >= 4.1.0 or >= 5.0.4 Password: PostgreSQL Recheck config.php Redo this step Required Safe Mode Safe mode disabled Select Language: Skip Upgrade and Continue to Step %d&raquo; Something went wrong when we tried to upgrade the core module.  In the boxes below you can find some debug information.  Report this in the %sGallery Forums%s and we'll help you diagnose the problem. Stack Trace: Start Over Success System Checks Test skipped due to other errors. The Gallery Core Module is the heart of the Gallery application.  You can upgrade most other modules using the Site Administration interface, but this module must be handled separately in order for the upgrade to go smoothly. The following modules can be automatically upgraded for you.  If you choose not to upgrade them now, you may experience problems with your Gallery.   You can always upgrade or deactivate them on the Site Administration page, or return to this page later so any decision you make here is not permanent. The installed version is newer than the version you are trying to upgrade to. You cannot downgrade G2. Please replace the gallery2 files with files from the currently installed version or later. Themes These files are no longer part of Gallery. They probably won't cause any problems but it is a good idea to remove them to keep your install clean. Try Again Unable to commit database transaction Unable to get the module list Unable to get the theme list Unable to load the %s module Unable to load the %s theme Unable to upgrade the %s module Unable to upgrade the %s theme Unable to write to config.php in your %s directory.  Please change its permissions. Unknown Upgrade %d%% complete Upgrade Core Upgrade Modules Upgrade More Modules Upgrade Other Modules Upgrade Selected Modules Upgrade Status Upgrade Steps Upgraded Gallery Core Module successfully. Upgraded the %s module successfully Upgraded the %s theme successfully Upgrader Help Upgrading Gallery 2.0 requires %d steps. This upgrade tool will guide you through these steps and provide assistance along the way if additional steps are required. Please read the %sHelp File%s before proceeding. Upgrading modules Upgrading the Gallery Core Module Upgrading themes Warning Warning: The exec() function is disabled in your php by the <b>disabled_functions</b> parameter in php.ini. You won't be able to use modules that require external binaries (e.g. ImageMagick, NetPBM or Ffmpeg). This can only be set server-wide, so you will need to change it in the global php.ini. Warning: The set_time_limit() function is disabled in your php by the <b>disabled_functions</b> parameter in php.ini.  Gallery can function with this setting, but it will not operate reliably.  Any operation that takes longer than %d seconds will fail (and in some cases just return a blank page) possibly leading to data corruption. Warning: Your PHP is configured not to allow file uploads (<b>file_uploads</b> parameter in php.ini). You will need to enable this option if you want to upload files to your Gallery with a web browser. Warning: Your PHP is configured to limit the memory to %sb (<b>memory_limit</b> parameter in php.ini). You should raise this limit to at least <b>%sMB</b> for proper Gallery operation. Warning: Your PHP is configured to limit the post data to a maximum of %sb (<b>post_max_size</b> parameter in php.ini). You should raise this limit to allow uploading bigger files. Warning: Your PHP is configured to limit the size of file uploads to %sb (<b>upload_max_filesize</b> parameter in php.ini). You should rise this limit to allow uploading bigger files. Warning: Your PHP is configured with Zend ze1_compatibility_mode which can cause PHP to crash.  Click <a href="%s">here</a> to test your PHP.  If you see "SUCCESS" then your PHP is ok.  If you get an error then you must turn off ze1_compatibility_mode before proceeding. We have successfully cleaned out your cache directories. We were unable to clean the following cache directories.  This is probably ok, but if you notice any weird behaviour, you should try to delete these directories yourself.  It's perfectly safe to get rid of them at any time. We've successfully upgraded the Gallery Core Module. Welcome Welcome to the Gallery Upgrader You can do <i>chmod 666 config.php</i> to fix this. Your Gallery Core Module is up to date! Your config.php appears to use the old form of multisite support.  Please see the %sHelp File%s for instructions to update your configuration before proceeding. Zend compatibility mode exec() allowed mysqldump -u%s -p<i>YourPassword</i> --opt %s > %s.sql no limit pg_dump --format=t %s > %s.sql set_time_limit() allowed Project-Id-Version: Gallery: Upgrader 1.0
POT-Creation-Date: 2005-08-03 23:11-0400
PO-Revision-Date: 2005-08-03 23:11-0400
Last-Translator: Stephen Chu <stephen@ju-ju.com>
Language-Team: Chinese Traditional <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 %sæ¨¡çµéè¦è¨­å® å¨é¨å¾é¸æå¨é¨ä¸é¸ <b>é¯èª¤ï¼<b>ç¡æçå¯ç¢¼ã <b>é¯èª¤ï¼<b>æ²æå¯ç¢¼ã <b>æç¤º</b>ï¼è«æª¢æ¥ config.php æªæ¡çå­åæ¬éä¸¦ç¢ºå®å®ä¸æ¯ææäººé½å¯å¯«å¥ã æç´ Gallery æ ¸å¿æ¨¡çµæç¼çä¸åé¯èª¤ã èªè­ ç¢ºèªæçèº«å èªè­æå å¨ä½ æç´ä¹åï¼æå<b>å¼·çå°å»ºè­°</b>ä½ ååä»½ä½ çè³æåº«ï¼å¦æä½ æ²æåä»½èä¸ç¼çäºåé¡ï¼å¾å¯è½æåæç¡æ³åå©ä½ å¾©åä½ çè³æï¼è«åèä¸é¢çç¯ä¾ï¼ éå§æç´ Config.php æç´ æ­ç¦§ï¼ä½ ç Gallery 2 æç´å·²ç¶å®æï¼ä½ å¯ä»¥ä½¿ç¨ç¶²ç«ç®¡çå¡çé¢ä¾æç´å¶ä»ç Gallery æ¨¡çµã ç¹¼çºå°æ­¥é© %d&raquo; ç®å ç®åå®è£ é¤è²è¼¸åºï¼ åªé¤å¿«åç®é è©³ç´°æè¿° æ¸é¤å¿«å é¯èª¤ï¼Gallery 2 éè¦ PHP çæ¬ 4.1.0 ä»¥ä¸æ 5.0.4 ä»¥ä¸ãä½ å®è£ç PHP çæ¬æ¯ %sãè«è¦æ±ä½ çç¶²é ä¼ºæå¨ç®¡çå¡æç´ãæ°ççæ¬å¨ %sPHP çç¶²ç«ä¸%sã é¯èª¤ï¼ä½ ç PHP çæ¬è¨­å®çºä½¿ç¨å®å¨æ¨¡å¼ï¼Safe Modeï¼ãä½ å¿éééå®å¨æ¨¡å¼æè½ç¹¼çºå·è¡ Galleryã é¯èª¤ï¼ä½ ç PHP __FILE__ æä»¤å·¥ä½ä¸æ­£å¸¸ãè«åä½ çç¶²é ä¼ºæå¨ç®¡çå¡æ Gallery è¨è«åè¦æ±æè¡æ¯æ´ã å³ä½¿æé¯èª¤ç¼çï¼ä½ éæ¯å¯ä»¥ç¹¼çºãæèï¼ä½ å¯ä»¥è©¦èèªè¡åªé¤éäºç®éç¶å¾æãåè©¦ä¸æ¬¡ãçéµæ¥ã FILE æä»¤ æ¯æ´ FILE æä»¤ å¤±æ åè¨±ä¸è¼æªæ¡ å®æ å®æäºï¼ Gallery æå¨ä½ çç¡¬ç¢ä¸ç¢çä¸äºæ«å­æªæ¡ãéæå©æ¾å®çå·è¡éåº¦ãå¯æ¯å¨ä½ æç´çæåï¼éäºæªæ¡ä¸­å¯è½æä¸äºæéæï¼æä»¥æå¥½ç¾å¨æå®åæ¸é¤æãGallery æå¨éè¦æéæ°ç¢çéäºæªæ¡ã Gallery å®æ´æ§ Galleryï¼<strong>ä½ çç§ç</strong>ã<strong>ä½ çç¶²ç«</strong> éå§ åå¾æç Galleryï¼ å¦æä½ ä½¿ç¨ Apacheï¼å¨ Gallery ä¸»ç®éä¸­ç¢çä¸åå« .htaccess çæªæ¡ä¸¦å å¥ä¸åå§å®¹ï¼ çºäºç¹¼çºå®è£çç¨åºï¼æåå¿éç¢ºèªä½ çèº«åãç¶ä½ å®è£æï¼config.php å­å¥äºä½ è¼¸å¥çä¸åå¯ç¢¼ãè«è¼¸å¥é£åå¯ç¢¼ãå¦æä¸è¨å¾çè©±ï¼å¯ä»¥æ¥ç config.phpã æ¾ä¸å°æç¡æ³å­åæªæ¡æ¸å® æå¤§ POST å¤§å° æä¸ä¸è¼å¤§å° è¨æ¶ç©ºééå¶ ç¼ºå°çæªæ¡ï¼%dï¼ ä¿®æ¹éçæªæ¡ï¼%dï¼ MySQL åç¨± æ°ç æ°çæ¬ æ³¨æï¼ä½ æ­£å¨å·è¡ç± CVS ä¸­ä¸è¼ç Galleryï¼æä»¥æäºæè¿ç§»é¤çæªæ¡å¯è½æåºç¾å¨éè£¡ãå¯è½å¯ä»¥å®å¨çå¿½ç¥å®åã æ³¨æï¼ä½ æ­£å¨å·è¡ç± CVS ä¸­ä¸è¼ç Galleryï¼æä»¥ææäºä¿®æ¹éçæªæ¡ãä½ å¤§æ¦å¯ä»¥å¿½ç¥éäºæªæ¡ï¼å¯æ¯çºäºå®å¨èµ·è¦ï¼ä½ æå¥½åå·è¡ãcvs update -Pdãæä»¤åç¹¼çºã èççæªæ¡ï¼%dï¼ ä¸æ¦æç´çåä½éå§å¾ï¼è«èå¿ç­åãå¦æä½ åæ¶æéæ°è¼å¥éåé é¢ï¼ä½ å¯è½æå¹²æ¾æç´çç¨åºã å¶ä» PHP çæ¬ PHP çæ¬å¤§æ¼æç­æ¼ 4.1.0 æå¤§æ¼æç­æ¼ 5.0.4 å¯ç¢¼ï¼ PostgreSQL åæª¢æ¥ config.php éè¦éåæ­¥é© ï¼å¿è¦ï¼ å®å¨æ¨¡å¼ å®å¨æ¨¡å¼å·²éé é¸æèªè¨ï¼ ç¥éæç´ä¸¦ç¹¼çºå°æ­¥é© %d&raquo; ç¶æåè©¦èæç´æ ¸å¿æ¨¡çµæç¼çäºåé¡ãä½ å¯ä»¥å¨ä¸é¢æ¾å°ä¸äºé¤é¯çè³è¨ãè«å¨ %sGallery è«è­ %sä¸­å ±åéåé¯èª¤ï¼æåæå¹«ä½ æ¨æ¸¬éååé¡ã å çè¨éï¼ éæ°éå§ æå ç³»çµ±æª¢æ¥ å å¶ä»é¯èª¤ç¥éæ¸¬è©¦ã Gallery æ ¸å¿æ¨¡çµæ¯ Gallery æç¨ç¨å¼çä¸­å¿ãä½ å¯ä»¥ç¨ç¶²ç«ç®¡ççé¢ä¾æç´å¤§é¨åå¶ä»çæ¨¡çµï¼å¯æ¯éåæ¨¡çµä¸å®è¦åéèçæè½ä½¿æç´çåä½å¹³é é²è¡ã ä¸åçæ¨¡çµå¯ä»¥èªåçºä½ æç´ãå¦æä½ é¸æä¸è¦ç¾å¨æç´å®åï¼ä½ å¯è½æå¨ä½ ç Gallery ä¸­é­éåé¡ãä½ å¯ä»¥å¨ç¶²ç«ç®¡çé é¢ä¸­æç´æåç¨éäºæ¨¡çµï¼æç¨å¾åå°éåé é¢ãæä»¥ä½ å¨éè£¡åçä»»ä½æ±ºå®é½ä¸æ¯ä¸è½æ¹è®çã ç®åå®è£ççæ¬æ¯ä½ è¦æç´ççæ¬éæ°ãä½ ä¸è½æ G2 éç´ãè«æ Gallery 2 çæªæ¡ææç®åå®è£ææ´æ°ççæ¬ ä¸»é¡ Gallery å·²ç¶ä¸åä½¿ç¨éäºæªæ¡ãå®åå¤§æ¦ä¸æé æä»»ä½åé¡å¯æ¯æå¥½éæ¯æå®ååªé¤ã åè©¦ä¸æ¬¡ ç¡æ³éåºè³æåº«ç°å ç¡æ³åå¾æ¨¡çµåè¡¨ ç¡æ³åå¾ä¸»é¡åè¡¨ ç¡æ³è¼å¥%sæ¨¡çµ ç¡æ³è¼å¥%sæ¨¡çµ ç¡æ³æç´%sæ¨¡çµ ç¡æ³æç´%sä¸»é¡ ç¡æ³å¯«å¥å¨ä½ ç %s ç®éä¸­ç config.php æªæ¡ãè«æ´æ¹å®çå­åæ¬éã æªç¥ æç´é²åº¦ %d%% åç´æ ¸å¿ åç´æ¨¡çµ æç´å¶ä» Gallery æ¨¡çµ æç´å¶ä»æ¨¡çµ æç´æé¸æ¨¡çµ æç´çæ³ æç´æ­¥é© æç´ Gallery æ ¸å¿æ¨¡çµæåã %sæ¨¡çµæç´æå %sä¸»é¡æç´æåã æç´ç¨å¼èªªæ æç´å° Gallery 2.0 éè¦ %d åæ­¥é©ãéåæç´å·¥å·æå¸¶ä½ èµ°ééäºæ­¥é©ä¸¦å¨éè¦é¡å¤æ­¥é©ææä¾åå©ãå¨ç¹¼çºä¹åï¼è«åé±è®%sèªªææªæ¡%sã æ­£å¨åç´æ¨¡çµ æ­£å¨æç´ Gallery æ ¸å¿æ¨¡çµ æ­£å¨åç´ä¸»é¡ è­¦å è­¦åï¼ä½ ç PHP ä¸­ç exec() å½æ¸è¢« php.ini ä¸­ç <b>disabled_functions</b> ééäºãä½ å°ç¡æ³ä½¿ç¨éè¦å¤é¨å·è¡æªçæ¨¡çµï¼å¦ ImageMagickãNetPBM æ Ffmpegï¼ãéåé¸é åªè½å¨ä¼ºæå¨ç«¯æ¹è®ï¼æä»¥ä½ éè¦å¨å¨é«å±ç¨ç php.ini ä¸­æ¹æ­£ã è­¦åï¼ä½ ç PHP ä¸­ç set_time_limit() å½æ¸è¢« php.ini ä¸­ç <b>disabled_functions</b> ééäºãGallery ä»ç¶å¯ä»¥å¨éåè¨­å®ä¸å·è¡ï¼å¯æ¯ç©©å®åº¦ææåé¡ãä»»ä½åè½å·è¡è¶é %d ç§éé½æå¤±æï¼æææå³åä¸åç©ºç½é é¢ï¼ä¸¦å¯è½å°è´è³æææ¯ã è­¦åï¼ä½ ç PHP è¨­å®æç¦æ­¢æªæ¡ä¸è¼ï¼å¨ php.ini ä¸­ç <b>file_uploads</b> åæ¸ï¼çè¨æ¶ç©ºéãä½ éè¦ååéåé¸é æè½ç¨ç¶²é çè¦½ç¨å¼ä¸è¼æªæ¡å° Galleryã è­¦åï¼ä½ ç PHP è¨­å®æåªè½ä½¿ç¨ %sbï¼å¨ php.ini ä¸­ç <b>memory_limit</b> åæ¸ï¼çè¨æ¶ç©ºéãä½ æè©²æéåéå¶ææå°è³å° <b>%sMB</b>ï¼Gallery æè½æ­£å¸¸å·¥ä½ã è­¦åï¼ä½ ç PHP è¨­å®ææå¤§ POST è³æçº %sbï¼å¨ php.ini ä¸­ç <b>post_max_size</b> åæ¸ï¼ãä½ æè©²æé«éåéå¶ä»¥åè¨±ä¸è¼æ´å¤§çæªæ¡ã è­¦åï¼ä½ ç PHP è¨­å®æä¸è¼æªæ¡æå¤§çº %sbï¼å¨ php.ini ä¸­ç <b>upload_max_filesize</b> åæ¸ï¼ãä½ æè©²æé«éåéå¶ä»¥åè¨±ä¸è¼æ´å¤§çæªæ¡ã è­¦åï¼ä½ ç PHP è¨­å®ä½¿ç¨å¯è½ä½¿ PHP ç¶æ©ç Zend ze1_compatibility_mode é¸é ãè«æ<a href="%s">éè£¡</a>æ¸¬è©¦ PHPãå¦æä½ çå°ãSUCCESSãè¡¨ç¤ºä½ ç PHP æ­£å¸¸ãå¦æä½ å¾å°ä¸åé¯èª¤è¨æ¯ï¼ä½ éè¦æ ze1_compatibility_modeéææè½ç¹¼çºã æåæåå°æ¸é¤äºä½ çå¿«åç®éã æåç¡æ³æ¸é¤ä¸åçå¿«åç®éãéæè©²ä¸æé æåé¡ï¼ä½æ¯å¦æä½ ç¼ç¾ä»»ä½ä¸æ­£å¸¸çå°æ¹ï¼ä½ å¯ä»¥è©¦èèªå·±åªé¤éäºç®éãå¨ä»»ä½æåï¼å®åé½å¯ä»¥å¾å®å¨çåªé¤ã æåæåå°æç´äº Gallery æ ¸å¿æ¨¡çµã æ­¡è¿ æ­¡è¿ä½¿ç¨ Gallery æç´ç¨å¼ ä½ å¯ä»¥ç¨ãchmod 666 config.phpãæä»¤ä¾ä¿®æ­£éåé¯èª¤ã ä½ ç Gallery æ ¸å¿æ¨¡çµå·²ç¶æ¯ææ°çï¼ ä½ ç config.php ä¼¼ä¹æ¯ä½¿ç¨èå¼çå¤ç«å°æ¯æ´ãè«åè%sèªªææªæ¡%sä¸­çæç¤ºä¾æç´ä½ çè¨­å®åç¹¼çºã Zend ç¸å®¹æ¨¡å¼ åè¨± exec() mysqldump -u%s -p<i>ä½ çå¯ç¢¼</i> --opt %s > %s.sql æ²æéå¶ pg_dump --format=t %s > %s.sql åè¨± set_time_limit() 