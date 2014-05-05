#pragma config(Sensor, S1, MyEOPD, sensorAnalogActive)
#include "drivers/HTEOPD-driver.h"
int EOPDReading(bool shortRange, tSensors port)
// The closer an object is to the EOPD, the higher the reading.
// The further away an object is from the EOPD, the lower the reading.
// The EOPD has two modes, short range and long range.
// Short range is relatively more sensitive to movements closer to the EOPD.
// Long range is relatively more sensitive to movements further away from the EOPD.
// Both ranges can get a bit crazy with VERY close objects; test, test, test...
// I'd like to thank Xander Soldaat for the original RobotC code
// but any errors are MINE!
// I'd like to thank Yaya Lu for her help testing this code.
// Xander's web site is http://botbench.com/blog/
// Yaya's web site is http://www.YayaLu.net
// See more of these free tutorials at http://www.DrGraeme.net
{
  if (shortRange)
  { // Set EOPD sensor into short range mode
    HTEOPDsetShortRange(port);
  } else
  { // Set EOPD sensor into long range mode
    HTEOPDsetLongRange(port);
  }
  return HTEOPDreadProcessed(port);
}
task main()
{
  int distanceShort, distanceLong;
  while(true)
  {
    // Read the EOPD value to get a number that is approximately related to the
    // distance between the EOPD sensor and a nearby object.
    // The bigger the number, the closer the object.
    // The smaller the number, the further away the object.
    // But these numbers get a bit crazy when the object is VERY close to the EOPD sensor.
    // Make a few tests with differently shaped and coloured objects to make sure. (-:
    // Get an EOPD distance reading in short range mode
    distanceShort = EOPDReading(true, MyEOPD);
    nxtDisplayBigStringAt(0,18, "S: %3i", distanceShort);
    wait1Msec(50);
    // Get an EOPD distance reading in long range mode
    distanceLong = EOPDReading(false, MyEOPD);
    nxtDisplayBigStringAt(0, 38, "L: %3i", distanceLong);
    wait1Msec(50);
  }
}
