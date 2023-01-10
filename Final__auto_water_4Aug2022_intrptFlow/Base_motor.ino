///Bismillah

//// if the tank is full; wait for 30 mints before starting motor
//// if tank is not full; run motor and check water flow.
/// if water not there for 3 mints; wait for 15 mints and check again,




void Activate_Base_Motor_Control(){

unsigned long wait_for_sometime =  0;
static unsigned long  this_loop_time = 0; // static: it is initialized once
static unsigned long  this_loop_time1 = 0; // static: it is initialized once


 
//// setting basement tank conditions

 goto_top:
 
        basement_tank_full = readBase_tank();

  ////// If tank is full
  
if (basement_tank_full == 1 && basetank_was_full_wait==0){ // basement tank is full so close valve and turn off basement motor
  delay(1000);
  digitalWrite(basement_motor_pin, LOW);   // turn off basement motor; and before valve
  basement_motor_status = 0;
  delay(3000); // be patient
  digitalWrite(basement_valve_pin, HIGH); // Activate the valve which means close it. Valve is normally open!
// set status
Serial.println("\n \n Base Tank full. Base motor OFF, Valve closed.");
digitalWrite(valve_status_LED,HIGH); //works as base tank full
digitalWrite(no_flow_pause_LED,LOW);

 basetank_was_full_wait =1;

// this_loop_time = millis () + motor_pause_time_In_seconds(5);  /// short time for debugging
 this_loop_time = millis() + motor_pause_time_In_minutes(1);  /// actual time to use; pause time is used on top of valve own mechanical pause(ball rolling up and down) to prevent motor flickering

  }

  
//////////////////////////////////////////////////////////////////////////////////////////////////

if(basetank_was_full_wait == 1){
        if (this_loop_time <= millis ()) // wait untill motor pause time is elapsed
            {   
                 Serial.println("Alert! Base motor pause after base tank became full is  OVER !!!  System will check base tank again NOW...");
                 delay(2000);
                 basetank_was_full_wait =0; // wait time over; no need to repeat this loop; this_loop_time has to be updated from full tank routine above.

                 digitalWrite(basement_valve_pin, LOW); // 
                 delay (1000);
                 goto  goto_top;   /// wait time over; go check if tank is full; if not it will automatically proceed to !!basement_tank_full routine
            }




            digitalWrite(no_flow_pause_LED,LOW);
            
            Serial.println("\n Alert! Base motor pause after base tank became full is  ACTIVE !!! ");
            Serial.println("The pause time will refresh if tank is continuously full!");
            Serial.print("this_loop_time = "); Serial.println(this_loop_time);
            
            delay(3000);

           /////////valve protection// release valve if there is no flow
            /////////valve protection// release valve if there is no flow
            /////////valve protection// release valve if there is no flow

            basement_flowsensor = readFlowSensor_Intrpt();
            if(basement_flowsensor <= 8){  // if slight flow detected because of WASA direct pressure then skip to ELSE statement
            digitalWrite(basement_valve_pin, LOW); // deactivate the valve if flow is low or not detected... no need for continuously on..
            Serial.print("flow=  "); Serial.println(basement_flowsensor);
          }

            
            else{
              delay(5000);
              digitalWrite(basement_valve_pin, HIGH); 
            }


            delay(1000);


//////// newly added: 23 june 2022
// since since mechanical sensor has its own mechanism of ball rolling up and down which created delay and prevent flickering;
// the base tank full motor pause action above becomes unnecessary;
// even then delay of ~10 seconds is put in between lvl sensor read; to prevent motor flickering
// following code will technically skip above wait time and rely more on lvl sensor going low=tank empty.

      basement_tank_full = readBase_tank();
        ////// If tank is empty  
      if (basement_tank_full == 0){
      Serial.println("\n \n ***************** \n TANK EMPTY \n ***************** \n Motor turning ON now by skipping pause time!!");
      basetank_was_full_wait =0;
      
      digitalWrite(valve_status_LED,LOW); //works as base tank full
      digitalWrite(no_flow_pause_LED,LOW);
      delay(500);
      digitalWrite(valve_status_LED,HIGH); //works as base tank full
      digitalWrite(no_flow_pause_LED,HIGH);
      delay(500);
      digitalWrite(valve_status_LED,LOW); //works as base tank full
      digitalWrite(no_flow_pause_LED,LOW);
      delay(500);
      digitalWrite(valve_status_LED,HIGH); //works as base tank full
      digitalWrite(no_flow_pause_LED,HIGH);
      delay(500);
      digitalWrite(valve_status_LED,LOW); //works as base tank full
      digitalWrite(no_flow_pause_LED,LOW);
      
      delay(3000);       
      }
            
            
            goto  goto_top; //         
}





///////////////////////////////////////////////////////////////////////////////////////////
  
  if (basement_tank_full ==0 && activate_basemotor_pause_action ==0){ // this happens  after 15 mints of delay ;; activate_basemotor_pause_action ==0 is global variable


    digitalWrite(basement_valve_pin, LOW); // Deactivate the valve which means open it. Valve is normally open!
    delay(2000); //be patient with motors
    digitalWrite(rooftop_motor_pin, LOW);  /// turn off rooftop motor to reduce load of both motors running simultaneously
    rooftop_motor_status = 0;
    delay(2000); //be patient with motors
    digitalWrite(basement_motor_pin, HIGH);  /// turn on base motor 
    basement_motor_status = 1;

//         Serial.println("in second if loop!");  delay(2000);
Serial.println(" \n Base tank filling now. Base motor on; valve open!");
 digitalWrite(valve_status_LED,LOW);
digitalWrite(no_flow_pause_LED,LOW);
      
      //// check flow sensor here to prevent basement motor from running empty!!
       basement_flowsensor = readFlowSensor_Intrpt();
       Serial.print(" readFlow_tank()="); Serial.println(basement_flowsensor);

       // If flow is less than some val then turn off base motor after 3mints; or check time is kept 3mints; if no water try after 15mints. 
       // Take care, if flowsensor has little fan then it might show some reading
       if(basement_flowsensor <= flow_min_limit){  // flow_min_limit in main tab

        
        /////////////////////////////////////////////PAUSE TIME /////////////////////////////////////////////
//          wait_for_sometime = millis() + motor_pause_time_In_seconds(10); // for testing; in seconds
          wait_for_sometime = millis() + motor_pause_time_In_seconds(60); /// should be 1 to 3 mints; motor will keep checking for this much time for water flow if it is less than threshhold
                
                //////////////////////////////////////////////
                Serial.print(" readFlow_tank()="); Serial.println(basement_flowsensor);
                Serial.println("Alert: Water flow rate below required threshold; Loop will check flow for 3 minutes. \n If less than threshold for 3 mints, base motor will pause for 15 mints and will check flow again.");
                //////////////////////////////////////////////
                
             while(millis() <= wait_for_sometime) {  /// while 3 mints have not passed; do following
                   basement_flowsensor = readFlowSensor_Intrpt(); // update flowsensor val;

                   Serial.println("Alert: Checking flow while in 3 mint loop.");
                   Serial.print(" readFlow_tank()="); Serial.println(basement_flowsensor);
                   
                   digitalWrite(valve_status_LED,LOW); //works as base tank full

 
                   delay(200);

                   digitalWrite(no_flow_pause_LED,LOW);
                   delay(60);
                   digitalWrite(no_flow_pause_LED,HIGH);
                   delay(60);
                   digitalWrite(no_flow_pause_LED,LOW);
                   delay(60);
                   digitalWrite(no_flow_pause_LED,HIGH);
                   delay(60);
                   digitalWrite(no_flow_pause_LED,LOW);
                   delay(200);


                   /// also check tank full in between....////
                   basement_tank_full = readBase_tank();
                   if (basement_tank_full == 1){
                    basetank_was_full_wait =0; /// make this zero so that top routine may be executed..
                    goto goto_top;
                   }
                   //////////
                   
                   if(basement_flowsensor >= flow_min_limit){ /// so if in between 3mints while checking for water; if flow is detected then exit loop to the main. otherwise activae motor pause
                         Serial.println("Alert: While in 3 mints flow check loop; Flow higher than threshold detected. Program will now start basement motor control from beginning.");
                         delay(800);
                         basetank_was_full_wait =0;
                         activate_basemotor_pause_action =0;
                         goto goto_top; /// exit to main loop because good flow of water detected.
                          } 
                   }
                   
                   //// if loop is here it means 3 mints passed, water flow not detected; assign 15min wait time and make one of if (!basement_tank_full && !activate_basemotor_pause_action) conditons false
                  
                   Serial.println("Alert: Flow check time of 3 mint is over; Base Motor will now pause for 15 mints before checking water flow again. "); delay(2000);
                   
                   digitalWrite(basement_motor_pin, LOW);   // turn off basement motor; and but keep valve open
                   basement_motor_status = 0;
                   digitalWrite(basement_valve_pin, LOW); // Deactivate the valve which means open it. Valve is normally open!
                   digitalWrite(valve_status_LED,LOW); //works as base tank full
                  
             /////////////////////////////////////////////PAUSE TIME /////////////////////////////////////////////
//                   this_loop_time1 = millis () + motor_pause_time_In_seconds(15);   // for testing
                   this_loop_time1 = millis () + motor_pause_time_In_minutes(40);   /// if water flow below threshold continuously for 1 to 3 mint(as set above); motor will pause for this much time and try filling again.
                   activate_basemotor_pause_action =1;
       }

  }////




////////////////////////////////////////////////////////////////////////
  if (basement_tank_full==0 && activate_basemotor_pause_action==1){ // introduce a wait of 15mints if tank is not full and water not flowing

          Serial.println("Alert: Base motor did not detect water flow for 3 mints. It will check again for water after 15 mints (or after var: this_loop_time1 ).");
          delay(2000);
          
          digitalWrite(no_flow_pause_LED,HIGH);

          
           /// also check tank full in between....////
                   basement_tank_full = readBase_tank();
                   if (basement_tank_full == 1){
                    goto goto_top;
                   }
                   //////////
                   
          if (this_loop_time1 <= millis ()){ //when it is true; run following
          activate_basemotor_pause_action =0; // self-invalidation; make motor pause false as 15 mints have passed
          }
  }////
////////////////////////////////////////////////////////////////////////
    
/////////////////////////////////////////////////////////////////   
 
 
 goto_end_of_loop:   basement_tank_full = readBase_tank(); // just extra instruction to maintain label.
  

  }// main loop

  
