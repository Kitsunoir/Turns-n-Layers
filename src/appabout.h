//--------------------------------- about.h ----------------------------------

/***************************************************************************
                            -  Description
                             -------------------
    Begin                : 25 June, 2012
    Copyright            : (C) 2012 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.1.0
 **************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *                                                                         *
 *   If software can be free, why can't dolphins?                          *
 *                                                                         *
 ***************************************************************************

*/

#ifndef ABOUT_H
#define ABOUT_H

#include <fox-1.6/fx.h>

//------------------------------- Text Macros --------------------------------

#define ABOUT_MSG \
"\nTurns-n-Layers:"\
"\n"\
"\nAn electronic project design aid:"\
"\nTurns-n-Layers is useful for the *physical*"\
"\nDesign of coils and transformers. You can"\
"\ndetermine the length and weight of the wire"\
"\nrequired to wind a coil, or the number of"\
"\nturns that can be wound from a given length"\
"\nof wire. The finished dimensions of the coil"\
"\nis also determined. It does not do the"\
"*electronic* design."\
"\n"\
"\nVersion: "VERSION\
"\n"\
"\nSee the on-line help for further details on using"\
"\nTurns-n-Layers"\
"\n"\
"\nTurns-n-Layers written by: Simo,"\
"\nwith FOX and XEMACS"\
"\n"\
"\nCopyright(C) 2013 by Simo"\
"\nIF SOFTWARE CAN BE FREE, WHY CAN'T DOLPHINS?"

#define IMG_FILE_ERROR \
"\nWan't able to open the file \"FreeMe.gif\"."

//--------------------------------------

class About : public FXDialogBox
{
    FXDECLARE(About)
    public:
                 About(FXApp *aApp);
                 virtual ~About(void);

    protected:
                 About(void) {}

    private:
                 About(const About&);
                 About& operator=(const About&);

    public:
                 enum
	         {
	             ID_TITLE= FXDialogBox::ID_LAST,
	             ID_LAST
	         };

    protected:
        	 FXIcon  *DolphinLogo, *OKCheck;
                 FXImage *FreeMe;

    private:
		 FXApp *ThisApp;
};

#endif

//-------------------------------- about.h ----------------------------------
