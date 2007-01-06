��    $      <  5   \      0  !   1      S  #   t     �  �   �  "   �     �  .   �     �     
        7  z   @     �     �     �     �  "  
     -	  +   D	  4   p	     �	  �   �	  �   b
  �     -   �     $     @     \  �   j           �   1  �   �  �   v  �  �  0   �  *   �  %     2   ;  �   n  !   I     k  .   ~  "   �     �  '  �      t   "  #   �     �     �     �  5  �     $  6   <  ?   s     �  �   �  �   �  �   C  3   (  !   \  +   ~     �  �   �     h    �  �   �  �   /  �   �                                                       $   !                                               
   "                 	                           #                            'Connect to WebDAV' rule disabled 'OPTIONS Requests' rule disabled Alternative URL missing DAV headers Bad URL rewrite configuration Because OPTIONS responses are missing DAV headers, we try to fall back on an alternative URL, but alternative URL responses are also missing DAV headers.  Troubleshooting documentation is in the %sGallery Codex%s. Configuration checked successfully Connect to WebDAV Give davmount resources the correct extension. HTTP auth module disabled Missing DAV headers Most WebDAV clients will fail to connect because the URL rewrite module is disabled.  You should activate the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting documentation is in the %sGallery Codex%s. Most WebDAV clients will fail to connect because the URL rewrite rule to generate short WebDAV URLs is disabled.  You should activate the 'Connect to WebDAV' rule in the %sSite Admin URL Rewrite option%s.  Troubleshooting documentation is in the %sGallery Codex%s. Most WebDAV clients will successfully connect.  Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s. Mount Gallery on your desktop. Mount WebDAV Mount with WebDAV OPTIONS Requests PHP PathInfo rewrite doesn't support the rule to fall back on an alternative URL.  You should uninstall and reinstall the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting information is in the %sGallery Codex%s. PHP has no XML support Path to an item (eg. /album/image.jpg.html) Redirect OPTIONS requests so we can set DAV headers. Remote Interfaces Some WebDAV clients, e.g. Mac OS X WebDAVFS, will fail to connect and automated checks failed to find a cause.  Troubleshooting documentation is in the %sGallery Codex%s. Some WebDAV clients, e.g. Mac OS X WebDAVFS, will fail to connect because OPTIONS responses are missing DAV headers.  Troubleshooting documentation is in the %sGallery Codex%s. The URL rewrite rule to fall back on an alternative URL is disabled.  You should activate the WebDAV 'OPTIONS Requests' rule in the %sSite Admin URL Rewrite option%s.  Troubleshooting documentation is in the %sGallery Codex%s. The URL to connect to Gallery with WebDAV is: This album's WebDAV URL is: URL rewrite module disabled Unknown Cause Use short URL because most WebDAV clients don't support query strings.  The Windows WebDAV client requires that you don't add a slash before the %path% variable. WebDAV Settings You can connect with WebDAV anonymously, but you can't do anything which requires you to login because the HTTP auth module is disabled.  You should activate the HTTP auth module in the %sSite Admin Plugins option%s.  Troubleshooting documentation is in the %sGallery Codex%s. You can mount Gallery on your desktop with a WebDAV client.  Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s. You can mount Gallery on your desktop with a WebDAV client.  You can then add items to Gallery by drag and drop.  Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s. You can't connect with WebDAV because PHP has no XML support on this server.  Troubleshooting documentation is in the %sGallery Codex%s. Project-Id-Version: Gallery: WebDAV 0.7.1
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2007-01-03 09:28+0100
PO-Revision-Date: 2007-01-03 09:28+0100
Last-Translator: Anders Lindquist <andersl@saaf.se>
Language-Team: Swedish <gallery-translations@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 'Anslutning till WebDAV' reglen är ej aktiverad 'OPTIONS-begäran' reglen är ej aktiverad Alternativ URL saknar DAV-information Felaktig konfiguration av URL-omskrivnings modulen Pga. att OPTIONS-svaren saknar DAV-information, så försöker vi att falla tillbaka till en alternativ URL, men den alternativa URLen saknar också DAV-information. Felsökningsdokumentation finns i %sGallery Codex%s. Konfigurationen har kontrollerats Anslut till WebDAV Ge davmount-resurser den korrekta extensionen. HTTP-auth modulen är ej aktiverad Saknad DAV-information De flesta WebDAV klienter kommer inte att kunna ansluta pga att URL-omskrivnings modulen inte är aktiverad. Du bör aktivera URL-omskrivnings modulen i %sSite Admin Plugins option%s och välja antingen Apache mod_rewrite eller ISAPI_Rewrite. Felsökningsdokumentation finns i %sGallery Codex%s. De flesta WebDAV klienterna kommer inte att kunna ansluta pga URL-omskrivningsreglen för att generera korta WebDAV URLer ej är aktiverad. Du bör aktivera 'Anslut till WebDAV' reglen i %sSite Admin URL Rewrite option%s. Felsökningsdokumentation finns i %sGallery Codex%s. De flesta WebDAV klienterna fungerar. Dokumentation om hur man monterar Gallery med WebDAV fins i %sGallery Codex%s. Montera Gallery på ditt skrivbord. Montera WebDAV Montera med WebDAV OPTIONS-begäran PHP PathInfo-omskrivning understödjer inte reglen för att falla tillbaka till en alternativ URL. Du bör avinstallera och återinstallera URL-omskrivnings modulen i %sSite Admin Plugins option%s och välja antingen Apache mod_rewrite eller ISAPI_Rewrite. Felsökningsdokumentation finns i %sGallery Codex%s. PHP har inget XML-stöd Sökväg till ett objekt (t.ex. /album/image.jpg.html) Styr om OPTIONS-begäran så att vi kan sätta DAV-information. Fjärstyrningsgränssnitt Vissa WebDAV klienter, t.ex. Mac OS X WebDAVFS, kommer inte att kunna ansluta och de automatiska kontrollerna kommer inte att kunna hitta orsaken. Felsökningsdokumentation finns i %sGallery Codex%s. Vissa WebDAV klienter t.ex. Mac OS X WebDAVFS, kommer inte att kunna ansluta pga. OPTIONS-svaren saknar DAV-information. Felsökningsdokumentation finns i %sGallery Codex%s. URL-omskrivnings reglen för att falla tillbaka till en alternativ URL är ej aktiverad. Du bör aktivera WebDAV 'OPTIONS-begäran' reglen i %sSite Admin URL Rewrite option%s. Felsökningsdokumentation finns i %sGallery Codex%s. URLen för att ansluta till Gallery med WebDAV är: Det här albumets WebDAV URL är: URL-omskrivnings modulen är inte aktiverad Okänd orsak Använd korta URL:er pga. de flesta WebDAV klienter inte understödjer frågesträngar. Windows WebDAV klient kräver att du lägger till ett snedstreck före variablen %path%. Inställningar för WebDAV Du kan ansluta dig annonymt med WebDAV, men du kan inte utföra några operationer som kräver att du är inloggad eftersom HTTP-auth modulen ej är aktiverad. Du br aktivera HTTP-auth modulen i %sSite Admin Plugins option%s. Felsökningsdokumentation finns i %sGallery Codex%s. Du kan inte montera Gallery på ditt skrivbord med en WebDAV klient. Dokumentation om hur man monterar Gallery med WebDAV finns i %sGallery Codex%s. Du kan montera Gallery på ditt skrivbord med en WebDAV klient. Du kan sen addera objekt till Gallery med 'drag och släpp'. Dokumentation om hur du monterar Gallery med WebDAV finns i %sGallery Codex%s. Du kan inte ansluta med WebDAV pga. PHP inte har något XML-stöd på denna server. Felsökningsdokumentation finns i %sGallery Codex%s. 