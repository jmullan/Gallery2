<div class="gbAdmin">
  {if !empty($form.webPageUrls)}
  <script type="text/javascript">
    function toggleSelections() {ldelim}
      form = document.forms[0];
      state = form.elements['selectionToggle'].checked;
      {foreach from=$form.webPageUrls item=url}
      form.elements['{g->elementName name="form[webPageUrls][`$url.url`]"}'].checked = state;
      {/foreach}
    {rdelim}
  </script>
  {/if}

  <script type="text/javascript">
    function selectPath(path) {ldelim}
      document.forms[0].elements['{g->elementName name="form[webPage]"}'].value = path;
    {rdelim}
  </script>

  <div class="giDescription">
    {g->text text="Import files into Gallery from another website.  Enter a URL below to a web page anywhere on the net and Gallery will allow you to upload any media files that it finds on that page.  Note that if you're entering a URL to a directory, you should end the URL with a trailing slash (eg, http://example.com/directory/). "}
  </div>

  {if empty($form.webPageUrls)}
  <div class="gbDataEntry">
    <div class="giTitle">
      {g->text text="URL"}
    </div>

    <input type="text" size="80" name="{g->formVar var="form[webPage]"}" value="{$form.webPage}"/>
    
    {if isset($form.error.webPage.missing)}
    <div class="giError">
      {g->text text="You must enter a URL to a web page"}
    </div>
    {/if}
    
    {if isset($form.error.webPage.invalid)}
    <div class="giError">
      {g->text text="The URL entered must begin with http://"}
    </div>
    {/if}
    
    {if isset($form.error.webPage.unavailable)}
    <div class="giError">
      {g->text text="The web page you specified is unavailable"}
    </div>
    {/if}
  </div>
    
  {if !empty($ItemAddFromWeb.recentPaths)}
  {g->text text="Recent URLs"}
  <ul>
    {foreach from=$ItemAddFromWeb.recentPaths item=dir}
    <li>
      <a href="javascript:"selectPath('{$dir}')">
	{$dir}
      </a>
    </li>
    {/foreach}
  </ul>
  {/if}

  <input type="submit" name="{g->formVar var="form[action][findFilesFromWebPage]"}" value="{g->text text="Find Files"}"/>
  {else} {* {if empty($form.webPageUrls)} *}
  <b>
    {g->text text="URL: %s" arg1=$form.webPage}
    <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`" arg4="form[webPage]=`$form.webPage`" arg5="form[formName]=ItemAddFromWeb" arg6="addPlugin=ItemAddFromWeb"}">{g->text text="change"}</a>
  </b>

  <input type="hidden" name="{g->formVar var="form[webPage]"}" value="{$form.webPage}"/>

  <br /

  {g->text one="%d url found" 
           many="%d urls found" 
           count=$ItemAddFromWeb.webPageUrlCount 
           arg1=$ItemAddFromWeb.webPageUrlCount}

  <table width="100%">
    <tr>
      <th>
	<input name="selectionToggle" type="checkbox" onClick="javascript:toggleSelections()"/>
      </th>
      <th>
	{g->text text="URL"}
      </th>
      <th>
	{g->text text="Type"}
      </th>
    </tr>

    {foreach from=$form.webPageUrls item=url}
    <tr class="{cycle values="gbEven,gbOdd"}">
      <td>
	<input type="checkbox" name="{g->formVar var="form[webPageUrls][`$url.url`]"}"/>
      </td>
      <td>
	{$url.url}
      </td>
      <td>
	{$url.itemType}
      </td>
    </tr>
    {/foreach}
  </table>
  <input type="submit" name="{g->formVar var="form[action][addFromWebPage]"}" value="{g->text text="Add URLs"}"/>
  {/if} {* {if !empty($form.webPageUrls)} *}
</div>
