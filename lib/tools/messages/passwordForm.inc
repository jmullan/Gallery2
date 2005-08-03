<div class="password_form">

  <div class="example">
    <span class="message">
      In order to verify you, we require you to enter your Gallery setup password.  This is the
      password you entered when you installed Gallery.  It can be found in your gallery/config.php
      file like this:
    </span>
    <pre>
      $gallery->setConfig('setup.password', '<b>your password here</b>');
    </pre>

    <form method="post">
      Password:
      <input type="password" name="g2_password"/>
      <script type="text/javascript">document.forms[0]['g2_password'].focus();</script>
      <input type="submit" value="Verify Me"/>
    </form>
  </div>
</div>
