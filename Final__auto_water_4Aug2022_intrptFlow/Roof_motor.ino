void Activate_Roof_Motor_Control(){

static unsigned long  this_loop_time1 = 0; // static: it is initialized once
static unsigned long  this_loop_time2 = 0; // static: it is initialized once


//// setting roof tank conditions

exit_rooftank_main:
          
          rooftop_tank_full = readRoof_tank();


if (rooftop_tank_full == 1){
   this_loop_time1 = millis () + motor_pause_time_In_seconds(15); /// should be 60mints;; keep refreshing this_loop_time1 parameter if roof tank is full
   digitalWrite(rooftop_motor_pin, !LOW);  /// turn off rooftop motor ;
   rooftop_motor_status = 0;

   Serial.println("\n Roof tank is full; Motor will pause for 60 mints. \n");
   delay(1000);
}

///////////////////////////////////////////////////
while( millis() <= this_loop_time1){
Serial.println("\n Roof tank full motor in 60mint pause time loop.  \n"); delay(1000);
}
//////////////////////////////////////////////////




if ( millis() >= this_loop_time1){
//// if program is here; it means tank is not full since last one hour!! so try filling it.

    //// if (basetank_was_full_wait && basement_motor_status==0){   /// tank_was_full_wait variable has more consistency and basement motor is not running then run roof tank motor


     if (basement_motor_status==0){   /// priority to basemotor; if it is off then proceed to roof motor; otherwise when it ll be off and roof tank will not be full; this will automtly run.

                            // but this has draw back of not knowing basement tank.


    
      rooftop_tank_full = readRoof_tank();
      
            if (rooftop_tank_full == 0){

              
              /// run for 15 mints
              delay(2000); //be patient with motors
              digitalWrite(basement_motor_pin, !LOW);  /// turn off base motor; just double make sure. 
              basement_motor_status = 0;
              delay(2000);
              digitalWrite(rooftop_motor_pin, !HIGH);  /// turn off rooftop motor to reduce load of both motors running simultaneously
              rooftop_motor_status = 1;

              Serial.println("\n Roof motor ON; Base motor OFF; Roof tank not full.");
              
              // and monitor roof tank at the same time
              this_loop_time2 = millis () + motor_pause_time_In_seconds(10); /// shoould be 15 mints; actually this is roof motor running time; not pause time.

                    while( millis() <= this_loop_time2 ){ /// here rooftop motor is stuck in 15mint loop; it will exit either at 15mints over or roof tank becomes full.
                      rooftop_tank_full = readRoof_tank(); // monitor roof tank if it get full;
                        delay(2000);
                        Serial.println("Alert: Roof motor running; waiting for roof tank to become full  or 15mints to elapse.");
                        if (rooftop_tank_full == 1){
                            Serial.println("Alert: Roof tank full before 15mints; Turning roof motor OFF.");
                            goto exit_rooftank_main;
                                                                    
                        }
                    }


              
            }
       
      }

}
 

}//// main bkt
