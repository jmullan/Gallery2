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
	{g->text text="Remote Settings"}
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
    <ul class="gbAdminList">
      <li>
	<input id="showItemAdd" type="checkbox" name="{g->formVar var="form[showItemAdd]"}"
	       {if $form.showItemAdd}checked="checked"{/if}/>
	<label for="showItemAdd">
	  {g->text text="Show information about Gallery Remote in \"add items\" view"}
	</label>
      </li>
    </ul>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
  </div>
</div>
