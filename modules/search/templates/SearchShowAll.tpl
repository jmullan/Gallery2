{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SearchShowAll.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}

<ul class="gbBreadCrumb">
  <li class="giBreadCrumbFirst">
    <a href="{g->url}">{g->text text="Gallery"}</a>
  </li>
  <li>
    {g->text text="Search Results"}
  </li>
</ul>

<div id="gsContents">
  {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}

  <div id="gsAlbumContents">
    <form action="{g->url}" method="post">
      {g->hiddenFormVars}
      <input type="hidden" name="{g->formVar var="controller"}" value="{$SearchShowAll.controller}"/>
      <input type="hidden" name="{g->formVar var="form[formName]"}" value="SearchShowAll"/>
      <input type="hidden" name="{g->formVar var="form[moduleId]"}" value="{$form.moduleId}"/>
      <input type="hidden" name="{g->formVar var="form[page]"}" value="{$form.page}"/>

      <script type="text/javascript">
    	// <![CDATA[
    	function setCheck(val) {ldelim}
    	  var frm = document.forms[0];
    	  {foreach from=$SearchShowAll.moduleInfo.options key=optionId item=optionInfo}
    	    frm.elements['g2_form[options][{$form.moduleId}][{$optionId}]'].checked=val;
    	  {/foreach}
    	{rdelim}

    	function invertCheck() {ldelim}
    	  var frm = document.forms[0];
    	  {foreach from=$SearchShowAll.moduleInfo.options key=optionId item=optionInfo}
    	    frm.elements['g2_form[options][{$form.moduleId}][{$optionId}]'].checked=!(frm.elements['g2_form[options][{$form.moduleId}][{$optionId}]'].checked)
    	  {/foreach}
    	{rdelim}
    	// ]]>
      </script>

	  <div id="gsSearchContents">

	 	<div class="gbTopFlag">
		  <div class="gbTitleBanner">
	        <h1 class="gbTitle">
	        {g->text text="%s Search Results for " arg1=$SearchShowAll.moduleInfo.name}
	        '{$form.searchCriteria}'
	        </h1>
	      </div>
	    </div>

    	<div class="gbAdmin">

          <div class="gbDataEntry">
            <input type="text" size="50" name="{g->formVar var="form[searchCriteria]"}" value="{$form.searchCriteria}" onfocus="this.style.background='#fff';" onblur="this.style.background='#eee';"/>
            <input type="hidden" name="{g->formVar var="form[lastSearchCriteria]"}" value="{$form.searchCriteria}"/>

    	    {if isset($form.error.searchCriteria.missing)}
    	    <h4 class="giError">
    	      {g->text text="You must enter some text to search for!"}
    	    </h4>
    	    {/if}
    	    <input type="submit" name="{g->formVar var="form[action][search]"}" value="{g->text text="Search"}"/>
          </div>

          {foreach from=$SearchShowAll.moduleInfo.options key=optionId item=optionInfo}
            {capture name=checkboxName}{g->formVar var="form[options][`$SearchShowAll.moduleId`][$optionId]"}{/capture}
            <input id="{$optionId}" type="checkbox" name="{$smarty.capture.checkboxName}" {if isset($form.options[$SearchShowAll.moduleId].$optionId)}checked="checked"{/if} />
            <label for="{$optionId}">
            {$optionInfo.description}
            </label>
          {/foreach}

          <ul class="giSearchCheck">
            <li><a href="javascript:setCheck(1)">{g->text text="Check All"}</a></li>
            <li><a href="javascript:setCheck(0)">{g->text text="Uncheck All"}</a></li>
            <li><a href="javascript:invertCheck(0)">{g->text text="Invert"}</a></li>
          </ul>

    	</div>

        {if !empty($SearchShowAll.results)}

        <div class="giTitle">
          <p>
          <input type="submit" name="{g->formVar var="form[action][scan]"}" value="{g->text text="Search all modules"}"/>
          </p>
          <p>
          {$SearchShowAll.moduleInfo.name}
            {if ($SearchShowAll.results.count > 0)}
        	  {g->text text="Results %d - %d of %d, Page %d of %d"
        	  arg1=$SearchShowAll.results.start
        	  arg2=$SearchShowAll.results.end
        	  arg3=$SearchShowAll.results.count
        	  arg4=$form.page
        	  arg5=$SearchShowAll.maxPages}
        	{/if}
            {if ($form.page > 1)}
          <input type="submit" name="{g->formVar var="form[action][previousPage]"}" value="{g->text text="&laquo; Back"}"/>
            {/if}
            {if ($form.page < $SearchShowAll.maxPages)}
          <input type="submit" name="{g->formVar var="form[action][nextPage]"}" value="{g->text text="Next &raquo;"}"/>
            {/if}
          </p>
        </div>

    	  {if (sizeof($SearchShowAll.results.results) > 0)}
    	  {assign var="childrenInColumnCount" value=0}
    	  <table id="gbThumbMatrix">
    	    <tr>
    	      {foreach from=$SearchShowAll.results.results item=result}
    	      {* Move to a new row *}
    	      {if ($childrenInColumnCount == 4)}
    	    </tr>
    	    <tr>
    	      {assign var="childrenInColumnCount" value=0}
    	      {/if}

    	      {assign var=childrenInColumnCount value="`$childrenInColumnCount+1`"}
    	      {assign var=itemId value=$result.itemId}
    	      <td class="{if $SearchShowAll.items.$itemId.canContainChildren}gbItemAlbum{else}gbItemImage{/if}" style="width: 10%">
    		    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=$itemId"}">
    		    {if isset($SearchShowAll.thumbnails.$itemId)}
    		    {g->image item=$SearchShowAll.items.$itemId image=$SearchShowAll.thumbnails.$itemId}
    		    {else}
    		    {g->text text="No thumbnail"}
    		    {/if}
    		    </a>
        		<ul class="giInfo">
        		  {foreach from=$result.fields item=field}
        		  <li>
        		    {$field.key}
        		    {$field.value|default:"&nbsp;"|ireplace:$form.searchCriteria:"<span class=\"giSearchHighlight\">\\1</span>"|markup}
        		  </li>
        		  {/foreach}
        		</ul>
    	      </td>
    	      {/foreach}

    	      {* flush the rest of the row with empty cells *}
    	      {section name="flush" start=$childrenInColumnCount loop=4}
    	      <td>&nbsp;</td>
    	      {/section}
    	    </tr>
    	  </table>
    	  {else}
            <div id="gsStatus">
              <div class="giEmpty">
                  <p>
                  {g->text text="No results found for"} '{$form.searchCriteria}'
                  </p>
              </div>
            </div>
    	  {/if}
      {/if}

      </div>
    </form>
  </div>
</div>