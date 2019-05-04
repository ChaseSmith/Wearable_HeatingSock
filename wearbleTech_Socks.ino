  /*
  Written by Chase Smith
  For temperature detecting self heating socks Project
  2/25/19

  Derived from:
  Heating Pad Hand Warmer Blanket Code Example

  Hardware Connections:
  - Mofset (heating pad) = 3;
  - temperature sensor 1 = 9;
  - temperature sensor 2 = 10;
 

  Usage: 
  1. Hit the switch to power
  2. Temperature sensor will power heating pads when they 
     detect temperatures below a certain level.
  3. When temperature rises to acceptable level
     turn the heating pads off
  4. Repeat
 */

int fetPin = 3; 
int tempSens1 = 9;
int tempSens2 = 10;

void setup() {                
// INITIALIZE THE PINS
  pinMode(tempSens1, INPUT);  
  pinMode(tempSens2, INPUT); 
  pinMode(fetPin, OUTPUT);  

  Serial.begin(9600);
}

void loop() {
// FIRST READ IN TEMPERATURES FROM SENSORS
  long rawTemp1; 
  float voltage1;
  float fahrenheit1;
  float celsius1;
  
  long rawTemp2; 
  float voltage2;
  float fahrenheit2;
  float celsius2;
  float avgTemp;

  digitalWrite(ledPin, HIGH); //turn on LED to indicate socks are on

  rawTemp1 = analogRead(tempSens1); // Read the raw 0-1023 value of temperature into a variable.  
  voltage1 = rawTemp1 * (3.3 / 1023.0); // max voltage 3.3, 4.2 if using USB power
  celsius1 = (voltage1 - 0.5) * 100;
  fahrenheit1 = (celsius1 * 9.0 / 5.0) + 32.0;

  rawTemp2 = analogRead(tempSens2);   
  voltage2 = rawTemp2 * (3.3 / 1023.0); 
  celsius2 = (voltage2 - 0.5) * 100;
  fahrenheit2 = (celsius2 * 9.0 / 5.0) + 32.0;

  //Print info to monitor from temperature sensor 1
  Serial.print("Fahrenheit 1: "); 
  Serial.print(fahrenheit1);
  //Print info to monitor from temperature sensor 2
  Serial.print("       Fahrenheit 2: "); 
  Serial.println(fahrenheit2);


  // WEIGHTED AVERAGE OF TEMP SENSORS to focus more on the toes
  avgTemp = 0.4 * (fahrenheit1) + 0.6 * (fahrenheit2);

  // ACTIVATE HEATING PADS BASED ON TEMPERATURE
  if( avgTemp < 90 && avgTemp > 80 ) //kinda cold
  {
    analogWrite(fetPin, 85); //33% duty cycle
    Serial.println("kinda cold");
  }
  
  if(avgTemp < 80 && avgTemp > 70 ) //fairly cold
  {
    analogWrite(fetPin, 170); //66% duty cycle
    Serial.println("cold");
  }

  if(avgTemp < 80) //very cold
  {
    analogWrite(fetPin, 255); //100% duty cycle
    Serial.println("very cold");
  }


  delay(500);  //delays for 0.5 second (decide on this later)
  
}
