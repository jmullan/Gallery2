{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}
<script type="text/javascript">
//<![CDATA[
var changeUrlPattern = '{g->url arg1="view=comment.CommentCallback" arg2="command=__COMMAND__" arg3="commentId=__COMMENT_ID__" useAuthToken=true htmlEntities=false}';
var prompts = {ldelim}
    'delete' : {ldelim}
	title : '{g->text text="Delete this comment?" forJavascript=true}',
	body : '{g->text text="Are you sure you want to delete this comment?" forJavascript=true}',
    {rdelim},

    'deleteAllSpam' : {ldelim}
	title : '{g->text text="Delete all spam comments?" forJavascript=true}',
	body : '{g->text text="Are you sure you want to delete all comments marked as spam?" forJavascript=true}',
    {rdelim},

    'despam' : {ldelim}
	title : '{g->text text="Mark this comment as not spam?" forJavascript=true}',
	body : '{g->text text="Are you sure you want to mark this comment as not spam?" forJavascript=true}',
    {rdelim},

    'spam' : {ldelim}
	title : '{g->text text="Mark this comment as spam?" forJavascript=true}',
	body : '{g->text text="Are you sure you want to mark this comment as spam?" forJavascript=true}',
    {rdelim},

    'yes' : '{g->text text="Yes" forJavascript=true}',
    'no' : '{g->text text="Cancel" forJavascript=true}',
{rdelim};
var errorPageUrl = '{g->url arg1="view=core.ErrorPage" htmlEntities=false}';

{literal}
function handleSuccess(response) {
  eval("var result = " + response.responseText);
  if (result['status'] == 'error') {
      document.location.href = errorPageUrl;
  }
}

var handleFailure = function(response) {
}

function changeComment(id, command) {
  YAHOO.util.Connect.asyncRequest(
    'GET', changeUrlPattern.replace('__COMMENT_ID__', id).replace('__COMMAND__', command),
    { success: handleSuccess, failure: handleFailure, scope: this });
  var anim = new YAHOO.util.Anim(
    'comment-' + id, { opacity: { to: 0.0 }, height: { to: '0' } }, 1,
    YAHOO.util.Easing.bounceOut);
  anim.onComplete.subscribe(function() {
    var el = this.getEl();
    el.parentNode.removeChild(el);
  });
  anim.animate();
}

function confirmChangeComment(id, command) {
    var dialog = new YAHOO.widget.SimpleDialog(
	"gDialog", { width: "20em",
            effect: { effect: YAHOO.widget.ContainerEffect.FADE, duration: 0.25 },
	    fixedcenter: true,
	    modal: true,
	    draggable: false
         });
    dialog.setHeader(prompts[command]['title']);
    dialog.setBody(prompts[command]['body']);
    dialog.cfg.setProperty("icon", YAHOO.widget.SimpleDialog.ICON_WARN);

    var handleYes = function() {
	this.hide();
	changeComment(id, command);
    }

    var handleNo = function() {
	this.hide();
    }

    var myButtons = [
        { text: prompts['yes'], handler: handleYes },
        { text: prompts['no'], handler: handleNo, isDefault: true }
    ];
    dialog.cfg.queueProperty("buttons", myButtons);
    dialog.render(document.body);
}
//]]>
</script>
{/literal}
