{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to Redirect.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<p>
  {g->text text="Use .htaccess code like this in your Gallery1 directory to activate URL Redirection:"}
</p>

<pre class="giDescription">&lt;IfModule mod_rewrite.c&gt;
  RewriteEngine On
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-f
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-d
  RewriteRule (.*)$ {$uriBase}?g2_controller=migrate:Redirect&amp;g2_file=$1&amp;g2_%{ldelim}QUERY_STRING{rdelim}
&lt;/IfModule&gt;</pre>

<p>
  {g->text text="This will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be."}
</p>
