��    n      �  �   �      P	  *   Q	  (   |	  %   �	  �   �	    �
  
   �     �     �     �  D   �  �   4     0     >     D     K  "   S  	   v  	   �     �  |   �          -     ;     I  U   W     �  Y   �  2   &  
   Y  �   d     �     �       a        u  �  �     &  '   3     [     u  A   �  ?   �     
  �   #     �     �  >   �  D  :  A        �  �   �     ~     �     �     �     �     �     �     �     �               (     9  "   G      j  *   �  	   �     �     �     �    �  "        *     9  '   M     u     |     �     �     �     �     �          
  @     >   S     �  %   �  C   �  B     ?   G  -   �     �     �  -   �       	     1     \   M  
   �     �     �     �     �  �   �  $   �  $   �  I   �    D  M   \   H   �   �   �   �  �!  x  }#     �%  #   &  !   0&  E   R&     �&  B  '      [)     |)     �)     �)  3   �)     �)  )   �)  +   #*  �   O*  !   ;+  &   ]+  &   �+  %   �+  �   �+  K   �,  �   -  �   �-     �.    �.     �/     �/     �/  �   �/  $   �0    �0     �3  I   4  =   Q4  6   �4  �   �4  �   �5     �6  �  �6     �8     �8  �   �8  w  /9  �   �;     2<  8  R<     �=  +   �=     �=     �=  '    >  @   (>     i>  !   �>     �>  !   �>  '   �>     ?  %   +?  Z   Q?  @   �?  9   �?     '@  7   8@  4   p@  A   �@    �@  6   C  5   ;C  8   qC  \   �C     D  =   D  5   TD  A   �D  +   �D  3   �D  -   ,E     ZE     qE  �   �E  �   8F     G  +   &G  �   RG  �   =H  v   �H  U   ;I     �I  !   �I  M   �I     J     2J  a   IJ  �   �J     aK  "   uK     �K  O   �K     L  �  'L  G   �M  M   �M  w   LN             C      .   U   c       8   A       1   3   T   V   d       =   $   ?              0   '             4       e   
   7   >   H                 	              i       k   5          2   Z   W       m   ;   %      j   f   \   L                 [   9   F          E                    <   &   6       :      )   ^                   (         !          B   Y   R   *          N   /      b       S       l      J   n   _   g   "          I   K      ,       @   D       G   h   ]           P   +   a                         `      M   X   O   #       -      Q    %sSummary%s was truncated for %sitem %d%s. %sTitle%s was truncated for %sitem %d%s. (Default to summary value if not set) <b>Note:</b> Before you import any data you should make sure your Gallery 1 is installed correctly by adding a photo through the Gallery 1 web interface.  Make sure you resolve any errors you see there first. Add the same <tt>.htaccess</tt> block in the Gallery1 albums directory if you also wish to redirect links to image files and album directories. Note that these redirects are not active until the G1 images are actually removed or moved. Omit the !-f line shown below to redirect anyway. Album Name Album Notes Album Title Albums to import: An album already exists with this name.  This album will be renamed. Any hidden albums or items will be imported with restricted view permissions. Activate the Hidden Items module before migration to import these as "hidden" which means they are invisible to guest users until accessed by the direct URL for those items. Base filename Blank Cancel Caption Character Encoding of Source Text: Check All Clear All Confirm Migration Copy all or part of an existing Gallery 1 installation into your Gallery 2.  It won't modify your Gallery 1 data in any way. Creating thumbnails Custom Field: Custom field: Custom fields Custom fields imported into item fields above will not be duplicated as custom fields Custom fields will be imported Custom fields will not be imported.  Activate Custom Fields module to enable this option. Default to same as summary if custom field not set Delete All Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries? Description Description: %s Destination: Do not create Gallery 2 custom fields for fields selected above for title, summary or description Download .htaccess file Edit or create a file called <tt>.htaccess</tt> in your Gallery1 directory and add the text shown below to the file. Remove G1 rewrite rules from an existing file. Redirects will also work in your Gallery2 directory if G2 is installed in the path where G1 used to be. However, if you also use the G2 URL Rewrite module then activate the G1 redirect rule in that module instead of using the block shown below. Encoding: %s Ensure the %s Apache module is enabled. Enter a custom field name Error importing %s Error while importing %d album. Errors while importing %d albums. Error while importing %d user. Errors while importing %d users. Example: /var/www/albums G1 URL redirect. Use only if G2 is installed where G1 used to be and you have run a G1 import with the URL redirect option selected. Otherwise follow instructions in %sMigrate Site Admin%s. G1 path G1-&gt;G2 Mapping G1-&gt;G2 mappings will be recorded for use in URL Redirection Gallery 2 has the following fields for all items and albums: title, summary text shown with thumbnails and description text shown in item or album view. G1 albums already have these three items (though the names of summary and description are reversed). G1 items have only a filename and caption. For items imported into G2: Gallery can redirect old Gallery1 URLs to the new Gallery2 pages. Hidden Items If G2 is installed in the path where G1 used to exist, you will need to remove the G1 file "gallery_remote2.php" file before you can use Gallery Remote to upload images to G2. Import Import %s now. Import Albums Import Complete Import Users Import custom fields Import from Gallery 1 Import more data Imported %s Importing Photos Importing Users Invert Selection Item captions Item fields will be imported from: Map entries deleted successfully Migrate your Gallery 1 albums to Gallery 2 Migration No albums imported. No available users No users imported. Normally Gallery will generate thumbnails the first time you look at them, then save them for subsequent views.  If you check this box, we'll create the thumbnails at migration time.  Migration will take longer but the first time you view an album will go much faster. Path to Gallery 1 albums directory Prepare Import Recently Used Paths Record G1-&gt;G2 mappings during import Select Select Albums and Users Select the albums to migrate Select the users to migrate Set description from: Set summary from: Set title from: Set: Source: Successfully imported %d album. Successfully imported %d albums. Successfully imported %d user. Successfully imported %d users. Summary The path that you entered is invalid. There is one G1-&gt;G2 map entry There are %d G1-&gt;G2 map entries These users are already in your gallery, and will not be imported: This album has an illegal name and will be renamed to <i>%s</i> This album's owner (%s) hasn't been imported. Thumbnail %d of %d Thumbnail generation Thumbnails will be generated during migration Title Title: %s To enable URL Redirection under Apache webserver: Top level albums and albums whose parents are not selected will be imported into this album: Truncated: URL Redirection Username Users to import: You did not enter a path. You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the %sModules%s page to activate a Graphics Toolkit. You must choose something to import! You must specify a custom field name Your Gallery 1 will be converted from this character encoding into UTF-8: Project-Id-Version: Gallery: Migration 1.0.12
POT-Creation-Date: 2003-10-19 05:10+0200
PO-Revision-Date: 2008-03-01 23:45+0300
Last-Translator: Ser Moro <webber@morozov-sm.ru>
Language-Team: Russian <gallery-devel@lists.sourceforge.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);
X-Generator: KBabel 1.10.1
X-Poedit-Language: Russian
X-Poedit-Country: RUSSIAN FEDERATION
 %sПодзаголовок%s  %sэлемента %d%s был искажён . %sЗаголовок%s  %sэлемента %d%s был искажён  . (Значение по умолчанию аналогично подзаголовку, если не  установлено другое) <b>Примечание:</b> Перед тем как импортировать любые данные вы должны удостовериться, что Gallery 1 инсталлирована корректно. Вы можете проверить это, попробовав добавить фотографию в Gallery 1 через форму веб-интерфейса. Если вы уверены, что решили все проблемы можете продолжать дальше. Добавьте аналогичный блок <tt>.htaccess</tt> в папку с альбомами Gallery1, если вы также желаете перенаправить ссылки на файлы изображений и директорий альбомов. Обратите внимание, что эти перенаправления не будут активны до тех пор, пока изображения G1 не будут в дейсвительности удалены или перемещены. Удалите строку !-f для перенаправления в любом случае. Имя альбома Примечание альбома Заголовок альбома Альбомы, которые будут импортированы: Альбом с таким именем уже существует. Этот альбом будет переименован. Любые скрытые альбомы или элементы будут импортированы с ограниченными правами просмотра. Активизируйте модуль Скрытые элементы перед миграцией для того, чтобы импортировать все  ''скрытые'' элементы. Это нужно для того, чтобы они не были видны гостям до тех пор, пока они не введут точный адерс URL для этих элементов. Базовое имя файла Пустой Отменить Заголовок Кодировка исходного текста: Отметить всё Снять отметку со всего Подтверждение миграции Копирует целиком или частично существующую инсталляцию Gallery 1 в Gallery 2. В любом случае это не окажет влияния на ваши данные в Gallery 1. Создание миниатюр Дополнительное поле: Дополнительное поле: Дополнительные поля Для указанных выше дополнительных полей, которые будут импортированы в поля элементов, не будут созданы дубликаты дополнительных полей. Дополнительные поля будут импортированы Дополнительные поля не будут импортированы. Аквивизируйте модуль Дополнительные поля для выполнения этой функции. По умолчанию аналогично подзаголовоку, если не установлено дополнительное поле Удалить всё Удаление записей о переходах приведёт к тому, что старые адреса URL G1 выдадут HTTP Not Found ошибки вместо перенаправления на страницы G2. Удалить все записи? Описание Описание: %s Назначение: Не создавать в Gallery 2 дополнительные поля для полей, которые были выбраны для заголовка, подзаголовка или описания. Скачать файл '.htaccess'  Редактируйте или создайте файл с названием <tt>.htaccess</tt> с папке с вашей Gallery 1 и внесите указанный ниже текст в этот файл. Удалите rewrite rules из существующего файла. Перенаправления будут так же работать в папке с вашей Gallery 2 в случае, если Gallery 2 была установлена в папку, где ранее была G1. Однако, если вы также используете модуль URL Rewrite в Gallery 2, тогда активирйте модуль правил перенаправления G1 вместо использования блока, указанного ниже. Кодировка: %s Удостовертесь, что %s Apache модуль включен. Введите имя дополнительного поля Возникла ошибка при импорте %s Возникла ошибка при импорте %d альбома. Возникла ошибка при импорте %d альбомов. Возникла ошибка при импорте %d альбомов. Возникла ошибка при импорте %d пользователя. Возникла ошибка при импорте %d пользователей. Возникла ошибка при импорте %d пользователей. Пример: /var/www/albums URL перенаправление для G1.  Используйте эту опцию только в том случае, если G2 инсталлирована на том же сервере, что и G1 и вы выполнили импорт G1 с включенной опцией URL перенаправления. В противном случае, следуйте инструкциям в %sАдминистрирование Миграция%s. Путь к G1 G1-&gt;G2 Переходы G1-&gt;G2 переходы будут записаны для использования в URL перенаправлениях Gallery 2 содержит следующие поля для всех элементов и альбомов: заголовок, подзаголовок и текст описания,  который отображается вместе с миниатюрой элемента или альбома. Альбомы G1 так же содержат эти три элемента (но имена подзаголовка и описания поменяны местами). Элементы G1 содержат только имя файла и заголовок. Для элементов, импортируемых в G2: Галерея может перенаправлять старые адреса URL Gallery 1 к новым страницам Gallery 2. Скрытые элементы Если G2 инсталлирована в папку, где ранее находилась G1, необходимо удалить в G1 файл  'gallery_remote2.php' перед тем, как вы начнете использовать Gallery Remote для загрузки изображений в G2. Импорт Импортировать %s сейчас. Импорт альбомов Импорт завершён Импорт пользователей Импортировать дополнительные поля Импорт из Gallery 1 Импортировать ещё Импортировано %s  Импорт фотографий Импорт пользователей Инвертировать Заголовки элементов Следующие поля элементов будут импортированы из: Записи о переходах успешно удалены Импорт альбомов из Gallery 1 в Gallery 2 Миграция Альбомы импортированы не были Нет доступных пользователей Пользователи импортированы не были Обычно Галерея создает миниатюры, когда вы первый раз просматриваете элементы альбома, и затем сохраняет их для последующих просмотров. Если вы поставите галочку, миниатюры будут созданы во время импорта. Импорт будет продолжаться дольше, но первый просмотр альбома будет идти намного быстрее. Путь к папке с альбомами Gallery 1 Подготовить данные к импорту Последние использованные пути Записать переходы G1-&gt;G2 в процессе импортирования Выбрать Выберите альбомы и пользователей Выберите альбомы для импорта Выберите пользователей для импорта Установить описание из: Установить подзаголовок из: Установить заголовок из: Установить:  Источник: %d альбом успешно импортирован. %d альбома успешно импортированы. %d альбомов успешно импортированы. Успешно импортирован %d пользователь. Успешно импортировано %d пользователя. Успешно импортировано %d пользователей. Подзаголовок Введенный путь неверен. Здесь находится %d запись о переходе G1-&gt;G2 Здесь находятся %d  записи о переходах G1-&gt;G2 Здесь находятся %d записей о переходах G1-&gt;G2 Эти пользователи уже находятся в вашей галерее, и импортированы не будут: Данный альбом содержит неверное имя и будет переименован в <i>%s</i> Владелец этого альбома (%s) не был импортирован. Миниатюра %d из %d Создание миниатюр Миниатюры будут созданы во время миграции Заголовок Заголовок: %s Для разрешения URL перенаправлений на веб-сервере Apache: Альбомы верхнего уровня и альбомы, чьи родители не были выбраны, будут импортированы в этот альбом: Искажения: URL перенаправление Имя пользователя Пользователи, которые будут импортированы: Вы не ввели путь. У вас не активизирован ни один графический инструмент для работы с JPEG изображениями. Если вы импортируете сейчас, вы не будете иметь  миниатюр. Зайдите на страницу %sПлагины%s для активизиации графических инструментов. Вы должны выбрать что-либо для импорта! Вы должны указать имя дополнтельного поля Ваша Gallery 1 будет преобразована из этой кодировки в кодировку  UTF-8: 