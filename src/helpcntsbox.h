//------------------------------- helpcntsbox.h  -------------------------------

#ifndef HCB_H
#define HCB_H

#include <fox-1.6/fx.h>

#define HELP_ERR \
"Failed to open the file: help.txt"\
"\nMissing or corrupt?"

class HelpCntsBox : public FXDialogBox
{
    FXDECLARE(HelpCntsBox)

    public:

      HelpCntsBox(FXApp *aApp);
      virtual ~HelpCntsBox(void);

      enum
      {
          ID_CLOSE= FXDialogBox::ID_LAST,
          ID_LAST
      };

    protected:

        FXIcon *DolphinIco, *ExitIco;
	FXchar *Buffer;

        HelpCntsBox(void) {}
        HelpCntsBox(const HelpCntsBox&);
};

#endif

//------------------------------- helpcntsbox.h  -------------------------------
