{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ViewCart.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsHeader">
  <!-- Header -->
</div>

<ul class="gbBreadCrumb">
  <li>
    <a href="{g->url}">
      {g->text text="Gallery"}
    </a>
  </li>

  <li>
    {g->text text="View Cart"}
  </li>
</ul>

<div class="gsContents">
  {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}	    

  <div class="gsOtherContents">
    {if isset($status)}
    <div id="gsStatus">
      {if isset($status.cartModified)}
      <div class="giStatus">
	{g->text text="Cart updated successfully"}
      </div>
      {/if}
    </div>
    {/if}

    <form action="{g->url}" method="post">

      {g->hiddenFormVars}
      <input type="hidden" name="{g->formVar var="controller"}" value="{$ViewCart.controller}"/>
      <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}"/>

      <div class="gbAdmin">
    	<table class="gbDataTable">
    	  <tr>
    	    <th>
    	      {g->text text="Quantity"}
    	    </th>
    
    	    <th colspan="2" align="center">
    	      {g->text text="Item"}
    	    </th>
    
    	    <th>
    	      {g->text text="Type"}
    	    </th>
    
    	    <th>
    	      {g->text text="Remove"}
    	    </th>
    	  </tr>
    
    	  {foreach from=$ViewCart.items item=item}
    	  <tr class="{cycle values="gbEven,gbOdd"}">
    	    <td>
    	      <input type="text" size="3" name="{g->formVar var="form[counts][`$item.id`]"}" value="{$form.counts[$item.id]}"/>
    	    </td>
    
    	    <td>
    	      <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$item.id`"}">
    		{if isset($ViewCart.thumbnails[$item.id])}
    		{g->image item=$ViewCart.items[$item.id] image=$ViewCart.thumbnails[$item.id] maxSize=90}
    		{else}
    		{g->text text="No thumbnail"}
    		{/if}
    	      </a>
    	    </td>
    
    	    <td>
        		<ul class="gbCartInfo">
        		  <li>
        		      <strong>{g->text text="Title:"}</strong> 
        		    {$item.title|markup}
        		  </li>
    
        		  <li>
        		      <strong>{g->text text="Summary:"}</strong> 
        		    {$item.summary|markup}
        		  </li>
        	    </ul>
    	    </td>
    
    	    <td>
    	      {$ViewCart.itemTypeNames[$item.id].0}
    	    </td>
    
    	    <td align="center">
    	      <input type="checkbox" name="{g->formVar var="form[delete][`$item.id`]"}"/>
    	    </td>
    	  </tr>
    	  {/foreach}
    	</table>

      <div class="gbAdmin">
	<select name="{g->formVar var="form[pluginId]"}" class="giActionSelect">
	  <option label="{g->text text="Update Quantities"}" value="updateCart"> {g->text text="Update Quantities"} </option>
	  <option label="{g->text text="Empty Cart"}" value="emptyCart"> {g->text text="Empty Cart"} </option>
	  {foreach from=$ViewCart.plugins key=pluginId item=pluginData}
	  <option label="{$pluginData.actionDisplayName}" value="{$pluginId}"> {$pluginData.actionDisplayName} </option>
	  {/foreach}
	</select>
	<input type="submit" name="{g->formVar var="form[action][modify]"}" value="{g->text text="Go"}" class="button"/>
      </div>
    </form>
  </div>
</div>
