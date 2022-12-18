# Синтезатор на сенсорах
## Комплектующие 
+ Провода "п-п" × 24
+ Макетная плата × 1
+ Arduino UNO × 1
+ Резисторы на 1 мОМ × 8
+ Динамик × 1
+ Кнопка × 1

## Capacative Sensor
### Предназначение

**Библиотека CapacitiveSensor** позволяет сделать из двух (или более) контактов Arduino емкостный датчик, способный определять электроемкость человеческого тела. Для создания такого датчика понадобятся резистор и провод. Будучи настроенным на наибольшую чувствительность, этот датчик начнет определять близость руки или человеческого тела в нескольких сантиметрах от себя.

Измерение электроемкости применяется в ситуациях, когда желательно, чтобы человек не прикасался к определенной поверхности. Таким образом, при помощи Arduino, библиотеки CapacitiveSensor и изоляционного материала (пластика, дерева, керамики и пр., но не металла) можно сделать так, чтобы датчик чувствовал прикосновение за полсантиметра от себя. Кроме того, это позволяет замаскировать датчик.

Емкостный датчик, покрытый бумагой или другим изолятором, также может работать в качестве неплохого датчика давления (с примерно экспоненциальным откликом). В некоторых приложениях он даже превосходит даже силоизмерительные резисторы.

### Особенности ###

+ Для каждого сенсорного датчика требуется только один провод, подключенный к нему.
+ Может быть скрыт под любым неметаллическим материалом.
+ Можно легко использовать вместо кнопки.
+ Может обнаружить руку с нескольких сантиметров.

## Как работает сенсор?
Функция CapasitiveSensor() переключает отправляющий контакт платы в новое состояние, а затем ждет, пока принимающий контакт не примет то же состояние, что и отправляющий контакт. Чтобы синхронизировать изменение состояния у принимающего контакта, внутри цикла while() увеличивается специальная переменная. После этого функция возвращает значение переменной (в произвольных единицах измерения).

## Сборка. Как работает Arduino?
Чтобы сконструировать датчик, потребуется резистор (номиналом от 100 кОм до 50 МОм на свое усмотрение, однако я использую резистор на 1МОм для того, чтобы датчик считывал при нажатии), стоящий между отправляющим и принимающим (сенсорным) контактами. Принимающий контакт – это крайняя часть датчика. Датчик можно усовершенствовать, подключив к принимающему контакту кусочек алюминиевой фольги (при помощи провода). В большинстве приложений датчик лучше покрыть бумагой, пластиком или другим изоляционным материалом – это обеспечит наилучший диапазон значений, определяемых датчиком, и позволит сделать так, чтобы пользователи не касались металлической фольги.

Вот так выглядит схема:
![sketch_МП](https://user-images.githubusercontent.com/97258310/208322738-8a14aaff-c7e2-4181-aef6-16e3ccb47c1e.png)
В итоге должна получиться вот такая __махина__:
![ZghuIEF - Imgur](https://user-images.githubusercontent.com/97258310/208322773-da2b7f1d-0b79-41a9-a469-960b79f090f6.jpg)

## Советы по сборке
+ Еще раз повторюсь, если вы хотите, чтобы срабатывало при нажатии, а не за км от датчика, то используйте резистор на 1 МОм (можно и больше).
+ С резисторами с меньшим сопротивлением будет действовать на большем расстоянии(10-15см)

##### P.S. Кому интересно, то может почитать, как работает библиотека [CapacitiveSensor.h](https://playground.arduino.cc/Main/CapacitiveSensor/)

##О кривом интерфейсе на Python
В файле DataFromArduino.py я создал простецкий интерфейс с помощью модуля tkinter и связь c ArduinoUNO через serial. 
Сначала получаем список доступных COM-портов и инициализируем экземпляр объекта:
```python
ports = serial.tools.list_ports.comports()
serialObj = serial.Serial()
```
