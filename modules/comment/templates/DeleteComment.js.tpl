{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}
<script type="text/javascript">
//<![CDATA[
var deleteUrlPattern = '{g->url arg1="view=comment.CommentCallback" arg2="command=delete" arg3="commentId=__COMMENT_ID__" useAuthToken=true htmlEntities=false}';
var deleteCommentTitle = '{g->text text="Delete this comment?" forJavascript=true}';
var deleteCommentBody = '{g->text text="Are you sure?" forJavascript=true}';
var deleteCommentYes = '{g->text text="Delete" forJavascript=true}';
var deleteCommentNo = '{g->text text="Cancel" forJavascript=true}';

{literal}
function deleteComment(id) {
  YAHOO.util.Connect.asyncRequest('GET', deleteUrlPattern.replace('__COMMENT_ID__', id));
  var anim = new YAHOO.util.Anim(
    'comment-' + id, { opacity: { to: 0.0 }, height: { to: '0' } }, 1,
    YAHOO.util.Easing.bounceOut);
  anim.onComplete.subscribe(function() {
    var el = this.getEl();
    el.parentNode.removeChild(el);
  });
  anim.animate();
}

function confirmDeleteComment(id) {
    var dialog = new YAHOO.widget.SimpleDialog(
	"gDialog", { width: "20em",
            effect: { effect: YAHOO.widget.ContainerEffect.FADE, duration: 0.25 },
	    fixedcenter: true,
	    modal: true,
	    draggable: false
         });
    dialog.setHeader(deleteCommentTitle);
    dialog.setBody(deleteCommentBody);
    dialog.cfg.setProperty("icon", YAHOO.widget.SimpleDialog.ICON_WARN);

    var handleYes = function() {
	this.hide();
	deleteComment(id);
    }

    var handleNo = function() {
	this.hide();
    }

    var myButtons = [
        { text: deleteCommentYes, handler: handleYes },
        { text: deleteCommentNo, handler: handleNo, isDefault: true }
    ];
    dialog.cfg.queueProperty("buttons", myButtons);
    dialog.render(document.body);
}
//]]>
</script>
{/literal}
