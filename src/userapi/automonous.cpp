#include "userapi/automonous.hpp"

#include "userapi/configuration.hpp"

using namespace devices;
using namespace ez;

const int DRIVE_SPEED = 127;
const int TURN_SPEED = 127;
const int SWING_SPEED = 110;

void reset_pos() {
    chassis.pid_targets_reset();                // Resets PID targets to 0
	chassis.drive_imu_reset();                  // Reset gyro position to 0
	chassis.drive_sensor_reset();               // Reset drive sensors to 0
	chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
	chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
}

namespace autom::Qualifications {
    void left() {
        reset_pos();
    }

    void right() {
        reset_pos();
    }
}

namespace autom::Eliminations {
    void left() {
        reset_pos();
    }

    void right() {
        reset_pos();
    }
}

namespace autom::AWP {
    void left() {
        reset_pos();
    }

    void right() {
        reset_pos();
    }
}

namespace autom::Skills {
    void skills() {
        reset_pos();
    }
}

namespace autom::None {
    void none() {
        reset_pos();
    }
}