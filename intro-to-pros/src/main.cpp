#include "main.h"

pros::Motor frontLeft(1, pros::E_MOTOR_GEAR_BLUE, true);
pros::Motor middleLeft(2, pros::E_MOTOR_GEAR_BLUE, true);
pros::Motor backLeft(3, pros::E_MOTOR_GEAR_BLUE, true);
pros::Motor frontRight(4, pros::E_MOTOR_GEAR_BLUE, false);
pros::Motor middleRight(5, pros::E_MOTOR_GEAR_BLUE, false);
pros::Motor backRight(6, pros::E_MOTOR_GEAR_BLUE, false);

pros::Motor_Group leftMotors({
	frontLeft,
	middleLeft,
	backLeft
});

pros::Motor_Group rightMotors({
	frontRight,
	middleRight,
	backRight
});

pros::Distance leftDist(9);
pros::Distance rightDist(10);

		/**

	 * Runs initialization code. This occurs as soon as the program is started.
	 *
	 * All other competition modes are blocked by initialize; it is recommended
	 * to keep execution time for this mode under a few seconds.
	 */
	void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	// pros::lcd::register_btn1_cb(on_center_button);
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
void autonomous() {}

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
void opcontrol()
{

	pros::Controller master(pros::E_CONTROLLER_MASTER);

	// std::cout << master.get_battery_level() << std::endl;
	std::cout << "left_dist,right_dist" << std::endl;

	int leftDistance = 0;
	int rightDistance = 0;

	while (true)
	{
		leftMotors = master.get_analog(ANALOG_LEFT_Y);
		rightMotors = master.get_analog(ANALOG_RIGHT_Y);

		leftDistance = leftDist.get();
		rightDistance = rightDist.get();
		
		std::cout << leftDistance << ",";
		std::cout << rightDistance << std::endl;

		pros::delay(100);
	}
}
