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
	{g->text text="New Item Settings"}
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
      {g->text text="Album sorts reset successfully"}
    </div>
    {/if}

    {if isset($status.deactivated)}
    <div class="giError">
      {g->text text="Reset albums with New Items sort to enable deactivation (see below)"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Enter length of time in days items should be marked as new and updated, or zero to disable."}
    </p>
    <table class="gbDataTable">
      <tr><td>
	<label for="new">
	  {g->text text="New:"}
	</label>
      </td><td>
	<input id="new" type="text" size="5" name="{g->formVar var="form[days][new]"}"
					     value="{$form.days.new}"/>
	{if isset($form.error.new)}
	<div class="giError">
	  {g->text text="Invalid value"}
	</div>
	{/if}
      </td></tr>

      <tr><td>
	<label for="updated">
	  {g->text text="Updated:"}
	</label>
      </td><td>
	<input id="updated" type="text" size="5" name="{g->formVar var="form[days][updated]"}"
						 value="{$form.days.updated}"/>
	{if isset($form.error.updated)}
	<div class="giError">
	  {g->text text="Invalid value"}
	</div>
	{/if}
      </td></tr>
    </table>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
  </div>

  {if ($form.isDefault || $form.count > 0)}
  <div class="gbAdmin">
    <div class="giDescription">
      {if $form.isDefault}
      {g->text text="This gallery is using New Items sort as the default album sort.  This must be changed to another sort type before this module can be deactivated.  You can reset the default to manual sort order here."} <br/>
      {/if}
      {if ($form.count > 0)}
      {g->text one="This gallery contains %d album using New Items sort.  It must be reset to the default sort before this module can be deactivated.  You can reset the album here."
               many="This gallery contains %d albums using New Items sort.  These must be reset to the default sort before this module can be deactivated.  You can reset all albums here."
               count=$form.count arg1=$form.count} <br/>
      {/if}
      {g->text text="Warning: there is no undo."}
    </div>

    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset album sorts"}"/>
  </div>
  {/if}
</div>
