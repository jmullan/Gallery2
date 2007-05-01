{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}
  var prompt = {ldelim}
    "header" : '{g->text text="Warning!" forJavascript=true}',
    "body"   : '{g->text text="Do you really want to delete " forJavascript=true}',
    "wait"   : '{g->text text="Deleting... Please wait" forJavascript=true}',
    "yes"    : '{g->text text="Yes" forJavascript=true}',
    "no"     : '{g->text text="No" forJavascript=true}',
    "OK"     : '{g->text text="OK" forJavascript=true}',
    "more"   : '{g->text text="Delete more items..." forJavascript=true}',
    "errorPageUrl" : '{g->url arg1="view=core.ErrorPage"}'
  {rdelim};

{literal}
function core_confirmDelete(url, moreUrl, title) {
  var pageItemId = this.pageItemId;
  var dialog = new YAHOO.widget.SimpleDialog("gDialog", { width: "20em",
    effect: { effect:YAHOO.widget.ContainerEffect.FADE, duration:0.25 },
    fixedcenter: true,
    modal: true,
    draggable: false });
    
  dialog.setHeader(prompt['header']);
  var bodyText = prompt['body'] + title + '?';
  if (moreUrl != '') {
    bodyText += '<br /><br /><a href="' + moreUrl + '">' 
      + prompt['more'] + '</a>';
  }
  dialog.setBody(bodyText);
  dialog.cfg.setProperty("icon", YAHOO.widget.SimpleDialog.ICON_WARN);
  
  var handleYes = function() {
    var handleSuccess = function(response) {
      eval("var result = " + response.responseText);
      if (result['status'] == 'error') {
        document.location.href = prompt['errorPageUrl'];
      } else {
        document.location.href = result['redirect'];
      }
    }

    var handleFailure = function(response) {
      waitDialog.hide();

      var dismiss = function() {
        errorDialog.hide();
      }
      
      /* Instantiate error dialog. The contents comes from the server */
      errorDialog = new YAHOO.widget.SimpleDialog("errorDialog", 
         { fixedcenter: true,
           visible: false,
           draggable: false,
           text: response.responseText,
           zIndex: 100,
           icon: YAHOO.widget.SimpleDialog.ICON_ALARM,
           constraintoviewport: true,
           buttons: [ { text:prompt["OK"], handler:dismiss, isDefault:true }]
         } );
      errorDialog.render(document.body);
      errorDialog.show();
    }
  
    var callback = {
      success: handleSuccess,
      failure: handleFailure,
      scope: this
    }
  
    this.hide();
    waitDialog = new YAHOO.widget.Panel("waitDialog", {
      width:"240px", 
      fixedcenter:true, 
      close:false, 
      draggable:false, 
      modal:true, 
      visible:false, 
      effect:{effect:YAHOO.widget.ContainerEffect.FADE, duration:0.25}});
    waitDialog.setHeader(prompt['wait']);
    waitDialog.setBody("<img src='images/rel_interstitial_loading.gif'/>");
    waitDialog.render(document.body);
    waitDialog.show();
    YAHOO.util.Connect.asyncRequest('GET', url, callback);
  }
    
  var handleNo = function() {
    this.hide();
  }
    
  var myButtons = [ { text: prompt['yes'], handler:handleYes },
        { text: prompt['no'], handler:handleNo, isDefault:true } ];
  dialog.cfg.queueProperty("buttons", myButtons);
  dialog.render(document.body);
}
{/literal}

