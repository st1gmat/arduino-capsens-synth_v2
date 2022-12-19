# Синтезатор на сенсорах
## Комплектующие 
+ Провода "п-п" × 24
+ Макетная плата × 1
+ Arduino UNO × 1
+ Резисторы на 1 мОМ × 8
+ Динамик × 1
+ Кнопка × 1

## Capacitive Sensor
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

## Сборка. Код + схема Arduino.
Чтобы сконструировать датчик, потребуется резистор (номиналом от 100 кОм до 50 МОм на свое усмотрение, однако я использую резистор на 1МОм для того, чтобы датчик считывал при нажатии), стоящий между отправляющим и принимающим (сенсорным) контактами. Принимающий контакт – это крайняя часть датчика. Датчик можно усовершенствовать, подключив к принимающему контакту кусочек алюминиевой фольги (при помощи провода). Можно покрыть бумагой, пластиком или другим изоляционным материалом – это обеспечит наилучший диапазон значений, определяемых датчиком.

Нажатия на кнопку отвечают за октаву в которой воспроизводятся ноты:
```c++
  if (btn.click()) {
    if (++mode >= MODE_AM) mode = 0;
  }
```
Предварительно в void loop() данные с сенсоров записываются в массив:
```c++
  long total[7];
  int idx = 0;
  // Ставим чувствительность сенсоров
  long total1 =  cs_2_3.capacitiveSensor(3000); total[idx++] = total1; 
  long total2 =  cs_2_4.capacitiveSensor(3000); total[idx++] = total2; 
  long total3 =  cs_2_5.capacitiveSensor(3000); total[idx++] = total3; 
  long total4 =  cs_2_6.capacitiveSensor(3000); total[idx++] = total4; 
  long total5 =  cs_2_7.capacitiveSensor(3000); total[idx++] = total5; 
  long total6 =  cs_2_8.capacitiveSensor(3000); total[idx++] = total6; 
  long total7 =  cs_2_9.capacitiveSensor(3000); total[idx++] = total7; 
```
Далее в switch, относительно состояние мода(номера нажатия на кнопку), массив с данными передается в нужную нам функцию:
```c++
  switch (mode) { //режим воспроизведения звука
      case 0: octave_small(total);
        break;
      case 1: octave_1(total);
        break;
      case 2: octave_2(total);
        break;
      case 3: octave_3(total);
        break;
    }
    
    //когда рука не касается сенсора ничего не воспроизводится
    if (total1<=500  &  total2<=500  &  total3<=500 & total4<=500  &  total5<=500  &  total6<=500 &  total7<=500/* &  total8<=500*/)
      noTone(speaker);
```
В функции через **tone()** воспроизводится нота соответсвующая проводу + в serial port выводится сама нота, которая считывается через DataFromArduino.py:
```c++
void octave_small(long total[]) { // МАЛАЯ ОКТАВА
  // Serial.println("\nsmall octave!\n");
  //когда касаемся рукой сенсора, динамик воспроизводит звук
  if (total[0] >500) { tone(speaker,131);Serial.println(131);} // ДО
  if (total[1] >500) { tone(speaker,147);Serial.println(147);}// РЕ
  if (total[2] >500) { tone(speaker,165);Serial.println(165);}// МИ
  if (total[3] >500) { tone(speaker,175);Serial.println(175);}// ФА
  if (total[4] >500) { tone(speaker,196);Serial.println(196);}// СОЛЬ
  if (total[5] >500) { tone(speaker,220);Serial.println(220);}// ЛЯ
  if (total[6] >500) { tone(speaker,247);Serial.println(247);}// СИ
  // if (total[7] >500) { tone(speaker,262); // ДО 1АЯ
```


Вот так выглядит схема:
![sketch_МП](https://user-images.githubusercontent.com/97258310/208322738-8a14aaff-c7e2-4181-aef6-16e3ccb47c1e.png)
В итоге должна получиться вот такая __махина__:
![ZghuIEF - Imgur](https://user-images.githubusercontent.com/97258310/208322773-da2b7f1d-0b79-41a9-a469-960b79f090f6.jpg)

## Советы по сборке
+ Еще раз повторюсь, если вы хотите, чтобы срабатывало при нажатии, а не за км от датчика, то используйте резистор на 1 МОм (можно и больше).
+ С резисторами с меньшим сопротивлением будет действовать на большем расстоянии(10-15см)

##### P.S. Кому интересно, тот может почитать подробнее, как работает библиотека [CapacitiveSensor.h](https://playground.arduino.cc/Main/CapacitiveSensor/)

## О кривом интерфейсе на Python
В файле DataFromArduino.py я создал простецкий интерфейс с помощью модуля tkinter и связь c ArduinoUNO через serial. 
Сначала получаем список доступных COM-портов и инициализируем экземпляр объекта:
```python
ports = serial.tools.list_ports.comports()
serialObj = serial.Serial()
```
Далее создаю окно для нашего GUI. Фон пусть будет серым:
```python
root = Tk()
root.config(bg='grey')
```
Создаю функцию инициализрующую serial port:
```python
def initComPort(index):
    currentPort = str(ports[index])
    comPortVar = str(currentPort.split(' ')[0])
    print(comPortVar)
    serialObj.port = comPortVar
    serialObj.baudrate = 9600
    serialObj.open()
```
Кнопки для выбора порта:
```python
for onePort in ports:
    comButton = Button(root, text=onePort, font=('Calibri', '13'), height=1, width=45, command =  functools.partial(initComPort, index = ports.index(onePort)))
    comButton.grid(row=ports.index(onePort), column=0)
```
Tkinter Canvas с выводом данных получаемых от Arduino:

```python
dataCanvas = Canvas(root, width=600, height=400, bg='white')
dataCanvas.grid(row=0, column=1, rowspan=100)
```
Решил сделать scrollbar, чтобы, если окно данных выходит за пределы окна GUI, мы могли прокрутить его до самого низа, чтобы увидеть новые данные:
```python
vsb = Scrollbar(root, orient='vertical', command=dataCanvas.yview)
vsb.grid(row=0, column=2, rowspan=100, sticky='ns')

dataCanvas.config(yscrollcommand = vsb.set)
```
Привизяываем это все к GUI:
```python
dataFrame = Frame(dataCanvas, bg="white")
dataCanvas.create_window((10,0),window=dataFrame,anchor='nw')
```
Создаем функцию, которая позволит нам циклически проверять наличие новых данных от нашего Arduino:
```python
def checkSerialPort():
    if serialObj.isOpen() and serialObj.in_waiting:
        recentPacket = serialObj.readline()
        recentPacketString = recentPacket.decode('utf').rstrip('\n')
        note = freq_to_note(recentPacketString)
        Label(dataFrame, text=note, font=('Calibri','13'), bg='white').pack()
```
Конвертирую Гц из serial port'a в дефолтные ноты по этой формуле:
![image](https://user-images.githubusercontent.com/97258310/208324749-2909a629-a353-4ec0-ba90-7856018e18e9.png)
```python
def freq_to_note(freq):
    freqe = int(freq)
    notes = ['A', 'A#', 'B', 'C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#']
    note_number = 12 * math.log2(freqe / 440) + 49  
    note_number = round(note_number)  
    note = (note_number - 1 ) % len(notes)
    note = notes[note]
    return note
```
Бесконечный цикл, который будет запускать наше окно GUI и проверять новые данные в фоновом режиме:
```python
while True:
    root.update()
    checkSerialPort()
    dataCanvas.config(scrollregion=dataCanvas.bbox("all"))
```
В итоге должно получиться так:
![image](https://user-images.githubusercontent.com/97258310/208325030-500cc474-c286-4327-96ee-2444472383d0.png)

[bruh](https://r.mtdv.me/xJsAWIXPkH)





