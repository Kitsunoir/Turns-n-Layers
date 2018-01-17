//-------------------------------- sdabout.cpp ---------------------------------

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

#include "appabout.h"
#include "defs.h"
#include "locations.h"
#include "icons.h"

//     Make the FOX Message/Target Callback Map

FXDEFMAP(About) AboutSM[]=
{
    FXMAPFUNC(SEL_CLOSE, About::ID_TITLE, FXDialogBox::onCmdAccept)
};

FXIMPLEMENT(About, FXDialogBox, AboutSM, ARRAYNUMBER(AboutSM))

/*
       Name: About

       Type: Subroutine (Constructor)

       Parameters: aApp (Pointer: FXApp) -- Pointer to the main event loop

       Note: Create the "About" Box GUI. No other functionality to implement.
*/

About::About(FXApp *aApp) :
FXDialogBox(aApp, "About Turns-n-Layers", DECOR_ALL, 0, 0, 639, 343),
ThisApp(aApp)

{
//        Declare Layout Managers

    FXVerticalFrame   *MainLO;
    FXHorizontalFrame *SubLO, *CmdBtnGrp;

//        Initialize Icons

    DolphinLogo= new FXGIFIcon(ThisApp, smDolphin_gif);
    OKCheck=     new FXGIFIcon(ThisApp, OKCheck_gif);
    FreeMe=      new FXGIFImage(ThisApp, NULL, IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP, 256, 256);

    FXString ImgFile(IMAGE_DIR);
    ImgFile+= "FreeMe.gif";

    FXFileStream ImageStr;

    if (ImageStr.open(ImgFile.text(), FXStreamLoad))
    {
	FreeMe->loadPixels(ImageStr);
	ImageStr.close();
	FreeMe->create();
    }
    else fprintf(stderr, IMG_FILE_ERROR);

    setMiniIcon(DolphinLogo);
    setTarget(this);
    setSelector(ID_TITLE);

    MainLO=    new FXVerticalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL|FRAME_NORMAL);
    SubLO=     new FXHorizontalFrame(MainLO, LAYOUT_FILL|FRAME_NONE|LAYOUT_SIDE_TOP);
               new FXImageView(SubLO, FreeMe, NULL, 0, LAYOUT_FILL|FRAME_GROOVE, 0, 0, 256, 256);
               new FXVerticalSeparator(SubLO);
               new FXLabel(SubLO, ABOUT_MSG, NULL, JUSTIFY_LEFT|ICON_BEFORE_TEXT);
    CmdBtnGrp= new FXHorizontalFrame(MainLO, LAYOUT_FILL_X|FRAME_NORMAL|LAYOUT_SIDE_BOTTOM);
               new FXButton(CmdBtnGrp, "&OK", OKCheck, this, FXDialogBox::ID_ACCEPT,
			    BUTTON_NORMAL|LAYOUT_RIGHT);
}
//------------------------------------------------------------------------------
/*
       Name: ~About

       Type: Subroutine (Destructor)

       Parameters: (none)

       Note: Clean up objects FOX doesn't clean up for us
*/

About::~About(void)
{
    delete DolphinLogo;
    delete OKCheck;
    delete FreeMe;
}

//-------------------------------- tabout.cpp ----------------------------------
