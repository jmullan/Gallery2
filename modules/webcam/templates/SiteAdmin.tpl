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
	{g->text text="WebCam Settings"}
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
      {g->text text="Reset webcam items to enable deactivation"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Enter length of time a webcam item should keep one image before refreshing from the source url."}
    </p>
    <ul class="gbAdminList">
      <li>
	<label for="duration">
	  {g->text text="Duration in minutes:"}
	</label>
	<input id="duration" type="text" size="5" name="{g->formVar var="form[duration]"}"
						  value="{$form.duration}"/>
	{if isset($form.error.duration)}
	<div class="giError">
	  {g->text text="Invalid duration value"}
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
      {g->text one="This gallery contains %d webcam item.  It must be reset to a standard photo, locking in the current image, before this module can be deactivated.  You can reset the item here."
	       many="This gallery contains %d webcam items.  These must be reset to standard photos, locking in the current images, before this module can be deactivated.  You can reset all items here."
	       count=$form.count arg1=$form.count}
      {g->text text="Warning: there is no undo."}
    </div>

    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset all items"}"/>
  </div>
  {/if}
</div>
