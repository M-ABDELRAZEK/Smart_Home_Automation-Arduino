/*
RFID RC522 Card Function
*/

/*
void RFID() {
  // Check for new card and read NUID efficiently
  if (!rfid.PICC_IsNewCardPresent()) {
    
    return;  // No new card, exit function
  }

  if (!rfid.PICC_ReadCardSerial()) {
    // Handle failed NUID read (optional: display error message, retry)
    return;
  }

  // Efficiently copy NUID into NUID_PICC array (consider using memcpy)
  memcpy(NUID_PICC, rfid.uid.uidByte, sizeof(rfid.uid.uidByte));

  // Access control and door operation logic
  if (GrantAccess(BlueID, NUID_PICC) == true) {
    // Access granted, unlock door
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS OBTAINED");

    digitalWrite(RELAY_GREENLED, HIGH);  // Unlock the solenoid

    delay(100);

    // Use a dedicated servo library for smooth motion control (optional)
    for (int pos = 0; pos <= 90; pos += 1) {
      ser.write(pos);  // Send servo position command
      delay(5);        // Delay between position updates
    }

    delay(4000);  // Hold door open for 4 seconds

    for (int pos = 90; pos >= 0; pos -= 1) {
      ser.write(pos);
      delay(5);
    }

    delay(100);

    digitalWrite(RELAY_GREENLED, LOW);

    LcdInitialization();

  } else {
    // Access denied, display message and sound alarm
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS DENIED");

    digitalWrite(BUZZER_REDLED, HIGH);

    delay(1000);  // Sound alarm for 1 second

    digitalWrite(BUZZER_REDLED, LOW);
  }

  delay(20);  // Debounce delay before next scan (optional)

  LcdInitialization();
}

bool GrantAccess(const byte* authorizedID, const byte* cardID) {
  // Implement access control logic using byte-by-byte comparison
  for (int i = 0; i < sizeof(rfid.uid.uidByte); i++) {
    if (authorizedID[i] != cardID[i]) 
    {
      return false;  // Access denied if any byte doesn't match
    }
  }
  return true;  // Access granted if all bytes match
}
*/