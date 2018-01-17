//------------------------------ helpcntsbox.cpp  ------------------------------

#include "helpcntsbox.h"
#include "icons.h"
#include "defs.h"
#include "locations.h"

FXDEFMAP(HelpCntsBox) Callbacks[]=
{
  FXMAPFUNC(SEL_CLOSE, HelpCntsBox::ID_CLOSE, FXDialogBox::onCmdAccept)
};

FXIMPLEMENT(HelpCntsBox, FXDialogBox, Callbacks, ARRAYNUMBER(Callbacks))

HelpCntsBox::HelpCntsBox(FXApp *aApp) :
FXDialogBox(aApp, "Turns-n-Layers Help", DECOR_ALL, 0, 0, 455, 515, 6, 6, 6, 6, 4, 4)
{
  FXVerticalFrame *MainLO;
  FXHorizontalFrame *CmdBtnLO, *TxtLO;
  FXText *Display;
  FXButton *CloseBtn;
  FXint Length;

  DolphinIco= new FXGIFIcon(aApp, atldolphin_gif);
  ExitIco= new FXGIFIcon(aApp, Exit_gif);

  setTarget(this);
  setSelector(ID_CLOSE);

  MainLO= new FXVerticalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL|FRAME_SUNKEN|FRAME_THICK);
  TxtLO= new FXHorizontalFrame(MainLO, LAYOUT_SIDE_TOP|LAYOUT_FILL|FRAME_SUNKEN|FRAME_THICK);
  Display= new FXText(TxtLO, NULL, 0, TEXT_READONLY|TEXT_WORDWRAP|LAYOUT_FILL);
  CmdBtnLO= new FXHorizontalFrame(MainLO, LAYOUT_SIDE_BOTTOM|FRAME_GROOVE|LAYOUT_FILL_X);
  CloseBtn= new FXButton(CmdBtnLO, "&Close", ExitIco, this, FXDialogBox::ID_ACCEPT,
			 BUTTON_INITIAL|BUTTON_DEFAULT|ICON_BEFORE_TEXT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK);

  Display->setVisibleRows(35);
  Display->setVisibleColumns(75);
  Display->setTabColumns(7);

  FXFile ReadHelp(DOC_PATH, FXFile::Reading);

  if (! ReadHelp.isOpen()) FXMessageBox::error(aApp, MBOX_OK, "Turns-n-Layers Error", HELP_ERR);

  Length= ReadHelp.size();
  FXMALLOC(&Buffer, FXchar, CEIL(Length+1));
  ReadHelp.readBlock(Buffer, Length);
  Display->setText(Buffer, Length);

  CloseBtn->setFocus();
}

//------------------------------------------------------------------------------

HelpCntsBox::~HelpCntsBox(void)
{
  delete DolphinIco;
  delete ExitIco;
  FXFREE(&Buffer);
}

//------------------------------ helpcntsbox.cpp  ------------------------------
