��    (      \  5   �      p  $   q     �     �     �     �     �  D     6   P  �   �  �   "  `   �  �   '  	   �     �       M   (      v     �     �  B  �  ?   	     C	     I	     N	  �   j	  �   �	    �
     �     �     �     �       /   $     T     f  5  |  r  �  )   %  �   O  <  =  M   z     �     �  )   �  *     B   J  o   �  t   �    r    �  �   �  �  @  !   �  4   �  1     �   Q  J   #     n  -   �  �  �  t   o     �     �  4     	  =  v  G  f  �  )   %!  %   O!  ;   u!  B   �!  E   �!  d   :"     �"     �"  �  �"  �  �$  [   4'  {  �'                              &      #          
                (                                          %             '          	                $            !              "       'Authorization Header' rule disabled Authentication Authentication Type Pattern: Authorization Header Authorization header. Bad URL rewrite configuration By default HTTP authentication is only enabled for specific modules. Gallery can handle HTTP Basic authentication directly. Gallery can't access HTTP usernames and passwords and automated checks failed to find a cause.  Troubleshooting documentation is in the %sGallery Codex%s. Gallery can't access HTTP usernames and passwords.  You can still use your web server's authentication.  Troubleshooting documentation is in the %sGallery Codex%s. Gallery tried to logout but failed.  You should close the browser window to logout successfully. Gallery will prompt you to login with HTTP authentication when permission is denied.  HTTP authentication sends your client a realm to which your username belongs.  It's safe to leave the realm blank. HTTP Auth HTTP Auth Settings HTTP Authentication Realm: If you're not automatically redirected, %sclick here to finish logging out%s. Login using HTTP authentication. Logout failed Missing HTTP Authorization PHP Path Info rewrite doesn't support the rule to fall back on passing HTTP usernames and passwords to Gallery.  You should uninstall and reinstall the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting documentation is in the %sGallery Codex%s. Pass the Authorization header to Gallery in a request variable. Reset Save Settings saved successfully Specify here a regular expression which the authentication type must match for authentication to proceed; for instance /Negotiate/ Specify here a regular expression which the username must match for authentication to proceed and a string with which to replace it.  See PHP %s documentation for more information. The URL rewrite rule to fall back on passing HTTP usernames and passwords to Gallery is disabled.  You should activate the HTTP auth 'Authorization Header' rule in the %sSite Admin URL Rewrite option%s.  Troubleshooting documentation is in the %sGallery Codex%s. URL rewrite module disabled Unknown Cause Use HTTP Authentication: Use Regular Expressions: Use Web Server Authentication: Use the authentication plugins for all modules: Username Pattern: Username Replacement: We can't fall back on passing HTTP usernames and passwords to Gallery because the URL rewrite module is disabled.  You should activate the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting documentation is in the %sGallery Codex%s. You may wish to trust only HTTP authentication types or HTTP usernames which match specified regular expressions - or HTTP usernames may not match your Gallery usernames; for instance if using %s authentication, the REMOTE_USER environment variable may be username@REALM.TLD.  In these cases, you may use regular expressions to filter authentication types and usernames. You must enter a valid regular expression Your web server may offer more comprehensive and more secure authentication.  If you configured your web server to authenticate requests to Gallery, you may choose to trust the username it reports in the REMOTE_USER environment variable. Project-Id-Version: Gallery: HTTP Auth 1.0.2
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2006-12-20 10:02-0800
PO-Revision-Date: 2008-10-12 00:23+0300
Last-Translator: Ser Moro <webber@morozov-sm.ru>
Language-Team: Russian <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);
X-Poedit-Language: Russian
X-Poedit-Country: RUSSIAN FEDERATION
 Правило 'Заголовок авторизации' отключено Аутентификация Образец  Заголовок авторизации Заголовок авторизации. Неверная конфигурация модуля URL rewrite По умолчанию HTTP аутентификация включена не для всех модулей. Галерея может напрямую обработать основную HTTP  аутентификацию. Галерея не имеет доступа к HTTP логинам и паролям и автоматическая проверка не находит причины.  Диагностическая документация находится по адресу %sGallery Codex%s. Галерея не имеет доступа к HTTP логинам и паролям. Вы можете всё же использовать вход на сервер.  Диагностическая документация находится по адресу %sGallery Codex%s. Выход из  Галереи неудачен. Вы должны закрыть окно браузера для успешного выхода. Галерея вам предложит пройти авторизацию при помощи HTTP аутентификации, когда доступ запрещён.  HTTP аутентификация пошлёт вашему клиенту  область, где ваше имя подходит. Можно оставить область пустой, это безопасно. HTTP Аутентификация Настройки HTTP аутентификации Область HTTP аутентификации: Если ваш браузер не поддерживает автоматическую переадресацию,  кликните%s здесь%s для завершения процесса выхода. Вход с использованием HTTP аутентификации Выход неудачен Неверная HTTP авторизация. PHP PathInfo rewrite не поддерживает проверку логинов и паролей к Галерее.  Вы должны деинсталлировать и снова установить модуль URL rewrite здесь:  %sНастройки плагинов%s, и выбрать Apache mod_rewrite или ISAPI_Rewrite. Документация для помощи находится здесь %sGallery Codex%s.  Передача заголовка авторизации в заданную переменную Галерею  Отменить Сохранить Настройки успешно сохранены Задайте здесь  регулярное выражение, которому тип аутентификации должен соответствовать, чтобы успешно пройти аутентификацию; например,  /Negotiate/ Задайте здесь  регулярное выражение, которому должен соответствовать логин для успешного прохождения аутентификации и строку, которая заменит его. Смотрите PHP %s документацию для более полной информации.  Правило URL rewrite для проверки логинов и паролей к Галерее отключено. Вы должны активизировать HTTP auth 'Authorization Header' здесь: %sНастройки модуля URL rewrite%s.  Документация для помощи находится здесь %sGallery Codex%s. Модуль URL rewrite отключен Неизвестная причина Использовать HTTP Аутентификацию: Использовать  регулярные выражения: Использовать аутентификацию сервера: Использовать плагины аутентификации для всех модулей: Образец логина: Замена логина: Мы не можем проверить логины и пароли к Галерее потому, что отключен модуль URL rewrite.  Вы должны активизировать модуль URL rewrite здесь: %sНастройки модулей%s, и выбрать Apache mod_rewrite или ISAPI_Rewrite.  Документация для помощи находится здесь %sGallery Codex%s. Вы можете пожелать верить только HTTP типам аутентификации или HTTP именам которые соответствуют определённым регулярным выражениям или,  HTTP именам не соответствующим именам Галереи. Например, если выбрать %s аутентификацию, переменная REMOTE_USER может быть такой - username@REALM.TLD. В этом случае вы можете использовать регулярные выражения для фильтрации типов аутентификации и логинов. Вы должны ввести допустимое регулярное выражение Ваш сервер может иметь более совершенную и безопасную аутентификацию. Если вы настроите сервер на аутентификацию запросов к Галерее, вы можете выбрать настоящее имя пользователя в переменной среды - REMOTE_USER. 