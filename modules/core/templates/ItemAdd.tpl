<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Add Items"}
      </div>
    </div>
    
    <div class="spacer">
      &nbsp;
    </div>
  </div>

  <div class="gbAdmin">
    <div class="gbTabBar">
      <ul>
	{foreach from=$ItemAdd.plugins item=plugin} 
	{if $plugin.isSelected}
	<li class="giSelectedTab"> 
	  {$plugin.title}
	</li>
        {else}
        <li>
	  <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`" arg4="addPlugin=`$plugin.id`"}">{$plugin.title}</a>
	</li>
	{/if}
        {/foreach}
      </ul>
    </div>

    <input type="hidden" name="{g->formVar var="addPlugin"}" value="{$ItemAdd.addPlugin}"/>
    {include file=$ItemAdd.pluginFile l10Domain=$ItemAdmin.viewL10Domain}
  </div>
</div>
