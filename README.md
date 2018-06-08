![PROJECT_PHOTO](https://github.com/AlexGyver/POV_display/blob/master/proj_img.jpg)
# POV вращающийся дисплей своими руками
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
Вращающийся дисплей
Особенности:
- Собран из доступных компонентов, на адресной ленте WS2812
- Разрешение 10 градусов
- Плавный разгон и торможение (уменьшение нагрузки на редуктор и муфту)
- Воспроизведение 9-кадровой анимации (Arduino NANO/UNO/MINI)
- На Arduino MEGA влезет около 80 кадров анимации
- Подробности в видео: https://youtu.be/RL3j-3fyWM8
<a id="chapter-1"></a>
## Папки
**ВНИМАНИЕ! Если это твой первый опыт работы с Arduino, читай [инструкцию](#chapter-4)**
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **POV_display** - прошивка
- **images** - исходники картинок
- **schemes** - схемы подключения

<a id="chapter-2"></a>
## Схемы
![SCHEME](https://github.com/AlexGyver/POV_display/blob/master/schemes/scheme1.jpg)
![SCHEME](https://github.com/AlexGyver/POV_display/blob/master/schemes/scheme2.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
### Ссылки оставлены на магазины, с которых я закупаюсь уже не один год
### Почти все компоненты можно взять в магазине WAVGAT по первым ссылкам
* Arduino NANO с ногами http://ali.pub/2kendk http://ali.pub/2kenec
* Arduino NANO без ног http://ali.pub/2kenfp http://ali.pub/2kenif
* Адресная лента http://ali.ski/CjdQCL
	- Black PCB / White PCB - цвет подложки ленты, чёрная / белая. В видео была чёрная
	- 1m/5m - длина ленты в метрах (чтобы заказать 2 метра, берите два заказа 1m, очевидно)
	- 30/60/74/96/100/144 - количество светодиодов на 1 метр ленты. В видео использовалась лента 60 диодов на метр
	- IP30 лента без влагозащиты
	- IP65 лента покрыта силиконом
	- IP67 лента полностью в силиконовом коробе
	- **Лента как на видео: White PCB 144. Берите IP30**
* Датчик Холла http://ali.pub/2keo7w или такой http://ali.pub/2keo8v
* Мотор http://ali.pub/2kenw8
* Повышайка http://ali.pub/2kenyd
* Мосфет модуль (вместо голого фета) http://ali.pub/2keoa8
* Штекер https://www.chipdip.ru/product/sp20-6.35s-n
* Гнездо https://www.chipdip.ru/product/st-008s-04
* Блок питания 5V - любой зарядник для смартфона
* Транзисторы, конденсаторы, кнопки и резисторы - в ЛЮБОМ магазине радиодеталей

## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить библиотеки в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
* Подключить Ардуино к компьютеру
* Запустить файл прошивки (который имеет расширение .ino)
* Настроить IDE (COM порт, модель Arduino, как в статье выше)
* Настроить что нужно по проекту
* Нажать загрузить
* Пользоваться  

## Настройки в коде
    #define NUM_LEDS 72     // количество светодиодов
    #define BRIGHTNESS 200  // яркость
    #define MOTOR_MAX 160   // скорость мотора (0-255)
    #define RES 10          // разрешение (каждые n градусов)
    #define COEF 0.3        // коэф. сглаживания частоты оборотов
    #define PODGON 1.3      // коэф. подгона (у, блет)
    #define OFFSET 240      // сдвиг по углу (0-360)
    #define NUM_FRAMES 8    // количество фреймов анимации
    #define FRAME_RATE 30   // количество перерисовок между сменой кадра
    
    #define PIN 4           // пин ленты
    #define MOS 3           // пин мосфета (мотора)
    #define BTN1 8          // пин кнопки 1
    #define BTN1_G 6        // земля кнопки 1
    #define BTN2 11         // пин кнопки 2      
    #define BTN2_G 9        // земля кнопки 2 
	
<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Вылетает ошибка загрузки / компиляции!
О: Читай тут: https://alexgyver.ru/arduino-first/#step-5

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту
В: Подойдёт ли обычная RGB лента?  
О: Нет.

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)