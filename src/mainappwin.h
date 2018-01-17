//-------------------------------- mainappwin.h --------------------------------

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

#ifndef MAIN_H
#define MAIN_H

#include <fox-1.6/fx.h>
#include "defs.h"

#define ENABLE  FXWindow::ID_ENABLE
#define DISABLE FXWindow::ID_DISABLE

class  Wire;
struct CoreData;

//------------------------------------------------------------------------------

/*
        Name     : MainAppWin

	Object   : Daughter Class

	Ancestor : FXMainWindow (FOX Class Library)

	Public Methods:
	                Name: MainAppWin
			Type: Constructor
			Parameters:
			            aApplication (Pointer - FXApp) -  Object created in
				    main program

			            aMWHeight (FXint) - Main Window height
				    aMWWidth  (FXint) -   "     "   width

			Type: Event Handlers (long function)
			Parameters:
                                    Sender (Pointer - FXObject) Base class of all FOX Objects
			            Sel (FXSelector) Message source identifier
				    Data (Pointer - void) May be cast to type to retrieve event
				                          data.
			Note: This application uses two classes of event handlers:
			      those which are called to handle user-generated events,
			      and those which are called by the system for the purpose
			      of keeping the main window interface up to date

        Private Methods: See sdmainwindow.cpp for details
 */

class MainAppWin : public FXMainWindow
{
  FXDECLARE(MainAppWin)

//------------------------ Functions 'n' Subroutines ---------------------

//  Public Methods

    public:
            MainAppWin(FXApp *aApp);
            virtual ~MainAppWin(void);

	    //  Event Handlers : Command

	    long MainMenuClick(FXObject*, FXSelector, void*);
	    long RadioBtnClick(FXObject*, FXSelector, void*);
	    long CmdBtnClick(FXObject*, FXSelector, void*);
	    long ProjectFinalizer(FXObject*, FXSelector, void*);


	    //  Event Handlers : Update

            long AllEditsUD(FXObject*, FXSelector, void*);
            long RadioBtnUD(FXObject*, FXSelector, void*);
            long MenuItemsUD(FXObject*, FXSelector, void*);
            long CmdBtnUD(FXObject*, FXSelector, void*);

	    virtual void create(void);

    protected:
	    MainAppWin(void) {}   //   Inline default constructor


    private:
	    MainAppWin(const MainAppWin&);
	    MainAppWin &operator=(const MainAppWin&);

	    long NewMenuExe(void);
	    long OKCmdExe(void);
	    long ProjectSelector(FXuint);
	    long ProjectSaver(void);
	    long ProjectPrinter(void);
	    long Dialogs(FXuint);
            FXdouble GetData(FXTextField*);
	    void WriteOut(CoreData&, FXint, FXint, FXdouble, FXint, FXint, FXdouble);
            void* CalcCoreData(CoreData&, FXdouble, const FXdouble, const FXint,
			       FXint&, FXint&);
	    FXString& FormatData(FXdouble, const FXchar);

//---------------------- Declair Variables -------------------------------


//  Public Variables

    public:
	    FXTextField   *DataIn[ALL_EDITS];
            FXRadioButton *Units[2];
	    FXMenuPane    *ProjMain, *CoreMain, *HelpMain;
	    FXText        *Output;
            FXStatusBar   *StatusBar;
            FXLabel       *LengthLbl, *WidthLbl, *HeightLbl, *DiamLbl, *ThickLbl,
		          *WireDiamLbl, *WireLenLbl, *StatusLbl;

	    enum    //  Message target identifiers
	    {
	      ID_CHEDIT= FXMainWindow::ID_LAST,
	      ID_CWEDIT,
	      ID_CDEDIT,
	      ID_CLEDIT,
	      ID_ILEDIT,
	      ID_TTEDIT,
	      ID_GEDIT,
	      ID_WLEDIT,
	      ID_NEW,
	      ID_TOTALTURNS,
	      ID_WIRELENGTH,
	      ID_SAVEAS,
	      ID_PRINT,
	      ID_RECT,
	      ID_RND,
	      ID_QUIT,
	      ID_SPECIAL,
	      ID_HELP,
	      ID_ABOUT,
	      ID_OK,
	      ID_CANCEL,
	      ID_US,
	      ID_METRIC,
	      ID_TITLE,
	      ID_LAST
            };

//  Protected Variables

    protected:
	       FXIcon *FileSaveasIcon, *FilePrintIcon,  *HelpIcon, *RectCoreIcon, *RndCoreIcon,
		      *WhatsThisIcon,  *Sm_DolphinIcon, *ExitIco, *CopyIco,
		      *OKCheckIco,     *CancelXIco,     *Bg_DolphinIcon, *LEDGrayIco, *LEDOnIco, *LEDOffIco;
//  Private Variables

    private:
	       enum
	       {
                 NO_PROJ=    0,    //  Project Status (ProjStat)
		 PROJ_PEND,
		 PROJ_COMP
	       };

               enum
               {
		 NOT_SAVED= 0,     // Saved Status (SavedStat)
	         SAVED
               };

               enum
               {

		 NO_TYPE= 0,       //  Project Type (ProjType)
		 TT_TYPE,
		 WL_TYPE
	       };

               enum
	       {
		 NO_CORE=   0,     //  Core X-Sect. Geometry (CoreGeo)
                 RND_CORE,
		 RECT_CORE
	       };

	       Wire     *Table[MINGAGE+1];
               FXString *Results;
               FXuint    ProjStatus, SaveStatus, CoreGeo, ProjType, Metric;
	       FXApp    *ThisApp;
};

#endif

//-------------------------------- mainappwin.h --------------------------------
