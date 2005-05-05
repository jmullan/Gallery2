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

    RewriteBase {$Htaccess.rewriteBase}

    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} -f [OR]
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} -d [OR] 
    RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} gallery\_remote2\.php
    RewriteCond %{ldelim}REQUEST_URI{rdelim} !{$Htaccess.baseFile}
    RewriteRule .   -   [L]

    
{foreach from=$Htaccess.rules item=rule}
{if isset($rule.settings.condition)}
  {foreach from=$rule.settings.condition item=condition}
    RewriteCond {$condition}
  {/foreach}
{/if}
{if $rule.urlPattern == '^(.+)$'}
    RewriteCond %{ldelim}REQUEST_URI{rdelim} !{$Htaccess.baseFile}
{/if}
{if isset($rule.settings.forbidden)}
    RewriteRule {$rule.urlPattern}   -   [F,L]
{else}
  {if strpos($rule.queryString, 'view=core:DownloadItem') !== false}
    RewriteRule {$rule.urlPattern}   {$Htaccess.galleryDirectory}main.php?{$rule.queryString}   [QSA,L]
  {else}
    RewriteRule {$rule.urlPattern}   {$Htaccess.directory}{$Htaccess.baseFile}{$rule.queryString}   [QSA,L]
  {/if}
{/if}

{/foreach}
</IfModule>

# END Url Rewrite section

