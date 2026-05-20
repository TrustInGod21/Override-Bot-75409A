#pragma once

#include "EZ-Template/drive/drive.hpp"

#include "gamers-forge/bmapper.hpp"
#include "pros/abstract_motor.hpp"
//#include "pros/motors.h"
#include "pros/motors.hpp"
#include "userapi/controls/drive.hpp"
//#include <algorithm>

namespace devices {
    inline ez::Drive chassis(
        // These are your drive motors, the first motor is used for sensing!
        {-11, -12, -13},     // Left Chassis Ports (negative port will reverse it!)
        {18, 19, 20},  // Right Chassis Ports (negative port will reverse it!)

        7,      // IMU Port
        3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
        360.0);   // Wheel RPM = cartridge * (motor gear / wheel gear)
     inline pros::Motor intake_motor (2, pros::MotorGearset::green); // Intake motor
};

namespace configuration::drive {
    void default_constants();
    void initialize();
}

namespace configuration::controls {
    inline BMapper::ButtonHandler button_handler(master);

    inline void configure() {
        // Drive
        button_handler.bind(pros::E_CONTROLLER_DIGITAL_A, pros::E_CONTROLLER_DIGITAL_Y)
            .setCategory("Drive")
            .onPress(keybindActions::drive::toggle_arcade);
    }
    inline void intake_configure() {
        button_handler.bind(pros::E_CONTROLLER_DIGITAL_R1)
            .setCategory("Intake")
            .onPress([]() { devices::intake_motor.move(120); })
            .onRelease([]() { devices::intake_motor.move(0); });

        button_handler.bind(pros::E_CONTROLLER_DIGITAL_R2)
            .setCategory("Intake")
            .onPress([]() { devices::intake_motor.move(-120); })
            .onRelease([]() { devices::intake_motor.move(0); });
    }
}

namespace configuration::autonomous {
    void configure();
}