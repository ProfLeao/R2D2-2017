 /**
 * \file      main.cc
 * \brief     Program for giving an indication when a rfid card has been detected, a database connection has been made and a string has been encrypted
 * \author    Tim IJntema, Stefan de Beer, Arco Gelderblom, Rik Honcoop, Koen de Groot, Ricardo Bouwman, jeremy ruizenaar
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
 
#include "mysql.hh"
#include "mfrc522.hh"
#include "encryption.hh"
#include "led-controller.hh"
#include "matrix-keypad.hh"
#include "config-file-parser.hh"
#include "databasemanager.hh"

#include <wiringPi.h>
#include <wiringPiSPI.h>
 
#include <iostream>

int main(int argc, char **argv) {
    try {

        std::string ip;
        std::string username;
        std::string password;
        int encryptionKey;
        
        ConfigFileParser factory("database-config.txt", "encryption-config.txt");

        factory.loadDatabaseSettings(ip, username, password);
        factory.loadEncryptionSettings(encryptionKey);

        databasemanager database;

        database.connectTo(ip, username, password);
        database.selectDatabase("R2D2");

        std::cout << "Made connection to the database\n";
        wiringPiSetup();
        wiringPiSPISetup(0, 10000000);//max speed for mfrc522 is 10Mhz
        Mfrc522 rfid;
        rfid.init();

        //Keypad pinSetup
        const int keypadRow[] = {4, 1, 16, 15};
        const int keypadColumn[] = {2, 7, 9, 8};

        //Keypad objects
        MatrixKeypad keypad(keypadRow, keypadColumn, 4);
        char c;
        
        Encryption encryption(encryptionKey);

        LedController led(0);

        while (true) {
            std::cout << "\n\nWaiting for rfid tag: \n";

            while (!rfid.isTagPresent()) {}
            
            std::cout << "Hello tag\n";
            std::cout << "Waiting for key press\n";
            while ((c = keypad.getKey()) == 'h') {
                delay(100);
            }

            std::cout << c << " key has been pressed\n";

            std::cout << "Enter a pincode, ending with '#'\n";

            std::string pin = keypad.getString();
            std::cout << "The pin you entered was: " << pin << "\n";

            std::cout << "Database information: "
                      << database.getAllCardIdFromDatabase()
                      << '\n';
            
            std::cout << "String before encryption: R2D2 project\n";
            std::cout << "String after encryption: "
                      << encryption.Encrypt("R2D2 project")
                      << '\n';

            led.blinkLed(1000);
        }
    } catch(const std::string & error) {
        std::cerr << error << '\n';
        exit(EXIT_FAILURE);
    } catch(...) {
        std::cerr << "Something went wrong\n";
        exit(EXIT_FAILURE);
    }  
    return 0;
}
