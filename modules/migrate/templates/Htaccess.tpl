{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to Htaccess.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<IfModule mod_rewrite.c>
  RewriteEngine On
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-f
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-d
  Rewritecond %{ldelim}REQUEST_FILENAME{rdelim} !gallery_remote2.php
  RewriteRule (.*)$ {$uriBase}?g2_controller=migrate:Redirect&g2_file=$1&g2_%{ldelim}QUERY_STRING{rdelim}
</IfModule>
