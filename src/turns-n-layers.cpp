//----------------------------- turns-n-layers.cpp -----------------------------

/***************************************************************************
                            -  description
                             -------------------
    Begin                : 25 June, 2012
    Copyright            : (C) 2012 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.1.9
 **************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *                                                                         *
 *       ----> If software can be free, why can't dolphins? <----          *
 *                                                                         *
 ***************************************************************************/

#include <signal.h>
#include <fox-1.6/fx.h>
#include "mainappwin.h"
/*
       Name: main

       Type: Integer function

       Parameters:
                   argc (int) - Number of command line options
		   argv (Array of char pointers) - The actual command line options

       Returns:
                0 - Signals success to shell
		1 -    "    failure  "   "

       Note: The app's main program. Initializes the main window,
             sets up the ability to terminate the app with CNTL-C,
	     and enters the program event loop (waits for user input).
	     TMainWindow takes just the one parameter, as the constructor
	     is called indirectly.
 */
int main(int argc, char *argv[])
{
    for (int i= 0; i < argc; i++)
    {
      if (! (strcmp(argv[i], "-v") && strcmp(argv[i], "--version")))
      {
	  printf("Turns-n-Layers Version: %s\n", VERSION);
	  return 0;
      }
    }

    FXApp MyApp("Turns-n-Layers", "Simo");
    MyApp.init(argc, argv);
    MainAppWin *NewWin= new MainAppWin(&MyApp);
    MyApp.addSignal(SIGINT, NewWin, MainAppWin::ID_QUIT);
    MyApp.create();
    return MyApp.run();
}

//---------------------------- turns-n-layers.cpp -----------------------------
