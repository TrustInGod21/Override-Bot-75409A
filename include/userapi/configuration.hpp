#pragma once

#include "EZ-Template/drive/drive.hpp"

#include "gamers-forge/bmapper.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
//#include "pros/motors.h"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "api.h"
#include "EZ-Template/api.hpp"
//#include "userapi/controls/drive.hpp"
//#include <algorithm>
extern pros::adi::Pneumatics clawPiston;
namespace devices {
    inline ez::Drive chassis(
        // These are your drive motors, the first motor is used for sensing!
        // LT = 12, LB = 13, and LF = 11
        {-18, -19, -20},     // Left Chassis Ports (negative port will reverse it!)
        // RT = 18, RB = 20, and RF = 19
        {11, 12, 13},  // Right Chassis Ports (negative port will reverse it!)

        7,      // IMU Port
        3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
        360.0);   // Wheel RPM = cartridge * (motor gear / wheel gear)
     inline pros::Motor intake_motor (2, pros::MotorGearset::blue); // Intake motor
    //  inline pros::Motor lift_motor (3, pros::MotorGearset::green); // Lift motor
    //  inline pros::Motor lift_motor2 (4, pros::MotorGearset::green); // Lift motor
    inline pros::MotorGroup lift_motors({3, -4}, pros::MotorGearset::green); // Lift motor group
};

namespace configuration::drive {
    void default_constants();
    void initialize();
}
namespace intake {
    inline void spin() {
        devices::intake_motor.move(127);
    }

    inline void backwards() {
        devices::intake_motor.move(-127);
    }

    inline void stop() {
        devices::intake_motor.move(0);
    }
}

namespace lift {
    inline void up() {
        devices::lift_motors.move(127);
    }

    inline void down() {
        devices::lift_motors.move(-127);
    }

    inline void stop() {
        devices::lift_motors.move(0);
    }
}

namespace configuration::controls {
    inline BMapper::ButtonHandler button_handler(master);

    inline void configure() {
        // Drive
    //     button_handler.bind(pros::E_CONTROLLER_DIGITAL_A, pros::E_CONTROLLER_DIGITAL_Y)
    //         .setCategory("Drive")
    //         .onPress(keybindActions::drive::toggle_arcade);
    // }
    // inline void intake_configure() {
    //     button_handler.bind(pros::E_CONTROLLER_DIGITAL_R1)
    //         .setCategory("Intake_up")
    //         .onHold([]() { devices::intake_motor.move(120); })
    //         .apply();
            

    //     button_handler.bind(pros::E_CONTROLLER_DIGITAL_R2)
    //         .setCategory("Intake_down")
    //         .onHold([]() { devices::intake_motor.move(-120); })
    //         .apply();
    PROSLogger::Manager::setLevel(PROSLogger::LogLevel::DEBUG);

    // Lift up
    button_handler.bind(pros::E_CONTROLLER_DIGITAL_R2)
        .setCategory("Intake forward")
        .onPress(intake::spin)
        .onRelease(intake::stop);

    button_handler.bind(pros::E_CONTROLLER_DIGITAL_R1)
        .setCategory("Intake backward")
        .onPress(intake::backwards)
        .onRelease(intake::stop);


    // Lift motors
    button_handler.bind(pros::E_CONTROLLER_DIGITAL_L2)
        .setCategory("Lift up")
        .onPress(lift::up)
        .onRelease(lift::stop);

    button_handler.bind(pros::E_CONTROLLER_DIGITAL_L1)
        .setCategory("Lift down")
        .onPress(lift::down)
        .onRelease(lift::stop);

    // // Open Claw
    //     button_handler.bind(pros::E_CONTROLLER_DIGITAL_A)
    //     .setCategory("Claw open")
    //     .onPress([]() { clawPiston.set_value(true); })
    //     .onRelease([]() { clawPiston.set_value(false); });

    // // Claw close
    // button_handler.bind(pros::E_CONTROLLER_DIGITAL_A)
    //     .setCategory("Claw close")
    //     .onPress([]() { clawPiston.set_value(false); })
    //     .onRelease([]() { clawPiston.set_value(false); });
            
    }
}

namespace configuration::autonomous {
    void configure();
}
