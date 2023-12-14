#include "vex.h"

using namespace vex;

void Function::setVel(double AxisOne, double AxisTwo) {
  /*
    Sets the motor speed using the infomation from the driveControl function
  */
  LMG.spin(fwd, AxisTwo, volt);         RMG.spin(fwd, AxisOne, volt);
}

void Function::setStop(brakeType type){
  /*
    Motor brakeType brake brakes when stopped
    Motor brakeType hold position when stopped
  */

  LMG.setStopping(coast);               RMG.setStopping(coast);
}

void Function::driveControl(){
  /*
    The function that controls the user movement of the bot
  */
  setStop(coast);
  double AxisDrive = -Controller1.Axis2.position() * 2;
  double AxisRot = -Controller1.Axis4.position() * 2; //reversed 3.4.23

  // Deadzones
  if(abs(Controller1.Axis2.position()) < 5) {AxisDrive = 0;}
  if(abs(Controller1.Axis4.position()) < 5) {AxisRot = 0;}

  double setRMG = -(AxisDrive - AxisRot); //reversed??
  double setLMG = -(AxisDrive - AxisRot); //reversed?? lets try it out 1/12
  
    setVel(setLMG,setRMG);
}
  