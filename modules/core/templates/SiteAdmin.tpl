{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SiteAdmin.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<form action="{g->url}" enctype="{$SiteAdmin.enctype|default:"application/x-www-form-urlencoded"}" method="post">
  <div>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="{$controller}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}" />
  </div>

  <ul class="gbBreadCrumb">
    <li class="giBreadCrumbFirst">
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
          <li {*TEMP:*}style="text-decoration:underline"> {$group.0.groupLabel} </li>
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
        {/foreach}
        </ul>
      </div>
  
      <div class="gbMenu">
          <h2 class="giTitle"> {g->text text="Navigation"} </h2>
          
          <ul>
            <li> 
              <a href="{g->url}">
                {g->text text="Browse Gallery"}
              </a>
            </li>
          </ul>
      </div>
    </div>
      {include file="gallery:`$SiteAdmin.viewBodyFile`" l10Domain=$SiteAdmin.viewL10Domain}
  </div>
</form>
