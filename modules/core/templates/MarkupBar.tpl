{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if $main.markupType == 'bbcode'}
{if !empty($firstMarkupBar)}
<script type="text/javascript">{literal}
  // <![CDATA[
  function openOrCloseTextElement(elementId, bbCodeElement, button, buttonLabel) {
    element = document.getElementById(elementId);
    if (!button.g2ToggleMode) {
      element.value = element.value + '[' + bbCodeElement + ']';
      button.value = '*' + buttonLabel;
    } else {
      element.value = element.value + '[/' + bbCodeElement + ']';
      button.value = buttonLabel;
    }
    element.focus();
    button.g2ToggleMode = !button.g2ToggleMode;
  }

  function appendTextElement(elementId, bbCodeElement, button) {
    element = document.getElementById(elementId);
    element.value = element.value + '[' + bbCodeElement + ']';
    element.focus();
  }

  {/literal}
  function appendUrlElement(elementId, bbCodeElement) {ldelim}
    element = document.getElementById(elementId);
    url = prompt("{g->text text="Enter a URL"}");
    text = prompt("{g->text text="Enter some text describing the URL"}");
    element.value = element.value + '[url=' + url + ']' + text + '[/url]';
    element.focus();
  {rdelim}

  function appendImageElement(elementId, bbCodeElement) {ldelim}
    element = document.getElementById(elementId);
    url = prompt("{g->text text="Enter an image URL"}");
    element.value = element.value + '[img]' + url + '[/img]';
    element.focus();
  {rdelim}
  // ]]>
</script>
{/if}

<div class="gbMarkupBar">
  <input type="button" class="inputTypeButton" value="{g->text text="B"}"
	 onclick="openOrCloseTextElement('{$element}', 'b', this, '{g->text text="B"}')"
	 style="font-weight: bold;"/>
  <input type="button" class="inputTypeButton" value="{g->text text="i"}"
	 onclick="openOrCloseTextElement('{$element}', 'i', this, '{g->text text="i"}')"
	 style="font-style: italic; padding-left: 1px; padding-right: 4px"/>
  <input type="button" class="inputTypeButton" value="{g->text text="list"}"
	 onclick="openOrCloseTextElement('{$element}', 'list', this, '{g->text text="list"}')"/>
  <input type="button" class="inputTypeButton" value="{g->text text="bullet"}"
	 onclick="appendTextElement('{$element}', '*', this)"/>
  <input type="button" class="inputTypeButton" value="{g->text text="url"}"
	 onclick="appendUrlElement('{$element}', this)"/>
  <input type="button" class="inputTypeButton" value="{g->text text="image"}"
	 onclick="appendImageElement('{$element}', this)"/>
</div>
{/if}
