{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if isset($ImageFrame_data[$ImageFrame_frame])}
  {assign var="data" value=$ImageFrame_data[$ImageFrame_frame]}
{/if}
{if !isset($data) || $data.type=='none' || $data.type=='style'}
  {if isset($ImageFrame_pre)}{$ImageFrame_pre}{/if}
  {if isset($src)}
    <img src="{$src}" alt="" class="ImageFrame_{$ImageFrame_frame}"/>
  {else}
    {g->image item=$item image=$image class="ImageFrame_$ImageFrame_frame"}
  {/if}
  {if isset($ImageFrame_post)}{$ImageFrame_post}{/if}
{elseif $data.type=='image'}
  {counter name="ImageFrame_counter" assign="IF_count"}
  <table class="ImageFrame_{$ImageFrame_frame}" border="0" cellspacing="0" cellpadding="0">
  {if !empty($data.imageTT) || !empty($data.imageTL) || !empty($data.imageTR) ||
      !empty($data.imageTTL) || !empty($data.imageTTR)}
    <tr>
    <td class="TL"></td>
    {if $data.wHL}<td class="TTL"></td>{/if}
    <td class="TT"{if $data.wHL or $data.wHR}
     style="width:expression((document.getElementById('IFid{$IF_count}').width-{$data.wHL+$data.wHR})+'px')"
    {/if}><div class="H"></div></td>
    {if $data.wHR}<td class="TTR"></td>{/if}
    <td class="TR"></td>
    </tr>
  {/if}
  <tr>
  {if $data.hVT}<td class="LLT"></td>{else}<td class="LL"{if $data.hVT or $data.hVB}
   style="height:expression((document.getElementById('IFid{$IF_count}').height-{$data.hVT+$data.hVB})+'px')"
   {/if}><div class="V">&nbsp;</div></td>{/if}
  <td rowspan="{$data.rowspan}" colspan="{$data.colspan}">{if
   isset($ImageFrame_pre)}{$ImageFrame_pre}{/if}{if isset($src)}<img src="{$src}" alt=""
   id="IFid{$IF_count}"/>{else}{g->image item=$item image=$image
                                class="" id="IFid`$IF_count`"}{/if}{if
   isset($ImageFrame_post)}{$ImageFrame_post}{/if}</td>
  {if $data.hVT}<td class="RRT"></td>{else}<td class="RR"{if $data.hVT or $data.hVB}
   style="height:expression((document.getElementById('IFid{$IF_count}').height-{$data.hVT+$data.hVB})+'px')"
   {/if}><div class="V">&nbsp;</div></td>{/if}
  </tr>
  {if $data.hVT}
    <tr>
    <td class="LL"{if $data.hVT or $data.hVB}
     style="height:expression((document.getElementById('IFid{$IF_count}').height-{$data.hVT+$data.hVB})+'px')"
    {/if}><div class="V">&nbsp;</div></td>
    <td class="RR"{if $data.hVT or $data.hVB}
     style="height:expression((document.getElementById('IFid{$IF_count}').height-{$data.hVT+$data.hVB})+'px')"
    {/if}><div class="V">&nbsp;</div></td>
    </tr>
  {/if}
  {if $data.hVB}
    <tr>
    <td class="LLB"></td>
    <td class="RRB"></td>
    </tr>
  {/if}
  {if !empty($data.imageBB) || !empty($data.imageBL) || !empty($data.imageBR) ||
      !empty($data.imageBBL) || !empty($data.imageBBR)}
    <tr>
    <td class="BL"></td>
    {if $data.wHL}<td class="BBL"></td>{/if}
    <td class="BB"{if $data.wHL or $data.wHR}
     style="width:expression((document.getElementById('IFid{$IF_count}').width-{$data.wHL+$data.wHR})+'px')"
    {/if}><div class="H"></div></td>
    {if $data.wHR}<td class="BBR"></td>{/if}
    <td class="BR"></td>
    </tr>
  {/if}
  </table>
{/if}
