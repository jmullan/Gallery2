{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<form action="{g->url}" enctype="{$SiteAdmin.enctype|default:"application/x-www-form-urlencoded"}" method="post">
  <div>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="{$controller}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}" />
  </div>

  <div id="gsSystemLinks">
    <ul>
    {foreach from=$SiteAdmin.moduleSystemLinks item=module}
    {foreach from=$module item=link}
    {if isset($link.params.view) && $link.params.view == "core:SiteAdmin"}
      <li class="giSelected">
        {$link.text}
      </li>
    {else}
      <li>
        <a href="{g->url params=$link.params}">{$link.text}</a>
      </li>
    {/if}
    {/foreach}
    {/foreach}
    </ul>
  </div>

  <ul class="gbBreadCrumb">
    <li class="giBreadCrumbFirst">
      <a href="{g->url}">{$SiteAdmin.rootAlbum.title}</a>
    </li>

    <li>
      {g->text text="Site Administration"}
    </li>
  </ul>
  <div id="gsContents">
    <div id="gsAdminSidebar">
      <div class="gbMenu">
        <h2 class="giTitle"> {g->text text="Admin Options"} </h2>
  
        <!-- TODO: Figure out how to get icons in here in a modular way -->
        <ul>
          {foreach from=$SiteAdmin.subViewGroups item=group}
          <li> {$group.0.groupLabel} 
	    <ul>
	      {foreach from=$group item=choice}
	      {if ($SiteAdmin.subViewName == $choice.view)}
	      <li class="giSelected"> {$choice.name} </li>
	      {else}
	      <li>
		<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=`$choice.view`"}">
		  {$choice.name}
		</a>
	      </li>
	      {/if}
	      {/foreach}
            </ul>
          </li>
          {/foreach}
        </ul>
      </div>
  
      <div class="gbMenu">
          <h2 class="giTitle"> {g->text text="Navigation"} </h2>
          
          <ul>
          {foreach from=$SiteAdmin.navigationLinks item=link}
            <li> 
              <a href="{$link.url}">
                {$link.name}
              </a>
            </li>
          {/foreach}
          </ul>
      </div>
    </div>
      {include file="gallery:`$SiteAdmin.viewBodyFile`" l10Domain=$SiteAdmin.viewL10Domain}
  </div>
</form>
