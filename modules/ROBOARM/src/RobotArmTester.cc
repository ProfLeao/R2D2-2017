/**
 * \file
 * \author    David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "RobotArmTester.hh"

const char *RobotArmTester::commandList1[15] = {
        // Reset
        "RESET 1",

        // Z axis test
        "WAIT_S 2", "Z 90", "WAIT_S 2", "Z -90", "WAIT_S 2",

        // Y axis test
        "Y 90", "WAIT_S 2", "Y -45", "WAIT_S 2",

        // X axis test
        "X 45", "WAIT_S 2", "X -45", "WAIT_S 2",

        // Reset
        "RESET 1",
};

const char *RobotArmTester::commandList2[26] = {
        // Reset
        "RESET 1",

        // Z axis test
        "WAIT_S 2", "Z 90", "WAIT_S 2", "Z -90", "WAIT_S 2", "Z 180",
        "WAIT_S 2", "Z -180", "WAIT_S 2",

        // Y axis test
        "Y 90", "WAIT_S 2", "Y -90", "WAIT_S 2", "Y 180", "WAIT_S 2",
        "Y -180", "WAIT_S 2",

        // X axis test
        "X 90", "WAIT_S 2", "X -90", "WAIT_S 2", "X 180", "WAIT_S 2",
        "X -240",

        // Reset
        "RESET 1",
};

void RobotArmTester::run_test(const char *commandList[], int commandListLen){
    using namespace RoboArm::Parser;

    for (int i = 0; i < commandListLen; ++i) {
        Status result = parseCommand((hwlib::string<12>)commandList[i], robotarm);

        switch (result) {
            case Status::SyntaxError:
                hwlib::cout << "Syntax error" << "\r\n";
                break;
            case Status::Successful:
                break;
        }
    }
}

RobotArmTester::RobotArmTester(RoboArm::RobotArmController &robotarm) :
        robotarm(robotarm) {}

void RobotArmTester::run(int test) {
    hwlib::cout << "START SEQUENCE" << "\r\n";
    robotarm.enable();

    robotarm.startup(); // resets the robot position
    hwlib::cout << "Position has been reset" << "\r\n";

    if (test == 0 || test == 1) {
        hwlib::cout << "Run test 1" << "\r\n";
        run_test(commandList1, sizeof(commandList1)/ sizeof(commandList1[0]));
    }

    if (test == 0 || test == 2) {
        hwlib::cout << "Run test 2" << "\r\n";
        run_test(commandList2, sizeof(commandList2)/ sizeof(commandList2[0]));
    }

    robotarm.disable();
    hwlib::cout << "END SEQUENCE" << "\r\n";
}