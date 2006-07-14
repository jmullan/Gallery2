{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Link Item Settings"} </h2>
</div>

{if isset($status.saved)}
<div class="gbBlock"><h2 class="giSuccess">
  {g->text text="Settings saved successfully"}
</h2></div>
{/if}

<div class="gbBlock">
  <table class="gbDataTable">
    <tr><td>
      <label for="arrowWatermark">
	{g->text text="Add small arrow watermark on thumbnails"}
      </label>
    </td><td>
      <input type="checkbox" id="arrowWatermark"{if $form.arrowWatermark} checked="checked"{/if}
       name="{g->formVar var="form[arrowWatermark]"}"/>
    </td></tr><tr><td>
      <label for="urlSnapshot">
	{g->text text="Generate webpage snapshot for thumbnails of URL links"}
      </label>
    </td><td>
      <input type="checkbox" id="urlSnapshot"{if $form.urlSnapshot} checked="checked"{/if}
       name="{g->formVar var="form[urlSnapshot]"}"/>
    </td></tr><tr><td>
      <label for="snapshotExec">
	{g->text text="Command to capture webpage snapshot"}
      </label>
    </td><td>
      <input type="text" id="snapshotExec" size="58"
       name="{g->formVar var="form[snapshotExec]"}" value="{$form.snapshotExec}"/>
      <p class="giDescription">
	{g->text text="Use %URL% %WIDTH% %HEIGHT% %OUTFILE% tokens"}
      </p>
    </td></tr>
  </table>
  <p class="giDescription">
    {capture assign=maintenanceLink}<a href="{g->url arg1="view=core.SiteAdmin"
     arg2="subView=core.AdminMaintenance"}">{/capture}
    {g->text text="Webpage snapshots can be captured with %skhtml2png%s. This program is not trivial to setup, requiring ImageMagick and a running X server, with appropriate access permission for your webserver/PHP user. Install and test outside of Gallery to ensure the command entered above works as expected. Test with the webserver/PHP user to verify Gallery won't have permission problems. If Gallery produces broken thumbnails then try the Build Thumbnails %sMaintenance task%s to see debug output."
     arg1="<a href=\"http://khtml2png.sourceforge.net/\">" arg2="</a>"
     arg3=$maintenanceLink arg4="</a>"}
    <br/>
    {g->text text="If you don't use webpage snapshots then URL links are given a default thumbnail. Use the Thumbnail Manager module to upload a custom thumbnail for these items."}
  </p>
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
</div>
