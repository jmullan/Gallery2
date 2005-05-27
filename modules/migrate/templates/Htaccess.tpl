{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<IfModule mod_rewrite.c>
  RewriteEngine On
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-f
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-d
  Rewritecond %{ldelim}REQUEST_FILENAME{rdelim} !gallery_remote2.php
  RewriteRule (.*)$ {$uriBase}?g2_controller=migrate.Redirect&g2_file=$1&g2_%{ldelim}QUERY_STRING{rdelim}
</IfModule>
