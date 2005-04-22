{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <div class="dtree">
    {assign var="params" value=$AlbumSelectSystemContent.params}
    {if $params.treeExpandCollapse and !$params.treeCloseSameLevel}
      <p>
	<a href="javascript: albumTree.openAll(); this.blur()">{g->text text="Expand"}</a>
	|
	<a href="javascript: albumTree.closeAll(); this.blur()">{g->text text="Collapse"}</a>
      </p>
    {/if}

    <script type="text/javascript">
      // <![CDATA[
      var albumTree = new dTree('albumTree');
      albumTree.config.useLines = {if $params.treeLines}true{else}false{/if};
      albumTree.config.useIcons = {if $params.treeIcons}true{else}false{/if};
      albumTree.config.useCookies = {if $params.treeCookies}true{else}false{/if};
      albumTree.config.closeSameLevel = {if $params.treeCloseSameLevel}true{else}false{/if};
      albumTree.add(0, -1, " {$AlbumSelectSystemContent.titles.root}",
		    '{g->url}');
      {foreach from=$AlbumSelectSystemContent.tree item=node}
	{assign var="title" value=$AlbumSelectSystemContent.titles[$node.id]}
	albumTree.add({$node.nodeId}, {$node.parentNode}, "{$title}",
		      '{g->url arg1="view=core:ShowItem" arg2="itemId=`$node.id`"}');
      {/foreach}
      document.write(albumTree);
      // ]]>
    </script>
  </div>
</div>
