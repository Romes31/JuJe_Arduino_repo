/* Perso Project 
 * ---------------
 *
 * Communication with an other Arduino Board
 * 3 pins : CS, CLK and Datas
 *
 */
 
 //Declaration
 int com_CS = 13;              // CS connected to pin
 int com_CLK = 12;             // CLK connected to pin
 int com_DATAS = 11;           // Datas connected to pin
 int command_button = 8;      // Button connected to pin
 int button_state = 0;         // STate of the button
 int green_led = 10;           // Green Led 
 int yellow_led = 9;          // Yellow led
 int red_led = 7;
 int temp = 0;
 
 
 //Setup Part
 void setup()
 {
   // Data com pins
   pinMode(com_CS, OUTPUT);
   pinMode(com_CLK, OUTPUT);
   pinMode(com_DATAS, OUTPUT);
   pinMode(command_button, INPUT);
   
   // Com Initialization
   digitalWrite(com_CS, HIGH);
   digitalWrite(com_CLK, LOW);
   digitalWrite(com_DATAS, LOW);
   
   // LED Initialization
   pinMode(green_led, OUTPUT);
   pinMode(yellow_led, OUTPUT);
   pinMode(red_led, OUTPUT);
   
   // Serial Com Initialization
   Serial.begin(9600);
   Serial.print("***** Welcome to the Main Program ***** \n");
   Serial.print("Press the push button\n");
 }
 
 // Loop Part
 void loop()
 {
     button_state = 0;
     //Read the state of the button
     button_state = digitalRead(command_button);
     
     // CHeck the button State
     if (button_state == 1)
     {
       // Send the frame
       temp = send_frame();
     }
     else
     {
       // Do nothing
     }
 }
 
 // Function
 
 void send_frame(void)
 {
   // Declaration
   int incoming_serial = 0;
   int serial_bit[3];
   int cpt_bit = 0;
   
   digitalWrite(green_led, LOW);
   digitalWrite(red_led, LOW);
   
   Serial.print("Quel Hardware : 0- Moteur; 1- Led; 2- Bip\n");
   while (Serial.available() == 0);
   incoming_serial = Serial.read();
   incoming_serial = incoming_serial - 48;
   Serial.print("Datas received : ");
   Serial.println(incoming_serial, DEC);
   switch (incoming_serial)
   {
     case 0:
       serial_bit[0] = LOW;
       serial_bit[1] = LOW;
       break;
     case 1:
       serial_bit[0] = HIGH;
       serial_bit[1] = LOW;
       break;
     case 2:
       serial_bit[0] = LOW;
       serial_bit[1] = HIGH;
       break;
     default:
       Serial.print("ERROR ! The value is not in the range\n");
       digitalWrite(red_led, HIGH);
       continue;
        
   }
   Serial.print("What is your command ? 1- ON; 0- OFF\n");
   while (Serial.available() == 0);
   incoming_serial = Serial.read();
   incoming_serial = incoming_serial - 48;
   Serial.print("Datas received : ");
   Serial.println(incoming_serial, DEC);
   switch (incoming_serial)
   {
     case 0:
       serial_bit[2] = LOW;
       break;
     case 1:
       serial_bit[2] = HIGH;
       break;
     default:
       Serial.print("ERROR! The value is not in the range\n");
       digitalWrite(red_led, HIGH);
       continue;
   }
   digitalWrite(yellow_led, HIGH);
   digitalWrite(com_CS, LOW);
   while (cpt_bit < 3)
   {
     digitalWrite(com_DATAS, serial_bit[cpt_bit]);
     digitalWrite(com_CLK, HIGH);
     delay(1000);
     digitalWrite(com_CLK, LOW);
     delay(1000);
     cpt_bit ++;
   }
   digitalWrite(com_CS, HIGH);
   digitalWrite(green_led, HIGH);
   digitalWrite(yellow_led, LOW);
 }

