/*
Gas & Smoke Sensor Function
*/

void gas_sensor()
{
  {
    short gas_threshold = 300;
    short MQ5_Value = analogRead(MQ5PIN);
    // short MQ5_Value = digitalRead(MQ5PIN); For Proteus Simulation

    if(MQ5_Value >= gas_threshold){
      
      //digitalWrite(BUZZER_REDLED, HIGH);
      
      digitalWrite(PIN_BUZZER_ALERT, HIGH);
      digitalWrite(PIN_REDLED, HIGH);
      sprintf(RemoteXY.Alert, "%s", "GAS DETECTED");
    } else {
      
      //digitalWrite(BUZZER_REDLED, LOW);
      
      digitalWrite(PIN_REDLED, LOW);
      digitalWrite(PIN_BUZZER_ALERT, LOW);
      //sprintf(RemoteXY.Alert, "%s", "");
    }
  }
}