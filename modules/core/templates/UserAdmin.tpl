{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<form action="{g->url}" enctype="{$UserAdmin.enctype|default:"application/x-www-form-urlencoded"}" method="post">
  <div>      
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="{$controller}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}"/>
  </div>

  <div id="gsSystemLinks">
    <ul>
    {foreach from=$UserAdmin.moduleSystemLinks item=module}
    {foreach from=$module item=link}
    {if isset($link.params.view) && $link.params.view == "core:UserAdmin"}
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
      {g->text text="Your Account"}
    </li>

    {if ($UserAdmin.show.userInPathbar)}
    <li>
      {$UserAdmin.user.fullName|default:$UserAdmin.user.userName}
    </li>
    {/if}
  </ul>

  <div id="gsContents">
    <div id="gsAdminSidebar">
      <div class="gbMenu">
        <h2 class="giTitle">
          {g->text text="User Options"}
        </h2>
  
        <ul>
          {foreach from=$UserAdmin.subViewChoices item=choice}
          {if ($UserAdmin.subViewName == $choice.view)}
          <li class="giSelected">
            {$choice.name}
          </li>
          {else}
	    <li class="gbAdminLink" id="gbLink_{$choice.controller|default:''|safecssname}{$choice.view|default:''|safecssname}{$choice.subView|default:''|safecssname}">
            <a href="{g->url arg1="view=core:UserAdmin" arg2="subView=`$choice.view`"}">
              {$choice.name}
            </a>
          </li> 
          {/if}
          {/foreach}
        </ul>
      </div>
      
      <div class="gbMenu">
        <h2 class="giTitle">
          {g->text text="Navigation"}
        </h2>
  
        <ul>
          {foreach from=$UserAdmin.navigationLinks item=link}
            <li> 
              <a href="{$link.url}">
                {$link.name}
              </a>
            </li>
          {/foreach}
        </ul>
      </div>
    </div>

    {include file="gallery:`$UserAdmin.viewBodyFile`" l10Domain=$UserAdmin.viewL10Domain}

  </div>
</form>
