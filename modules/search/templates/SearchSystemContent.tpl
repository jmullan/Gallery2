{*
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
    <ul>
      <li>
        <input type="hidden" name="{g->formVar var="view"}" value="{$SearchSystemContent.subView}" />
        <input type="hidden" name="{g->formVar var="form[formName]"}" value="SearchSystemContent" />
        <input type="text" value="{g->text text="Search the Gallery"}" name="{g->formVar var="form[searchCriteria]"}" id="searchCriteria" size="15" onfocus="this.style.background='#fff';this.value='';this.style.color='#333';" onblur="this.style.background='#eee';this.style.color='#ccc';" />
        <input type="hidden" name="{g->formVar var="form[useDefaultSettings]"}" value="1" />
        <input type="submit" value="{g->text text="Go"}"/>
      </li>
      <li>
      <a href="{g->url arg1="view=search:SearchScan" arg2="form[useDefaultSettings]=1"}">{g->text text="advanced search"}</a>
      </li>
    </ul>
  </form>
</div>
