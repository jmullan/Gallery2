{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbAdmin">
  <script type="text/javascript">
  function SetSizeLimitOption_toggleXY() {ldelim}
      document.forms[0].elements["{g->formVar var="SizeLimitOption_dimensions[width]"}"].disabled = 
          !document.forms[0].elements["{g->formVar var="form[SizeLimitOption][dimensionChoice]"}"][1].checked;
      document.forms[0].elements["{g->formVar var="SizeLimitOption_dimensions[height]"}"].disabled = 
          !document.forms[0].elements["{g->formVar var="form[SizeLimitOption][dimensionChoice]"}"][1].checked;
  {rdelim}
  function SetSizeLimitOption_toggleSize() {ldelim}
      document.forms[0].elements["{g->formVar var="form[SizeLimitOption][filesize]"}"].disabled = 
          !document.forms[0].elements["{g->formVar var="form[SizeLimitOption][sizeChoice]"}"][1].checked;
  {rdelim}
  </script>
  <h2 class="giTitle">
    {g->text text="Define picture size limit"}
  </h2>

  <div class="gbDataEntry">
    <div class="giTitle">
    {g->text text="Maximum dimensions of full sized images"}
    </div>
    <input name="{g->formVar var="form[SizeLimitOption][dimensionChoice]"}" value="unlimited" 
      type="radio" onclick="javascript:SetSizeLimitOption_toggleXY()"
      {if $SizeLimitOption.dimensionChoice == "unlimited"}checked="checked"{/if}/>
    {g->text text="No Limits"} <br>
    <input name="{g->formVar var="form[SizeLimitOption][dimensionChoice]"}" value="explicit" 
      type="radio" onclick="javascript:SetSizeLimitOption_toggleXY()"
      {if $SizeLimitOption.dimensionChoice == "explicit"}checked="checked"{/if}/>
    {g->dimensions formVar="SizeLimitOption_dimensions" 
      height=$SizeLimitOption.height width=$SizeLimitOption.width}
    {if $SizeLimitOption.dimensionChoice == "unlimited"}
    <script type="text/javascript">
      document.forms[0].elements["{g->formVar var="SizeLimitOption_dimensions[width]"}"].disabled = true;
      document.forms[0].elements["{g->formVar var="SizeLimitOption_dimensions[height]"}"].disabled = true;
    </script>
    {/if}
    {if !empty($form.error.SizeLimitOption.dim.missing)}
    <div class="giError">
      {g->text text="You must specify at least one of the dimensions"}
    </div>
    {/if}
    <p/>
    <div class="giTitle">
    {g->text text="Maximum file size of full sized images in kilobytes"}
    </div>
    <input name="{g->formVar var="form[SizeLimitOption][sizeChoice]"}" value="unlimited" 
      type="radio" onclick="javascript:SetSizeLimitOption_toggleSize()"
      {if $SizeLimitOption.sizeChoice == "unlimited"}checked="checked"{/if}/>
      {g->text text="No Limits"}<br>
    <input name="{g->formVar var="form[SizeLimitOption][sizeChoice]"}" value="explicit" 
      type="radio" onclick="javascript:SetSizeLimitOption_toggleSize()"
      {if $SizeLimitOption.sizeChoice == "explicit"}checked="checked"{/if}/>
    <input name="{g->formVar var="form[SizeLimitOption][filesize]"}" type="text" size="7" 
      {if $SizeLimitOption.sizeChoice != "explicit"}disabled="disabled"{/if}
      maxlength="6" value="{$SizeLimitOption.filesize}"/>
    {if !empty($form.error.SizeLimitOption.filesize.invalid)}
    <div class="giError">
      {g->text text="You must enter a number (greater than zero)"}
    </div>
    {/if}
    <p>
    <input name="{g->formVar var="form[SizeLimitOption][keepOriginal]"}" type="checkbox"
      {if $SizeLimitOption.keepOriginal}checked="checked"{/if}/> 
    {g->text text="Keep original image?"} 
    </p>
  </div>
</div>
