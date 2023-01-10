//// Bismillah
// final upload 4Aug2022
//valve protection succcess// night edt :)
//// Made for Arduino Mega because ESP32 just got roasted :) :(
// By Abdul Sattar


///// sensors PINS
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

////// input pins // analog pins are used to read noise free
int basement_flowsensor_pin = A15;  /// not used when using interrupts; see below for int pin

int basement_tank_full_pin = A8;
//int basement_tank_empty_pin = A14;
int rooftop_tank_full_pin = A13; // not used

//// WASA Valve output
int basement_valve_pin = 7;

//// Motors PINS output
int basement_motor_pin = 6;
int rooftop_motor_pin = 10;


///// indicator LEDs
int no_flow_pause_LED = 4;
int valve_status_LED = 5;



//////////////////////////////////////////////////
/// Interrupt setup
const int flowSensor_inputPin = 21;
volatile int  Pulse_Count;
int  new_reading=0;
int  Liter_per_hour;
int updated_val = 0;
//unsigned long Current_Time=0;
//unsigned long   Loop_Time =0;



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////




///// sensors values
int basement_tank_full = 0;
int rooftop_tank_full = 0;

int basement_flowsensor = 0;
int basement_valve = 0;


int basement_motor_status = 0;
int rooftop_motor_status = 0;



//////////////// Other parameters..
int basetank_was_full_wait =0;
int flow_min_limit = 55;  // L/mint
int activate_basemotor_pause_action = 0;

//////////////////////////// following method of declarration not working
//unsigned long motor_pause_time15min = (1000*60);  /// in milli-seconds
//unsigned long motor_pause_time30min = (1000)*(60)*30;  /// in milli-seconds
//unsigned long motor_pause_time45min = (1000)*(60)*45;  /// in milli-seconds
//unsigned long motor_pause_time60min = (1000)*(60)*60;  /// in in milli-seconds


//  Serial.print("time variable = "); Serial.println(motor_pause_time_mint(30),DEC); delay(1000);  //// delcare separately in func ; this works




void setup(){


  Serial.begin(9600);

pinMode(flowSensor_inputPin, INPUT);
attachInterrupt(2, Detect_Rising_Edge, RISING);   /// D21 pin on Mega is Interrupt02

pinMode(basement_tank_full_pin, INPUT);
//pinMode(rooftop_tank_full_pin, INPUT);
pinMode(basement_flowsensor_pin, INPUT);

pinMode(basement_valve_pin, OUTPUT);
//pinMode(rooftop_motor_pin, OUTPUT);
pinMode(basement_motor_pin, OUTPUT);


pinMode(no_flow_pause_LED, OUTPUT);
pinMode(valve_status_LED, OUTPUT);



///Start with motors off in state
  digitalWrite(basement_motor_pin, LOW);
//  digitalWrite(rooftop_motor_pin, LOW);
  digitalWrite(basement_valve_pin, LOW);

  basement_motor_status = 0;
  rooftop_motor_status = 0;


pinMode(13, OUTPUT);
digitalWrite(13,LOW );
Serial.println("\n\n\n\n Bismillah!! System active in 4 seconds!\n\n\n\n");


digitalWrite(13,HIGH);
digitalWrite(no_flow_pause_LED,HIGH);
digitalWrite(valve_status_LED,LOW);

delay(2000); // wait for 5secs; just brace up!



pinMode(13, OUTPUT);
digitalWrite(13,HIGH);
digitalWrite(no_flow_pause_LED,HIGH);
digitalWrite(valve_status_LED,LOW);
delay(300);
digitalWrite(13,LOW);
digitalWrite(no_flow_pause_LED,LOW);
digitalWrite(valve_status_LED,HIGH);
delay(300);
digitalWrite(13,HIGH);
digitalWrite(no_flow_pause_LED,HIGH);
digitalWrite(valve_status_LED,LOW);
delay(300);
digitalWrite(13,LOW);
digitalWrite(no_flow_pause_LED,LOW);
digitalWrite(valve_status_LED,HIGH);
delay(300);
digitalWrite(13,HIGH);
digitalWrite(no_flow_pause_LED,HIGH);
digitalWrite(valve_status_LED,LOW);
delay(300);
digitalWrite(13,LOW);
digitalWrite(no_flow_pause_LED,LOW);
digitalWrite(valve_status_LED,HIGH);
delay(300);
digitalWrite(13,HIGH);
digitalWrite(no_flow_pause_LED,HIGH);
digitalWrite(valve_status_LED,LOW);
delay(300);
digitalWrite(13,LOW);
digitalWrite(no_flow_pause_LED,LOW);
digitalWrite(valve_status_LED,HIGH);
delay(300);
digitalWrite(valve_status_LED,LOW);
digitalWrite(no_flow_pause_LED,LOW);


//
//
//while(1){
//  digitalWrite(basement_motor_pin, LOW);
//  digitalWrite(rooftop_motor_pin, LOW);
//  digitalWrite(basement_valve_pin, LOW);  
//  }



//#define Debug_code; ////just comment this to deactivate ifdef code and uncomment to start ifdef code..

#ifdef Debug_code



 while(1){ 
//  Serial.print("in while 1 loop! readBase_tank()="); Serial.println(readBase_tank()); delay(100);
//  Serial.print("in while 1 loop! readRoof_tank()="); Serial.println(readRoof_tank()); delay(100);
//  Serial.print("in while 1 loop! readFlowSensor()= "); Serial.println(readFlowSensor()); delay(100); // based on analog input value
//  Serial.print("in while 1 loop! readFlowSensor()= "); Serial.println(readFlowSensor_Intrpt()); delay(100);

//  Serial.print("time variable = "); Serial.println(motor_pause_time_mint(30),DEC); delay(1000);


  Serial.println(" \n ");delay(500);
  }

#endif

} ///void setup end

void loop(){

Activate_Base_Motor_Control();

//Serial.print("basement_motor_status="); Serial.println(basement_motor_status);

//Activate_Roof_Motor_Control();



///// Print control status
//print_system_status();

}
