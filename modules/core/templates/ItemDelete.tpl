{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Delete Item"}
    {/g->title}
  {/g->banner}
  
  {if (isset($status))}
    {g->success}
      {if ($status.deleted.count == 0)}
        {g->text text="No items were selected for deletion"}
      {else}
        {g->text one="Successfully deleted %d item"
      	many="Successfully deleted %d items" 
        count=$status.deleted.count
        arg1=$status.deleted.count}
      {/if}
    {/g->success}
  {/if}
  
  {if !empty($ItemDelete.peers)}
    {g->box style="admin"}	
      {g->title}
        {g->text text="Delete"}
      {/g->title}
      
      {g->description}
	{g->text text="Choose the items you want to delete"}
      {/g->description}
      {g->input type="hidden" name="form[formname]"}DeleteItem{/g->input}
      {g->element}
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
      {/g->element}
      {foreach from=$ItemDelete.peers item=peer}
	{assign var="peerItemId" value=$peer.id}
	{g->element}
  	  {g->input type="checkbox" name="form[selectedIds][$peerItemId]"}{$peer.selected}{/g->input}
  	  {$peer.title|default:$peer.pathComponent}
  	  {if isset($ItemDelete.peerTypes.data.$peerItemId)}
  	    {g->text text="(data)"}
  	  {/if}
  	  {if isset($ItemDelete.peerTypes.album.$peerItemId)}
  	    {g->text text="(album)"}
  	  {/if}
	{/g->element}
	
      {/foreach}
    {/g->box}

    {g->box style="admin"}
      {g->element}
	{g->input type="submit" name="form[action][delete]"}{g->text text="Delete"}{/g->input}
	{g->input type="submit" name="form[action][cancel]"}{g->text text="Cancel"}{/g->input}
        {g->input type="button" name="form[action][checkall]" onclick="javascript:setCheck(1)"}
          {g->text text="Check All"}
        {/g->input}
        {g->input type="button" name="form[action][checknone]" onclick="javascript:setCheck(0)"}
          {g->text text="Check None"}{/g->input}
        {g->input type="button" name="form[action][invert]" onclick="javascript:invertCheck()"}
          {g->text text="Invert"}
        {/g->input}
      {/g->element}
    {/g->box}
  {else}
    {g->box style="admin"}
      {g->description}
	{g->text text="This album contains no items to delete"}
      {/g->description}
    {/g->box}
  {/if}
{/g->pagebox}
