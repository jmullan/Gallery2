<div class="gbAdmin">
  <div class="giDescription">
    {g->text one="Upload a file directly from your computer."
             many="Upload up to %d files directly from your computer."
             count=$form.uploadBoxCount
             arg1=$form.uploadBoxCount}
    {g->text text="Enter the full path to the file and an optional caption in the boxes below."}
    <input type="hidden" name="{g->formVar var="form[uploadBoxCount]"}" value="{$form.uploadBoxCount}" />
  </div>

  <div class="gbAdmin">
    {section name="uploadBoxes" loop=$form.uploadBoxCount}
    {assign var=iteration value=$smarty.section.uploadBoxes.iteration}
    <div class="gbDataEntry">
      <div class="giTitle">
	<div class="giTitle">
	  {g->text text="File"}
	</div>

	<input name="{g->formVar var="form[$iteration]"}" type="file" size="60"/>
      </div>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Caption"}
      </div>

      <textarea rows="2" cols="60" name="{g->formVar var="form[caption][$iteration]"}"></textarea>
    </div>
    {/section}
  </div>

  <div class="gbBottomFlag">
    <div class="giActionSelect">
      <input type="submit" name="{g->formVar var="form[action][addFromBrowser]"}" value="{g->text text="Add Items"}"/>
    </div>
  </div>
</div>
