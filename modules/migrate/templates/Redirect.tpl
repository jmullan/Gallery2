{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to Redirect.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<p>
  {g->text text="To enable URL Redirection under Apache webserver:"}
</p>
<ol>
  <li> {g->text text="Ensure the <a href=\"%s\">mod_rewrite</a> Apache module is enabled."
                arg1="http://httpd.apache.org/docs/mod/mod_rewrite.html"}
  <li> {g->text text="Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. This will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be."}
  <li> {g->text text="Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories."}
</ol>

<pre class="giDescription">&lt;IfModule mod_rewrite.c&gt;
  RewriteEngine On
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-f
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-d
  RewriteRule (.*)$ {$uriBase}?g2_controller=migrate:Redirect&amp;g2_file=$1&amp;g2_%{ldelim}QUERY_STRING{rdelim}
&lt;/IfModule&gt;</pre>
<p>
  <a href="{g->url arg1="view=migrate:Redirect"}">
    {g->text text="Download .htaccess file"}
  </a>
</p>
