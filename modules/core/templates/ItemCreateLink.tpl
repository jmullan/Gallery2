{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemCreateLink.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Link an Item"}
      </div>
    </div>
    
  </div>

  {if (isset($status))}
  <div id="gsStatus">
    <div class="giStatus">
      {g->text one="Successfully linked %d item"
               many="Successfully linked %d items" 
               count=$status.linked.count
               arg1=$status.linked.count}
    </div>
  </div>
  {/if}

  {if !empty($ItemCreateLink.peers)}
  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Source"}
    </div>
      
    <div class="giDescription">
      {g->text text="Choose the items you want to link"}
      {if ($ItemCreateLink.numPages > 1) }
      {g->text text="(page %d of %d)"
	       arg1=$ItemCreateLink.page
	       arg2=$ItemCreateLink.numPages}
      {/if}
    </div>
    
    <table>
      {foreach from=$ItemCreateLink.peers item=peer}
      {assign var="peerItemId" value=$peer.id}
      <tr>
        <td width="60">
          {if isset($peer.thumbnail)}
          <div class="giThumbImage">
	    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$peer.id`"}">
	      {g->image item=$peer image=$peer.thumbnail maxSize=50}
	    </a>
          </div>		    
          {else}
          &nbsp;
          {/if} 
        </td>
        <td> 
          <input type="checkbox" name="{g->formVar var="form[selectedIds][$peerItemId]"}"
          {if $peer.selected}checked="checked"{/if}
          />
        </td> 
        <td> 
          {$peer.title|default:$peer.pathComponent}
        </td>
      </tr>
    {/foreach}
    </table>

    {if ($ItemCreateLink.page > 1)}
    <input type="submit" name="{g->formVar var="form[action][previous]"}" value="{g->text text="Previous Page"}"/>
    {/if}
    {if ($ItemCreateLink.page < $ItemCreateLink.numPages)}
    <input type="submit" name="{g->formVar var="form[action][next]"}" value="{g->text text="Next Page"}"/>
    {/if}
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Destination"}
    </div>
      
    <div class="giDescription">
      {g->text text="Choose a new album for the link"}
    </div>
      
    <select name="{g->formVar var="form[destination]"}">
      {foreach from=$ItemCreateLink.albumTree item=album}
      <option value="{$album.data.id}">
	{"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}`--
	{$album.data.title|default:$album.data.pathComponent}
      </option>
      {/foreach}
    </select>

    {if !empty($form.error.destination.empty)}
    <div class="giError">
      {g->text text="No destination chosen"}
    </div>
    {/if}
  </div>
    
  <div class="gbButtons">
    <input type="hidden" name="{g->formVar var="page"}" value="{$ItemCreateLink.page}"/>
    <input type="hidden" name="{g->formVar var="form[numPerPage]"}" value="{$ItemCreateLink.numPerPage}"/>
    {foreach from=$ItemCreateLink.selectedIds item=selectedId}
    <input type="hidden" name="{g->formVar var="form[selectedIds][$selectedId]"}" value="on"/>
    {/foreach}
    <input type="submit" name="{g->formVar var="form[action][link]"}" value="{g->text text="Link"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
  {else}
  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="This album contains no items to link."}
    </div>
  </div>
  {/if}
</div>
