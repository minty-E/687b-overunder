#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "lemlib/api.hpp"

pros::Motor left1 (1, pros::E_MOTOR_GEARSET_36);
pros::Motor left2 (2, pros::E_MOTOR_GEARSET_36);
pros::Motor left3 (6, pros::E_MOTOR_GEARSET_36);

pros::Motor right1 (4, pros::E_MOTOR_GEARSET_36);
pros::Motor right2 (5, pros::E_MOTOR_GEARSET_36);
pros::Motor right3 (3, pros::E_MOTOR_GEARSET_36);

pros::Motor_Group LMG ({left1, left2, left3});
pros::Motor_Group RMG ({right1, right2, right3});

pros::Motor cata1 (7, pros::E_MOTOR_GEARSET_36);
pros::Motor cata2 (8, pros::E_MOTOR_GEARSET_36);

pros::ADIDigitalOut wingsRight ('C'); //right
pros::ADIDigitalOut wingsLeft ('B'); //left

pros::Imu inert_sens (7);

double get_sensor_value() {
	double rot = inert_sens.get_rotation();
	return rot;
}

// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
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
	10,
	3.25,
	360
};
lemlib::OdomSensors_t sensors {
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

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
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "i love vex");

	pros::lcd::register_btn1_cb(on_center_button);
	chassis.calibrate();
	chassis.setPose(0,0,0);
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
	chassis.moveTo(10,0, 1000);
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
		int left = master.get_analog(ANALOG_LEFT_Y) * -1;
		int right = master.get_analog(ANALOG_RIGHT_Y) * -1;

		if(master.get_digital(DIGITAL_X)){
            //cata1.move_relative(800, 200 * 0.8);
			//cata2.move_relative(-800, 200 * 0.8);
			cata1.move(1000);
			cata2.move(1000);
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
