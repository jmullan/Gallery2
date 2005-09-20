{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  {if !empty($ItemAddUploadApplet.NoProtocolError)}
  <div class="giError">
    {g->text text="The upload applet relies on a G2 module that is not currently enabled.  Please ask an administrator to enable the 'remote' module."}
  </div>
  {else}
  <form name="form1">
  <object classid="clsid:8AD9C840-044E-11D1-B3E9-00805F499D93"
	  codebase="http://java.sun.com/products/plugin/autodl/jinstall-1_4-windows-i586.cab#Version=1,4,0,0"
	  width="600" height="400" mayscript="true">
    <param name="code" value="com.gallery.GalleryRemote.GRAppletMini"/>
    <param name="archive" value="{g->url href="modules/uploadapplet/applets/GalleryRemoteAppletMini.jar},{g->url href="modules/uploadapplet/applets/GalleryRemoteHTTPClient.jar"},{g->url href="modules/uploadapplet/applets/applet_img.jar"}"/>
    <param name="type" value="application/x-java-applet;version=1.4"/>
    <param name="scriptable" value="false"/>
    <param name="progressbar" value="true"/>
    <param name="boxmessage" value="{g->text text="Downloading the Gallery Remote Applet"}"/>
    <param name="gr_url" value="{$ItemAddUploadApplet.g2BaseUrl}"/>
    <param name="gr_cookie_name" value="{$ItemAddUploadApplet.cookieName}"/>
    <param name="gr_cookie_value" value="{$ItemAddUploadApplet.cookieValue}"/>
    <param name="gr_cookie_domain" value="{$ItemAddUploadApplet.cookieDomain}"/>
    <param name="gr_cookie_path" value="{$ItemAddUploadApplet.cookiePath}"/>
    <param name="gr_album" value="{$ItemAddUploadApplet.album}"/>
    <param name="gr_user_agent" value="{$ItemAddUploadApplet.userAgent}"/>
    <param name="gr_gallery_version" value="{$ItemAddUploadApplet.galleryVersion}"/>
    {foreach key=key item=value from=$ItemAddUploadApplet.defaults}
    <param name="GRDefault_{$key}" value="{$value}"/>
    {/foreach}
    {foreach key=key item=value from=$ItemAddUploadApplet.overrides}
    <param name="GROverride_{$key}" value="{$value}"/>
    {/foreach}

    <comment>
      <embed
          type="application/x-java-applet;version=1.4"
          code="com.gallery.GalleryRemote.GRAppletMini"
          archive="{g->url href="modules/uploadapplet/applets/GalleryRemoteAppletMini.jar},{g->url href="modules/uploadapplet/applets/GalleryRemoteHTTPClient.jar"},{g->url href="modules/uploadapplet/applets/applet_img.jar"}"
          width="600"
          height="400"
          mayscript="true"
          progressbar="true"
          boxmessage="{g->text text="Downloading the Gallery Remote Applet"}"
          pluginspage="http://java.sun.com/j2se/1.4.2/download.html"
          gr_url="{$ItemAddUploadApplet.g2BaseUrl}"
          gr_cookie_name="{$ItemAddUploadApplet.cookieName}"
          gr_cookie_value="{$ItemAddUploadApplet.cookieValue}"
          gr_cookie_domain="{$ItemAddUploadApplet.cookieDomain}"
          gr_cookie_path="{$ItemAddUploadApplet.cookiePath}"
          gr_album="{$ItemAddUploadApplet.album}"
          gr_user_agent="{$ItemAddUploadApplet.userAgent}"
          gr_gallery_version="{$ItemAddUploadApplet.galleryVersion}"
          {foreach key=key item=value from=$ItemAddUploadApplet.defaults}
          GRDefault_{$key}="{$value}"
          {/foreach}
          {foreach key=key item=value from=$ItemAddUploadApplet.overrides}
          GROverride_{$key}="{$value}"
          {/foreach}
      >
          <noembed alt="{g->text text="Your browser doesn't support applets; you should use one of the other upload methods."}">
            {g->text text="Your browser doesn't support applets; you should use one of the other upload methods."}
          </noembed>
      </embed>
    </comment>
  </object>
  </form>
  {/if}
</div>

<div id="uploadapplet_Feedback">
</div>

{g->addToTrailer}
<script type="text/javascript">
  // <![CDATA[
  var text = '';
  var textUrls = '';

  function startingUpload() {ldelim}
    text = textUrls = '';
    addText('<h2>{g->text text="Uploading files..."}</h2><ul>');
  {rdelim}

  function uploadedOne(itemId, itemName) {ldelim}
    addTextUrls('<li>' + itemName + '</li>',
    	'<li><a href="{g->url arg1="view=core.ShowItem" arg2="itemId="}' + itemId + '">' + itemName + '</a></li>');
  {rdelim}

  function doneUploading() {ldelim}
    addText('</ul><h2>{g->text text="Upload complete"}</h2>'
    	+ '<p>{g->text text="you can keep uploading or go to some of the pictures you uploaded by clicking on the links above"}<p>');

    showUrls();
  {rdelim}

  function addTextUrls(s, s1) {ldelim}
    text = text + s;
    textUrls = textUrls + s1;

    getRef().innerHTML='<div class="gbBlock gcBackground1">' + text + '</div>';
  {rdelim}

  function addText(s) {ldelim}
    text = text + s;
    textUrls = textUrls + s;

    getRef().innerHTML='<div class="gbBlock gcBackground1">' + text + '</div>';
  {rdelim}

  function showUrls() {ldelim}
    getRef().innerHTML='<div class="gbBlock gcBackground1">' + textUrls + '</div>';
  {rdelim}

  function getRef() {ldelim}
    if (document.getElementById) {ldelim}
      return document.getElementById("uploadapplet_Feedback");
    {rdelim} else if (document.all) {ldelim}
      return document.all["uploadapplet_Feedback"];
    {rdelim}
  {rdelim}

  //setTimeout('test()', 2000);

  function test() {ldelim}
    startingUpload();
    setTimeout('test1()', 2000);
  {rdelim}
  function test1() {ldelim}
    uploadedOne('7', 'toto');
  {rdelim}
  // ]]>
</script>
{/g->addToTrailer}
