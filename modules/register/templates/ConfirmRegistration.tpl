<div id="gsHeader">
  <div class="gbTitleBanner">
    <div class="giTitle">
      {g->text text="Account activation"}
    </div>
  </div>


 {if isset($form.error.unknownUser)}
  <div class="gbAdmin">
    <div class="gbDataEntry"}>
     <div class="giError">
	   {g->text text="This user cannot be activated."}
      </div>
    </div>
    <div class="gbDataEntry"}>
      <span>
		{g->text text="This can happen if the URL you entered is not correct or you already activated this account. Please check if your mailclient broke the link into several lines and append them without spaces."}
      </span>
    </div>
  </div>

 {else}
  <div class="gbAdmin">
    <div class="gbDataEntry"}>
      <span>
		{g->text text="Your account has been activated."}
      </span>
    </div>
    <div class="gbDataEntry"}>
      <span>
		{g->text text="You can now login to your account with your username and password."}
      </span>
    </div>
  </div>
 {/if}

 
</div>
