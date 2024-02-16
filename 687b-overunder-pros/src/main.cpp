#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "lemlib/api.hpp"

pros::Motor left1 (1, pros::E_MOTOR_GEARSET_36);
pros::Motor left2 (2, pros::E_MOTOR_GEARSET_36);
pros::Motor left3 (3, pros::E_MOTOR_GEARSET_36, true);

pros::Motor right1 (4, pros::E_MOTOR_GEARSET_36);
pros::Motor right2 (5, pros::E_MOTOR_GEARSET_36);
pros::Motor right3 (6, pros::E_MOTOR_GEARSET_36, true);

pros::Motor_Group LMG ({left1, left2, left3});
pros::Motor_Group RMG ({right1, right2, right3});

pros::Motor cata1 (7, pros::E_MOTOR_GEARSET_36, true); // 6?
pros::Motor cata2 (8, pros::E_MOTOR_GEARSET_36, true); // 6?

pros::Motor intake1 (9, pros::E_MOTOR_GEARSET_36);

pros::ADIDigitalOut wingsRight ('C'); //left
pros::ADIDigitalOut wingsLeft ('B'); //right

pros::Imu inert_sens ('D');

/*
// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
	5
};
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};
lemlib::Drivetrain_t drivetrain {
	&LMG,
	&RMG,
	10.5,
	3.25,
	100
};
lemlib::OdomSensors_t sensors {
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	&inert_sens
};
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
*/
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	/*
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
	*/
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void screen() {
    // loop forever
	/*
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
	*/
}
void initialize() {

	pros::lcd::register_btn1_cb(on_center_button);
	//chassis.calibrate();
	//chassis.setPose(0,0,0);
	pros::lcd::initialize(); // initialize brain screen
    //pros::Task screenTask(screen); // create a task to print the position to the screen
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
	// fix later
	/*
	LMG.move(100);
	RMG.move(100);
	pros::delay(250);
	RMG.move(100);
	pros::delay(250);
	LMG.move(300);
	RMG.move(300);
	pros::delay(250);
	cata1.move_relative(1000, 200 * 0.9);
	cata2.move_relative(1000, 200 * 0.9);
	*/ 
	/*
	chassis.moveTo(10, 0, 15000);
	chassis.turnTo(30, 0, 15000);
	chassis.moveTo(58, 0, 15000);
	chassis.turnTo(90, 0, 15000);
	//shoot preload cata?
	cata1.move_relative(1000, 200 * 0.9);
	cata2.move_relative(1000, 200 * 0.9);
	chassis.turnTo(-45, 0, 15000);
	chassis.moveTo(-7, 0, 15000);
	// input method??
	chassis.moveTo(7, 0, 15000);
	chassis.turnTo(45, 0, 15000);
	cata1.move_relative(1000, 200 * 0.9);
	cata2.move_relative(1000, 200 * 0.9);
	*/

	//LMG.move_relative(3000,100);
	//RMG.move_relative(3000,100);
	//chassis.moveTo(10, 0, 15000);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 
void opcontrol() {

	pros::Controller master(pros::E_CONTROLLER_MASTER);
	
	bool tR = false;
	int tL = 0;

	while (true) {

		if(master.get_digital(DIGITAL_X)){
			cata1.move(1000);
			cata2.move(1000);
        } else{
			cata1.move(0);
			cata2.move(0);
		}
		if(master.get_digital(DIGITAL_L1)){
			wingsLeft.set_value(true);
		}
		if(master.get_digital(DIGITAL_L2)){
			wingsLeft.set_value(false);
		}
		if(master.get_digital(DIGITAL_R1)){
			wingsRight.set_value(true);
		}
		if(master.get_digital(DIGITAL_R2)){
			wingsRight.set_value(false);
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			intake1.move_velocity(12000);
		} else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			intake1.move_velocity(-12000);
		} else {
			intake1.move_velocity(0);
		}

		double AxisDrive = -master.get_analog(ANALOG_LEFT_X) * -1;
		double AxisRot = -master.get_analog(ANALOG_RIGHT_Y) * -1;

		double setLMG = -(AxisDrive + AxisRot);
		double setRMG = -(AxisDrive - AxisRot);

		LMG.move_velocity(setLMG);
		RMG.move_velocity(setRMG);

		pros::delay(20);
		pros::lcd::set_text(1, "testing");
	}
}
