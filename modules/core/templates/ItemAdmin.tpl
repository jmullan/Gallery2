{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemAdmin.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<form action="{g->url}" enctype="{$ItemAdmin.enctype}" method="post">
  <p>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="{$controller}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}"/>
    <input type="hidden" name="{g->formVar var="itemId"}" value="{$ItemAdmin.item.id}"/>
  </p>

  <ul class="gbBreadCrumb">
    {foreach name="parent" from=$ItemAdmin.parents item=parent}
    <li {if $smarty.foreach.parent.first}class="giBreadCrumbFirst"{/if}>
      <a href="{g->url arg1="view=core:ShowItem"
         arg2="itemId=`$parent.id`"}">{$parent.title|default:$parent.pathComponent|markup}</a>
    </li>
    {/foreach}
    
    <li {if empty($ItemAdmin.parents)}class="giBreadCrumbFirst"{/if}>
      <a href="{g->url arg1="view=core:ShowItem" 
         arg2="itemId=`$ItemAdmin.item.id`"}">{$ItemAdmin.item.title|default:$ItemAdmin.item.pathComponent|markup}</a>
    </li>
  </ul>

  
  <div id="gsContents">
    <div id="gsAdminSidebar">
      {if !$ItemAdmin.isRootAlbum}
      <div class="gbMenu">
        {if empty($ItemAdmin.thumbnail)}
        <span>
          {g->text text="No Thumbnail"}
        </span>
        {else}
        {g->image item=$ItemAdmin.item image=$ItemAdmin.thumbnail maxSize=130}
        {/if}
  
        <h3 class="giTitle">
          {$ItemAdmin.item.title|markup}
        </h3>
      </div>
      {/if}
  
      <div class="gbMenu">
        <h3 class="giTitle">
          {g->text text="Options"}
        </h3>
        
        <ul>
          {foreach from=$ItemAdmin.subViewChoices key=choiceName item=choiceParams}
          <li>
            <a href="{g->url params=$choiceParams}">
              {$choiceName}
            </a>
          </li>
          {/foreach}
        </ul>
      </div>
      
      <div class="gbMenu">
        <h3 class="giTitle">
          {g->text text="Navigation"}
        </h3>
        
        <ul>
          {if ($ItemAdmin.isSiteAdmin)}
          <li>
            <a href="{g->url arg1="view=core:SiteAdmin"}">
              {g->text text="Site Admin"}
            </a>
          </li>
          {/if}
  
          {if ($ItemAdmin.itemType == 'item')}
          <li>
            <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$ItemAdmin.item.id`"}">
              {g->text text="Back to Item View"}
            </a>
          </li>
          <li>
            <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$ItemAdmin.parent.id`"}">
              {g->text text="Back to Album View"}
            </a>
          </li>
  
          {else}
          <li>
            <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$ItemAdmin.item.id`"}">
              {g->text text="Back to Album View"}
            </a>
          </li>
          {/if}
  
        </ul>
      </div>
    </div>

  {include file="gallery:`$ItemAdmin.viewBodyFile`" l10Domain=$ItemAdmin.viewL10Domain}
  </div>
</form>
