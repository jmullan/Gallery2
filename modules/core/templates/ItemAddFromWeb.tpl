{g->element}
  {if !empty($form.webPageUrls)}
    <script type="text/javascript" language="javascript">
      function toggleSelections() {ldelim}
        form = document.forms[0];
        state = form.elements['{g->elementName name="selectionToggle"}'].checked;
        {foreach from=$form.webPageUrls item=url}
        form.elements['{g->elementName name="form[webPageUrls][`$url.url`]"}'].checked = state;
        {/foreach}
      {rdelim}
    </script>
  {/if}

  <script type="text/javascript" language="javascript">
    function selectPath(path) {ldelim}
      document.forms[0].elements['{g->elementName name="form[webPage]"}'].value = path;
    {rdelim}
  </script>
{/g->element}

{g->box style="admin"}
  {g->description}
    {g->text text="Import files into Gallery from another website.  Enter a URL below to a web page anywhere on the net and Gallery will allow you to upload any media files that it finds on that page.  Note that if you're entering a URL to a directory, you should end the URL with a trailing slash (eg, http://example.com/directory/). "}
  {/g->description}

  {if empty($form.webPageUrls)}
    {g->element}
      {g->text text="URL"}
      {g->input type="text" size="80" name="form[webPage]"}{$form.webPage}{/g->input}
    {/g->element}
    
    {if isset($form.error.webPage.missing)}
      {g->error}
	{g->text text="You must enter a URL to a web page"}
      {/g->error}
    {/if}
    
    {if isset($form.error.webPage.invalid)}
      {g->error}
	{g->text text="The URL entered must begin with http://"}
      {/g->error}
    {/if}
    
    {if isset($form.error.webPage.unavailable)}
      {g->error}
	{g->text text="The web page you specified is unavailable"}
      {/g->error}
    {/if}
    
    {g->element}
      {if !empty($ItemAddFromWeb.recentPaths)}
	{g->text text="Recent URLs"}
	{g->listing}
	  {foreach from=$ItemAddFromWeb.recentPaths item=dir}
	    {g->item}
	      {g->title}
		{g->link javascript="selectPath('$dir')"}
		  {$dir}
		{/g->link}
	      {/g->title}
	    {/g->item}
	  {/foreach}
	{/g->listing}
      {/if}

      {g->input type="submit" name="form[action][findFilesFromWebPage]"}
	{g->text text="Find Files"}
      {/g->input}
    {/g->element}
  {else} {* {if empty($form.webPageUrls)} *}
    {g->element style="emphasized"}
      {g->text text="URL: %s" arg1=$form.webPage}
      {g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemAddFromWeb" arg3="itemId=`$ItemAdmin.item.id`" arg4="form[webPage]=`$form.webPage`" arg5="form[formName]=ItemAddFromWeb"}
	{g->text text="change"}
      {/g->link}
      {g->input type="hidden" name="form[webPage]"}{$form.webPage}{/g->input}
    {/g->element}
    {g->element}
      {g->text one="%d url found" 
      many="%d urls found" 
      count=$ItemAddFromWeb.webPageUrlCount 
      arg1=$ItemAddFromWeb.webPageUrlCount}
    {/g->element}

    {g->table style="admin_listing" evenodd="true"}
      {g->row}
	{g->column header="true"}
	  {g->input name="selectionToggle" type="checkbox" onClick="javascript:toggleSelections()"}{/g->input}
	{/g->column}
	{g->column header="true"}
	  {g->text text="URL"}
	{/g->column}
	{g->column header="true"}
	  {g->text text="Type"}
	{/g->column}
      {/g->row}

      {foreach from=$form.webPageUrls item=url}
	{g->row}
	  {g->column}
	    {g->input type="checkbox" name="form[webPageUrls][`$url.url`]"}{/g->input}
	  {/g->column}
	  {g->column}
	    {$url.url}
	  {/g->column}
	  {g->column}
	    {$url.itemType}
	  {/g->column}
	{/g->row}
      {/foreach}
    {/g->table}
    {g->input type="submit" name="form[action][addFromWebPage]"}{g->text text="Add URLs"}{/g->input}
  {/if} {* {if !empty($form.webPageUrls)} *}
{/g->box}
