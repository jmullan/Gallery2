<div class="gbMenu">
  <div class="giTitle">
    <a href="{g->url arg1="view=search:SearchScan"}">
      {g->text text="Search"}
    </a>
  </div>

  <form action="{g->url}" method="post">
    <p>
      <input type="hidden" name="{g->formVar var="view"}" value="{$SearchSystemContent.view}"/>
      <input type="hidden" name="{g->formVar var="form[formName]"}" value="SearchSystemContent"/>
      <input type="text" name="{g->formVar var="form[searchCriteria]"}" size="15"/>
      <input type="hidden" name="{g->formVar var="form[useDefaultSettings]"}" value="1"/>
    </p>
  </form>
</div>
