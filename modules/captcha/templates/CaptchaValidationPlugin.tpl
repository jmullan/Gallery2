{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <h4>
    {g->text text="Type the word appearing in the picture."}
  </h4>
  <div>
    <img src="{g->url arg1="view=captcha:CaptchaImage"}" style="width: 100px; height: 100px;"/>
  </div>
  <input type="text" name="{g->formVar var="form[CaptchaValidationPlugin][word]"}" size="16" value=""/>

  {if isset($form.error.CaptchaValidationPlugin)}
  <div class="giError">
    {if isset($form.error.CaptchaValidationPlugin.missing)}
    {g->text text="You must enter the number appearing in the picture."}
    {/if}
    {if isset($form.error.CaptchaValidationPlugin.invalid)}
    {g->text text="Incorrect number."}
    {/if}
  </div>
  {/if}
</div>

