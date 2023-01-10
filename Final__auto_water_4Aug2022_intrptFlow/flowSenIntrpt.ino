
//
////////////////////////////////////////
//int readFlowSensor_Intrpt(){
//
//if(new_reading==1){
//        new_reading=0;
//        updated_val= readFlowSensor_Int ();
//        return updated_val;
//}
//
//else 
//return updated_val;
//  
//}
//




//////////////////////////////////////////
int readFlowSensor_Intrpt ()    
{

unsigned long   Current_Time = millis();
static unsigned long    Loop_Time=Current_Time;

Current_Time = millis();
Loop_Time=Current_Time;
Pulse_Count = 0;


while(Current_Time <= (Loop_Time + 500)){ 
     
     Current_Time = millis(); // update cur time

   if(Current_Time >= (Loop_Time + 500))
   {
//       Loop_Time=Current_Time;
       
//      Liter_per_hour = (Pulse_Count * 60 / 7.5);  /// original per 60 min

      Liter_per_hour = ((Pulse_Count) * 60 / 7.5);  

      new_reading=1;
//      return Liter_per_hour;
//      Serial.print(Liter_per_hour, DEC);
//      Serial.println(" Liter/hour");
   }

}   //while loop



  if(new_reading==1){
        new_reading=0;
        updated_val = Liter_per_hour;
        return updated_val;
  }

  else return updated_val;



        
}



//////////////////////////////////////////////////////////////////
void Detect_Rising_Edge ()
{ 
   Pulse_Count++;
   
} 
