//--------------------------------- defs.h -----------------------------------

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
 *        ----> If software can be free, why can't dolphins? <----         *
 *                                                                         *
 ***************************************************************************/

/*
     Note: This header defines widely used constants and macro functions in
           one central location so that these may be more easily revised if
	   needed for version upgrades.
*/

#ifndef DEFS_H
#define DEFS_H

//      Wire gages, and the number of line edits

#define MAXGAGE   0
#define MINGAGE   40
#define ALL_EDITS 8

#ifndef PI
#define PI 3.14159265359
#endif

//      Macro functions

#define IN2MM(x)    ((x)*25.4)
#define IN2CM(x)    ((x)*2.54)
#define IN2MTR(x)   ((x)*25.4E-3)
#define METER2IN(x) ((x)/25.4E-3)
#define CM2IN(x)    ((x)/2.54)
#define MM2IN(x)    ((x)/25.4)
#define CEIL(x)     (((x)+15) & -16)

//      Text Macros

#define SAVE_Q "You haven't saved your current project. Save it before starting a new one?"

#define EXIT_Q "You haven't saved your current project yet. Quit anyway?"

#define ENTRY_ERR(m) { FXMessageBox::error(ThisApp, MBOX_OK, "Turns-n-Layers Error", m); return 0; }

#endif

//--------------------------------- defs.h -----------------------------------
