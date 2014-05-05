//////////////////////////////////////////////////////////////
//                Teleop Avoid Wierd Code                   //
//////////////////////////////////////////////////////////////

int avoidWeird(int joyval, int noise)
{
/*--------Code to Reduce Noise-----------
       reduces the noise from the
       controller
*/
  if (abs(joyval) < noise)
  {
    joyval = 0;
  }
  return (joyval);
}

int returnValueMotor(int cord, int maxVal)
{
/*-----Code to create value of cord-------
      Creates a function that maps the
      value of cord to a power value for
              the motors

       cord: cordinate value from controller
       returns: a power value for motors
*/
  int velocity = ((maxVal*cord)/127); //Set velocity value based on joystick value
  return velocity;
}
