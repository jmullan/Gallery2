{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="DAPI (Digibug API) for Photo Printing Settings"} </h2>
</div>

{if isset($status.saved)}
<div class="gbBlock"><h2 class="giSuccess">
  {g->text text="Settings saved successfully"}
</h2></div>
{/if}

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="DAPI (Digibug API) allows you to sell your photos as prints, or printed gift products through the Digibug.com website."}
  </p>

  {g->text text="Digibug Company ID <a href="http://www.digibug.com/digibugapi/" target="_blank">[What's this?]</a>:"}
  <input type="text" size="6" name="{g->formVar var="form[digibugCustomerId]"}" value="{$form.digibugCustomerId}"
    id="formDigibugCustomerId" autocomplete="off"/>

  {g->text text="Event ID <a href="http://www.digibug.com/digibugapi/" target="_blank">[What's this?]</a>:"}
  <input type="text" size="6" name="{g->formVar var="form[digibugPricelistId]"}" value="{$form.digibugPricelistId}"
    id="formDigibugEventId" autocomplete="off"/>

  {if isset($form.error.digibugCustomerId.missing)}
  <div class="giError">
    {g->text text="You must enter a digibug customer id."}
  </div>
  {/if}

  {if isset($form.error.digibugPricelistId.missing)}
  <div class="giError">
    {g->text text="Please create an event or use your default event id as your pricelist id."}
  </div>
  {/if}

</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Settings"}"/>
  {if $AdminDigibug.isConfigure}
    <input type="submit" class="inputTypeSubmit"
     name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  {else}
    <input type="submit" class="inputTypeSubmit"
     name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
  {/if}
</div>
