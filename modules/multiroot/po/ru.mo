��          �      \      �     �     �  -   �     (     0  %   ?     e    s  6   w     �     �  �  �  �  c  �  =     �	     
  5   *
  !   `
     �
  <  �
  '   �     �  ]        o     �  x   �  )     �  C  ~   �     e  D   v  �  �      �  �  >     #   V  �   z  1   �  6   /                  
             	                                                                    Alternate guest user Configure Multiroot Define an alternate guest view of the Gallery Display Generate Files Leave blank to define a virtual root. Missing value Multiroot allows you to create an alternate URL to view part of the Gallery.  This configuration screen assists in setup and creation of a PHP file for the alternate URL.  This module never activates and is not needed to use multiroot.  There are two options: New user will be created if given name does not exist. Reset Root album of new view The original/real guest user must have view permission for all items accessible by any alternate guest user.  The form below assists in creation of an alternate guest and will assign view permission for the default album and all subalbums/items.  If these albums are already public and can remain that way, no more setup is required.  Setup for mutually exclusive views is more complicated: the original guest user must have access to items in all views, so first setup those permissions.  Then use the tools here to create each alternate view.  Just use the set of alternate URLs.  Keep the original Gallery URL unpublished as it shows the combined set of items. This option defines a default album for this view and adjusts navigation links so that no parent albums above the default are shown.  Both guests and logged in users accessing the alternate URL will see this effect.  However, Gallery permissions are unchanged so modules like imageblock and search, or manually entered URLs, can lead visitors to items outside the default album.  This option is easier to setup as it uses guest permissions already defined for your Gallery. This option defines a new guest view with permissions defined for exactly what this view should display.  Guests using the alternate URL cannot see any items outside those granted permission, by browsing or via any modules or URLs.  Logged in users see whatever their permissions allow, whether accessing the normal or alternate URL.  This option provides greater access control over the alternate view, but requires additional permissions setup: URI for new guest view: URI for this Gallery: User created and permissions assigned on target album Username of alternate guest user: Virtual root Project-Id-Version: Gallery: Multiroot 1.0.2
Report-Msgid-Bugs-To: gallery-translations@lists.sourceforge.net
POT-Creation-Date: 2006-09-12 11:50-0700
PO-Revision-Date: 2008-10-05 14:16+0300
Last-Translator: Ser Moro <webber@morozov-sm.ru>
Language-Team: Russian <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);
X-Poedit-Language: Russian
X-Poedit-Country: RUSSIAN FEDERATION
 Альтернативный гость Настроить Multiroot Создание альтернативных правил  просмотра Галереи Отображение Создать файлы Оставьте пустым для определения виртуального корневого каталога Недопустимое значение Multiroot позволяет вам создать альтернативный URL для просмотра части Галереи. Эта страница помогает создать PHP файл для альтернативного адреса URL. Данный модуль никогда не активизируется и не является частью Multiroot. Имеется 2 условия: Новый пользователь будет зарегистрирован, если такого имени ещё нет. Отменить Корневой альбом для нового просмотра Обычный гость должен иметь разрешение просматривать все элементы, доступные любому альтернативному гостю. Нижерасположенная форма помогает создать альтернативного гостя и правила просмотра для альбома по умолчанию и всех вложенных в него альбомов/элементов. Если эти альбомы открыты для всех, то нет смысла создавать альтернативный просмотр. Создание взаимоисключающих просмотров сложнее: обычный гость должен иметь доступ к элементам во всех просмотрах, это во-первых. Затем создаются альтернативные просмотры. Для этого используйте набор альтернативных адресов. Держите истинный адрес Галереи в секрете, так как он показывает объединённый набор элементов. Это условие определяет альбом по умолчанию для этого просмотра и создаёт навигационные ссылки так, чтобы не показывать альбомы, находящиеся выше в иерархии. То есть  альбом по умолчанию становится главным. И гости, и зарегистрированные пользователи, зашедшие по альтернативному адресу будут наблюдать этот эффект. Однако правила доступа Галереи не изменяются, такие модули как <b>imageblock</b> и <b>search</b> (а также вручную введённый адрес) могут вывести посетителей на элементы, находящиеся вне альбома по умолчанию. Это условие аналогично правилам доступа для гостей в Галерее. Это условие определяет новый гостевой просмотр, в котором правила чётко указывают что будет, а что не будет показано. Гости использующие  альтернативный URL не смогут увидеть  элементы, которые запрещено просматривать правилами. Это условие усиливает контроль доступа при альтернативном просмотре, но требует дополнительных настроек правил доступа: URI для нового гостевого просмотра: URI для этой Галереи: Пользователи и правила доступа, принятые для рассматриваемого альбома Имя альтернативного гостя: Виртуальный корневой каталог 