/*
For ArduTooth Application
*/

void temp_hum()
{
  // Send Humidity Data To Mobile Application
  BT.print(H);
  BT.print(" %");
  BT.print(",");

  // Send Tempreture (Celsius) Data To Mobile Application
  BT.print(T);
  BT.print(" C");
  BT.print(",");

  // Send Tempreture (Fahrenheit) Data To Mobile Application
  BT.print(F);
  BT.print(" F");
  BT.print(";");

  delay(20);
}