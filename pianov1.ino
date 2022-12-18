//  CapacitiveSensor Library.
#include <CapacitiveSensor.h>
//Вспомогательная библиотке для кнопок
#include <EncButton.h>


#define BTN_PIN 13    // кнопка смены режима
#define MODE_AM 4    // количество режимов
#define speaker 11   // пин динамика

EncButton<EB_TICK, BTN_PIN> btn; // eb_tick по дефолту 0
byte mode = 0; //переменная для переключания по модам
//EncButton<EB_TICK, BTN_S> btn_s; // eb_tick по дефолту 0
//два прина: один отправляет сигнал, другой принимает
CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4);         
CapacitiveSensor   cs_2_5 = CapacitiveSensor(2,5);     
CapacitiveSensor   cs_2_6 = CapacitiveSensor(2,6);     
CapacitiveSensor   cs_2_7 = CapacitiveSensor(2,7);      
CapacitiveSensor   cs_2_8 = CapacitiveSensor(2,8);         
CapacitiveSensor   cs_2_9 = CapacitiveSensor(2,9);  
CapacitiveSensor   cs_2_10 = CapacitiveSensor(2,10);     

void print(long total[])
{
  Serial.print(total[0]);
  Serial.print("\t");
  Serial.print(total[1]);
  Serial.print("\t");
  Serial.print(total[2]);
  Serial.print("\t");
  Serial.print(total[3]);
  Serial.print("\t");
  Serial.print(total[4]);
  Serial.print("\t");
  Serial.print(total[5]);
  Serial.print("\t");
  Serial.print(total[6]);
  Serial.print("\n");
   // Serial.print("\t");
  // Serial.println(total8);
}

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
  
}
void octave_1(long total[]) { // ПЕРВАЯ ОКТАВА
  // Serial.println("\nfirst octave!\n");
  if (total[0] >500) { tone(speaker,261); Serial.println(261);}
  if (total[1] >500) { tone(speaker,293);Serial.println(293);}
  if (total[2] >500) { tone(speaker,329);Serial.println(329);}
  if (total[3] >500) { tone(speaker,349);Serial.println(349);}
  if (total[4] >500) { tone(speaker,392);Serial.println(392);}
  if (total[5] >500) { tone(speaker,440);Serial.println(440);}
  if (total[6] >500) { tone(speaker,493);Serial.println(493);}
  // if (total[7] >500) { tone(speaker,262);
}
void octave_2(long total[]) { // ВТОРАЯ ОКТАВА
  // Serial.println("\nsecond octave!\n");
  if (total[0] >500) { tone(speaker,523);Serial.println(523);}
  if (total[1] >500) { tone(speaker,587);Serial.println(587);}
  if (total[2] >500) { tone(speaker,659);Serial.println(659);}
  if (total[3] >500) { tone(speaker,698);Serial.println(698);}
  if (total[4] >500) { tone(speaker,784);Serial.println(784);}
  if (total[5] >500) { tone(speaker,880);Serial.println(880);}
  if (total[6] >500) { tone(speaker,987);Serial.println(987);}
}
void octave_3(long total[]) { // ТРЕТЬЯ ОКТАВА
  // Serial.println("\nsecond octave!\n");
  if (total[0] >500) { tone(speaker,1046);Serial.println(1046);}
  if (total[1] >500) { tone(speaker,1174);Serial.println(1174);}
  if (total[2] >500) { tone(speaker,1318);Serial.println(1318);}
  if (total[3] >500) { tone(speaker,1396);Serial.println(1396);}
  if (total[4] >500) { tone(speaker,1568);Serial.println(1568);}
  if (total[5] >500) { tone(speaker,1760);Serial.println(1760);}
  if (total[6] >500) { tone(speaker,1975);Serial.println(1975);}
}
void setup()                    
{
  cs_2_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
}

void loop()                    
{
  long start = millis(); // таймер начала
  
  btn.tick();
  if (btn.click()) {
    if (++mode >= MODE_AM) mode = 0;
  }
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
  // long total8 = cs_2_10.capacitiveSensor(3000); total[idx]  = total8; 


  

  // if(Serial.available() > 0)
  // {
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
  // }

  delay(10);
}
