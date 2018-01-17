//------------------------------- mainappwin.cpp -------------------------------

/***************************************************************************
                            -  Description
                             -------------------
    Begin                : 25 June, 2012
    Copyright            : (C) 2012 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.1.9
    ************************************************************************

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *                                                                         *
 *        ----> IF SOFTWARE CAN BE FREE, WHY CAN'T DOLPHINS? <----         *
 *                                                                         *
 ***************************************************************************

*/

#include "mainappwin.h"
#include "icons.h"
#include "wire.h"
#include "coredata.h"
#include "appabout.h"
#include "splmsgbox.h"
#include "helpcntsbox.h"
#include "locations.h"

/******************************************************************************/

//                        Map messages to Event Handlers

FXDEFMAP(MainAppWin) Callbacks[]=
{
  FXMAPFUNCS(SEL_UPDATE, MainAppWin::ID_CHEDIT, MainAppWin::ID_WLEDIT, MainAppWin::AllEditsUD),
  FXMAPFUNCS(SEL_UPDATE, MainAppWin::ID_NEW, MainAppWin::ID_RND, MainAppWin::MenuItemsUD),
  FXMAPFUNCS(SEL_UPDATE, MainAppWin::ID_US, MainAppWin::ID_METRIC, MainAppWin::RadioBtnUD),
  FXMAPFUNCS(SEL_UPDATE, MainAppWin::ID_OK, MainAppWin::ID_CANCEL, MainAppWin::CmdBtnUD),
  FXMAPFUNCS(SEL_COMMAND, MainAppWin::ID_NEW, MainAppWin::ID_ABOUT, MainAppWin::MainMenuClick),
  FXMAPFUNCS(SEL_COMMAND, MainAppWin::ID_US, MainAppWin::ID_METRIC, MainAppWin::RadioBtnClick),
  FXMAPFUNC(SEL_COMMAND, MainAppWin::ID_OK, MainAppWin::CmdBtnClick),
  FXMAPFUNC(SEL_COMMAND, MainAppWin::ID_CANCEL, MainAppWin::CmdBtnClick),
  FXMAPFUNC(SEL_COMMAND, MainAppWin::ID_QUIT, MainAppWin::CmdBtnClick),
  FXMAPFUNC(SEL_SIGNAL, MainAppWin::ID_QUIT, MainAppWin::ProjectFinalizer),
  FXMAPFUNC(SEL_CLOSE, MainAppWin::ID_TITLE, MainAppWin::ProjectFinalizer)
};

FXIMPLEMENT(MainAppWin, FXMainWindow, Callbacks, ARRAYNUMBER(Callbacks))
/*
        Name       : MainAppWin

	Type       : Constructor

	Parameters : aApp (Pointer - FXApp) - Pointer to the application object in
	             the main program.

	Note       : Set the main and auxillary application icons in the function,
	             not the ancestor constructor (don't have icons yet)
*/
MainAppWin::MainAppWin(FXApp *aApp) :
FXMainWindow(aApp, "Turns-n-Layers", NULL, NULL, DECOR_ALL, 0, 0, 774, 600),
ProjStatus(NO_PROJ),
SaveStatus(SAVED),
CoreGeo(NO_CORE),
ProjType(NO_TYPE),
Metric(0),
ThisApp(aApp)

{

//              Create Application Icons

  FileSaveasIcon= new FXGIFIcon(ThisApp, filesaveas_gif);
  FilePrintIcon=  new FXGIFIcon(ThisApp, fileprint_gif);
  CopyIco=        new FXGIFIcon(ThisApp, editcopy_gif);
  HelpIcon=       new FXGIFIcon(ThisApp, help_gif);
  RectCoreIcon=   new FXGIFIcon(ThisApp, RectCore_gif);
  RndCoreIcon=    new FXGIFIcon(ThisApp, RoundCore_gif);
  WhatsThisIcon=  new FXGIFIcon(ThisApp, about_gif);
  Bg_DolphinIcon= new FXGIFIcon(ThisApp, smDolphin_gif);
  Sm_DolphinIcon= new FXGIFIcon(ThisApp, TinyDolphin_gif);
  ExitIco=        new FXGIFIcon(ThisApp, Exit_gif);
  OKCheckIco=     new FXGIFIcon(ThisApp, OKCheck_gif);
  CancelXIco=     new FXGIFIcon(ThisApp, CancelX_gif);
  LEDGrayIco=     new FXGIFIcon(ThisApp, LedGray_gif, 0, IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);
  LEDOnIco=       new FXGIFIcon(ThisApp, LedOn_gif, 0, IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);
  LEDOffIco=      new FXGIFIcon(ThisApp, LedOff_gif, 0, IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);

  LEDOnIco->create();
  LEDGrayIco->create();
  LEDOffIco->create();

  setIcon(Bg_DolphinIcon);
  setMiniIcon(Sm_DolphinIcon);
  setTarget(this);
  setSelector(ID_TITLE);

//------------------------------------------------------------------------------

//                     Layout Managers

  FXVerticalFrame   *MainLO;
  FXHorizontalFrame *BtnGroup, *SubLO, *TxtLO;
  FXMatrix          *Grid, *Grid1;
  FXGroupBox        *CoreDataGB, *WireDataGB, *RadioGB;

//                     Main Menu

  FXDockSite *DockUp, *DockDwn, *DockRt, *DockLt;
  DockUp=   new FXDockSite(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
  DockDwn=  new FXDockSite(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);
  DockRt=   new FXDockSite(this, LAYOUT_SIDE_RIGHT|LAYOUT_FILL_Y);
  DockLt=   new FXDockSite(this, LAYOUT_SIDE_LEFT|LAYOUT_FILL_Y);

  FXToolBarShell *MenuShell= new FXToolBarShell(this, FRAME_RAISED);
  FXMenuBar      *MainMenu=  new FXMenuBar(DockUp, MenuShell, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|
					   FRAME_RAISED);
  new FXToolBarGrip(MainMenu, MainMenu, FXMenuBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);

//                     Add menu items to menubar

  ProjMain= new FXMenuPane(this);
            new FXMenuTitle(MainMenu,"&Project", NULL, ProjMain);
	    new FXMenuCommand(ProjMain, "&New Project", NULL, this, ID_NEW);
	    new FXMenuSeparator(ProjMain);
            new FXMenuCommand(ProjMain, "&Total Turns", NULL, this, ID_TOTALTURNS);
            new FXMenuCommand(ProjMain, "&Wire Length", NULL, this, ID_WIRELENGTH);
            new FXMenuSeparator(ProjMain);
            new FXMenuCommand(ProjMain, "&Save as...", NULL, this, ID_SAVEAS);
            new FXMenuCommand(ProjMain, "&Print...", NULL, this, ID_PRINT);
            new FXMenuSeparator(ProjMain);
            new FXMenuCommand(ProjMain, "&Exit", NULL, this, ID_QUIT);

  CoreMain= new FXMenuPane(this);
            new FXMenuTitle(MainMenu, "&Cores", NULL, CoreMain);
            new FXMenuCommand(CoreMain, "&Rect", NULL, this, ID_RECT);
            new FXMenuCommand(CoreMain, "R&ound", NULL, this, ID_RND);

  HelpMain= new FXMenuPane(this);
            new FXMenuTitle(MainMenu, "&Help", NULL, HelpMain, LAYOUT_RIGHT);
            new FXMenuCommand(HelpMain, "&Contents...", NULL, this, ID_HELP);
            new FXMenuCommand(HelpMain, "&About...", NULL, this, ID_ABOUT);
	    new FXMenuSeparator(HelpMain);
	    new FXMenuCommand(HelpMain, "&Dolphins...", NULL, this, ID_SPECIAL);

  //                 2) Tool Bar: Create a dockable/floatable toolbar

  FXToolBarShell *TBShell= new FXToolBarShell(this, FRAME_RAISED);
  FXToolBar      *ToolBar= new FXToolBar(this, TBShell, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|
					 FRAME_RAISED);
  new FXToolBarGrip(ToolBar, ToolBar, FXToolBar::ID_TOOLBARGRIP, TOOLBARGRIP_DOUBLE);

  //                 3) Statusbar - Create now since we'll need it for tool tips

  StatusBar= new FXStatusBar(this,LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER|
			     FRAME_RAISED);
             new FXButton(StatusBar, "\tClick me!\tA special message for you",
			  Bg_DolphinIcon, this, ID_SPECIAL, LAYOUT_FILL_Y|LAYOUT_RIGHT);

	     new FXLabel(StatusBar, "Project Status", NULL, JUSTIFY_RIGHT|FRAME_NONE);
  StatusLbl= new FXLabel(StatusBar, "No Project", LEDGrayIco, LABEL_NORMAL|FRAME_NORMAL|ICON_BEFORE_TEXT);

  //                    Create the Toolbar Buttons

    new FXButton(ToolBar, "\tSave...\tSave current project to disk", FileSaveasIcon, this,
                 ID_SAVEAS, ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

    new FXButton(ToolBar, "\tPrint...\tPrint the current project", FilePrintIcon, this,
                 ID_PRINT, ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

    new FXFrame(ToolBar, FRAME_SUNKEN|LAYOUT_CENTER_Y|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH,
		0, 0, 2, 22);

    new FXButton(ToolBar, "\tRectangular\tSelect core with rectangular cross-section",
		 RectCoreIcon, this, ID_RECT, ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|
		 LAYOUT_TOP|LAYOUT_LEFT);

    new FXButton(ToolBar, "\tRound\tSelect core with round cross-section", RndCoreIcon, this,
                 ID_RND, ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

    new FXFrame(ToolBar,FRAME_SUNKEN|LAYOUT_CENTER_Y|LAYOUT_FIX_HEIGHT|LAYOUT_FIX_WIDTH,0,0,2,22);

    new FXButton(ToolBar, "\tAbout...\tInvoke the program \"About\" Box", WhatsThisIcon, this,
                 ID_ABOUT, ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

    new FXButton(ToolBar, "\tHelp...\tInvoke the on-line help", HelpIcon, this,
                 ID_HELP, ICON_ABOVE_TEXT|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_RIGHT);

    new FXToolTip(ThisApp, 0);

/*                   3) Create main layout for remaining window componenets:

                        A) Multi-line Display Box
                        B) Core Data Group Box
			   i)  5 Text Labels
			   ii) 5 Text Fields
			C) Wire Data group Box
			   i)  3 Text Labels
			   ii) 3 Text Fields
			D) Button Group
			   i)  OK Button
			   ii) Cancel Button
*/

  MainLO= new FXVerticalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL|FRAME_NORMAL);
  TxtLO=  new FXHorizontalFrame(MainLO, LAYOUT_SIDE_TOP|LAYOUT_FILL|FRAME_NORMAL);
  Output= new FXText(TxtLO, NULL, 0, TEXT_READONLY|TEXT_WORDWRAP|LAYOUT_FILL);
  Output->setVisibleRows(12);
  Output->setMarginLeft(20);
  Output->setMarginTop(20);
  Output->setMarginRight(10);
  Output->setMarginBottom(10);

  SubLO=      new FXHorizontalFrame(MainLO, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL|FRAME_NONE);
  RadioGB=    new FXGroupBox(SubLO, "Units", GROUPBOX_TITLE_CENTER|LAYOUT_FILL_X|
			     LAYOUT_CENTER_Y|FRAME_GROOVE);

  Units[0]=   new FXRadioButton(RadioGB, "American", this, ID_US);
  Units[1]=   new FXRadioButton(RadioGB, "Metric", this, ID_METRIC);
              new FXVerticalSeparator(SubLO);
  CoreDataGB= new FXGroupBox(SubLO, "Core Data", GROUPBOX_TITLE_CENTER|LAYOUT_FILL_X|
			     FRAME_GROOVE);
  Grid=       new FXMatrix(CoreDataGB, 5);

  HeightLbl= new FXLabel(Grid, "Core Height (in.)", NULL, JUSTIFY_LEFT);
  WidthLbl=  new FXLabel(Grid, "Core Width (in.)", NULL, JUSTIFY_LEFT);
  DiamLbl=   new FXLabel(Grid, "Core Diameter (in.)", NULL, JUSTIFY_LEFT);
  LengthLbl= new FXLabel(Grid, "Core Length (in.)", NULL, JUSTIFY_LEFT);
  ThickLbl=  new FXLabel(Grid, "Inter-layer Insulation (mils)", NULL, JUSTIFY_LEFT);

  DataIn[0]= new FXTextField(Grid, 16, this, ID_CHEDIT, TEXTFIELD_LIMITED|FRAME_NORMAL);
  DataIn[1]= new FXTextField(Grid, 16, this, ID_CWEDIT, TEXTFIELD_LIMITED|FRAME_NORMAL);
  DataIn[2]= new FXTextField(Grid, 16, this, ID_CDEDIT, TEXTFIELD_LIMITED|FRAME_NORMAL);
  DataIn[3]= new FXTextField(Grid, 16, this, ID_CLEDIT, TEXTFIELD_LIMITED|FRAME_NORMAL);
  DataIn[4]= new FXTextField(Grid, 16, this, ID_ILEDIT, TEXTFIELD_LIMITED|FRAME_NORMAL);

               new FXVerticalSeparator(SubLO);
  WireDataGB=  new FXGroupBox(SubLO, "Wire Data", GROUPBOX_TITLE_CENTER|LAYOUT_FILL_X|
			      LAYOUT_CENTER_Y|FRAME_GROOVE);
  Grid1=       new FXMatrix(WireDataGB, 3);
  WireDiamLbl= new FXLabel(Grid1, "Wire Gage (AWS)", NULL, JUSTIFY_LEFT);
  WireLenLbl=  new FXLabel(Grid1, "Wire Length (ft.)", NULL, JUSTIFY_LEFT);
               new FXLabel(Grid1, "Total Turns", NULL, JUSTIFY_LEFT);
  DataIn[5]=   new FXTextField(Grid1, 16, this, ID_GEDIT, TEXTFIELD_LIMITED|FRAME_NORMAL);
  DataIn[6]=   new FXTextField(Grid1, 16, this, ID_WLEDIT, TEXTFIELD_LIMITED|FRAME_NORMAL);
  DataIn[7]=   new FXTextField(Grid1, 16, this, ID_TTEDIT, TEXTFIELD_LIMITED|FRAME_NORMAL);

  BtnGroup=    new FXHorizontalFrame(MainLO, FRAME_NORMAL|LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);

               new FXButton(BtnGroup, "&OK", OKCheckIco, this, ID_OK,
			   ICON_BEFORE_TEXT|FRAME_RAISED|FRAME_THICK|LAYOUT_LEFT);

               new FXButton(BtnGroup, "&Cancel", CancelXIco, this, ID_CANCEL,
			   ICON_BEFORE_TEXT|FRAME_RAISED|FRAME_THICK|LAYOUT_LEFT);

	       new FXButton(BtnGroup, "&Exit", ExitIco, this, ID_QUIT,
			    ICON_BEFORE_TEXT|LAYOUT_SIDE_RIGHT|FRAME_RAISED|FRAME_THICK|
			    LAYOUT_RIGHT);

    Units[0]->setCheck(TRUE);
    Output->setTabColumns(10);
    Output->setText("Physical Design of Coils:\n");

/*
                                     GUI Complete

         Build the wire characteristic table: data from
         _Design and Construction of Induction Coils_ by
         A. Frederick Collins, Lindsay Publications Inc.
         Bradley, IL 60915, 1990. Indices correspond to
         wire gage.
*/

//  (Wire Diameter(in.), Ohms/1000', Lbs/1000'

  Table[0]=  new Wire(0.32486, 0.0983, 319.45);
  Table[1]=  new Wire(0.2893, 0.124, 253.34);
  Table[2]=  new Wire(0.25763, 0.1564, 200.91);
  Table[3]=  new Wire(0.22942, 0.1972, 159.32);
  Table[4]=  new Wire(0.20431, 0.2486, 126.35);
  Table[5]=  new Wire(0.18194, 0.3136, 100.2);
  Table[6]=  new Wire(0.16202, 0.3954, 79.462);
  Table[7]=  new Wire(0.14428, 0.4987, 63.013);
  Table[8]=  new Wire(0.12849, 0.6529, 49.976);
  Table[9]=  new Wire(0.11443, 0.7892, 39.636);
  Table[10]= new Wire(0.10189, 0.8441, 31.426);
  Table[11]= new Wire(0.09074, 1.254, 24.924);
  Table[12]= new Wire(0.0808, 1.58, 19.766);
  Table[13]= new Wire(0.07196, 1.995, 15.674);
  Table[14]= new Wire(0.06408, 2.504, 12.436);
  Table[15]= new Wire(0.05706, 3.172, 9.859);
  Table[16]= new Wire(0.05082, 4.001, 7.819);
  Table[17]= new Wire(0.04525, 5.04, 6.199);
  Table[18]= new Wire(0.0408, 6.36, 4.916);
  Table[19]= new Wire(0.03589, 8.25, 3.899);
  Table[20]= new Wire(0.03196, 10.12, 3.094);
  Table[21]= new Wire(0.02846, 12.76, 2.452);
  Table[22]= new Wire(0.02534, 16.25, 1.945);
  Table[23]= new Wire(0.02257, 20.3, 1.542);
  Table[24]= new Wire(0.0201, 25.6, 1.223);
  Table[25]= new Wire(0.0179, 32.2, 0.9699);
  Table[26]= new Wire(0.01594, 40.7, 0.7692);
  Table[27]= new Wire(0.01419, 51.3, 0.6099);
  Table[28]= new Wire(0.01264, 64.8, 0.4807);
  Table[29]= new Wire(0.01125, 81.6, 0.3835);
  Table[30]= new Wire(0.01002, 103.0, 0.3002);
  Table[31]= new Wire(0.00892, 130.0, 0.2413);
  Table[32]= new Wire(0.00795, 164.0, 0.1913);
  Table[33]= new Wire(0.00708, 206.0, 0.1517);
  Table[34]= new Wire(0.0063, 260.0, 0.1204);
  Table[35]= new Wire(0.00561, 328.0, 0.0956);
  Table[36]= new Wire(0.005, 414.0, 0.0757);
  Table[37]= new Wire(0.00445, 523.0, 0.06);
  Table[38]= new Wire(0.00396, 660.0, 0.0475);
  Table[39]= new Wire(0.00353, 832.0, 0.0875);
  Table[40]= new Wire(0.00314, 1049.0, 0.0299);

  Results= new FXString();

}

//--------------------------------------------------------------------------------
/*
        Name: ~MainAppWin

	Type: Destructor

	Parameters: None

	Note: Clean up all explicitly allocated FOX pointers. Let FOX take
	      care of the rest. Clean up our own objects.
*/
MainAppWin::~MainAppWin(void)
{
  delete FileSaveasIcon;
  delete FilePrintIcon;
  delete CopyIco;
  delete HelpIcon;
  delete RectCoreIcon;
  delete RndCoreIcon;
  delete WhatsThisIcon;
  delete ExitIco;
  delete OKCheckIco;
  delete CancelXIco;
  delete Bg_DolphinIcon;
  delete Sm_DolphinIcon;
  delete LEDGrayIco;
  delete LEDOnIco;
  delete LEDOffIco;
  delete ProjMain;
  delete CoreMain;
  delete HelpMain;
  delete Results;
  
  for (int i= 0; i < MINGAGE + 1; i++) delete Table[i];

}

/*
        Name: create

        Type: Subroutine (void function)

        Parameters: None

        Note: FOX maintenance routine. Called from the main program on start-up.
              Calls the ancestor class create subroutine for initialization, then
	      calls "show" to actually display the window.
*/
void MainAppWin::create(void)
{
  FXMainWindow::create();
  show(PLACEMENT_SCREEN);  //  Puts window in center of the screen.
}
//  End create

/*------------------------- Event Handlers: Command ----------------------------

        Note: These are the command event handlers, called in
	      response to a SEL_COMMAND signal. All FOX event handlers use these
	      Parameters:
	                  Sender (Pointer: FXObject) - Pointer to the calling widget
			  object.

			  Select (FXSelector) - Simple hash of the calling widget's
			  target ID and the signal ID.

			  Data (Pointer: void) - Pointer to any extra data the caller
			  may have sent. (Cast to required type before use).

              Returns:
                       0 (long) -  Event not handled, send up the class hierarchy to find
		                   another event handler or ignore. GUI update not required.

		       1 (long) -  Event handled successfully. GUI update may be required.

------------------------------------------------------------------------------*/

long MainAppWin::MainMenuClick(FXObject *Sender, FXSelector IDHash, void*)
{
    long RetCode;
    FXuint CallerID= FXSELID(IDHash);

    switch (CallerID)
    {
      case ID_NEW:        RetCode= NewMenuExe(); break;

      case ID_RECT:

      case ID_RND:
      
      case ID_TOTALTURNS:

      case ID_WIRELENGTH: RetCode= ProjectSelector(CallerID); break;

      case ID_SAVEAS:     RetCode= ProjectSaver(); break;

      case ID_PRINT:      RetCode= ProjectPrinter(); break;

      case ID_HELP:

      case ID_ABOUT:

      case ID_SPECIAL:    RetCode= Dialogs(CallerID); break;

      case ID_QUIT:       RetCode= ProjectFinalizer(Sender, IDHash, 0); break;
    }

    return RetCode;
}

//------------------------------------------------------------------------------

long MainAppWin::CmdBtnClick(FXObject *Sender, FXSelector IDHash, void*)
{
  long RetCode= 0;

  switch (FXSELID(IDHash))
  {
      case ID_OK:
	
	  RetCode= OKCmdExe();
	  if (! RetCode) return 0;
	  ProjStatus= PROJ_COMP;
	  SaveStatus= NOT_SAVED;
	  StatusLbl->setText("Project Complete; Not Saved");
	  break;

      case ID_CANCEL:

          ProjStatus=  PROJ_PEND;
	  CoreGeo=     NO_CORE;
	  ProjType=    NO_TYPE;

          for (int i= 0; i < ALL_EDITS; i++) DataIn[i]->setText("");

	  break;

      case ID_QUIT:   ProjectFinalizer(Sender, IDHash, 0); break;
  }

  return RetCode;
}

//______________________________________________________________________________

long MainAppWin::RadioBtnClick(FXObject*, FXSelector IDHash, void*)
{
    FXuint Select= FXSELID(IDHash);

    Metric= (Select == ID_METRIC) ? 1 : 0;

    if (Metric)
    {
	HeightLbl->setText("Core Height (mm/cm)");
	WidthLbl->setText("Core Width (mm/cm)");
	DiamLbl->setText("Core Diameter (mm/cm)");
	LengthLbl->setText("Core Length (mm/cm)");
	ThickLbl->setText("Inter-layer Insulation Thickness (mm)");
	WireDiamLbl->setText("Wire Diameter (mm)");
	WireLenLbl->setText("Wire Length (meters)");
    }
    else
    {
	HeightLbl->setText("Core Height (in.)");
	WidthLbl->setText("Core Width (in.)");
	DiamLbl->setText("Core Diameter (in.)");
	LengthLbl->setText("Core Length (in.)");
	ThickLbl->setText("Inter-layer Insulation Thickness (mils)");
	WireDiamLbl->setText("Wire Gage (AWS)");
	WireLenLbl->setText("Wire Length (ft)");
    }

    return 1;
} 

//-------------------------- Event Handlers: Update ----------------------------
/*
         Note: These functions are called in response to a GUI update request
	       sent by the system's idle message. These keep the app's
	       widgets up to date with the current state of the app.
*/

/*
        Name: AllEditsUD

	Flags: ProjStatus, CoreGeo

	Activates/deactivates the line edit fields
*/

long MainAppWin::AllEditsUD(FXObject *Sender, FXSelector IDHash, void*)
{
    FXuint CallerID= FXSELID(IDHash);
    
    if ((ProjStatus == NO_PROJ) || (ProjStatus == PROJ_COMP))
    {
        Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
        return 1;
    }
    else if ((CallerID == ID_CLEDIT) || (CallerID == ID_ILEDIT) || (CallerID == ID_GEDIT))
    {
        Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0);
	return 1;
    }

    switch (CallerID)
    {
      case ID_CWEDIT:

      case ID_CHEDIT:
	
	(CoreGeo == RECT_CORE) ? Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0) :
	  Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	break;

      case ID_CDEDIT:

	(CoreGeo == RND_CORE) ? Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0) :
	  Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	break;

      case ID_TTEDIT:

        (ProjType == WL_TYPE) ? Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0) :
	  Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	break;

      case ID_WLEDIT:

	(ProjType == TT_TYPE) ? Sender->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0) :
	  Sender->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	break;
    }

    return 1;
}

//------------------------------------------------------------------------------

long MainAppWin::RadioBtnUD(FXObject *Sender, FXSelector IDHash, void*)
{
    FXRadioButton *Current= (FXRadioButton*)Sender;

    (ProjStatus == PROJ_COMP) ? Current->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0) :
	Current->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0);

    switch (FXSELID(IDHash))
    {
        case ID_US: (Metric) ? Current->setCheck(FALSE) : Current->setCheck(TRUE); break;

        case ID_METRIC: (Metric) ? Current->setCheck(TRUE) : Current->setCheck(FALSE); break;
    }

    return 1;
}

//------------------------------------------------------------------------------

/*
       Name: MenuItemsUD

       Flags: ProjStatusus

       Updates main menu entries and associated toolbar buttons
*/

long MainAppWin::MenuItemsUD(FXObject *Caller, FXSelector Ident, void*)
{
    switch(FXSELID(Ident))
    {
        case ID_PRINT:

        case ID_NEW:
	    (ProjStatus == PROJ_COMP) ?
		Caller->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0) :
		Caller->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	    break;

        case ID_SAVEAS:
	    ((ProjStatus == PROJ_COMP) && (SaveStatus == NOT_SAVED)) ?
		Caller->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0) :
		Caller->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	    break;

        case ID_TOTALTURNS:

        case ID_WIRELENGTH:
	    ProjType ?
		Caller->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0) :
	        Caller->handle(this, FXSEL(SEL_COMMAND, ENABLE),0);
	    break;

        case ID_RECT:

        case ID_RND:
	    (ProjStatus == NO_PROJ) ?
		Caller->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0) :
		Caller->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0);
    }

    return 1;
}

//------------------------------------------------------------------------------

/*
        Name: CmdBtnUD

	Flags: ProjStatus

	Updates the command buttons
*/

long MainAppWin::CmdBtnUD(FXObject *Caller, FXSelector Ident, void*)
{
    FXuint CallerID= FXSELID(Ident);

    if ((CallerID == ID_CANCEL) && (ProjStatus == PROJ_COMP))
    {
	Caller->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
	return 1;
    }

    (ProjStatus == PROJ_PEND) ? Caller->handle(this, FXSEL(SEL_COMMAND, ENABLE), 0) :
	Caller->handle(this, FXSEL(SEL_COMMAND, DISABLE), 0);
    return 1;
}

//------------------------ Functions: Application  ----------------------------

/*
        Name: ProjectSelector

	Type: long function

	Parameters: Select (FXuint)

	Returns: 1 - Signals the application that the message was handled
                     successfully

	Note: Sets the Project status and project type flags

*/

long MainAppWin::ProjectSelector(FXuint Select)
{
    switch (Select)
    {
      case ID_TOTALTURNS: ProjType= TT_TYPE; break;

      case ID_WIRELENGTH: ProjType= WL_TYPE; break;

      case ID_RECT:       CoreGeo= RECT_CORE; break;

      case ID_RND:        CoreGeo= RND_CORE;
    }

    StatusLbl->setText("Project Pending");
    StatusLbl->setIcon(LEDOffIco);
    ProjStatus=  PROJ_PEND;
    SaveStatus= NOT_SAVED;
    return 1;
}

//------------------------------------------------------------------------------

/*
         Name: ProjectSaver

	 Type: long function

	 Parameters: unused

	 Note: Saves the current project, and propmts for a file name.
 */
long MainAppWin::ProjectSaver(void)
{
    FXString FileName;
    FXuint Code;

    FXFileDialog SaveDlg(this, "Save Project to File");
    SaveDlg.setSelectMode(SELECTFILE_ANY);
    SaveDlg.setPatternList("Project (*.tnl)\nText (*.txt)\nAny (*.*)");
    SaveDlg.setCurrentPattern(0);

    if (! SaveDlg.execute(PLACEMENT_OWNER))
    {
        FXMessageBox::information(ThisApp, MBOX_OK, "Turns-n-Layers Advisory", "File Save Cancelled");
        return 0;
    }

    FileName= SaveDlg.getFilename();

    if (FXStat::exists(FileName))
      Code= FXMessageBox::question(ThisApp, MBOX_YES_NO, "Turns-n-Layers Question",
				   "Overwrite File: %s", FileName.text());

    if (Code == MBOX_CLICKED_NO) return 1;

    FXFile WriteFile(FileName, FXFile::Writing);
    WriteFile.writeBlock(Results->text(), Results->length());
    SaveStatus= SAVED;
    StatusLbl->setText("Project Saved");
    StatusLbl->setIcon(LEDOnIco);
    return 1;
}

//------------------------------------------------------------------------------

/*
        Name: ProjectPrinter

	Type: long function

	Parameters: unused

	Note: Prints the project. this involves a hack
	      since the FOX Print D.C. is still under
	      development. Need to copy the text output
	      to another substring in order to print
	      seperate lines. Otherwise, print treats it
	      as one long line and runs off the page.
 */
long MainAppWin::ProjectPrinter(void)
{
    FXint Length;                         //  Length of the text buffer, line to print
    const FXint X_Margin= 60;             //  Page metrics: fix the left margin
    FXint Y_Margin=       60, LineHeight; //  Page metrics: start of top margin and line spacing

    const FXchar *Buffer, *Head, *Tail;
    FXchar    C;
    FXint     i= 1;
    FXdouble  PageHeight;
    FXPrinter ThePrinter;

    Buffer= Head= Tail= 0;
/*
          Invoke print dialog box to get the system printer
	  and set it up for printing
*/
    FXPrintDialog PDlgBox(this, "Print Current Project");
    if (PDlgBox.execute(PLACEMENT_OWNER))
    {
      PDlgBox.getPrinter(ThePrinter);
      FXDCPrint Pdc(ThisApp);  
      if (! Pdc.beginPrint(ThePrinter))
      {
        FXMessageBox::error(this, MBOX_OK, "Turns-n-Layers Error", "Print Fault");
        return 1;
      }

      Length=          Results->length();
      FXFont *SysFont= ThisApp->getNormalFont();
      LineHeight=      SysFont->getFontHeight();
      PageHeight=      ThePrinter.mediaheight;

      FXchar OneLine[Length];
      Pdc.setFont(SysFont);
      Pdc.beginPage(i);
      Results->append('\n');
      Buffer= Results->text();
      Head=   Tail= Buffer;
/*
          Note: Parse the text buffer into a new string at the newline
	        breaks. Otherwise, printer treats the buffer as one
		long string. FOX bug or ideosyncracy?

          1)  Parse the string to newline (character copy)
	  2)  Append C string terminator (ASCII Null)
	  3)  Draw text into image and print.
	  4)  Update the vertical margin, and reset to grab the next line.
*/
      while ((C= *Head++))
      {
	  if (C == '\n')
	  {
	      memcpy(&OneLine[0], Tail, Head-Tail);
	      OneLine[Head-Tail - 1]= '\0';
	      Pdc.drawText(X_Margin, Y_Margin, OneLine, Head-Tail);
	      Y_Margin+= LineHeight;
	      Tail= Head;

	      if (PageHeight - Y_Margin < 145)
	      {
		  Pdc.endPage();
		  Y_Margin= 60;
		  Pdc.beginPage(i++);
	      }
	  }
      }

      Pdc.endPage();
      Pdc.endPrint();
    }

    else FXMessageBox::information(this, MBOX_OK, "Turns-n-Layers Advisory", "Print job cancelled");

    return 1;
}

//------------------------------------------------------------------------------

/*
         Name: ProjectFinalizer

	 Type: long function

	 Parameters: none

	 Note: Sets up for app exit. Prompts to save the current project if
	       this hasn't been done already.
 */
long MainAppWin::ProjectFinalizer(FXObject*, FXSelector, void*)
{
    FXint Code= -1;

    if ((SaveStatus != SAVED) && (ProjStatus == PROJ_COMP))
	Code= FXMessageBox::warning(ThisApp, MBOX_QUIT_CANCEL, "Turns-n-Layers Warning",
				    EXIT_Q);

    switch(Code)
    {
        case MBOX_CLICKED_QUIT: ThisApp->exit(0); break;

        case MBOX_CLICKED_CANCEL: return 0;
    }

    ThisApp->exit(0);
    return 0;
}

//------------------------------------------------------------------------------

/*
        Name: Dialogs

	Type: long function

	Parameters: Select (FXSelector (uint))
       	    
	Returns: 1 - Message was successfully handled
*/

long MainAppWin::Dialogs(FXuint Select)
{
    FXDialogBox *MsgBox;  

    switch (Select)
    {
      case ID_ABOUT:
	  MsgBox= new About(ThisApp);
	  MsgBox->execute(PLACEMENT_OWNER);
	  break;

      case ID_SPECIAL:
	  MsgBox= new SplMsgBox(ThisApp);
	  MsgBox->execute(PLACEMENT_OWNER);
	  break;

      case ID_HELP:
          MsgBox= new HelpCntsBox(ThisApp);
          MsgBox->execute(PLACEMENT_OWNER);
          break;

    }

    delete MsgBox;

    return 1;
}

//------------------------------------------------------------------------------

/*
     Name: GetData

     Type: Function (double)

     Parameters: UsrEntry (Pointer: FXTextField object)

     Returns: User entered data. Dimensioned values converted to inches.
              Perform sanity checks to see if user entered data is complete/
	      valid.
*/

FXdouble MainAppWin::GetData(FXTextField *UsrData)
{
    FXdouble Val, RetVal;
    FXString Text;

    Text= UsrData->getText();
    Val= RetVal= FXDoubleVal(Text);

    if (!Val) return 0;

    if (Metric)
    {
	if (UsrData == DataIn[7]) return RetVal;
	if (Text.find("eter") > -1)    RetVal= METER2IN(Val);
	else if (Text.find("M") > -1)  RetVal= METER2IN(Val);
	else if (Text.find("cm") > -1) RetVal= CM2IN(Val);
	else RetVal= MM2IN(Val);
    }

    return RetVal;
}

//------------------------------------------------------------------------------

long MainAppWin::OKCmdExe(void)
{
    FXdouble CoreWidth, CoreHeight, CoreDiam, CoreLength, WireDiam, WireLen, Ilit;
    FXint    Gage, NumTurns, TurnsPerLayer, NoLayers;
    
    if (CoreGeo == RECT_CORE)
    {
        CoreDiam=   0;
        CoreWidth=  GetData(DataIn[1]);
        CoreHeight= GetData(DataIn[0]);

        if (! ((CoreWidth) && (CoreHeight))) ENTRY_ERR("The entry for core height and/or width missing")
    }
    else
    {
        CoreWidth= CoreHeight= 0;
        CoreDiam= GetData(DataIn[2]);
        if (! CoreDiam) ENTRY_ERR("The entry for core diameter missing")
    }

    CoreLength= GetData(DataIn[3]);
    
    if (! CoreLength) ENTRY_ERR("The entry for core length is missing")

    Ilit= (Metric) ? GetData(DataIn[4]) : GetData(DataIn[4])/1000.0;

    if (Metric)
    {
        Gage= -1;
        WireDiam= GetData(DataIn[5]);
	if (! WireDiam) ENTRY_ERR("Wire diameter entry missing and/or invalid")
    }
    else
    {
        Gage= int(GetData(DataIn[5]));
        if ((Gage < MAXGAGE) || (Gage > MINGAGE)) ENTRY_ERR("Gages larger than 0 or less than 40 are not supported")
        WireDiam= Table[Gage]->Diameter();
    }

    CoreData ProjResults(CoreDiam, CoreWidth, CoreHeight, CoreLength, Ilit);

    if (ProjType == TT_TYPE)
    {
        WireLen= GetData(DataIn[6]) * 12.0;

	if (! WireLen) ENTRY_ERR("The entry for wire length is missing")

        NumTurns= *((FXint*)CalcCoreData(ProjResults, WireDiam, WireLen, 0, TurnsPerLayer, NoLayers));
    }
    else
    {
        NumTurns= GetData(DataIn[7]);
	if (! NumTurns) ENTRY_ERR("The entry for total turns is missing")
        WireLen= *((FXdouble*)CalcCoreData(ProjResults, WireDiam, 0, NumTurns, TurnsPerLayer, NoLayers));
    }

    WriteOut(ProjResults, NumTurns, NoLayers, WireLen, TurnsPerLayer, Gage, WireDiam);
    return 1;
}

//------------------------------------------------------------------------------

long MainAppWin::NewMenuExe(void)
{
    FXuint Code;
    long RetCode;
    
    if (SaveStatus != SAVED)
        Code= FXMessageBox::warning(ThisApp, MBOX_YES_NO_CANCEL, "Turns-n-Layers Warning", SAVE_Q);
    
    if (Code == MBOX_CLICKED_YES) RetCode= ProjectSaver();

    ProjStatus=  NO_PROJ;
    CoreGeo=     NO_CORE;
    ProjType=    NO_TYPE;
    SaveStatus=  SAVED;
    Metric=      0;

    RetCode= RadioBtnClick(this, FXSEL(SEL_COMMAND, ID_US), 0);
    for (int i= 0; i < ALL_EDITS; i++) DataIn[i]->setText("");

    Results->clear();
    Output->setText("Physical Design of Coils\n");
    StatusLbl->setText("No Project");
    StatusLbl->setIcon(LEDGrayIco);
    return RetCode;
}

//------------------------------------------------------------------------------

/*
    Name: CalcCoreData

    Type: Function (Pointer: void)

    Parameters:
                aPD (Pointer: TCoreData) - Pointer to "PhysicalData" passed from
                main program. Structure holding the core dimensions. Use an
		object to group related data to keep number of seperate
		parameters down.

                Entry (Pointer: Wire) - Pointer to the wire characteristic table
                entry  requested by the user.

		aWL (FXdouble) - Wire length (feet)

                aTotTurns (FXint) - the coil's total number of turns

                aTpl (Reference: FXint) - Turns per layer. A calculated value
                returned to main program.

                aNoLayers (Reference: FXint) - Number of layers. A calculated value
                returned to main program.

    Returns: This function returns either an FXint or an FXdouble, depending
             on the project request. These returns are cast to type void*, and re-cast by the
	     calling routine.

	     Returns: Wire length (in)
	              Total turns.

             Other Returns:
                            Coil diameter (in.)
			    Coil X-Sect height (in.)
			    Coil X-Sect width (in.)

			    Note: these values are returned via the aPD pointer.

    Note: All calculations done in inches.
*/

void* MainAppWin::CalcCoreData
(CoreData &aPD, FXdouble WireDiam, const FXdouble aWL, const FXint aTotTurns,
 FXint &aTpl, FXint &aNoLayers)
{
   FXbool   NotDone;
   FXdouble cd, ch, cw, cl, ilit;
   FXdouble Lpt;
   FXint    NoLayers, Tpl, Turns;
   void    *RetVal= 0;

//          Static: Returning pointers, not the actual values themselves

   static FXdouble Length=  0;
   static FXint    NoTurns= 0;

   NoTurns=    0;
   Turns=      0;
   NoLayers=   0;
   Length=     aWL;


/*
     Read core metrics:

          cd: Core diameter (in.)
	  ch:   "  height (in.)
	  cw:   "  width (in.)
	  cl:   "  length (in.)
	  ilit: Inter-layer insulation thickness (in.)
*/
   cd=   aPD.CoreDiam;      
   ch=   aPD.CoreHeight;
   cw=   aPD.CoreWidth;
   cl=   aPD.CoreLength;
   ilit= aPD.Ilit;

   Tpl= int(cl/WireDiam);  //  Tpl: Turns per layer

   do
   {
      Lpt= cd ? (PI * cd) : (2 * (ch + cw));  //  Lpt:  Length per turn (in.)

      for (int i= 0; i < Tpl; i++)  //      Wind a layer
      {
	if (aTotTurns)
	{
	    Length+= Lpt;

	    if (aTotTurns == Turns++)
	    {
		NotDone= FALSE;
		break;
	    }
	    else NotDone= TRUE;
	}
	else if (aWL)
	{
	    Length-= Lpt;
	    NoTurns++;
	    if (Length <= 0)
	    {
		NotDone= FALSE;
		Length= 0;
		break;
	    }
	    else NotDone= TRUE;
	}
      }

      NoLayers++;
      if (cd) cd+= 2 * (WireDiam + ilit);  //  Account for growing dimensions of coil
      else
      {
         cw+= (2 * (WireDiam + ilit));
         ch+= (2 * (WireDiam + ilit));
      }
   } while (NotDone);

//        Set return values

   aTpl=           Tpl;
   aNoLayers=      NoLayers;
   aPD.CoreDiam=   cd;
   aPD.CoreWidth=  cw;
   aPD.CoreHeight= ch;

//        Cast return types to void*

   RetVal= Length ? (void*)&Length : (void*)&NoTurns;

   return RetVal;
}

//------------------------------------------------------------------------------

void MainAppWin::WriteOut(CoreData &aPR, FXint aNoTurns, FXint aNoLyr, FXdouble aWL, FXint aTpL, FXint aGage, FXdouble aWD)
{
  FXdouble CoreDiam, CoreWidth, CoreHeight, CoreLength, Ilit;
  CoreDiam=   aPR.CoreDiam;
  CoreWidth=  aPR.CoreWidth;
  CoreHeight= aPR.CoreHeight;
  CoreLength= aPR.CoreLength;
  Ilit=       aPR.Ilit;

  Results->append("\tCoil Details\n");

  if (Metric)
  {
      if (CoreDiam) Results->append(FXStringFormat("\nCore Diameter: %s", FormatData(CoreDiam, 'c').text()));
      else
      {
	  Results->append(FXStringFormat("\nCore Width: %s", FormatData(CoreWidth, 'c').text()));
	  Results->append(FXStringFormat("Core Height: %s", FormatData(CoreHeight, 'c').text()));
      }

      Results->append(FXStringFormat("Core Length: %s", FormatData(CoreLength, 'c').text()));
      Results->append(FXStringFormat("Interlayer Insulation: %s", FormatData(Ilit, 'm').text()));
      Results->append(FXStringFormat("Turns per Layer: %d\n", aTpL));
      Results->append(FXStringFormat("Number of Layers: %d\n", aNoLyr));
      Results->append(FXStringFormat("Total Turns: %d\n", aNoTurns));
      Results->append(FXStringFormat("Wire Length Needed: %s", FormatData(aWL, 'M').text()));
      Results->append(FXStringFormat("Wire Diameter: %s", FormatData(aWD, 'm').text()));
      Output->setText(*Results);
      return;
  }

  if (CoreDiam) Results->append(FXStringFormat("\nCore Diameter: %s", FormatData(CoreDiam, 'i').text()));
  else
  {
      Results->append(FXStringFormat("\nCore Width: %s", FormatData(CoreWidth, 'i').text()));
      Results->append(FXStringFormat("Core Height: %s", FormatData(CoreHeight, 'i').text()));
  }

  Results->append(FXStringFormat("Core Length: %s", FormatData(CoreLength, 'i').text()));
  Results->append(FXStringFormat("Interlayer Insulation: %s", FormatData(Ilit, 'i').text()));
  Results->append(FXStringFormat("Turns per Layer: %d\n", aTpL));
  Results->append(FXStringFormat("Number of Layers: %d\n", aNoLyr));
  Results->append(FXStringFormat("Total Turns: %d\n", aNoTurns));
  Results->append(FXStringFormat("Wire Length Needed: %s", FormatData(aWL, 'f').text()));
  Results->append(FXStringFormat("Wire Gage: %d\n", aGage));
  Output->setText(*Results);
}

//------------------------------------------------------------------------------

FXString& MainAppWin::FormatData(FXdouble aVal, const FXchar aDim)
{
    static FXString RetVal;

    RetVal.clear();

    switch (aDim)
    {
        case 'm': RetVal= FXStringFormat("%f mm\n", IN2MM(aVal)); break;

        case 'c': RetVal= FXStringFormat("%f cm\n", IN2CM(aVal)); break;

        case 'M': RetVal= FXStringFormat("%f meters\n", IN2MTR(aVal)); break;

        case 'i': RetVal= FXStringFormat("%f inches\n", aVal); break;

        case 'f': RetVal= FXStringFormat("%f feet\n", aVal/12.0); break;

    }

    return RetVal;
}

//----------------------------- sdmainwindow.cpp ------------------------------
