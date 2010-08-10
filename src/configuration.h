#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdio.h>
#include <string.h>

class Configuration
{
public:

    Configuration();

    static Configuration parse(int argc, char * argv[]);

    int simulations;    /// Number of executions.
    bool exec;          /// Start or not the simulator.
    bool noia1;         /// Do not start the strategy for team 1.
    bool noia2;         /// Do not start the strategy for team 2.
    bool log;           /// Saves a log file of the game.
    bool gui;           /// Show the graphical user interface.
    unsigned short strategyPort1[2];
    unsigned short strategyPort2[2];
    unsigned short viewerPort;

};

#endif // CONFIGURATION_H
