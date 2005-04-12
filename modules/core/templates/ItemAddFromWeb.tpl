{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<script type="text/javascript">
  // <![CDATA[
{if !empty($form.webPageUrls)}
  function toggleSelections() {ldelim}
    form = document.forms[0];
    state = form.elements['selectionToggle'].checked;
    for (i = 1; i <= {$ItemAddFromWeb.webPageUrlCount}; i++) {ldelim}
        cb = document.getElementById('cb_' + i);
        cb.checked = state;
    {rdelim}
  {rdelim}
{/if}

  function selectPath(path) {ldelim}
    document.forms[0].elements['{g->formVar var="form[webPage]"}'].value = path;
  {rdelim}
  // ]]>
</script>

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="Import files into Gallery from another website.  Enter a URL below to a web page anywhere on the net and Gallery will allow you to upload any media files that it finds on that page.  Note that if you're entering a URL to a directory, you should end the URL with a trailing slash (eg, http://example.com/directory/). "}
  </p>

  {if empty($form.webPageUrls)}
    <h4> {g->text text="URL"} </h4>

    <input type="text" size="80"
     name="{g->formVar var="form[webPage]"}" value="{$form.webPage}"/>

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
    {if isset($form.error.webPage.nothingSelected)}
    <div class="giError">
      {g->text text="Nothing added since no items were selected"}
    </div>
    {/if}

    {if !empty($ItemAddFromWeb.recentPaths)}
      <br/>
      {g->text text="Recent URLs"}
      {foreach from=$ItemAddFromWeb.recentPaths item=dir}
	<br/>
	<a href="javascript:"selectPath('{$dir}')"> {$dir} </a>
      {/foreach}
    {/if}

    {capture name="submitButtons"}
      <input type="submit" class="inputTypeSubmit"
       name="{g->formVar var="form[action][findFilesFromWebPage]"}"
       value="{g->text text="Find Files"}"/>
    {/capture}
  {else} {* {if empty($form.webPageUrls)} *}
    <strong>
      {g->text text="URL: %s" arg1=$form.webPage}
      &nbsp;
      <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd"
       arg3="itemId=`$ItemAdmin.item.id`" arg4="form[webPage]=`$form.webPage`"
       arg5="form[formName]=ItemAddFromWeb" arg6="addPlugin=ItemAddFromWeb"}">
	{g->text text="change"}
      </a>
    </strong>

    <input type="hidden" name="{g->formVar var="form[webPage]"}" value="{$form.webPage}"/>
    <br/>

    {g->text one="%d url found" many="%d urls found"
	     count=$ItemAddFromWeb.webPageUrlCount arg1=$ItemAddFromWeb.webPageUrlCount}

    <table class="gbDataTable" style="margin-top: 0.5em"><tr>
      <th> </th>
      <th> {g->text text="URL"} </th>
      <th> {g->text text="Type"} </th>
    </tr>
    {foreach from=$form.webPageUrls item=url}
    <tr class="{cycle values="gbEven,gbOdd"}">
      <td>
	<input type="checkbox" id="cb_{counter}"
	 name="{g->formVar var="form[webPageUrls][`$url.url`]"}"/>
      </td><td>
	{$url.url}
      </td><td>
	{$url.itemType}
      </td>
    </tr>
    {/foreach}
    <tr>
      <th>
	<input type="checkbox" name="selectionToggle" onClick="javascript:toggleSelections()"/>
      </th>
      <th colspan="2">
	{g->text text="(Un)check all"}
      </th>
    </tr></table>
  </div>

  <div class="gbBlock">
    <p class="giDescription">
      {g->text text="Copy base filenames to:"}
      <br/>

      <input type="checkbox" id="cbTitle"{if $form.set.title} checked="checked"{/if}
       name="{g->formVar var="form[set][title]"}"/>
      <label for="cbTitle"> {g->text text="Title"} </label>
      &nbsp;

      <input type="checkbox" id="cbSummary"{if $form.set.summary} checked="checked"{/if}
       name="{g->formVar var="form[set][summary]"}"/>
      <label for="cbSummary"> {g->text text="Summary"} </label>
      &nbsp;

      <input type="checkbox" id="cbDescription"{if $form.set.description} checked="checked"{/if}
       name="{g->formVar var="form[set][description]"}"/>
      <label for="cbDescription"> {g->text text="Description"} </label>
    </p>

    {capture name="submitButtons"}
      <input type="submit" class="inputTypeSubmit"
       name="{g->formVar var="form[action][addFromWebPage]"}" value="{g->text text="Add URLs"}"/>
    {/capture}
    {assign var="showOptions" value="true"}
  {/if} {* {if !empty($form.webPageUrls)} *}
</div>

{if isset($showOptions)}
  {* Include our extra ItemAddOptions *}
  {foreach from=$ItemAdd.options item=option}
    {include file="gallery:`$option.file`" l10Domain=$option.l10Domain}
  {/foreach}
{/if}

<div class="gbBlock gcBackground1">
  {$smarty.capture.submitButtons}
</div>
