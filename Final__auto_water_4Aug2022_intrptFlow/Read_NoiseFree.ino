/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

int readBase_tank(){
    int temp=0;
    for(int i=0;i<50;i++){
      if (analogRead(basement_tank_full_pin) >= 550) {temp += 1;}
//    temp = temp + int(digitalRead(basement_tank_full_pin));
    delay(1);  

    }
//    Serial.println(temp);

    if(temp>45)
    temp=1;
    else
    temp=0;
   
    return temp;
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

int readRoof_tank(){
       int temp=0;
    for(int i=0;i<50;i++){
      if (analogRead(rooftop_tank_full_pin) >= 550) {temp += 1;}
//    temp = temp + int(digitalRead(basement_tank_full_pin));
    delay(1);  

    }
//    Serial.println(temp);

    if(temp>45)
    temp=1;
    else
    temp=0;
   
    return temp;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
int readFlow(){
unsigned int temp=0;
    for(int i=0;i<20;i++){
//      if (analogRead(basement_flowsensor_pin) >= 550) {temp += 1;}
    temp +=  analogRead(basement_flowsensor_pin);
    delay(1);  
    }

    temp /= 20;
//  while(1) { Serial.println(temp); delay();}

//    if(temp>500)
//    temp=1;
//    else
//    temp=0;
   
    return temp;
    
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////
unsigned long motor_pause_time_In_minutes(unsigned long minutes){

  const unsigned long a=1000;
  const unsigned long b=60;
  const unsigned long c=a*b;

unsigned long ans = minutes*c;

  return ans;
}

unsigned long motor_pause_time_In_seconds(unsigned long secs){

  const unsigned long a=1000;
  

unsigned long ans = secs*a;

  return ans;
}
