{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SearchSystemContent.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}

<script type="text/javascript">
// <![CDATA[
function checkForm() {ldelim}
  sc = document.getElementById('SearchSystemContent').searchCriteria.value;
  if (sc == '{g->text text="Search the Gallery"}' || sc == '') {ldelim}
    alert('{g->text text="Please enter keywords to search."}');
    return false;
  {rdelim} else {ldelim}
     document.getElementById('SearchSystemContent').submit();
  {rdelim}

{rdelim}
// ]]>
</script>

<div class="gbMenu">
  <form id="SearchSystemContent" action="{g->url}" method="post" onsubmit="return checkForm()">
    <div>
      {g->hiddenFormVars}
      <input type="hidden" name="{g->formVar var="view"}" value="{$SearchSystemContent.subView}" />
      <input type="hidden" name="{g->formVar var="form[formName]"}" value="SearchSystemContent" />
    </div>
    <ul>
      <li>
        <input type="text" value="{g->text text="Search the Gallery"}" name="{g->formVar var="form[searchCriteria]"}" id="searchCriteria" size="18"
		onfocus="var field = document.getElementById('SearchSystemContent').searchCriteria; if (field.value == '{g->text text="Search the Gallery"}') {ldelim} field.value = '' {rdelim}"
		onblur="var field = document.getElementById('SearchSystemContent').searchCriteria; if (field.value == '') {ldelim} field.value = '{g->text text="Search the Gallery"}' {rdelim}"
	/>
        <input type="hidden" name="{g->formVar var="form[useDefaultSettings]"}" value="1" />
        <input type="submit" value="{g->text text="Go"}"/>
      </li>
      <li>
      <a href="{g->url arg1="view=search:SearchScan" arg2="form[useDefaultSettings]=1" arg3="return=1"}">{g->text text="advanced search"}</a>
      </li>
    </ul>
  </form>
</div>
