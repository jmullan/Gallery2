{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemAddUploadApplet.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  {if !empty($ItemAddUploadApplet.NoProtocolError)}
  <div class="giError">
    {g->text text="The upload applet relies on a G2 module that is not currently enabled.  Please ask an administrator to enable the 'remote' module."}
  </div>
  {else}
  <object classid="clsid:8AD9C840-044E-11D1-B3E9-00805F499D93"
	  codebase="http://java.sun.com/products/plugin/autodl/jinstall-1_4-windows-i586.cab#Version=1,4,0,0"
	  width="600" height="400">
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
          scriptable="false"
          progressbar="true"
          boxmessage="{g->text text="Downloading the Gallery Remote Applet"}"
          pluginspage="http://java.sun.com/j2se/1.4.2/download.html"
          gr_url="{$ItemAddUploadApplet.g2BaseUrl}"
          gr_cookie_name="{$ItemAddUploadApplet.cookieName}"
          gr_cookie_value="{$ItemAddUploadApplet.cookieValue}"
          gr_cookie_domain="{$ItemAddUploadApplet.cookieDomain}"
          gr_cookie_path="{$ItemAddUploadApplet.cookiePath}"
          gr_album="{$ItemAddUploadApplet.album}"
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
  {/if}
</div>
