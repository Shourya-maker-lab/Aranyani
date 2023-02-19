/*_________________________________________________________________________________________________________________________________________
|__________________________________________________________________________________________________________________________________________|
|                                                                                                                                          |
|         .8.          8 888888888o.            .8.          b.             8 `8.`8888.      ,8'    .8.          b.             8  8 8888  |
|        .888.         8 8888    `88.          .888.         888o.          8  `8.`8888.    ,8'    .888.         888o.          8  8 8888  |
|       :88888.        8 8888     `88         :88888.        Y88888o.       8   `8.`8888.  ,8'    :88888.        Y88888o.       8  8 8888  |
|      . `88888.       8 8888     ,88        . `88888.       .`Y888888o.    8    `8.`8888.,8'    . `88888.       .`Y888888o.    8  8 8888  |
|     .8. `88888.      8 8888.   ,88'       .8. `88888.      8o. `Y888888o. 8     `8.`88888'    .8. `88888.      8o. `Y888888o. 8  8 8888  |
|    .8`8. `88888.     8 888888888P'       .8`8. `88888.     8`Y8o. `Y88888o8      `8. 8888    .8`8. `88888.     8`Y8o. `Y88888o8  8 8888  |
|   .8' `8. `88888.    8 8888`8b          .8' `8. `88888.    8   `Y8o. `Y8888       `8 8888   .8' `8. `88888.    8   `Y8o. `Y8888  8 8888  |
|  .8'   `8. `88888.   8 8888 `8b.       .8'   `8. `88888.   8      `Y8o. `Y8        8 8888  .8'   `8. `88888.   8      `Y8o. `Y8  8 8888  |
| .888888888. `88888.  8 8888   `8b.    .888888888. `88888.  8         `Y8o.`        8 8888 .888888888. `88888.  8         `Y8o.`  8 8888  |
|.8'       `8. `88888. 8 8888     `88. .8'       `8. `88888. 8            `Yo        8 8888.8'       `8. `88888. 8            `Yo  8 8888  |
|__________________________________________________________________________________________________________________________________________|
|__________________________________________________________________________________________________________________________________________|
|                                                                                                                                          |
| The code for "ARANYANI Mark 1" is developed by Shourya Maker Lab and includes the fundamental movements of the robot.                    |
| It takes PWM signals from each channel of the receiver system (FS-R6B) and processes them for use by the motor driver                    |
| (MD 10C by Cytron) and the relay module.                                                                                                 |
|                                                                                                                                          |
| This code utilizes the following components:                                                                                             |
|                                                                                                                                          |
| 1. Fs-t6 computrized R/C remote controller                                                                                               |
| 2. FS-R6B receiver system                                                                                                                |
| 3. MD 10C motor driver by Cytron                                                                                                         |
| 4. MG995 180-degree servo motor                                                                                                          |
| 5. MG995 360-degree servo motor                                                                                                          |
| 6. Arduino Mega 2560                                                                                                                     |
|                                                                                                                                          |
| For more information about the name "Aranyani", please visit https://en.wikipedia.org/wiki/Aranyani.                                     |
|                                                                                                                                          |
|अरण्यनी मार्क  1 गर्व से भारत में निर्मित | Aranyani Mark 1 proudly made in Bharat.                                                                     |
|__________________________________________________________________________________________________________________________________________|
|__________________________________________________________________________________________________________________________________________|
|          _  _ ____ ___  ____     ___  _   _     ____ _  _ ____ _  _ ____ _   _ ____     _  _ ____ _  _ ____ ____     _    ____ ___       |
|          |\/| |__| |  \ |___     |__]  \_/      [__  |__| |  | |  | |__/  \_/  |__|     |\/| |__| |_/  |___ |__/     |    |__| |__]      |
|          |  | |  | |__/ |___     |__]   |       ___] |  | |__| |__| |  \   |   |  |     |  | |  | | \_ |___ |  \     |___ |  | |__]      |
|__________________________________________________________________________________________________________________________________________|
|__________________________________________________________________________________________________________________________________________|
|                                                                                                                                          |
|                                         d88b  .d8b.  d888888b db   db d888888b d8b   db d8888b.                                          |
|                                         `8P' d8' `8b   `88'   88   88   `88'   888o  88 88  `8D                                          |
|                                          88  88ooo88    88    88ooo88    88    88V8o 88 88   88                                          |
|                                          88  88~~~88    88    88~~~88    88    88 V8o88 88   88                                          |
|                                      db. 88  88   88   .88.   88   88   .88.   88  V888 88  .8D                                          |
|                                      Y8888P  YP   YP Y888888P YP   YP Y888888P VP   V8P Y8888D'                                          |
|__________________________________________________________________________________________________________________________________________|
|_________________________________________________________________________________________________________________________________________*/

// set the remote stick configuration  to moode 2.

int channel1 = 12; // for reciving input from channel 1.
int channel2 = 13; // for reciving input from channel 2.
int pwm1 = 10;     // for outputing pwm signal to motor driver 1.
int pwm2 = 11;     // for outputing pwm signal to motor driver 2.
int dir1 = 8;      // for outputing direction value to motor driver 1.
int dir2 = 9;      // for outputing direction value to motor driver 2.

void setup()
{

  pinMode(channel1, INPUT); // setting mode to input.
  pinMode(channel2, INPUT); // setting mode to input.
  pinMode(pwm1, OUTPUT);    // setting mode to output.
  pinMode(pwm2, OUTPUT);    // setting mode to output.
  pinMode(dir1, OUTPUT);    // setting mode to output.
  pinMode(dir2, OUTPUT);    // setting mode to output.
  Serial.begin(9600);       // this will begin serial monitor.
}

void loop()
{

  int pwm = 0;                              // this is dynamic speed variable.
  int rc1 = pulseIn(channel1, HIGH, 25000); // setting the pwm function for channel 1.
  int rc2 = pulseIn(channel2, HIGH, 25000); // setting the pwm function for channel 2.

  Serial.print(" raw channel1: "); // this will show value of channel 1 control's from the remote, for troubleshooting purposes.
  Serial.print(rc1);               // this will print the value of input channel 1.
  Serial.print('\n');              // prints a new line character.
  Serial.print(" raw channel2: "); // this will show value of channel 2 control's from the remote, for troubleshooting purposes.
  Serial.print(rc2);               // this will print the value of input channel 2.
  delay(500);                      // set's a delay for the serial message.

  if ((rc1 >= 1460) and (rc1 <= 1490) and (rc2 >= 1460) and (rc2 <= 1490)) // when the stick is not in use.
  {
    Serial.print("no movement"); // the movement which the bot is doing,for troubleshooting purposes.
    digitalWrite(dir1, LOW);     // direction will stay to forward but this motor will keep to 0. // changing this for testing  !!!!
    digitalWrite(dir2, LOW);     // direction will stay to forward but this motor will keep to 1.
    analogWrite(pwm1, 0);        // the power of the motor will be on halt.
    analogWrite(pwm2, 0);        // the power of the motor will be on halt.
  }

  if ((rc1 == 0) and (rc2 == 0)) // when the stick is not in use.
  {
    Serial.print("connection lost or remote off"); // the movement which the bot is doing,for troubleshooting purposes.   !!!!
    digitalWrite(dir1, LOW);                       // direction will stay to forward but this motor will keep to 0.
    digitalWrite(dir2, LOW);                       // direction will stay to forward but this motor will keep to 1.
    analogWrite(pwm1, 0);                          // the power of the motor will be on halt.
    analogWrite(pwm2, 0);                          // the power of the motor will be on halt.
  }

  if (rc2 >= 1491)
  {                                     // forward
    Serial.print("forward");            // the movement which the bot is doing,for troubleshooting purposes.
    pwm = map(rc2, 1491, 1960, 0, 255); // map our speed to 0-255 range.
    digitalWrite(dir1, HIGH);           // direction will stay to forward but this motor will keep to 0.       !!!!
    digitalWrite(dir2, LOW);            // direction will stay to forward but this motor will keep to 1.
    analogWrite(pwm1, pwm);             // the power of the motor will move forward.
    analogWrite(pwm2, pwm);             // the power of the motor will move forward.
  }

  if ((rc2 <= 1459) and (rc2 >= 990))
  {                                     // backward
    Serial.print("backwards");          // the movement which the bot is doing,for troubleshooting purposes.
    pwm = map(rc2, 1491, 1970, 0, 255); // map our speed to 0-255 range.
    digitalWrite(dir1, LOW);           // direction will stay to forward but this motor will keep to 0.       !!!!
†    digitalWrite(dir2, LOW);            // direction will stay to forward but this motor will keep to 1.
    analogWrite(pwm1, pwm);             // the power of the motor will move forward.
    analogWrite(pwm2, pwm);             // the power of the motor will move backward.
  }

  if ((rc1 >= 1491))
  {                                     // right
    Serial.print("right");              // the movement which the bot is doing,for troubleshooting purposes.
    pwm = map(rc1, 1491, 1970, 0, 255); // map our speed to 0-255 range.
    digitalWrite(dir1, LOW);            // direction will stay to forward but this motor will keep to 0.
    digitalWrite(dir2, LOW);            // direction will stay to forward but this motor will keep to 1.
    analogWrite(pwm1, pwm);             // the power of the motor will move backward.                      !!!
    analogWrite(pwm2, pwm);             // the power of the motor will move forward.                       !!!
  }

  if ((rc1 <= 1459) and (rc1 >= 990))
  {                                     // left
    Serial.print("left");               // the movement which the bot is doing,for troubleshooting purposes.
    pwm = map(rc1, 1491, 1970, 0, 255); // map our speed to 0-255 range.
    digitalWrite(dir1, LOW);            // direction will stay to forward but this motor will keep to 0.    !!!!!
    digitalWrite(dir2, HIGH);           // direction will stay to forward but this motor will keep to 1.
    analogWrite(pwm1, pwm);             // the power of the motor will move forward.                       !!!
    analogWrite(pwm2, pwm);             // the power of the motor will move backward.                      !!!
  }
}
