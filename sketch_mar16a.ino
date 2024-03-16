// Temperature Sensing using LM35 temperature Sensor With Arduino

float degreebelow30=61628.75;   //Preload timer value 61628.75 for 250 milliseconds 
float degreeabove30=57722.5;    //Preload timer value 57722.5 for 500 milliseconds 
float timer_value_sec;          //To store initial timer value 
void setup() {
  Serial.begin(9600);                 //Begin serial communication at 9600 baud rate
  
  pinMode(LED_BUILTIN,OUTPUT);        //Onboard LED in Ardiuno
  
  noInterrupts();                     // disable all interrupts

  TCCR1A = 0;                         //Timer1 is initialized.
  
  TCCR1B = 0;                         //Timer1 is initialized.

  timer_value_sec=degreebelow30;      //Intial timer value starts with 250 milliseconds

  TCNT1 = timer_value_sec;            // preloader timer value is set (Initially as 61628.75 for 250 milliseconds).

  TCCR1B |= (1 << CS10)|(1 << CS12);  // Prescaler value 1024 is set in the TCCR1B register

  TIMSK1 |= (1 << TOIE1);             // enable timer overflow interrupt ISR

  interrupts();                       // enable all interrupts
}
ISR(TIMER1_OVF_vect)                  // interrupt service routine for overflow

{

  TCNT1 = timer_value_sec;           // preload timer value with 250 milliseconds

  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);  //Turns LED ON and OFF

}


void loop() {
  
  // Get the voltage reading from the LM35
  int sensorvalue = analogRead(A0);  
   // Convert that reading into voltage
  float voltage=sensorvalue*(5.0/1024.0);
   // Convert the voltage into the temperature in Celsius
  float temperature=voltage*100;                 //1v=100Celsuius
  // Print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("\xC2\xB0");  // shows degree symbol
  Serial.print("C");
  Serial.println();
  delay(1000); // wait a second between readings
  
  if(temperature>30)
  {
    timer_value_sec = degreeabove30;             //Preload value 57722.5 for 500 milliseconds 
  }
  else
  {
    timer_value_sec = degreebelow30;            //Preload value 61628.75 for 250 milliseconds 
  }
}
