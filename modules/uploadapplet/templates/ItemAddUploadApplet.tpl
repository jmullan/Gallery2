{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemAddUploadApplet.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
{if $NoProtocolError == 1}
  <div class="giError">
  {g->text text="The upload applet relies on a G2 module that is not currently enabled. Please ask an administrator to enable the 'remote' module."}
  </div>
{else}

<object
	classid="clsid:8AD9C840-044E-11D1-B3E9-00805F499D93"
	codebase="http://java.sun.com/products/plugin/autodl/jinstall-1_4-windows-i586.cab#Version=1,4,0,0"
	width="{$width}" height="{$height}">
    <param name="code" value="{$code}">
    <param name="archive" value="{$archive}">
    <param name="type" value="application/x-java-applet;version=1.4">
    <param name="scriptable" value="false">
    <param name="progressbar" value="true">
    <param name="boxmessage" value="{g->text text="Downloading the Gallery Remote Applet"}">
    <param name="gr_url" value="{$url}">
    <param name="gr_cookie_name" value="{$cookie_name}">
    <param name="gr_cookie_value" value="{$cookie_value}">
    <param name="gr_cookie_domain" value="{$cookie_domain}">
    <param name="gr_cookie_path" value="{$cookie_path}">
    <param name="gr_album" value="{$album}">
{foreach key=key item=value from=$defaults}
    <param name="GRDefault_{$key}" value="{$value}">
{/foreach}
{foreach key=key item=value from=$overrides}
    <param name="GROverride_{$key}" value="{$value}">
{/foreach}

    <comment>
	<embed
	    type="application/x-java-applet;version=1.4"
	    code="{$code}"
	    archive="{$archive}"
	    width="{$width}"
	    height="{$height}"
	    scriptable="false"
	    progressbar="true"
	    boxmessage="{g->text text="Downloading the Gallery Remote Applet"}"
	    pluginspage="http://java.sun.com/j2se/1.4.2/download.html"
	    gr_url="{$url}"
	    gr_cookie_name="{$cookie_name}"
	    gr_cookie_value="{$cookie_value}"
	    gr_cookie_domain="{$cookie_domain}"
	    gr_cookie_path="{$cookie_path}"
	    gr_album="{$album}"
{foreach key=key item=value from=$defaults}
	    GRDefault_{$key}="{$value}"
{/foreach}
{foreach key=key item=value from=$overrides}
	    GROverride_{$key}="{$value}"
{/foreach}
	>
	    <noembed alt="{g->text text="Your browser doesn't support applets; you should use one of the other upload methods."}>
		{g->text text="Your browser doesn't support applets; you should use one of the other upload methods."}
	    </noembed>
	</embed>
    </comment>
</object>
{/if}
</div>
