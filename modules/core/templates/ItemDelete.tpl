{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemDelete.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Delete Item"}
      </div>
    </div>
    
  </div>

  {if (isset($status))}
  <div id="gsStatus">
    <div class="giStatus">
      {if ($status.deleted.count == 0)}
      {g->text text="No items were selected for deletion"}
      {else}
      {g->text one="Successfully deleted %d item"
               many="Successfully deleted %d items" 
               count=$status.deleted.count
               arg1=$status.deleted.count}
      {/if}
    </div>
  </div>
  {/if}
  
  {if !empty($ItemDelete.peers)}
  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Delete"}
    </div>
    
    <div class="giDescription">
      {g->text text="Choose the items you want to delete"}
      {if ($ItemDelete.numPages > 1) }
      {g->text text="(page %d of %d)"
	       arg1=$ItemDelete.page
	       arg2=$ItemDelete.numPages}
      {/if}
    </div>

    <input type="hidden" name="{g->formVar var="page"}" value="{$ItemDelete.page}"/>
    <input type="hidden" name="{g->formVar var="form[formname]"}" value="DeleteItem"/>

    <script type="text/javascript">
      function setCheck(val) {ldelim}
        var frm = document.forms[0];
        {foreach from=$ItemDelete.peers item=peer}
          {assign var="peerItemId" value=$peer.id}
          frm.elements['g2_form[selectedIds][{$peerItemId}]'].checked = val;
        {/foreach}
      {rdelim}
      function invertCheck(val) {ldelim}
        var frm = document.forms[0];
        {foreach from=$ItemDelete.peers item=peer}
          {assign var="peerItemId" value=$peer.id}
          frm.elements['g2_form[selectedIds][{$peerItemId}]'].checked = !frm.elements['g2_form[selectedIds][{$peerItemId}]'].checked;
        {/foreach}
      {rdelim}
    </script>
 
    <table>
      {foreach from=$ItemDelete.peers item=peer}
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
          <input type="checkbox" name="{g->formVar var="form[selectedIds][`$peer.id`]"}" {if $peer.selected}checked="checked"{/if} />
	</td>
	<td>
          {$peer.title|default:$peer.pathComponent}

          <i>
            {if isset($ItemDelete.peerTypes.data.$peerItemId)}
            {g->text text="(data)"}
            {/if}
            {if isset($ItemDelete.peerTypes.album.$peerItemId)}
            {if isset($ItemDelete.peerDescendentCounts.$peerItemId)}
            {g->text one="(album containing %d item)" 
      	       many="(album containing %d items)"
                     count=$ItemDelete.peerDescendentCounts.$peerItemId
                     arg1=$ItemDelete.peerDescendentCounts.$peerItemId}
            {else}
            {g->text text="(empty album)"}
            {/if}
            {/if}
          </i>
	</td>
      </tr>
      {/foreach}
    </table>

    {foreach from=$ItemDelete.selectedIds item=selectedId}
    <input type="hidden" name="{g->formVar var="form[selectedIds][$selectedId]"}" value="on"/>
    {/foreach}
    <input type="hidden" name="{g->formVar var="form[numPerPage]"}" value="{$ItemDelete.numPerPage}"/>

    <br/>

    <input type="button" name="{g->formVar var="form[action][checkall]"}" onclick="javascript:setCheck(1)" value="{g->text text="Check All"}" class="button"/>
    <input type="button" name="{g->formVar var="form[action][checknone]"}" onclick="javascript:setCheck(0)" value="{g->text text="Check None"}" class="button"/>
    <input type="button" name="{g->formVar var="form[action][invert]"}" onclick="javascript:invertCheck()" value="{g->text text="Invert"}" class="button"/>
    {if ($ItemDelete.page > 1)}
    <input type="submit" name="{g->formVar var="form[action][previous]"}" value="{g->text text="Previous Page"}" class="button"/>
    {/if}
    {if ($ItemDelete.page < $ItemDelete.numPages)}
    <input type="submit" name="{g->formVar var="form[action][next]"}" value="{g->text text="Next Page"}" class="button"/>
    {/if}

  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][delete]"}" value="{g->text text="Delete"}" class="button"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}" class="button"/>
  </div>
  {else}
  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="This album contains no items to delete"}
    </div>
  </div>
  {/if}
</div>
