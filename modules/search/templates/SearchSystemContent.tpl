{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SearchSystemContent.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}

<script type="text/javascript">
// <![CDATA[
function checkForm() {ldelim}
	sc = document.SearchSystemContent.searchCriteria.value;
    if (sc == '{g->text text="Search the Gallery"}' || sc == '') {ldelim}
		alert('Please enter keywords to search.');
		document.SearchSystemContent.searchCriteria.focus;
		return false;
	{rdelim} else {ldelim}
	   document.getElementById('SearchSystemContent').submit();
	{rdelim}
{rdelim}
// ]]>
</script>

<div class="gbMenu">
  <form id="SearchSystemContent" name="SearchSystemContent" action="{g->url}" method="post">
    <p>
      <input type="hidden" name="{g->formVar var="view"}" value="{$SearchSystemContent.view}"/>
      <input type="hidden" name="{g->formVar var="form[formName]"}" value="SearchSystemContent"/>
      <input type="text" value="{g->text text="Search the Gallery"}" name="{g->formVar var="form[searchCriteria]"}" id="searchCriteria" size="15" onfocus="this.style.background='#fff';this.value='';this.style.color='#333';" onblur="this.style.background='#eee';this.style.color='#ccc';"/>
      <input type="hidden" name="{g->formVar var="form[useDefaultSettings]"}" value="1"/>
	  <a href="#" onClick="return checkForm()" class="button">
		{g->text text="Go"}
	  </a>
    </p>
    <p>
	  <a href="javascript:document.getElementById('SearchSystemContent').submit()">advanced search</a>
    </p>
  </form>
</div>
