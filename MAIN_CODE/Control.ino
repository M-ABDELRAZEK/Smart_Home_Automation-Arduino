/*
To Control Prpject Via Mobile Phone
*/

int prevCommand; 
void remoteControl()
{
  RemoteXY_Handler();

  dtostrf(T, 0, 1, RemoteXY.temp); // To Display Temperature In celsius In Application ==> Transfer Double Type To String To be Displayed In Text Box
  dtostrf(H, 0, 1, RemoteXY.hum); // To Dispaly Humidity In Application 
  // sprintf(RemoteXY.temp, "%d %s", T, "C");
  // sprintf(RemoteXY.hum, "%d %s", H, "%");

  digitalWrite(PIN_GREENLED, (RemoteXY.GREEN_LED == 0) ? LOW : HIGH); // Switch For Green LED
  digitalWrite(PIN_REDLED, (RemoteXY.RED_LED == 0) ? LOW : HIGH); // Switch For Red LED
  digitalWrite(PIN_WHITELED, (RemoteXY.WHITE_LED == 0) ? LOW : HIGH); // Switch for White LED
  digitalWrite(PIN_BUZZER, (RemoteXY.BUZZER == 0) ? LOW : HIGH); // Button For Buzzer 
  digitalWrite(PIN_LOCK, (RemoteXY.Lock == 0) ? LOW : HIGH); // To Lock & Unlock The Door 
  
  if(RemoteXY.Lock != prevCommand)
  {
    if(RemoteXY.Lock == 1) // If The Lock Is Open
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ACCESS OBTAINED");
      digitalWrite(PIN_GREENLED, HIGH);

      int ms = RemoteXY.POS * 20 + 500; // Duty Cycle For Servo Motor Pulse Width Modulation
      myservo.writeMicroseconds(ms); // Servo Motor Rotation

      RemoteXY_delay(1000);

      digitalWrite(PIN_GREENLED, LOW);

      int prevCommand = 1;
      
      RemoteXY_delay(1000);
    
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ACCESS DENIED");
      
      digitalWrite(PIN_REDLED, HIGH);
      digitalWrite(PIN_BUZZER, HIGH);

      RemoteXY_delay(1000); // Sound alarm for 1 second
      
      digitalWrite(PIN_REDLED, LOW);
      digitalWrite(PIN_BUZZER, LOW);

      RemoteXY_delay(1000);
      
      prevCommand = 0; 
    }
  }
  LcdInitialization();
}
