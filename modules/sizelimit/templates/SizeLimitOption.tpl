{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<script type="text/javascript">
  // <![CDATA[
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
  // ]]>
</script>

<div class="gbBlock">
  <h3> {g->text text="Define picture size limit"} </h3>

  <div style="margin: 0.5em 0">
    <div style="font-weight: bold">
      {g->text text="Maximum dimensions of full sized images"}
    </div>
    <input type="radio" id="SizeLimit_DimNone" onclick="javascript:SetSizeLimitOption_toggleXY()"
     name="{g->formVar var="form[SizeLimitOption][dimensionChoice]"}" value="unlimited" 
     {if $SizeLimitOption.dimensionChoice == "unlimited"}checked="checked"{/if}/>
    <label for="SizeLimit_DimNone">
      {g->text text="No Limits"}
    </label>
    <br/>
    <input type="radio" onclick="javascript:SetSizeLimitOption_toggleXY()"
     name="{g->formVar var="form[SizeLimitOption][dimensionChoice]"}" value="explicit" 
     {if $SizeLimitOption.dimensionChoice == "explicit"}checked="checked"{/if}/>
    {g->dimensions formVar="SizeLimitOption_dimensions" 
		   width=$SizeLimitOption.width height=$SizeLimitOption.height}

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
  </div>

  <div style="margin: 0.5em 0">
    <div style="font-weight: bold">
      {g->text text="Maximum file size of full sized images in kilobytes"}
    </div>
    <input type="radio" id="SizeLimit_SizeNone" onclick="javascript:SetSizeLimitOption_toggleSize()"
     name="{g->formVar var="form[SizeLimitOption][sizeChoice]"}" value="unlimited" 
     {if $SizeLimitOption.sizeChoice == "unlimited"}checked="checked"{/if}/>
    <label for="SizeLimit_SizeNone">
      {g->text text="No Limits"}
    </label>
    <br/>
    <input type="radio" onclick="javascript:SetSizeLimitOption_toggleSize()"
     name="{g->formVar var="form[SizeLimitOption][sizeChoice]"}" value="explicit" 
     {if $SizeLimitOption.sizeChoice == "explicit"}checked="checked"{/if}/>
    <input type="text" size="7" maxlength="6"
     name="{g->formVar var="form[SizeLimitOption][filesize]"}" value="{$SizeLimitOption.filesize}"
     {if $SizeLimitOption.sizeChoice != "explicit"}disabled="disabled"{/if}/>

    {if !empty($form.error.SizeLimitOption.filesize.invalid)}
    <div class="giError">
      {g->text text="You must enter a number (greater than zero)"}
    </div>
    {/if}
  </div>

  <input type="checkbox" id="SizeLimit_KeepOrig"
   name="{g->formVar var="form[SizeLimitOption][keepOriginal]"}"
   {if $SizeLimitOption.keepOriginal} checked="checked"{/if}/>
  <label for="SizeLimit_KeepOrig">
    {g->text text="Keep original image?"} 
  </label>
</div>
