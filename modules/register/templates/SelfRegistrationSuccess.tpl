<div id="gsAdminContents">
	<div class="gbTopFlag">
	  <div class="gbTitle">
        <div class="giTitle">
          {g->text text="Registration successful"}
	    </div>
	  </div>
	</div>

  <div class="gbAdmin">

 {if isset($status.registeredUser)}
    <div class="gbDataEntry">
      <span>
		{g->text text="Your registration was successful."}
      </span>
    </div>
    <div class="gbDataEntry">
      <span>
		{g->text text="You will shortly receive an email  containing a link. You have to click this link to confirm and activate your account."}
      </span>
      <span>
		{g->text text="This procedure is necessary to prevent account abuse."}
      </span>
    </div>
  </div>

 {elseif isset($status.activatedUser)}

    <div class="gbDataEntry">
      <span>
		{g->text text="Your registration was successful and your account has been activated."}
      </span>
    </div>
    <div class="gbDataEntry">
      <span>
		{g->text text="You can now"}
		 <a href="{g->url arg1="view=core:UserAdmin" arg2="subView=core:UserLogin"}">{g->text text="login"}</a> 
		 {g->text text="to your account with your username and password."}
      </span>
    </div>
  </div>
  
 {else}
 
    <div class="giTitle">
		{g->text text="This page can only be called once."}
    </div>
    <div class="gbDataEntry">
      <span>
		{g->text text="This page has been requested before and can only be called once. Probable you have hit the Reload button. Please proceed to "}
		 <a href="{g->url arg1="view=core:UserAdmin" arg2="subView=core:UserLogin"}">{g->text text="login"}</a>.
      </span>
    </div>
  </div>
  
 {/if}
 
</div>
