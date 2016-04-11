/*Control 1-axis prototype using XBOX 360 controller
  Joystick:     |   Servo:
  5V  -> 5V     |   5V  -> 5V
  GND -> GND    |   GND -> GND
  VRX -> A1     |   CTL -> 9

  Jack Forney
*/

#include <Servo.h> //include servo library
#include <XBOXRECV.h> // include XBox Reciever Library

Servo servox;  //create servo object

USB Usb;
XBOXRECV Xbox(&Usb);

int joystickLHX;
int joystickLHY;
int xAxis;
int val;    // variable to read the value from the analog pin

int servox_min = 49;
int servox_max = 109;

void setup()
{
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\n System Engaged"));// makes sure servos are detached at the beginning of startup just in case control relay was not set off
  servox.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
 Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        Serial.print(F("LeftHatX: "));
        Serial.print(Xbox.getAnalogHat(LeftHatX, i));
        Serial.print("\t");

        xAxis = Xbox.getAnalogHat(LeftHatX, i);
        if((xAxis>7500)||(xAxis<-7500)){
          xAxis = map(xAxis, -40000, 40000, 49, 109);
          servox.write(xAxis);  // set servo to mapped value
        }
        else{
          servox.write(79);
        }
        Serial.print(xAxis);
        delay(10);
        Serial.println();
        

        if (Xbox.getButtonClick(L3, i))
          Serial.println(F("L3"));
          servox.write(49);
          
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
          Xbox.disconnect(i);
        }
      }
    }
  }
  /*val = analogRead(xAxis);          // read joystick x-axis value
    Serial.println(val);              // serial reading for debug only
    val = map(val, 0, 1023, 49, 109); // scale around 79 as equilibrium +/- 30
    servox.write(val);                // set servo to mapped value
    delay(15);                       // waits for the servo to get there
  */
}
