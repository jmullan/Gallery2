<li>
	<p>
		{gallery->input type="checkbox" name=form.migratealbum.$albumName}1{/gallery->input}
		<span class="albumname">{$albumName}</span>
		<span class="albumtitle" style="font-weight: bold;">{$albumList[$albumName].title}</span>
	</p>
	<ul>
		{foreach key=name item=fields from=$albumList}
			{if $fields.parentAlbumName eq $albumName}
				{include file="AlbumList.tpl" albumName=$name albumList=$albumList}
			{/if}
		{/foreach}
	</ul>
</li>