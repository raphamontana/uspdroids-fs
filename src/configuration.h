/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdio.h>
#include <string.h>

/**
 * This class contains the simulator configurations and the parser method.
 */
class Configuration
{
public:

    /**
     * The default constructor.
     * Initialises with the default parameters.
     */
    Configuration();

    /**
     * This method reads the command line arguments and parse the configuration.
     * @param argc The count of arguments.
     * @param argv The arguments vector.
     * @return A Configuration object.
     */
    static Configuration parse(int argc, char * argv[]);

    bool isConfOK();    /// Check if the configuration object is ok.

    bool useGUI();      /// Check if start or not the graphical user interface.

    int simulations;                 /// Number of executions.
    bool exec;                       /// Start or not the simulator.
    bool noia1;                      /// Do not start the strategy for team 1.
    bool noia2;                      /// Do not start the strategy for team 2.
    bool log;                        /// Saves a log file of the game.
    bool gui;                        /// Show the graphical user interface.
    unsigned short strategyPort1[2]; /// Connection port for strategy 1.
    unsigned short strategyPort2[2]; /// Connection port for strategy 2.
    unsigned short viewerPort;       /// Connection port for viewers.

};

#endif // CONFIGURATION_H
