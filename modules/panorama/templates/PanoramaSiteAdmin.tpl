{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Panorama Settings"}
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

    {if isset($status.reset)}
    <div class="giStatus">
      {g->text text="Items reset successfully"}
    </div>
    {/if}

    {if isset($status.deactivated)}
    <div class="giError">
      {g->text text="Reset panorama items to enable deactivation (see below)"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="The panorama viewer can be activated in two ways: the first allows album administrators to select individual images for panorama display (Panorama section in \"edit photo\"), overriding the normal display of the entire image.  The second method retains the normal image display but gives users an option in the \"item actions\" to view the image in the panorama viewer."}
    </p>
    <ul class="gbAdminList">
      <li>
        <input id="itemType" type="checkbox" name="{g->formVar var="form[itemType]"}" {if $form.itemType}checked="checked"{/if}/>
        <label for="itemType">
          {g->text text="Use applet to display wide images"}
        </label>
      </li>
      <li>
        <input id="itemLink" type="checkbox" name="{g->formVar var="form[itemLink]"}" {if $form.itemLink}checked="checked"{/if}/>
        <label for="itemLink">
          {g->text text="Add \"view panorama\" option in item actions for wide images"}
        </label>
      </li>
      <li>
        {g->text text="Width of panorama viewer: "}
        <input type="text" size="6" name="{g->formVar var="form[width]"}" value="{$form.width}" />

        {if isset($form.error.width)}
        <div class="giError">
          {g->text text="Invalid width value"}
        </div>
        {/if}
      </li>
    </ul>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
  </div>

  {if ($form.count > 0)}
  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="This gallery contains items activated for panorama view.  These must be reset to standard items before this module can be deactivated.  You can reset all items here.  Warning: there is no undo."}
    </div>

    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset all items"}"/>
  </div>
  {/if}
</div>
