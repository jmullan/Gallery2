{*
 * $Revision$
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
    RewriteCond %{ldelim}REQUEST_URI{rdelim} !{$Htaccess.matchBaseFile}$
    RewriteRule .   -   [L]

{foreach from=$Htaccess.rules item=rule}
{if isset($rule.conditions)}
{foreach from=$rule.conditions item="condition"}
    RewriteCond %{ldelim}{$condition.test}{rdelim} {$condition.pattern}{if !empty($condition.flags)}   [{$condition.flags|@implode:','}]{/if}

{/foreach}
{/if}
{if isset($rule.settings.restrict)}
{foreach from=$rule.settings.restrict item=condition}
    RewriteCond %{ldelim}QUERY_STRING{rdelim} {$condition}
{/foreach}
{foreach from=$rule.settings.exempt item=host}
    RewriteCond %{ldelim}HTTP_REFERER{rdelim} !://{$host}/ [NC]
{/foreach}
{if $Htaccess.allowEmptyReferer}
    RewriteCond %{ldelim}HTTP_REFERER{rdelim} !^$
{/if}
{elseif isset($rule.pattern)}
    RewriteCond %{ldelim}THE_REQUEST{rdelim} \ {$Htaccess.rewriteBase}{$rule.pattern}(\?.|\ .)
    RewriteCond %{ldelim}REQUEST_URI{rdelim} !{$Htaccess.matchBaseFile}$
{/if}
{if strpos($rule.queryString, 'view=core.DownloadItem') !== false ||
    strpos($rule.queryString, 'view=watermark.DownloadItem') !== false}
    RewriteRule .   {$Htaccess.galleryDirectory}{$Htaccess.mainPhp}?{$rule.queryString}{if !empty($rule.settings.flags)}   [{$rule.settings.flags}]{/if}
{else}
    RewriteRule .   {$Htaccess.directory}{$Htaccess.baseFile}{$rule.queryString}{if !empty($rule.settings.flags)}   [{$rule.settings.flags}]{/if}
{/if}

{/foreach}
</IfModule>

# END Url Rewrite section

