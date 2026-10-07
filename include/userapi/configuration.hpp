#pragma once

#include "EZ-Template/drive/drive.hpp"

#include "gamers-forge/bmapper.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
//#include "pros/motors.h"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "api.h"
#include "EZ-Template/api.hpp"
//#include "userapi/controls/drive.hpp"
//#include <algorithm>
// extern pros::adi::Pneumatics clawPiston;
// extern pros::adi::Pneumatics positionPiston;
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
    inline pros::adi::Pneumatics clawPiston('A', false);
    inline pros::adi::Pneumatics positionPiston('B', true);
};

namespace configuration::drive {
    void default_constants();
    void initialize();
}

// Making Claw Functions
namespace clawPiston {
    inline void open() {
        devices::clawPiston.set_value(true);
    }

    inline void close() {
        devices::clawPiston.set_value(false);
    }

    inline void toggle() {
        devices::clawPiston.toggle();
    }
}

// Making Position Piston Functions
namespace positionPiston {
    inline void extend() {
        devices::positionPiston.set_value(true);
    }

    inline void retract() {
        devices::positionPiston.set_value(false);
    }

    inline void toggle() {
        devices::positionPiston.toggle();
    }
}

// Making Intake Functions
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

// Making Cascade Lift Functions
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
    
    PROSLogger::Manager::setLevel(PROSLogger::LogLevel::DEBUG);
    
    /*----------------------Intake controls-----------------------*/

    // Intake pins and cups
    button_handler.bind(pros::E_CONTROLLER_DIGITAL_R2)
        .setCategory("Intake forward")
        .onHold(intake::spin)
        .onPress(positionPiston::extend)
        .onPress(clawPiston::open)
        .onRelease(intake::stop);
    
    // Outtake pins and cups
    button_handler.bind(pros::E_CONTROLLER_DIGITAL_DOWN)
        .setCategory("Intake backward")
        .onHold(intake::backwards)
        .onRelease(intake::stop);

    /*----------------------Cascade controls-----------------------*/

    // Moving the cascade up
    button_handler.bind(pros::E_CONTROLLER_DIGITAL_R1)
        .setCategory("Lift up")
        .onPress(lift::up)
        .onRelease(lift::stop);
    
    // Moving the cascade down
    button_handler.bind(pros::E_CONTROLLER_DIGITAL_L1)
        .setCategory("Lift down")
        .onPress(lift::down)
        .onRelease(lift::stop);

    /*----------------------Claw controls---------------------------*/

    // Open Claw
    // button_handler.bind(pros::E_CONTROLLER_DIGITAL_A)
    //     .setCategory("Toggling Claw")
    //     .onPress(clawPiston::toggle);

    /*----------------------Position Piston controls-----------------------*/

    // Position Piston Extended
    // button_handler.bind(pros::E_CONTROLLER_DIGITAL_B)
    //     .setCategory("Toggling Position Piston")
    //     .onPress(positionPiston::toggle);
    }
}

namespace configuration::autonomous {
    void configure();
}
