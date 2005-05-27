{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<script type="text/javascript">
  // <![CDATA[
  var searchDefault = '{g->text text="Search the Gallery"}';
  function checkForm() {ldelim}
    var sc = document.getElementById('SearchSystemContent').searchCriteria.value;
    if (sc == searchDefault || sc == '') {ldelim}
      alert('{g->text text="Please enter keywords to search."}');
      return false;
    {rdelim} else {ldelim}
      document.getElementById('SearchSystemContent').submit();
    {rdelim}
  {rdelim}
  // ]]>
</script>

<div class="gbBlock">
<form id="SearchSystemContent" action="{g->url}" method="post" onsubmit="return checkForm()">
  <div>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="view"}" value="{$SearchSystemContent.subView}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="SearchSystemContent"/>
  </div>
  <ul>
    <li>
      <input type="text" id="searchCriteria" size="18"
       name="{g->formVar var="form[searchCriteria]"}" value="{g->text text="Search the Gallery"}"
       {literal}
       onfocus="var f=document.getElementById('SearchSystemContent').searchCriteria; if (f.value == searchDefault) { f.value = '' }"
       onblur="var field = document.getElementById('SearchSystemContent').searchCriteria; if (field.value == '') { field.value = searchDefault }"
       {/literal}/>
      <input type="hidden" name="{g->formVar var="form[useDefaultSettings]"}" value="1" />
      <input type="submit" class="inputTypeSubmit" value="{g->text text="Go"}"/>
    </li>
    <li class="gbAdminLink {g->linkId view="search.SearchScan"}">
      <a href="{g->url arg1="view=search.SearchScan" arg2="form[useDefaultSettings]=1"
       arg3="return=1"}">{g->text text="advanced search"}</a>
    </li>
  </ul>
</form>
</div>
