{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
# BEGIN Url Rewrite section
# (Automatically generated.  Do not edit this section)
<IfModule mod_rewrite.c>
{if $Htaccess.needOptions == 'true'}
    Options +FollowSymlinks
{/if}
    RewriteEngine On

    RewriteBase {$Htaccess.directory}
    
    # Only redirect to Gallery base file if there's no such file already, and
    # make sure gallery_remote2.php generates a 404 in order to be compatible
    # with Gallery Remote.
    
{foreach from=$Htaccess.rules item=rule}
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-f
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-d
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !gallery\_remote2\.php
{if strpos($rule.queryString, 'view=core:DownloadItem') !== false}
    RewriteRule ^{$rule.urlPattern}$   {$Htaccess.galleryDirectory}main.php?{$rule.queryString}   [QSA,L]
{else}
    RewriteRule ^{$rule.urlPattern}$   {$Htaccess.directory}{$Htaccess.baseFile}{$rule.queryString}   [QSA,L]
{/if}

{/foreach}
</IfModule>

# END Url Rewrite section

