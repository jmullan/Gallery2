{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to Admin.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Zip Download Settings"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Settings saved successfully"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="Enter full path to the zip executable."}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Zip Path"}
      </h3>
      <input type="text" name="{g->formVar var="form[path]"}" value="{$form.path}"/>
    </div>

    {if isset($form.error.path.missing)}
    <div class="giError">
      {g->text text="You must enter a path to your zip binary"}
    </div>
    {/if}
    {if isset($form.error.path.badPath)}
    <div class="giError">
      {g->text text="The path you entered isn't valid"}
    </div>
    {/if}
    {if isset($form.test) && $form.test}
    <div class="giSuccess">
      {g->text text="The path you entered is valid"}
    </div>
    {/if}
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Test Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>
