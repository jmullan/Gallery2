{*
 * $Revision: 1.2 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <h3> {g->text text="Reupload Photo"} </h3>

  {if !$ReuploadPhotoOption.uploadsPermitted}
  <div class="giError">
    {g->text text="Your webserver is configured to disallow file uploads from your web browser at this time.  Please contact your system administrator for assistance."}
  </div>
  {else}
  <p class="giDescription">
    {g->text text="Upload a new revision of this picture instead of the old one."}
  </p>

  {if $ReuploadPhotoOption.maxFileSize != 0}
  <p class="giDescription">
      {g->text text="<b>Note:</b> The new file cannot be larger than %s. If you want to upload a larger file you must ask your system administrator to allow larger uploads."
	  arg1=$ReuploadPhotoOption.maxFileSize}
  </p>
  {/if}

  <h4> {g->text text="File"} </h4>
  <input type="file" size="60" name="{g->formVar var="form[reupload]"}"/>

  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Reupload File"}"/>

  {if isset($form.error.reupload.failure)}
  <div class="giError">
    {g->text text="Unable to reupload file."}
    {if $ReuploadPhotoOption.maxFileSize > 0}
      {g->text text="Please check the size and try again. The new file cannot be larger than %s."
	       arg1=$ReuploadPhotoOption.maxFileSize}
    {/if}
  </div>
  {/if}
  {if isset($form.error.reupload.toolkit)}
  <div class="gbBlock giError">
    {g->text text="Unable to reupload file. Are you sure the file is of the same type (image, movie) as the original?"}
  </div>
  {/if}
  {/if}
</div>
