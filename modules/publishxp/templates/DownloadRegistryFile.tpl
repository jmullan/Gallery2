Windows Registry Editor Version 5.00

[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\PublishingWizard\PublishingWizard\Providers\{$DownloadRegistryFile.domain}]
"displayname"="{$DownloadRegistryFile.title} at {$DownloadRegistryFile.domain}"
"description"="{g->text text="Publish Your Photos and Movies to %s" arg1=$DownloadRegistryFile.title}"
"href"="{g->url arg1="view=publishxp:Login"}"
"icon"="{g->url href="/favicon.ico"}"
