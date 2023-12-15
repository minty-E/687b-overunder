/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       edwardchoi                                                */
/*    Created:      Tue Oct 17 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LMG                  motor_group   1, 2            
// RMG                  motor_group   3, 4            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
competition comp;
void drivercontrol(void){
  vexcodeInit();
  while(true) {
    Function::driveControl();
    
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  comp.drivercontrol(drivercontrol);
  while(true) {
    wait(10, msec);
  }
  
}
