{*
 * $Revision: 1.15 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
# BEGIN Url Rewrite section
# (Automatically generated.  Do not edit this section)
<IfModule mod_rewrite.c>
{if $Htaccess.needOptions}
    Options +FollowSymlinks
{/if}
    RewriteEngine On

    RewriteBase {$Htaccess.rewriteBase}

    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} -f [OR]
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} -d [OR] 
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} gallery\_remote2\.php
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !{$Htaccess.matchBaseFile}
    RewriteRule .   -   [L]

    
{foreach from=$Htaccess.rules item=rule}
{if isset($rule.settings.condition)}
  {foreach from=$rule.settings.condition item=condition}
    RewriteCond {$condition}
  {/foreach}
{else}
    RewriteCond %{ldelim}THE_REQUEST{rdelim} \ {$Htaccess.rewriteBase}{$rule.urlPattern}(\?.|\ .)
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !{$Htaccess.matchBaseFile}
{/if}
{if strpos($rule.queryString, 'view=core.DownloadItem') !== false}
    RewriteRule .   {$Htaccess.galleryDirectory}{$Htaccess.mainPhp}?{$rule.queryString}   [{$rule.settings.flags}]
{else}
    RewriteRule .   {$Htaccess.directory}{$Htaccess.baseFile}{$rule.queryString}   [{$rule.settings.flags}]
{/if}

{/foreach}
</IfModule>

# END Url Rewrite section

