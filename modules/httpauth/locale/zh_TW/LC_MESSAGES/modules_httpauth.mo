��    &      L  5   |      P  $   Q     v     �     �     �     �  6   �  �   "  �   �  `   a  �   �  	   �     �     �  M   �           2     @  B  [  ?   �     �     �     �  �   	  �   �	    =
     D     `     n     �     �     �     �  5  �  r    )   �  �   �  v  �          ;     B     X     e     u  /   �  �   �  �   E  \   �  �   5     �     �       R   $     w     �     �    �  2   �     �          	  l     �   �  �   %               +  $   A     f     �     �    �  @  �  -     �   ;                             $                  	                &                          
                #             %                          "                           !       'Authorization Header' rule disabled Authentication Authentication Type Pattern: Authorization Header Authorization header. Bad URL rewrite configuration Gallery can handle HTTP Basic authentication directly. Gallery can't access HTTP usernames and passwords and automated checks failed to find a cause.  Troubleshooting documentation is in the %sGallery Codex%s. Gallery can't access HTTP usernames and passwords.  You can still use your web server's authentication.  Troubleshooting documentation is in the %sGallery Codex%s. Gallery tried to logout but failed.  You should close the browser window to logout successfully. Gallery will prompt you to login with HTTP authentication when permission is denied.  HTTP authentication sends your client a realm to which your username belongs.  It's safe to leave the realm blank. HTTP Auth HTTP Auth Settings HTTP Authentication Realm: If you're not automatically redirected, %sclick here to finish logging out%s. Login using HTTP authentication. Logout failed Missing HTTP Authorization PHP Path Info rewrite doesn't support the rule to fall back on passing HTTP usernames and passwords to Gallery.  You should uninstall and reinstall the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting documentation is in the %sGallery Codex%s. Pass the Authorization header to Gallery in a request variable. Reset Save Settings saved successfully Specify here a regular expression which the authentication type must match for authentication to proceed; for instance /Negotiate/ Specify here a regular expression which the username must match for authentication to proceed and a string with which to replace it.  See PHP %s documentation for more information. The URL rewrite rule to fall back on passing HTTP usernames and passwords to Gallery is disabled.  You should activate the HTTP auth 'Authorization Header' rule in the %sSite Admin URL Rewrite option%s.  Troubleshooting documentation is in the %sGallery Codex%s. URL rewrite module disabled Unknown Cause Use HTTP Authentication: Use Regular Expressions: Use Web Server Authentication: Username Pattern: Username Replacement: We can't fall back on passing HTTP usernames and passwords to Gallery because the URL rewrite module is disabled.  You should activate the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting documentation is in the %sGallery Codex%s. You may wish to trust only HTTP authentication types or HTTP usernames which match specified regular expressions - or HTTP usernames may not match your Gallery usernames; for instance if using %s authentication, the REMOTE_USER environment variable may be username@REALM.TLD.  In these cases, you may use regular expressions to filter authentication types and usernames. You must enter a valid regular expression Your web server may offer more comprehensive and more secure authentication.  If you configured your web server to authenticate requests to Gallery, you may choose to trust the username it reports in the REMOTE_USER environment variable. Project-Id-Version: Gallery: HTTP Auth 0.5.1
POT-Creation-Date: 2006-11-16 20:11-0500
PO-Revision-Date: 2006-11-16 14:00-0500
Last-Translator: Stephen Chu <stephen@ju-ju.com>
Language-Team: Chinese Traditional <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 認証檔頭規則未啟用 認証 認証類型樣式： 認証檔頭 認証檔頭。 網址改寫設定不正確 Gallery 可以直接處理 HTTP 基本認証。 Gallery 無法取得 HTTP 用戶名稱和密碼而且自動檢查無法找出原因。排除問題的說明在 %sGallery Codex%s。 Gallery 無法存取 HTTP 用戶名稱和密碼。你必需用你的網頁伺服器的認証手續。排除問題的說明在 %sGallery Codex%s。 Gallery 試著登出但是失敗了。你必需關掉網頁瀏覽程式才能完全登出。 Gallery 會在存取被拒時要求你使用 HTTP 認証來登入。HTTP 認証會送給你的網頁用戶程式一個你的用戶名稱所屬的領域。將領域留白也沒有關係。 HTTP 認証 HTTP 認証設定 HTTP 認証領域： 如果你沒有被自動轉到新的網頁，請%s按這裡完成登出手續%s。 使用 HTTP 認証登入。 登入失敗 沒有 HTTP 認証 PHP PathInfo 的改寫方式並不容許改寫規則傳送用戶名稱和密碼給 Gallery。你需要在%s網站管理的外掛組件設定%s中卸載再安裝網址改寫模組，並選擇 Apache mode_rewrite 或 ISAPI_Rewrite。排除問題的說明在 %sGallery Codex%s。 在要求變數中將認証檔頭傳給 Gallery。 重置 儲存 設定儲存成功 在這裡指定一個認証類型必需符合才能繼續認証手續的常規表示式；例如 /Negotiate/ 在這裡指定一個用戶名稱必需符合才能繼續認証手續的常規表示式，和一個用來替換的字串。請參考 PHP %s 說明文件。 傳送用戶名稱和密碼給 Gallery 的網址改寫規則沒有啟用。你需要在%s網站管理的網址改寫設定%s中啟用 HTTP 認証「認証檔頭」的規則。排除問題的說明在 %sGallery Codex%s。 網址改寫模組未啟用 不明原因 使用 HTTP 認証： 使用常規表示式（regexp）： 使用網頁伺服器認証： 用戶名稱樣式： 用戶名稱替換： 因為網址改寫模組沒有啟用，我們無法回到傳送用戶名稱和密碼給 Gallery 的方法。你需要在%s網站管理的外掛組件設定%s中啟用網址改寫模組，並選擇 Apache mode_rewrite 或 ISAPI_Rewrite。排除問題的說明在 %sGallery Codex%s。 你可以只信任符何指定的使用常規表示式的 HTTP 認証類型或 HTTP 用戶名稱，或不符合你的 Gallery 的用戶名稱；例如，在使用 %s 認証時，REMOTE_USER 環境變數可能是 username@REALM.TLD。在這些情形下，你可以用常規表示式來過濾認証類型或用戶名稱。 你必須輸入一個正確的常規表示式 你的網頁伺服器可能會提供更周詳和更安全的認証方式。如果你設定了你的網頁伺服器來認証對 Gallery 的要求，你可以選擇信任它在 REMOTE_USER 環境變數中報告的用戶名稱。 