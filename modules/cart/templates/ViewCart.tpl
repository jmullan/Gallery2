{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ViewCart.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsHeader">
    {include file="gallery:layouts/matrix/templates/banner.tpl"}    
</div>

<ul class="gbBreadCrumb">
  <li class="giBreadCrumbFirst">
    <a href="{g->url}">{$ViewCart.rootAlbum.title}</a>
  </li>

  <li>
    {g->text text="View Cart"}
  </li>
</ul>

<div id="gsContents">
  {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}	    
  
  <div id="gsOtherContents">

    <form action="{g->url}" method="post">
      
    <div class="gbTopFlag">
      <div class="gbTitleBanner">
        <h1 class="gbTitle">
    	  {g->text text="Items Currently in Your Cart"}
        </h1>
      </div>
    </div>
    
    <div class="gbNavBar">
      <div class="gbAdmin">
    	<select name="{g->formVar var="form[pluginId]"}" class="giActionSelect" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';">
    	  <option label="{g->text text="&laquo; cart actions &raquo;"}" value="" selected>{g->text text="&laquo; cart actions &raquo;"}</option>
    	  <option label="{g->text text="Update Quantities"}" value="updateCart"> {g->text text="Update Quantities"} </option>
    	  <option label="{g->text text="Empty Cart"}" value="emptyCart"> {g->text text="Empty Cart"} </option>
    	  {foreach from=$ViewCart.plugins key=pluginId item=pluginData}
    	  <option label="{$pluginData.actionDisplayName}" value="{$pluginId}"> {$pluginData.actionDisplayName} </option>
    	  {/foreach}
    	</select>
    	<input type="submit" name="{g->formVar var="form[action][modify]"}" value="{g->text text="Go"}" class="button"/>
      </div>
    </div>

  
    {if isset($status)}
    <div id="gsStatus">
      {if isset($status.cartModified)}
      <div class="giStatus">
	{g->text text="Cart updated successfully"}
      </div>
      {/if}
    </div>
    {/if}

    {if empty($ViewCart.items)}
    <div id="gsStatus">
      <div class="giEmpty">
          <p>
          {g->text text="Your cart is empty."}
          </p>
          <p>
          {g->text text="To add items, browse the gallery and select 'Add to cart' from the item's action menu."}
          </p>
      </div>
    </div>
    {else}
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
    	      <input type="text" size="3" name="{g->formVar var="form[counts][`$item.id`]"}" value="{$form.counts[$item.id]}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
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
      </div>

    </form>
    
    {/if}
    <div class="gbBottomFlag">
      <div class="gbNavBar">
        <div class="gbAdmin">
        &nbsp;
        </div>
      </div>
    </div>
    
  </div>
</div>
