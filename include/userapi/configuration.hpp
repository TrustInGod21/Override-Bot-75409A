#pragma once

#include "EZ-Template/drive/drive.hpp"

#include "gamers-forge/bmapper.hpp"
#include "userapi/controls/drive.hpp"

namespace devices {
    inline ez::Drive chassis(
        // These are your drive motors, the first motor is used for sensing!
        {1, 2, -3},     // Left Chassis Ports (negative port will reverse it!)
        {-4, 5, 6},  // Right Chassis Ports (negative port will reverse it!)

        7,      // IMU Port
        3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
        360.0);   // Wheel RPM = cartridge * (motor gear / wheel gear)
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
}

namespace configuration::autonomous {
    void configure();
}