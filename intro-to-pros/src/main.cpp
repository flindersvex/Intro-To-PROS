#include "main.h"

pros::Motor frontLeft(1, pros::E_MOTOR_GEAR_BLUE, true); // These lines initialise the individual cpp objects for each motor
pros::Motor middleLeft(2, pros::E_MOTOR_GEAR_BLUE, true); // The three arguments are the port number, the gearset, and whether the motor is reversed
pros::Motor backLeft(3, pros::E_MOTOR_GEAR_BLUE, true); 
pros::Motor frontRight(4, pros::E_MOTOR_GEAR_BLUE, false);
pros::Motor middleRight(5, pros::E_MOTOR_GEAR_BLUE, false);
pros::Motor backRight(6, pros::E_MOTOR_GEAR_BLUE, false);

pros::Motor_Group leftMotors({ // These motor groups allow you to control multiple motors at the same time, which is useful for drivetrain code
	frontLeft, // The initialiser is a single list of the motors that you want to be in the group
	middleLeft,
	backLeft
});

pros::Motor_Group rightMotors({
	frontRight,
	middleRight,
	backRight
});

pros::Distance leftDist(9); // These lines initialise the distance sensors, which are used to measure the distance to an object in front of them. 
pros::Distance rightDist(10); // The only argument is the port number

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

	pros::Controller master(pros::E_CONTROLLER_MASTER); // This initialises the controller, so we can get button and analog stick readings from it

	// std::cout << master.get_battery_level() << std::endl;
	std::cout << "left_dist,right_dist" << std::endl; // This line prints the column headers for the distance sensor readings, which will be printed in a loop below. This is useful for plotting the data in a spreadsheet or graphing program.

	int leftDistance = 0; // These variables will store the distance sensor readings, which are updated in the loop below and printed to the console.
	int rightDistance = 0;

	while (true)
	{
		leftMotors = master.get_analog(ANALOG_LEFT_Y); // This line sets the voltage of the left motors to the value of the left analog stick on the controller, which is a value from -127 to 127. This allows you to control the robot's movement with the controller.
		rightMotors = master.get_analog(ANALOG_RIGHT_Y); // The right motors are set to the right analog stick in the same way.

		leftDistance = leftDist.get(); // These lines get the distance sensor readings and store them in the variables declared above. The get() function returns the distance in millimeters, or PROS_ERR if there was an error (e.g. if the sensor is not connected).
		rightDistance = rightDist.get();
		
		std::cout << leftDistance << ","; // This line prints the left distance reading followed by a comma, which will separate it from the right distance reading in the console output.
		std::cout << rightDistance << std::endl;

		pros::delay(50); // This line adds a delay of 50 milliseconds at the end of the loop, which limits how often the distance sensor readings are updated and printed to the console. This is important because the get() function for the distance sensors can be slow, and we don't want to overwhelm the console with too many readings.
	}
}
