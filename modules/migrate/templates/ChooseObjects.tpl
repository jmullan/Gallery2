{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ChooseObjects.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Select Albums and Users"}
      </div>
    </div>

  </div>

  {if isset($form.error.nothingSelected)}
  <div id="gsStatus">
    <div class="giError">
      {g->text text="You must choose something to import!"}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Import Users"}
    </div>

    <div class="giDescription">
      {g->text text="Select the users to migrate"}
    </div>

    <script type="text/javascript">
      //<![CDATA[
      function setCheck(val) {ldelim}
          ufne=document.forms[0];
	  len = ufne.elements.length;
	  for(i = 0 ; i < len ; i++) {ldelim}
              if (ufne.elements[i].name.substring(0,20)=='g2_form[migrateUser]') {ldelim}
	          ufne.elements[i].checked=val;
	      {rdelim}
	  {rdelim}
      {rdelim}

      function invertCheck() {ldelim}
	  ufne=document.forms[0];
	  len = ufne.elements.length;
	  for(i = 0 ; i < len ; i++) {ldelim}
	      if (ufne.elements[i].name.substring(0,20)=='g2_form[migrateUser]') {ldelim}
	          ufne.elements[i].checked = !(ufne.elements[i].checked);
	      {rdelim}
	  {rdelim}
      {rdelim}
      // ]]>
     </script>

    <span>
      <a href="javascript:setCheck(1)">{g->text text="Check All"}</a>
      <a href="javascript:setCheck(0)">{g->text text="Clear All"}</a>
      <a href="javascript:invertCheck()">{g->text text="Invert Selection"}</a>
    </span>

    {if (sizeof($ChooseObjects.newUsers) > 0)} 
    <table class="gbDataTable">
      <tr>
	<th>
	  {g->text text="Select"}
	</th>
	<th>
	  {g->text text="Username"}
	</th>
	<th>
	  {g->text text="Select"}
	</th>
	<th>
	  {g->text text="Username"}
	</th>
	<th>
	  {g->text text="Select"}
	</th>
	<th>
	  {g->text text="Username"}
	</th>
      </tr>

      <tr class="{cycle values="gbEven,gbOdd"}">
        {foreach name=users key=uid item=username from=$ChooseObjects.newUsers}
	<td>
	  <input type="checkbox" name="{g->formVar var="form[migrateUser][$uid]"}" {if $form.migrateUser.$uid}checked="checked"{/if}/>
	</td>
	<td>
	  {$username}
	</td>

	{if ($smarty.foreach.users.iteration % 3) == 0}
        </tr> <tr class="{cycle values="gbEven,gbOdd"}">
        {/if}
        {/foreach}
      </tr>
      </table>
    {else}
    <b>
      {g->text text="No available users"}
    </b>
    {/if}

    {if sizeof($ChooseObjects.existingUsers) > 0}
    <div class="giTitle">
      {g->text text="These users are already in your gallery, and will not be imported:"}
    </div>

    {foreach key=uid item=username from=$ChooseObjects.existingUsers}
    {$username} <br/>
    {/foreach}
    {/if}
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Import Albums"}
    </div>

    <div class="giDescription">
      {g->text text="Select the albums to migrate"}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Source:"}
      </div>

      <select multiple="multiple" size="10" name="{g->formVar var="form[sourceAlbums][]"}">
	{foreach from=$ChooseObjects.g1AlbumTree item=album}
	<option value="{$album.data.urlencodedname}">
  	  {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}--
  	  {g->text text="%s (%s)" arg1=$album.data.title|htmlentities arg2=$album.data.name}
	</option>
        {/foreach}
      </select>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Destination:"}
      </div>

      <select name="{g->formVar var="form[destinationAlbumID]"}">
	{foreach from=$ChooseObjects.g2AlbumTree item=album}
	<option value="{$album.data.id}">
  	  {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}--
  	  {$album.data.title|default:$album.data.pathComponent}
	</option>
        {/foreach}
      </select>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
        {g->text text="Character Encoding of Source Text:"}
      </div>

      <select name="{g->formVar var="form[sourceEncoding]"}">
        {foreach from=$ChooseObjects.availableEncodings key=encodingName item=encoding}
	  {if strcmp($ChooseObjects.possibleEncodingMatch,$encodingName)}
	    <option value="{$encoding}">{$encodingName}</option>
	  {else}
	    <option value="{$encoding}" selected="selected">{$encodingName}</option>
	  {/if}
        {/foreach}
      </select>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
        {g->text text="URL Redirection"}
      </div>

      <input type="checkbox" name="{g->formVar var="form[urlRedirect]"}"{if $form.urlRedirect} checked="checked"{/if}/>
      {g->text text="Record G1->G2 mappings during import"}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
        {g->text text="Thumbnail generation"}
      </div>

      <input type="checkbox" name="{g->formVar var="form[generateThumbnails]"}"{if $form.generateThumbnails} checked="checked"{/if}/>
      {g->text text="Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster."}
    </div>

  </div>

  <div class="gbButtons">
    <input type="hidden" name="{g->formVar var="albumsPath"}" value="{$ChooseObjects.albumsPath}"/>
    <input type="submit" name="{g->formVar var="form[action][import]"}" value="{g->text text="Import"}"/>
  </div>
</div>
