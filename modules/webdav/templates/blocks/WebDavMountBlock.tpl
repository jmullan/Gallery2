{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{assign var="item" value=$item|default:$theme.item}
{g->callback type="webdav.LoadMountLink" itemId=$item.id}
<div class="{$class}">
  <p class="giDescription">
    {capture name="mountLink"}<a href="{$block.webdav.LoadMountLink.href}"{if !empty($block.webdav.LoadMountLink.script)} onclick="{$block.webdav.LoadMountLink.script}"{/if} {$block.webdav.LoadMountLink.attrs}>{/capture}
    {g->text text="On many platforms, you can %sautomatically mount%s Gallery on your desktop with WebDAV." arg1=$smarty.capture.mountLink arg2="</a>"}
  </p>

  <p class="giDescription">
    {capture name="connectUrl"}{g->url arg1="controller=webdav.WebDav" arg2="itemId=`$item.id`" forceFullUrl=true forceSessionId=false useAuthToken=false}{/capture}
    {g->text text="Alternatively, you can manually connect with WebDAV by entering this URL in a WebDAV client:"} <a href="{$smarty.capture.connectUrl}"> {$smarty.capture.connectUrl}</a>
  </p>

  <p class="giDescription">
    {g->text text="Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s." arg1="<a href=\"http://codex.gallery2.org/index.php/Gallery2:Modules:webdav:user\">" arg2="</a>"}
  </p>
</div>
