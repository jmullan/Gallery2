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
	{g->text text="Random Highlight Settings"}
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
    <p class="giDescription">
      {g->text text="Enter length of time a random highlight album should keep one highlight before picking a new one."}
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
    <input type="submit" name="{g->formVar var="form[action][save]"}"
     value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}"
     value="{g->text text="Reset"}"/>
  </div>
</div>
