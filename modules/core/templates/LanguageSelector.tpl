{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
<form id="LanguageSystemContent" method="post"
      action="{g->url arg1="controller=core:ChangeLanguage" arg2="return=1"}"><div>
  <h3> {g->text text="Language"} </h3>

  <select name="{g->formVar var="language"}" onchange="this.form.submit()" style="direction:ltr">
    {html_options options=$LanguageSelector.list selected=$LanguageSelector.language}
  </select>
  <noscript><div style="display: inline">
    <input type="submit" class="inputTypeSubmit" value="{g->text text="Go"}"/>
  </div></noscript>
</div></form>
</div>
