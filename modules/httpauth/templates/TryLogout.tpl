{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}
<script type="text/javascript">
  // <![CDATA[

  try {ldelim}
    {* http://msdn.microsoft.com/workshop/author/dhtml/reference/constants/clearauthenticationcache.asp *}
    document.execCommand("ClearAuthenticationCache");
  {rdelim} catch (exception) {ldelim}
  {rdelim}

  window.location = "{$TryLogout.scriptUrl}";

  // ]]>
</script>

<div class="gbBlock">
  <p class="giDescription">
    <h3><a href="{$TryLogout.hrefUrl}"> {g->text text="Finish Logout"} </a></h3>
  </p>
</div>
