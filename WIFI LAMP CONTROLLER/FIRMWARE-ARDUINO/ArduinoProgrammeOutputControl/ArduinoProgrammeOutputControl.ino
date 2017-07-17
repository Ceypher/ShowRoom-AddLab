String action;
String ledDizaine;
String ledUnite;

int numeroLed;
int etat;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
  
  for (int pinLed=2;pinLed<20;pinLed++){
       pinMode(pinLed,OUTPUT);
       digitalWrite(pinLed,HIGH);
      }
 

}

void loop() {
  
  while ((Serial.available()>0)) {  
    delay(10);
  }
  action = Serial.readString();

  //------------------ Action led individuelles

  if (action.length()==12){ // Pour les actions /leds/01/0
    
    ledDizaine = action[6];
    ledUnite = action[7];
    
    numeroLed = (ledDizaine.toInt())*10 + (ledUnite.toInt());
    numeroLed=numeroLed-1; //car on part de la sortie led 2 cablé sur le 3

    etat = !(String(action[9])).toInt();

    digitalWrite(numeroLed,etat);
    
  }

   //------------------ Action led collectives
  
  else if(action.length()==13){ //Pour les actions /leds/all/1
    
    etat = !(String(action[10])).toInt();
    for (int numeroLed=2;numeroLed<20;numeroLed++){
      digitalWrite(numeroLed,etat);
      }
    }

  //------------------ Action communication raté

    
   else{
    Serial.print(action);
    Serial.flush();
    delay(10);
   }
   
}
