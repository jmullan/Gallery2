{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{* Set defaults *}
{if empty($item)} {assign var=item value=$theme.item} {/if}
{g->callback type="comment.AddComment" itemId=$item.id}

{if !empty($block.comment.AddComment)}
<div id="AddComment_block" style="display: none" class="{$class}">
  {include file="gallery:modules/comment/templates/AddComment.tpl"
           AddComment=$block.comment.AddComment}
</div>

<div id="AddComment_trigger" class="{$class}" onclick="AddComment_showBlock()">
  <div class="gbBlock gcBackground1">
    <h2> {g->text text="Add Comment"} </h2>
  </div>
  <textarea cols=80 rows=5></textarea>
</div>

{literal}
<script>
  function AddComment_hideTrigger() {
    var anim1 = new YAHOO.util.Anim(
      'AddComment_trigger',
      { height: { to: 0 } },
      0, YAHOO.util.Easing.easeIn);
    anim1.animate();

    var anim2 = new YAHOO.util.Anim(
      'AddComment_block',
      { height: { to: 100, units: '%' } },
      1, YAHOO.util.Easing.easeIn);
    anim2.animate();
  }

  function AddComment_showBlock() {
    document.getElementById('AddComment_block').style.display='block';
    document.getElementById('AddComment_trigger').style.display='none';
  }
</script>
{/literal}
{/if}
