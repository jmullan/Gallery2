{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SearchShowAll.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<form action="{g->url}" method="post">
  <p>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="{$SearchShowAll.controller}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="SearchShowAll"/>
    <input type="hidden" name="{g->formVar var="form[moduleId]"}" value="{$form.moduleId}"/>
    <input type="hidden" name="{g->formVar var="form[page]"}" value="{$form.page}"/>
  </p>

  <div id="gsHeader">
    <div class="gbTitleBanner">
      <div class="gbBreadCrumb">
        <span>
          <a href="{g->url}">
            {g->text text="Gallery"}
          </a>
        </span>
        <span>
          {g->text text="Search"}
        </span>
      </div>
    </div>
  </div>

  <div id="gsSearchContents">
    <div class="gbTopFlag">
      <div class="giTitle">
        {g->text text="Search the Gallery"}
      </div>
    </div>

    <div class="gbAdmin">
      <div class="giTitle">
        {g->text text="Search"}
      </div>

      <input type="text" size="50" name="{g->formVar var="form[searchCriteria]"}" value="{$form.searchCriteria}"/>
      <input type="hidden" name="{g->formVar var="form[lastSearchCriteria]"}" value="{$form.searchCriteria}"/>

      {if isset($form.error.searchCriteria.missing)}
      <div class="giError">
        {g->text text="You must enter some text to search for!"}
      </div>
      {/if}

      <input type="submit" name="{g->formVar var="form[action][search]"}" value="{g->text text="Search"}"/>
    </div>

    <div class="gbAdmin">
      <div class="giTitle">
        {$SearchShowAll.moduleInfo.name}
      </div>
      
      {foreach from=$SearchShowAll.moduleInfo.options key=optionId item=optionInfo}
      {capture name=checkboxName}{g->formVar var="form[options][`$SearchShowAll.moduleId`][$optionId]"}{/capture}
      <input id="{$optionId}" type="checkbox" name={$smarty.capture.checkboxName}
      {if isset($form.options[$SearchShowAll.moduleId].$optionId)}checked="checked"{/if}
      />
      <label for="{$optionId}">
        {$optionInfo.description}
      </label>
      <br/>
      {/foreach}
    </div>

    {if !empty($SearchShowAll.results)}
    <div class="gbAdmin">
      <div class="giTitle">
        {g->text text="Search Results"}
      </div>
    </div>
          
    <div class="gbAdmin">
      <div class="giTitle">
        {g->text text="Searching %s only" arg1=$SearchShowAll.moduleInfo.name}
        <input type="submit" name="{g->formVar var="form[action][scan]"}" value="{g->text text="Search all modules"}"/>
        {$SearchShowAll.moduleInfo.name}
      </div>
    </div>

    <div class="gbAdmin">
      <div class="giTitle">
        {if ($SearchShowAll.results.count > 0)}
        {if ($form.page > 1)}
        <input type="submit" name="{g->formVar var="form[action][previousPage]"}" value="{g->text text="&laquo; Back"}"/>
        {/if}
        {g->text text="(Results %d - %d of %d, Page %d of %d)"
                 arg1=$SearchShowAll.results.start
                 arg2=$SearchShowAll.results.end
                 arg3=$SearchShowAll.results.count
                 arg4=$form.page
                 arg5=$SearchShowAll.maxPages}
        {/if}

        {if ($form.page < $SearchShowAll.maxPages)}
        <input type="submit" name="{g->formVar var="form[action][nextPage]"}" value="{g->text text="Next &raquo;"}"/>
        {/if}
      </div>

      {if (sizeof($SearchShowAll.results.results) > 0)}
      <table>
        {assign var="searchCriteria" value=$form.searchCriteria} 
        {foreach from=$SearchShowAll.results.results item=result} 
        {assign var=itemId value=$result.itemId} 
        <tr>
          <td>
            <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=$itemId"}">
      	{if isset($SearchShowAll.thumbnails.$itemId)}
      	{g->image item=$SearchShowAll.items.$itemId image=$SearchShowAll.thumbnails.$itemId}
      	{else}
      	{g->text text="No thumbnail"}
      	{/if}
            </a>
          </td>
      	    
          <td>
            <div class="giInfo">
      	{foreach from=$result.fields item=field} 
      	<span>
      	  <b>{$field.key}</b>
      	  {$field.value|default:"&nbsp;"|replace:$searchCriteria:"<b>$searchCriteria</b>"|markup}
      	</span>
      	{/foreach}
            </div>
          </td>
        </tr>
        {/foreach}
      </table>
      {else} 
      {g->text text="No results"}
      {/if}
    </div>
  </div>
  {/if}
</form>
