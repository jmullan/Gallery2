��    $      <  5   \      0  �   1  !   �      �  #     E   *     p  "   �     �  .   �     �          &    :  z   S     �     �     �            +   4  4   `     �  �   �  �   R  -   	     1	     M	  �   [	     �	     
     '
    C
    W  �   l  �   �  �  �  �   E  *   �  4     (   A  B   j  *   �  !   �     �  0   
  !   ;     ]     }    �  �   �  "   +     N     \     n  !   �  0   �  D   �       �   ;  �   �  .   �  2   �       �     "   �     �  $       *    .  �   6  �   �                                                   	   #   !                       $                          "                
                                                          %sClick here%s to mount Gallery on your desktop with a WebDAV client.  Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s. 'Connect to WebDAV' rule disabled 'OPTIONS Requests' rule disabled Alternative URL missing DAV headers Alternatively, you can enter the following URL in your WebDAV client: Bad URL rewrite configuration Configuration checked successfully Connect to WebDAV Give davmount resources the correct extension. HTTP auth module disabled HTTP auth plugin disabled Missing DAV headers Most WebDAV clients will fail to connect because the URL rewrite module is disabled.  You should activate the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting documentation is in the %sGallery Codex%s. Most WebDAV clients will successfully connect.  Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s. Mount Gallery on your desktop. Mount WebDAV Mount with WebDAV OPTIONS Requests PHP has no XML support Path to an item (eg. /album/image.jpg.html) Redirect OPTIONS requests so we can set DAV headers. Remote Interfaces Some WebDAV clients, e.g. Mac OS X WebDAVFS, will fail to connect and automated checks failed to find a cause.  Troubleshooting documentation is in the %sGallery Codex%s. Some WebDAV clients, e.g. Mac OS X WebDAVFS, will fail to connect because OPTIONS responses are missing DAV headers.  Troubleshooting documentation is in the %sGallery Codex%s. The URL to connect to Gallery with WebDAV is: URL rewrite module disabled Unknown Cause Use short URL because most WebDAV clients don't support query strings.  The Windows WebDAV client requires that you don't add a slash before the %path% variable. WebDAV Mount Instructions WebDAV Settings WebDAV requests not handled You can connect with WebDAV anonymously, but you can't do anything which requires you to login because neither HTTP authentication nor server authentication are enabled in the HTTP auth module.  You should activate HTTP authentication in the settings of the HTTP auth module. You can connect with WebDAV anonymously, but you can't do anything which requires you to login because the HTTP auth module is disabled.  You should activate the HTTP auth module in the %sSite Admin Plugins option%s.  Troubleshooting documentation is in the %sGallery Codex%s. You can't connect with WebDAV because PHP has no XML support on this server.  Troubleshooting documentation is in the %sGallery Codex%s. You can't connect with WebDAV because this server doesn't pass WebDAV requests to Gallery.  Troubleshooting documentation is in the %sGallery Codex%s. Project-Id-Version: Gallery: WebDAV 1.0.0
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2006-11-16 01:37+0100
PO-Revision-Date: 2007-03-16 10:46+0000
Last-Translator: Bjørn Graabek <bjorn AT graabek DOT com>
Language-Team: Danish <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 %sKlik her%s for at montere Gallery på din desktop med en WebDAV-klient. Dokumentation om montering af Gallery med WebDAVer at finde i %sGallerycodexen%s. 'Forbind til WebDAV' reglen er deaktiveret Regel for ‘OPTIONS-forespørsler’ er deaktiveret Alternativ nettadresse mangler DAV-hoder Alternativt kan du indtaste den følgende URL i din WebDAV-klient: Forkerte indstillinger for URL omskrivning Kontrol af indstillinger lykkedes Kobl til WebDAV Tildel davmount-ressourcer den korrekte filtype. HTTP-auth modulet  er deaktiveret HTTP-auth plugin er deaktiveret Mangler DAV headers De fleste WebDAV-klienter vil ikke kunne koble til fordi  URLomskrivingsmodulet er deaktivert. Du bør aktivere URL omskrivningsmodulet i %sPlugin Aministrationen%s og enten vælge Apache mod_rewrite eller ISAPI_Rewrite. Fejlsøgningsdokumentation er i %sGallerycodexen%s. De fleste WebDAV-klienter vil uden problemer tilkobe. Dokumentation om montering af Gallery med WebDAV er at finde i %sGallerycodexen%s. Monter Gallery på dit skrivebord. Monter WebDAV Monter med WebDAV OPTIONS-forespørgsler PHP har ingen XML-understøttelse Sti til et objekt (f.eks. /album/image.jpg.html) Videresend HTTP OPTIONS-forespørgsler så vi kan vælge DAV-header. Fjernbetjenings-grænseflader Nogle WebDAV-klienter, f.eks. Mac OS X WebDAVFS, kan ikke kunne koble til og automatiske kontroller kunne ikke finde nogen årsag dertil. Fejilsøgningsdokumentation er i %sGallerycodexen%s. Nogle WebDAV-klienter, f.eks. Mac OS X WebDAVFS, vil ikke kunne koble til fordi OPTIONS-svar mangler DAV-headers. Fejlsøgningsdokumentation er i %sGallerycodexen%s. URL'en for at koble til Gallery med WebDAV er: Modul for omskriving av nettadresser er deaktivert Ukendt årsag Benyt kort URL da de fleste WebDAV-klienter ikke understøtter forespørgsles-strenge. Windows’ WebDAV-klienten kræver at du ikke tilføjer en skråstreg (slash) før %path% variabelen. Monteringsinstruktioner for WebDAV WebDAV Indstillinger WebDAV-forespørgsler ikke behandlet Du kan koble til WebDAV anonymt, men du kan ikke gøre noget der kræver at du logger ind da hverken HTTP-authentication  eller server authentication er aktivert i HTTP-auth modulet. Du bør aktivere HTTP-authentication i indstillingene for HTTP-auth modulet. Du kan koble til med WebDAV anonymt, men du kan ikke gøre noget der kræver at du logger ind da HTTP-auth modulet er deaktiveret. Du bør aktivere HTTP-auth modulet i %sAdministratorens Plugin indstillinger%s. Fejlsøgingsdokumentationen er i %sGallerycodexen%s. Du kan ikke koble til med WebDAV da PHP på denne server ikke har nogen XML-understøttelse. Fejlsøgningsdokumentation er at finde i %sGallerycodexen%s. Du kan ikke koble til med WebDAV da denne server ikke videresender WebDAV-forespørgsler til Gallery. Fejlsøgningsdokumentation er at finde i %sGallerycodexen%s. 