/*
 * GrowController v0.1 
 * release date 23/04/2018
 * Hour: 4:20Pm
 * Board: Arduino Uno R3
 * Features: Controlar horas de luz de um growroom/growbox com suporte a FarReds.
 */

//configuração de variaveis/Não mexer./////////////
unsigned long int periodMillison, periodMillisoff, periodSecson, PeriodHourson, PeriodHoursoff;
unsigned long int PeriodFarReds, PeriodFarRedsmillis;
unsigned long startMillis;
unsigned long currentMillis;
byte control = 0, enbFarReds = 0; //Bit de controle, não mexer
//////////////////////////////////////////////////

//Pinos
const int relay = 8;  //pino do relé da iluminação.
const int farReds = 7;//pino das far reds.


void setup() { //configuração do fotoperiodo, respeitar o periodo de 24hrs
PeriodHourson = 16; //horas de luz ligada 
PeriodHoursoff = 8; //horas de luz desligada
enbFarReds = 1;     //Ligar ou desligar FarReds, 1 = ON 0 = OFF!
PeriodFarReds = 20; //minutos de duração das Far Reds, colocar entre 15 e 30 min
digitalWrite(relay, HIGH); //definir estado inicial da luz, High = on, Low = off
startMillis = millis();//Não mexer.
}

//Não editar se não souber o que está fazendo.

void loop() {
  periodMillison = PeriodHourson*3600000;
  periodMillisoff = PeriodHoursoff*3600000;
  PeriodFarRedsmillis = PeriodFarReds*60000;
  
  currentMillis = millis();
  
  if(digitalRead(relay) && currentMillis - startMillis >= periodMillison)
  {
    millisTimeroff();
    if(enbFarReds){
      FarRedson();
      control = 1; 
    }

  }
  else if(!digitalRead(relay) && currentMillis - startMillis >= periodMillisoff)
  {
   millisTimeron(); 
  }
  if(control &&  currentMillis - startMillis >= PeriodFarRedsmillis){
    FarRedsoff();
    control = 0;
  }
}

void millisTimeron(){
digitalWrite(relay, HIGH);
startMillis = currentMillis;
  
}
void millisTimeroff(){
  digitalWrite(relay, LOW);
  startMillis = currentMillis;
}
void FarRedson(){
  digitalWrite(farReds, HIGH);
}
void FarRedsoff(){
  digitalWrite(farReds, LOW);  
}
