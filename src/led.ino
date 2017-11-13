/*
 * Project led
 * Description:
 * Author:
 * Date:
 */

 #include "rgb-controls/rgb-controls.h"
 using namespace RGBControls;

 // RGB led on PWN pins
 Led led(D1, D2, D3); // red_pin = D0, green_pin = D1, blue_pin = D2

 // We will be using D1 to control our LED
 int ledPin = D0;

 // Our button wired to D0
 int buttonPin = D5;

// D0, D1, D2, D3, => analogWrite para el photon
 int pinRed = D1;                // LED connected to digital pin D1
 int pinGreen = D2;              // LED connected to digital pin D1
 int pinBlue = D3;               // LED connected to digital pin D1

 //int analogPin = A0;            // potentiometer connected to analog pin A0
 int colRed = 0;                // variable to store the read value
 int colGreen = 0;              // variable to store the read value
 int colBlue = 0;               // variable to store the read value


 // List of CheerLights color names
 const int NUM_COLORS=15;
 String colorName[] = {
     "black","none","red","pink","green","blue","cyan","white",
     "warmwhite","oldlace","purple","magenta","yellow","orange",
     "gold"};

 // Map of RGB values for each of the Cheerlight color names
 int colorRGB[][3] = {
                         0,  0,  0,  // "black"
                         0,  0,  0,  // "none"
                         255,  0,  0,  // "red"
                         255,192,203,  // "pink"
                           0,255,  0,  // "green"
                           0,  0,255,  // "blue"
                           0,215, 75,  // "cyan",
                         255,255,255,  // "white",
                         255,223,223,  // "warmwhite",
                         255,223,223,  // "oldlace",
                         128,  0,128,  // "purple",
                         255,  0,255,  // "magenta",
                         255,255,  0,  // "yellow",
                         255, 49,  0,  // "orange"};
                         240, 240,  60}; // "gold"};


 void setup()
 {
   // For input, we define the
   // pushbutton as an input-pullup
   // this uses an internal pullup resistor
   // to manage consistent reads from the device
   pinMode( buttonPin , INPUT_PULLUP); // sets pin as input
   // We also want to use the LED
   pinMode( ledPin , OUTPUT ); // sets pin as output

   pinMode(pinRed, OUTPUT);     // sets the pin as output
   pinMode(pinGreen, OUTPUT);     // sets the pin as output
   pinMode(pinBlue, OUTPUT);     // sets the pin as output


   // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("led",ledToggle);
   Particle.function("setcolor",setColor);
   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.
   // For good measure, let's also make sure both LEDs are off when we start:
   digitalWrite(ledPin, LOW);

 }

void loop() {
    // find out if the button is pushed
    // or not by reading from it.
    int buttonState = digitalRead( buttonPin );
    // remember that we have wired the pushbutton to
    // ground and are using a pulldown resistor
    // that means, when the button is pushed,
    // we will get a LOW signal
    // when the button is not pushed we'll get a HIGH
    // let's use that to set our LED on or off
    if( buttonState == LOW ) {
        // turn the LED On
        //digitalWrite( ledPin, HIGH);
    } else{
        // otherwise
        // turn the LED Off
        //digitalWrite( ledPin, LOW);
    }
}



int setColor(String command)    {
    // Look through the list of colors to find the one that was requested
    for(int iColor = 0; iColor < NUM_COLORS; iColor++)
    {
        if(command == colorName[iColor]) {
            // When it matches, look up the RGB values for that color in the table,
            // and write the red, green, and blue values.
            RGB.control(true);
            RGB.color(colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2]);

            analogWrite(pinRed,colorRGB[iColor][0]);
            analogWrite(pinGreen,colorRGB[iColor][1]);
            analogWrite(pinBlue,colorRGB[iColor][2]);
            return 0;
        }
    }

    return -1;
}



// We're going to have a super cool function now that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Particle.function earlier.
int ledToggle(String command) {
     /* Particle.functions always take a string as an argument and return an integer.
     Since we can pass a string, it means that we can give the program commands on how the function should be used.
     In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
     Then, the function returns a value to us to let us know what happened.
     In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
     and -1 if we received a totally bogus command that didn't do anything to the LEDs.
     */
     if (command=="on") {
         digitalWrite(ledPin,HIGH);
         return 1;
     }
     else if (command=="off") {
         digitalWrite(ledPin,LOW);
         return 0;
     }
     else {
         return -1;
     }
}
