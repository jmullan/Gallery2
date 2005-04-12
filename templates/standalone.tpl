{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{*
 * This file is for views that wish to present the entire <html> block
 * instead of just providing <head> and <body> data.  Anything that is
 * displayed using this template will take over the entire page,
 * instead of showing up inside the themed block, so it won't have the
 * standard header and footer.  It should only be used sparingly for
 * modal dialogs, etc.
 *}
{include file="gallery:`$main.html`" l10Domain=$main.viewL10Domain}
