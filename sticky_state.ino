void sticky_state() {
  //Controller code-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  int xAxis;
  int joystickLHX;
  
  if (Xbox.XboxReceiverConnected) {
    if (Xbox.Xbox360Connected[0]) {
      Serial.print(F("LeftHatX: "));
      Serial.print(Xbox.getAnalogHat(LeftHatX, 0));
      Serial.print("\t");

      joystickLHX = Xbox.getAnalogHat(LeftHatX, 0);
	  
      if ((joystickLHX > 6000) && (joystickLHX<20000) && (xAxis<servox_max)) {
        xAxis += 1;
      }

	  if ((joystickLHX < -6000) && (joystickLHX>-20000) && (xAxis>servox_min)) {
        xAxis -= 1;
      }
	  
	  if ((joystickLHX>20000) && (xAxis<servox_max)) {
        xAxis += 2;
      }
	  
	  if ((joystickLHX<-20000) && (xAxis>servox_min)) {
        xAxis -= 2;
      }
	  
	  servox.write(xAxis)
      Serial.print(xAxis);
      delay(10);
      Serial.println();

      if (Xbox.getButtonClick(XBOX, 0)) {
        Xbox.setLedMode(ROTATING, 0);
        Serial.print(F("Xbox (Battery: "));
        Serial.print(Xbox.getBatteryLevel(0)); // The battery level in the range 0-3
        Serial.println(F(")"));
      }
    }
  }
}
