{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ConfirmImport.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
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
	{g->text text="Title: %s" arg1=$ConfirmImport.targetAlbum.title}
      </span>
      <span>
	{g->text text="Description: %s" arg1=$ConfirmImport.targetAlbum.description}
      </span>
    </div>
    <input type="hidden" name="{g->formVar var="form[destinationAlbumID]"}" value="{$ConfirmImport.destinationAlbumID}"/>
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
  <input type="hidden" name="{g->formVar var="form[sourceEncoding]"}" value="{$form.sourceEncoding}"/>
  {if isset($form.urlRedirect)}
    <div class="gbAdmin">
      <p class="giDescription">
	{g->text text="G1->G2 mappings will be recorded for use in URL Redirection"}
      </p>
      <input type="hidden" name="{g->formVar var="form[urlRedirect]"}" value="{$form.urlRedirect}"/>
    </div>
  {/if}
  <div class="gbAdmin">
    <p class="giDescription">
    <input type="hidden" name="{g->formVar var="form[generateThumbnails]"}" value="{$form.generateThumbnails}" />
    {g->text text="Thumbnails will be generated during migration"}
    </p> 
  </div>
  <div class="gbButtons">
    <input type="hidden" name="{g->formVar var="albumsPath"}" value="{$ConfirmImport.albumsPath}"/>
    <input type="submit" name="{g->formVar var="form[action][import]"}" value="{g->text text="Import"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>
