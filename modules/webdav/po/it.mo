��    )      d  ;   �      �  �   �  !   +      M  #   n  E   �     �  �   �  "   �     �  .        0     J     d    x    �  z   �     	     4	     A	     S	  "  d	     �
  +   �
  4   �
     �
  �     �   �  �   m  -   P     ~     �  �   �     J     d  
   t         �    �  �   �  �   M  �  �  �   r  '     &   <  *   c  @   �  +   �  �   �  '   �     #  0   5     f     �     �  R  �  D  
  �   O  "   �               )  >  ;     z  2   �  L   �       �   &  �       �  ,   �  #        :  �   L           ,   
   B      M   �   j   2  g!  �   �"  �   C#               	                                            !              #                              
                             $   '   %                           "       &              (         )    %sClick here%s to mount Gallery on your desktop with a WebDAV client.  Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s. 'Connect to WebDAV' rule disabled 'OPTIONS Requests' rule disabled Alternative URL missing DAV headers Alternatively, you can enter the following URL in your WebDAV client: Bad URL rewrite configuration Because OPTIONS responses are missing DAV headers, we try to fall back on an alternative URL, but alternative URL responses are also missing DAV headers.  Troubleshooting documentation is in the %sGallery Codex%s. Configuration checked successfully Connect to WebDAV Give davmount resources the correct extension. HTTP auth module disabled HTTP auth plugin disabled Missing DAV headers Most WebDAV clients will fail to connect because the URL rewrite module is disabled.  You should activate the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting documentation is in the %sGallery Codex%s. Most WebDAV clients will fail to connect because the URL rewrite rule to generate short WebDAV URLs is disabled.  You should activate the 'Connect to WebDAV' rule in the %sSite Admin URL Rewrite option%s.  Troubleshooting documentation is in the %sGallery Codex%s. Most WebDAV clients will successfully connect.  Documentation on mounting Gallery with WebDAV is in the %sGallery Codex%s. Mount Gallery on your desktop. Mount WebDAV Mount with WebDAV OPTIONS Requests PHP PathInfo rewrite doesn't support the rule to fall back on an alternative URL.  You should uninstall and reinstall the URL rewrite module in the %sSite Admin Plugins option%s and choose either Apache mod_rewrite or ISAPI_Rewrite.  Troubleshooting information is in the %sGallery Codex%s. PHP has no XML support Path to an item (eg. /album/image.jpg.html) Redirect OPTIONS requests so we can set DAV headers. Remote Interfaces Some WebDAV clients, e.g. Mac OS X WebDAVFS, will fail to connect and automated checks failed to find a cause.  Troubleshooting documentation is in the %sGallery Codex%s. Some WebDAV clients, e.g. Mac OS X WebDAVFS, will fail to connect because OPTIONS responses are missing DAV headers.  Troubleshooting documentation is in the %sGallery Codex%s. The URL rewrite rule to fall back on an alternative URL is disabled.  You should activate the WebDAV 'OPTIONS Requests' rule in the %sSite Admin URL Rewrite option%s.  Troubleshooting documentation is in the %sGallery Codex%s. The URL to connect to Gallery with WebDAV is: URL rewrite module disabled Unknown Cause Use short URL because most WebDAV clients don't support query strings.  The Windows WebDAV client requires that you don't add a slash before the %path% variable. WebDAV Mount Instructions WebDAV Settings WebDAV URL WebDAV requests not handled You can connect with WebDAV anonymously, but you can't do anything which requires you to login because neither HTTP authentication nor server authentication are enabled in the HTTP auth module.  You should activate HTTP authentication in the settings of the HTTP auth module. You can connect with WebDAV anonymously, but you can't do anything which requires you to login because the HTTP auth module is disabled.  You should activate the HTTP auth module in the %sSite Admin Plugins option%s.  Troubleshooting documentation is in the %sGallery Codex%s. You can't connect with WebDAV because PHP has no XML support on this server.  Troubleshooting documentation is in the %sGallery Codex%s. You can't connect with WebDAV because this server doesn't pass WebDAV requests to Gallery.  Troubleshooting documentation is in the %sGallery Codex%s. Project-Id-Version: Gallery: WebDAV 1.0.1
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2007-01-03 14:05+0100
PO-Revision-Date: 2007-02-19 12:30+0100
Last-Translator: Ermanno Baschiera <ebaschiera@gmail.com>
Language-Team: Italian <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
 %sClicca qui%s per montare Gallery sul tuo desktop con un client WebDAV. La documentazione sul montaggio di Gallery con WebDAV si trova presso %sGallery Codex%s. Regola 'Connetti a WebDAV' disabilitata Regola 'OPTIONS Requests' disabilitata DAV headers mancanti nelle URL alternative Altrimenti, puoi inserire l'URL che segue nel tuo client WebDAV: Configurazione riscrittura URL non corretta Poiché alle risposte OPTIONS mancano gli headers DAV, proviamo ad appoggiarci alle URL alternative, ma anche alle risposte delle URL alternative mancano gli headers DAV. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. Configurazione controllata con successo Connetti a WebDAV Dai alla risorsa davmount l'estensione corretta. Modulo HTTP auth disabilitato Plugin HTTP auth disabilitato Headers DAV mancanti La maggior parte dei client WebDAV non riuscirà a connettersi perché il modulo riscrittura URL è disabilitato. Devi attivare il modulo riscrittura URL in %sAmministrazione Sito opzione Plugins%s e selezionare Apache mod_rewrite oppure ISAPI_Rewrite.  La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. La maggior parte dei client WebDAV fallisce la connessione perché la regola di riscrittura URL per generare URL WebDAV brevi è disabilitata. Devi attivare la regola 'Connetti a WebDAV' in %sAmministrazione Sito opzione Riscrittura URL%s. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. La maggior parte dei client WebDAV si connetterà con successo. La documentazione sul montaggio di Gallery con WebDAV si trova presso %sGallery Codex%s. Monta Gallery sulla tua scrivania. Monta WebDAV Monta con WebDAV Richieste OPTIONS PHP PathInfo rewrite non supporta la regola di appoggiarsi alle URL alternative. Devi disinstallare e reinstallare il modulo URL rewrite in %sAmministrazione Sito opzione Plugins%s e scegliere Apache mod_rewrite oppure ISAPI_Rewrite. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. PHP non ha supporto a XML Percorso di un oggetto (es. /album/image.jpg.html) Redireziona le richieste OPTIONS in modo da poter impostare gli headers DAV. Interfacce Remote Alcuni client WebDAV, ad es. Mac OS X WebDAVFS, non riusciranno a connettersi e i controlli automatici non avranno trovato una causa. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. Alcuni client WebDAV, ad es. Mac OS X WebDAVFS, non riusciranno a connettersi perché alle risposte OPTIONS mancano gli headers DAV. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. La regola di riscrittura URL di appoggiarsi alle URL alternative è disabilitata. Devi attivare la regola WebDAV 'OPTIONS Requests' in %sAmministrazione Sito opzione Riscrittura URL%s. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. L'URL da connettere a Gallery con WebDAV è: Modulo riscrittura URL disabilitato Causa Sconosciuta Utilizza URL brevi perché la maggior parte dei client WebDAV non supporta le stringhe di query. Il client WebDAV di Windows necessita che non sia aggiunta una barra prima della variabile %path%. Istruzioni Montaggio WebDAV Configurazione WebDAV URL WebDAV Richiesta WebDAV non gestita Puoi connetterti con WebDAV in modo anonimo, ma non puoi fare nulla che richieda di essere loggato perché né il modulo HTTP auth né l'autenticazione server sono attivati. Devi attivare l'autenticazione HTTP nella configurazione del modulo HTTP auth. Puoi connetterti con WebDAV in modo anonimo, ma non puoi fare nulla che richieda di essere loggato perché il modulo HTTP auth è disattivato. Devi attivare il modulo HTTP auth in %sAmministrazione Sito opzione Plugins%s. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. Non puoi connetterti con WebDAV perché PHP non ha supporto a XML in questo server. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. Non puoi connetterti con WebDAV perché il server non passa le richieste WebDAV a Gallery. La documentazione per la risoluzione dei problemi si trova presso %sGallery Codex%s. 