{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}

<ul class="gbBreadCrumb">
  <li class="giBreadCrumbFirst">
    <a href="{g->url}">{g->text text="Gallery"}</a>
  </li>
  <li>
    {g->text text="Search Results Summary"}
  </li>
</ul>

<div id="gsContents">
  {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}

  <div id="gsAlbumContents">
    <form action="{g->url}" method="post">
      {g->hiddenFormVars}
      <input type="hidden" name="{g->formVar var="controller"}" value="{$SearchScan.controller}" />
      <input type="hidden" name="{g->formVar var="form[formName]"}" value="SearchScan" />

      <script type="text/javascript">
        // <![CDATA[
        function setCheck(val) {ldelim}
    	  var frm = document.forms[0];
    	  {foreach from=$SearchScan.modules key=moduleId item=moduleInfo}
    	    {foreach from=$moduleInfo.options key=optionId item=optionInfo}
    	  frm.elements['g2_form[options][{$moduleId}][{$optionId}]'].checked=val;
    	    {/foreach}
    	  {/foreach}
        {rdelim}

        function invertCheck() {ldelim}
    	  var frm = document.forms[0];
    	{foreach from=$SearchScan.modules key=moduleId item=moduleInfo}
    	{foreach from=$moduleInfo.options key=optionId item=optionInfo}
    	  frm.elements['g2_form[options][{$moduleId}][{$optionId}]'].checked=!(frm.elements['g2_form[options][{$moduleId}][{$optionId}]'].checked)
    	{/foreach}
    	{/foreach}
          {rdelim}
          // ]]>
      </script>

      <div id="gsSearchContents">

	    <div class="gbTopFlag">
		   <div class="gbTitleBanner">
	          <h1 class="gbTitle">
	          {g->text text="Search the Gallery"}
	          </h1>
	       </div>
	    </div>

    	<div class="gbAdmin">

    	  <div class="gbDataEntry">
    	    <input type="text" size="50" name="{g->formVar var="form[searchCriteria]"}" value="{$form.searchCriteria}" onfocus="this.style.background='#fff';" onblur="this.style.background='#eee';"/>
    	    <input type="submit" name="{g->formVar var="form[action][search]"}" value="{g->text text="Search"}"/>

    	    {if isset($form.error.searchCriteria.missing)}
    	    <p class="giError">
    	      {g->text text="You must enter some text to search for!"}
    	    </p>
    	    {/if}
    	  </div>

          {foreach from=$SearchScan.modules key=moduleId item=moduleInfo}
        	{foreach from=$moduleInfo.options key=optionId item=optionInfo}
        	{capture name=checkboxName}{g->formVar var="form[options][$moduleId][$optionId]"}{/capture}
        	<input id="{$moduleId}.{$optionId}" type="checkbox" name="{$smarty.capture.checkboxName}" {if isset($form.options.$moduleId.$optionId)}checked="checked"{/if} />
        	<label for="{$moduleId}.{$optionId}">
        	{$optionInfo.description}
        	</label>
        	{/foreach}
          {/foreach}

          <ul class="giSearchCheck">
            <li><a href="javascript:setCheck(1)">{g->text text="Check All"}</a> </li>
            <li><a href="javascript:setCheck(0)">{g->text text="Uncheck All"}</a> </li>
            <li><a href="javascript:invertCheck(0)">{g->text text="Invert"}</a></li>
          </ul>

        </div>

          {assign var="resultCount" value="0"}
          {if !empty($SearchScan.searchResults)}

    	  {foreach from=$SearchScan.searchResults key=moduleId item=results}
    	  {assign var="resultCount" value=$resultCount+$results.count}

    	  <div class="giTitle">
    	    <p>
    	    {$SearchScan.modules.$moduleId.name}
    	    {if ($results.count > 0)}
    	    {g->text text="Results %d - %d"
    	    arg1=$results.start
    	    arg2=$results.end}
    	    {/if}

    	    {if ($results.count > $results.end)}
    	    {assign var="moduleId" value=$moduleId} &nbsp;
    	    <input type="submit" name="{g->formVar var="form[action][showAll][$moduleId]"}" value="{g->text text="Show all %d" arg1=$results.count}"/>
    	    {/if}
    	    </p>
    	  </div>

	    {assign var="searchCriteria" value=$form.searchCriteria}
	    {if (sizeof($results.results) > 0)}
	    <table id="gbThumbMatrix">
	      <tr>
    	      {foreach from=$results.results item=result}
    	      {assign var=itemId value=$result.itemId}
    	      <td class="{if $SearchScan.items.$itemId.canContainChildren}gbItemAlbum{else}gbItemImage{/if}" style="width: 10%">
        		<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=$itemId"}">
        		{if isset($SearchScan.thumbnails.$itemId)}
        		<div class="gbItemImage">
        		    {g->image item=$SearchScan.items.$itemId image=$SearchScan.thumbnails.$itemId}
        		</div>
        		{else}
        		{g->text text="No thumbnail"}
        		{/if}
        		</a>
    		    <ul class="giInfo">
    		      {foreach from=$result.fields item=field}
    		        {if isset($field.value)}
    		      <li>
    		        {$field.key}:
    		        {$field.value|default:"&nbsp;"|ireplace:$searchCriteria:"<span class=\"giSearchHighlight\">\\1</span>"|markup}
    		      </li>
    		        {/if}
    		      {/foreach}
    		    </ul>
	          </td>
	      {/foreach}
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
	  {/foreach}
	{/if}

        <div class="gbBottomFlag">
          <div class="gbButtons">
            {if $resultCount>0 && $SearchScan.slideshowAvailable}
            <input type="submit" name="{g->formVar var="form[action][slideshow]"}" value="{g->text text="View these results in a slideshow"}"/>
            {/if}
          </div>
        </div>
      </div>
    </form>
  </div>
</div>