��          �      l      �     �     �  6     �   D  	             *     E     K     P  �   l  �   �     �     �     �     �       r    )   �  �   �  v  �     	     &	  /   <	  �   l	     (
     4
     F
     [
     b
     i
  l   |
  �   �
     �  $   �     �     �     �  @    -   L  �   z                                                                
                              	    Authentication Authentication Type Pattern: Gallery can handle HTTP Basic authentication directly. Gallery will prompt you to login with HTTP authentication when permission is denied.  HTTP authentication sends your client a realm to which your username belongs.  It's safe to leave the realm blank. HTTP Auth HTTP Auth Settings HTTP Authentication Realm: Reset Save Settings saved successfully Specify here a regular expression which the authentication type must match for authentication to proceed; for instance /Negotiate/ Specify here a regular expression which the username must match for authentication to proceed and a string with which to replace it.  See PHP %s documentation for more information. Use HTTP Authentication: Use Regular Expressions: Use Web Server Authentication: Username Pattern: Username Replacement: You may wish to trust only HTTP authentication types or HTTP usernames which match specified regular expressions - or HTTP usernames may not match your Gallery usernames; for instance if using %s authentication, the REMOTE_USER environment variable may be username@REALM.TLD.  In these cases, you may use regular expressions to filter authentication types and usernames. You must enter a valid regular expression Your web server may offer more comprehensive and more secure authentication.  If you configured your web server to authenticate requests to Gallery, you may choose to trust the username it reports in the REMOTE_USER environment variable. Project-Id-Version: Gallery: HTTP Auth 0.5.0
POT-Creation-Date: 2006-11-16 20:11-0500
PO-Revision-Date: 2006-11-16 14:00-0500
Last-Translator: Stephen Chu <stephen@ju-ju.com>
Language-Team: Chinese Traditional <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
 認証 認証類型樣式： Gallery 可以直接處理 HTTP 基本認証。 Gallery 會在存取被拒時要求你使用 HTTP 認証來登入。HTTP 認証會送給你的網頁用戶程式一個你的用戶名稱所屬的領域。將領域留白也沒有關係。 HTTP 認証 HTTP 認証設定 HTTP 認証領域： 重置 儲存 設定儲存成功 在這裡指定一個認証類型必需符合才能繼續認証手續的常規表示式；例如 /Negotiate/ 在這裡指定一個用戶名稱必需符合才能繼續認証手續的常規表示式，和一個用來替換的字串。請參考 PHP %s 說明文件。 使用 HTTP 認証： 使用常規表示式（regexp）： 使用網頁伺服器認証： 用戶名稱樣式： 用戶名稱替換： 你可以只信任符何指定的使用常規表示式的 HTTP 認証類型或 HTTP 用戶名稱，或不符合你的 Gallery 的用戶名稱；例如，在使用 %s 認証時，REMOTE_USER 環境變數可能是 username@REALM.TLD。在這些情形下，你可以用常規表示式來過濾認証類型或用戶名稱。 你必須輸入一個正確的常規表示式 你的網頁伺服器可能會提供更周詳和更安全的認証方式。如果你設定了你的網頁伺服器來認証對 Gallery 的要求，你可以選擇信任它在 REMOTE_USER 環境變數中報告的用戶名稱。 