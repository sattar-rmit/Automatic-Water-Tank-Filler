////Bismillah


void print_system_status(){


 while(1){ 
  Serial.print("readBase_tank_full()="); Serial.println(readBase_tank());
  Serial.print("readRoof_tank_full()="); Serial.println(readRoof_tank()); 
  Serial.print("readFlow_tank()="); Serial.println(readFlow());
  Serial.println(" \n ");
  }




  
}
