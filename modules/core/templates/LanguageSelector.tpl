{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to LanguageSelector.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbMenu">
  <h3 class="giTitle"> {g->text text="Language"} </h3>
  <form id="LanguageSystemContent" action="{g->url arg1="controller=core:ChangeLanguage" arg2="return=1"}" method="post">
    <select name="{g->formVar var="language"}" onChange="this.form.submit()">
      {html_options options=$LanguageSystemContent.list selected=$LanguageSystemContent.language}
    </select>
    <noscript> <input type="submit" value="{g->text text="Go"}"/> </noscript>
  </form>
</div>
