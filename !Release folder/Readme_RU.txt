RESTool v1.8 by romalu86

--- Список поддерживаемых проектов:

- игры на базе движков AS1\ZS1:
Alien Shooter (PC NonSteam);
Alien Shooter (Steam);
Alien Shooter - Last Hope (Steam\Mobile);
Alien Shooter - Lost World (Theseus Mobile);
Alien Shooter - World (Mobile);
Alien Shooter - Revisited;
Theseus (PC);
Zombie Shooter 1 (PC Steam & NonSteam);
Zombie Shooter 1 (Mobile);
Crazy Lunch (PC\Mobile);
Chacks Temple,
Дорога на Кхон-Ка-Ду (Steamland или Locoland).

- игры на базе движков AS2\ZS2:
Alien Shooter - Revisited;
Alien Shooter 2 - Gold;
Alien Shooter 2 - Vengeance;
Alien Shooter 2 - Reloaded;
Alien Shooter 2 - Conscription;
Alien Shooter 2 - The Legend (Steam\Mobile);
Alien Shooter 2 - Tower Defence (Steam\Mobile);
Alien Shooter 2 - Reloaded (Mobile);
Alien Shooter 2 - New Era (Steam);
Zombie Shooter 2 (Steam\NonSteam);
Objects Extended Project.

--- Как использовать?

Программа на текущий момент работает через консоль. Для распаковки файла необходимо запустить RESTool, и следовать инструкциям на экране.

После того как процес декомпилияции будет завершен, появится папка "unpacked_inis" с файлами:  OBJ.ini, WEAP.ini, CNST.ini и SFX.ini.

Также возможен обратный процесс компиляции. В папке с программой присутствует все необходимое (компилятор и настроенные батники !MakeRES !MakeDB_OE_old, !MakeDB_OE_new, !MakeRES_Locoland).
При запуске одного из доступных батников программа берет файлы "OBJ.ini, WEAP.ini, CNST.ini, SFX.ini.", и производит обратную компиляцию.
Если компиляция прошла успешно в коренвой директории появится файл test.res или test.db.

--- Словарь переменных:

Программа поддерживает возможность дополнять базу неизвестных переменных которые распаковываются в формате INT (Простые числа - 1, 2, 4 и т.д.) или шестнадцатеричной системе счисления (пример 0x1000). Вся информация находится в файле constants.ini, новые значения добавляются по аналогии с другими.

--- Режимы работы программы:
"as1_engine" - Работает с Alien Shooter 1, Alien Shooter 1 Last Hope, Alien Shooter - Lost World (Theseus Mobile)

"theseus_pc" - Работает с Theseus (PC)

"as1world" - Работает с Alien Shooter 1 - World

"zs1" - Работает с Zombie Shooter 1 (PC)

"zs1_mobile" - Работает с Zombie Shooter 1 (Mobile).

"as2_original" - Работает с Золотым и Vengeance изданиями

"as2_addons" - Работает с Перезагрузкой, Воинским призывом (он же Захват), Zombie Shooter 2 Teaser, Objects Extended Project (Старые версии до патча 1.1.0.6)

"zs2_engine" - Работает с Zombie Shooter 2, Alien Shooter: Revisited

"as2legend_engine" - Работает с Alien Shooter 2 Legend & TD (Steam and Mobile), Alien Shooter 2 New Era, Alien Shooter 2 Reloaded (Mobile)

"oe_engine" - Работает с Objects Extended Project (начиная с патча 1.1.0.6)

"crazylunch" - Работает с Crazy Lunch

"chackstemple" - Работает с Chacks Temple

"locoland" - Работает с Steamland (Locoland в Steam)
