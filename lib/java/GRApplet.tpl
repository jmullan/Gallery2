{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  {if !empty($GRApplet.NoProtocolError)}
  <div class="giError">
    {g->text text="This applet relies on a G2 module that is not currently enabled.  Please ask an administrator to enable the 'remote' module."}
  </div>
  {else}
  <object classid="clsid:8AD9C840-044E-11D1-B3E9-00805F499D93"
	  codebase="http://java.sun.com/products/plugin/autodl/jinstall-1_4-windows-i586.cab#Version=1,4,0,0"
	  width="600" height="400">
    <param name="code" value="{$GRApplet.code}"/>
    <param name="archive" value="{g->url href="lib/java/GalleryRemoteAppletMini.jar},{g->url href="lib/java/GalleryRemoteHTTPClient.jar"},{g->url href="lib/java/applet_img.jar"}"/>
    <param name="type" value="application/x-java-applet;version=1.4"/>
    <param name="scriptable" value="false"/>
    <param name="progressbar" value="true"/>
    <param name="boxmessage" value="{g->text text="Downloading the Gallery Remote Applet"}"/>
    <param name="gr_url" value="{$GRApplet.g2BaseUrl}"/>
    <param name="gr_cookie_name" value="{$GRApplet.cookieName}"/>
    <param name="gr_cookie_value" value="{$GRApplet.cookieValue}"/>
    <param name="gr_cookie_domain" value="{$GRApplet.cookieDomain}"/>
    <param name="gr_cookie_path" value="{$GRApplet.cookiePath}"/>
    <param name="gr_album" value="{$GRApplet.album}"/>
    <param name="gr_user_agent" value="{$GRApplet.userAgent}"/>
    <param name="gr_gallery_version" value="{$GRApplet.galleryVersion}"/>
    {foreach key=key item=value from=$GRApplet.extra}
    <param name="{$key}" value="{$value}"/>
    {/foreach}
    {foreach key=key item=value from=$GRApplet.defaults}
    <param name="GRDefault_{$key}" value="{$value}"/>
    {/foreach}
    {foreach key=key item=value from=$GRApplet.overrides}
    <param name="GROverride_{$key}" value="{$value}"/>
    {/foreach}

    <comment>
      <embed
          type="application/x-java-applet;version=1.4"
          code="{$GRApplet.code}"
          archive="{g->url href="lib/java/GalleryRemoteAppletMini.jar},{g->url href="lib/java/GalleryRemoteHTTPClient.jar"},{g->url href="lib/java/applet_img.jar"}"
          width="600"
          height="400"
          scriptable="false"
          progressbar="true"
          boxmessage="{g->text text="Downloading the Gallery Remote Applet"}"
          pluginspage="http://java.sun.com/j2se/1.4.2/download.html"
          gr_url="{$GRApplet.g2BaseUrl}"
          gr_cookie_name="{$GRApplet.cookieName}"
          gr_cookie_value="{$GRApplet.cookieValue}"
          gr_cookie_domain="{$GRApplet.cookieDomain}"
          gr_cookie_path="{$GRApplet.cookiePath}"
          gr_album="{$GRApplet.album}"
          gr_user_agent="{$GRApplet.userAgent}"
          gr_gallery_version="{$GRApplet.galleryVersion}"
          {foreach key=key item=value from=$GRApplet.extra}
          {$key}="{$value}"
          {/foreach}
          {foreach key=key item=value from=$GRApplet.defaults}
          GRDefault_{$key}="{$value}"
          {/foreach}
          {foreach key=key item=value from=$GRApplet.overrides}
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
