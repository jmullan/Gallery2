{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Confirm Migration"}
      </div>
    </div>

  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Users to import:"}
    </div>

    {if isset($form.migrateUser)}
      {foreach from=$form.migrateUser key=uid item=junk}
      <input type="hidden" name="{g->formVar var="form[migrateUser][$uid]"}" value="1"/>
      {$ConfirmImport.uids.$uid} &nbsp;
      {/foreach}
    </table>
    {/if}
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Albums to import"}
    </div>

    <table class="gbDataTable">
      <tr>
	<th>
	  {g->text text="Album Name"}
	</th>
	<th>
	  {g->text text="Album Title"}
	</th>
	<th>
	  {g->text text="Album Notes"}
	</th>
      </tr>

      {foreach from=$form.sourceAlbums item=albumName}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {$ConfirmImport.urlDecoded.$albumName}
	  <input type="hidden" name="{g->formVar var="form[sourceAlbums][$albumName]"}" value="1"/>
	</td>

	<td>
	  {$ConfirmImport.titles.$albumName}
	</td>

	<td>
	  {if ($ConfirmImport.existingAlbums.$albumName)> 0}
	  {g->text text="An album already exists with this name.  This album will be renamed."}
	  <br />
	  {/if}

	  {if ($ConfirmImport.illegalAlbumNames.$albumName) != ''}
	  {g->text text="This album has an illegal name and will be renamed to <i>%s</i>"
		   arg1=$ConfirmImport.illegalAlbumNames.$albumName}
	  <br />
	  {/if}

	  {if (!$ConfirmImport.albumValidOwner.$albumName)}
	  {g->text text="This album's owner (%s) hasn't been imported." arg1=$ConfirmImport.albumOwnerUserName.$albumName}
	  <input type="checkbox" name="{g->formVar var="form[migrateUser][`$ConfirmImport.albumOwnerUid.$albumName`]}" />
	  {g->text text="Import %s now." arg1=$ConfirmImport.albumOwnerUserName.$albumName }
	  {/if}
	</td>
      </tr>
      {/foreach}
    </table>
  </div>

  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="Top level albums and albums whose parents are not selected will be imported into this album:"}
    </div>
    <div class="giInfo">
      <span>
	{g->text text="Title: %s" arg1=$ConfirmImport.targetAlbum.title|default:$ConfirmImport.targetAlbum.pathComponent}
      </span><br />
      <span>
	{g->text text="Description: %s" arg1=$ConfirmImport.targetAlbum.description|default:""}
      </span>
    </div>
    <input type="hidden" name="{g->formVar var="form[destinationAlbumID]"}"
     value="{$ConfirmImport.destinationAlbumID}"/>
  </div>
  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="Your Gallery 1 will be converted from this character encoding into UTF-8:"}
    </div>
    <div class="giInfo">
      <span>
	{g->text text="Encoding: %s" arg1=$form.sourceEncoding}
      </span>
    </div>
  </div>
  <input type="hidden" name="{g->formVar var="form[sourceEncoding]"}"
   value="{$form.sourceEncoding}"/>
  {if isset($form.urlRedirect)}
    <div class="gbAdmin">
      <p class="giDescription">
	{g->text text="G1->G2 mappings will be recorded for use in URL Redirection"}
      </p>
      <input type="hidden" name="{g->formVar var="form[urlRedirect]"}" value="{$form.urlRedirect}"/>
    </div>
  {/if}
  {if isset($form.generateThumbnails)}
  <div class="gbAdmin">
    <p class="giDescription">
    <input type="hidden" name="{g->formVar var="form[generateThumbnails]"}"
     value="{$form.generateThumbnails}"/>
    {g->text text="Thumbnails will be generated during migration"}
    </p>
  </div>
  {/if}
  <div class="gbAdmin">
    <input type="hidden" name="{g->formVar var="form[set][title]"}" value="{$form.set.title}"/>
    <input type="hidden" name="{g->formVar var="form[set][summary]"}" value="{$form.set.summary}"/>
    <input type="hidden" name="{g->formVar var="form[set][description]"}"
     value="{$form.set.description}"/>
    {if isset($form.customfield.title)}
      <input type="hidden" name="{g->formVar var="form[customfield][title]"}"
       value="{$form.customfield.title}"/>
    {/if}
    {if isset($form.customfield.summary)}
      <input type="hidden" name="{g->formVar var="form[customfield][summary]"}"
       value="{$form.customfield.summary}"/>
    {/if}
    {if isset($form.customfield.description)}
      <input type="hidden" name="{g->formVar var="form[customfield][description]"}"
       value="{$form.customfield.description}"/>
    {/if}
    {if isset($form.set.defaultDescription)}
      <input type="hidden" name="{g->formVar var="form[set][defaultDescription]"}"
       value="{$form.set.defaultDescription}"/>
    {/if}

    <p class="giDescription">
      {g->text text="Item fields will be imported from:"}
    </p>
    <table class="gbDataTable">
      <tr><td>
	{g->text text="Title"} =
	{if $form.set.title=="filename"} {g->text text="Base filename"}
	{elseif $form.set.title=="caption"} {g->text text="Caption"}
	{elseif $form.set.title=="custom"} {g->text text="Custom field:"}
					   {$form.customfield.title}
	{else} {g->text text="Blank"}
	{/if}
      </td></tr><tr><td>
	{g->text text="Summary"} =
	{if $form.set.summary=="filename"} {g->text text="Base filename"}
	{elseif $form.set.summary=="caption"} {g->text text="Caption"}
	{elseif $form.set.summary=="custom"} {g->text text="Custom field:"}
					     {$form.customfield.summary}
	{else} {g->text text="Blank"}
	{/if}
      </td></tr><tr><td>
	{g->text text="Description"} =
	{if $form.set.description=="filename"} {g->text text="Base filename"}
	{elseif $form.set.description=="caption"} {g->text text="Caption"}
	{elseif $form.set.description=="custom"} {g->text text="Custom field:"}
						 {$form.customfield.description}
	  {if !empty($form.set.defaultDescription)}
	    {g->text text="(Default to summary value if not set)"}
	  {/if}
	{else} {g->text text="Blank"}
	{/if}
      </td></tr>
    </table>
  </div>
  <div class="gbButtons">
    <input type="hidden" name="{g->formVar var="albumsPath"}" value="{$ConfirmImport.albumsPath}"/>
    <input type="submit" name="{g->formVar var="form[action][import]"}"
     value="{g->text text="Import"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}"
     value="{g->text text="Cancel"}"/>
  </div>
</div>
