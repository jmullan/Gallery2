{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<p>
  {g->text text="To enable URL Redirection under Apache webserver:"}
</p>
<ol>
  {capture name=mod_rewrite_anchor}
  <a href="http://httpd.apache.org/docs/mod/mod_rewrite.html">mod_rewrite</a>
  {/capture}
  <li>
    {g->text text="Ensure the %s Apache module is enabled."
             arg1=$smarty.capture.mod_rewrite_anchor}
  </li>
  <li>
    {g->text text="Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. This will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be."}
  </li>
  <li>
    {g->text text="Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories."}
  </li>
  <li>
    {g->text text="If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file \"gallery_remote2.php\" file before you can use Gallery Remote to upload images to G2."}
  </li>
</ol>

<pre class="giDescription">&lt;IfModule mod_rewrite.c&gt;
  RewriteEngine On
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-f
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !-d
  RewriteCond %{ldelim}REQUEST_FILENAME{rdelim} !gallery_remote2.php
  RewriteRule (.*)$ {$uriBase}?g2_controller=migrate:Redirect&amp;g2_file=$1&amp;g2_%{ldelim}QUERY_STRING{rdelim}
&lt;/IfModule&gt;</pre>

<p>
  <a href="{g->url arg1="view=migrate:Redirect"}">
    {g->text text="Download .htaccess file"}
  </a>
</p>
