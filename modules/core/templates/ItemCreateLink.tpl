<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Link an Item"}
      </div>
    </div>
    
    <div class="spacer">
      &nbsp;
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
    </div>

    {foreach from=$ItemCreateLink.peers item=peer}
    {assign var="peerItemId" value=$peer.id}
    <input type="checkbox" name="{g->formVar var="form[selectedIds][$peerItemId]"}"
    {if $peer.selected}checked="checked"{/if}
    />
    {$peer.title|default:$peer.pathComponent}
    <br />
    {/foreach}
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
    
  <div class="gbBottomFlag">
    <div class="giActionSelect">
      <input type="submit" name="{g->formVar var="form[action][link]"}" value="{g->text text="Link"}"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
    </div>
  </div>
  {else}
  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="This album contains no items to link."}
    </div>
  </div>
  {/if}
</div>
