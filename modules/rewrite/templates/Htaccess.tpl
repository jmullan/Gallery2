{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
# BEGIN Url Rewrite section
# (Automatically generated.  Do not edit this section)
<IfModule mod_rewrite.c>
    Options +FollowSymlinks
    RewriteEngine On

    RewriteBase {$Htaccess.galleryDirectory}
    
    # Only redirect to Gallery base file if there's no such file already, and
    # make sure gallery_remote2.php gets generates a 404 in order to be compatible
    # with Gallery Remote.
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !gallery\_remote2\.php
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-f
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-d

    RewriteRule ^v/(.*).html       {$Htaccess.galleryDirectory}{$Htaccess.baseFile}?{$Htaccess.g2Prefix}view=core:ShowItem&{$Htaccess.g2Prefix}path=/$1 [QSA]
    RewriteRule ^v/(.*)            {$Htaccess.galleryDirectory}{$Htaccess.baseFile}?{$Htaccess.g2Prefix}view=core:ShowItem&{$Htaccess.g2Prefix}path=/$1 [QSA]
    RewriteRule ^d/([0-9]+).*?     {$Htaccess.galleryDirectory}{$Htaccess.baseFile}?{$Htaccess.g2Prefix}view=core:DownloadItem&{$Htaccess.g2Prefix}itemId=$1 [QSA]
</IfModule>

# END Url Rewrite section

