//wersja dla 1 gracza
//led załączany stanem niskim                             czyli +5V - rezystor 330 Ohm - led - port Uno
//naciśnięcie przycisku podaje 0 czyli LOW (masę) na port Arduino   czyli +5V - rezystor 10 kOhm - port Uno i 1 styk przycisku 2 styk przycisku - masa
//do pomiaru czasu w milisekundach używamy millis(), a dla pomiaru w mikrosekundach możemy użyć micros();

#include <Timers.h>                       //by wykryć falstart nie możemy się posłużyć delay więc pomoża nam ta biblioteka
Timer mojTimer;                           //deklaracja timera

#include <Bounce2.h>                      //biblioteka obsługująca drgania styków przycisku i jego odczyt
Bounce przycisk1 = Bounce(); 

//wykorzystane piny Arduino
#define buttonPin   9
#define ledPin      12
#define buzzerPin   3

unsigned long reakcja=0;
unsigned long start=0;
boolean falstart=false;
boolean audio=true;

//----------------------------------------------------------------------------------------------------------------------
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);       //jeśli przycisk jest podciągnięty do +5V przez rezystor to wystarczy INPUT   
  przycisk1.attach(buttonPin);
  przycisk1.interval(5);                  //5 ms na drganie styków
  
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

//----------------------------------------------------------------------------------------------------------------------
void loop() {
  int k=1; falstart=false;
  
  Serial.println("Czekam");
  do  { przycisk1.update(); }while(!przycisk1.fell());   //czekamy na przycisk i program się powtarza  

//------------------------------------------------------------------------------------
//3 2 1 START - odliczanie
  while(k<4)
    {  
      mojTimer.begin(random(400,700));
      while(!mojTimer.available())                        //jeśli nie minął losowy czas sprawdzamy ew. falstart
        {
          przycisk1.update();               
          if(przycisk1.fell()) {falstart=true; break;}
        }
       digitalWrite(ledPin, LOW);
       for(int x=0; x<3; x++) 
         { if(audio) tone(buzzerPin,550+k*50);            //coraz wyższy ton
           mojTimer.begin(250);

          while(!mojTimer.available())                    //jeśli nie minął losowy czas sprawdzamy ew. falstart
            {
            przycisk1.update();               
            if(przycisk1.fell()) {falstart=true; break;}
            }
           digitalWrite(ledPin, HIGH);
           if(audio) noTone(buzzerPin);
           if(falstart) break;
         } 
         if(falstart) break;         
          switch(k)
          {
            case 1:
             Serial.println("Uwaga!");          
            break;  
            case 2:
             Serial.println("Do startu!");    
            break; 
            case 3:
             Serial.println("Gotowi!");
             break; 
            default:
             break;
          }
        
      k++;
    }
//------------------------------------------------------------------------------------
  //losowa przerwa i kontrola ewentualnego falstartu
  mojTimer.begin(600+random(200,1000)*2);
  while(!mojTimer.available() && !falstart)    //jeśli nie minął losowy czas
    {
        if(digitalRead(buttonPin)==0) {falstart=true; break;}
      }

//------------------------------------------------------------------------------------
  //mierzymy refleks
  if(falstart)     //jeśli był falstart
    {  start=0;   
       reakcja=-1;
       if(audio) { for(k=0; k<80; k+=4) { tone(buzzerPin, 900-k*10); delay(75+k*5); } }
       noTone(buzzerPin);
     }
   else            //nie było falstartu 
     {  
      if(audio) tone(buzzerPin, 1000, 300);
      Serial.println("Start!");
      digitalWrite(ledPin, LOW);

//------------------------------------------------------------------------------------
      start=micros();                                         //czas początkowy

       while (digitalRead(buttonPin)) ;                       //czekamy dopóki przycisk HIGH (HIGH=1 więc prawda)

      //pomiar czasu
      reakcja=(micros()-start);                               //obliczenie czasu reakcji
      while (!digitalRead(buttonPin)) ;                       //czekamy na zwolnienie przycisku
     } 
//------------------------------------------------------------------------------------
  if(!falstart)   Serial.println("Wynik:"+String(reakcja));  
  else            Serial.println("-1");    

  do  { przycisk1.update(); } while(!przycisk1.fell());        //czekamy na przycisk i program się powtarza  

//------------------------------------------------------------------------------------
  //koniec rozgrywki
  digitalWrite(ledPin, HIGH);
  
}
