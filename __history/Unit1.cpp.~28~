//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmainMenu *mainMenu;
//---------------------------------------------------------------------------
__fastcall TmainMenu::TmainMenu(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TmainMenu::exitButtonClick(TObject *Sender)
{
 if (MessageDlg("Are you sure you want to exit?", mtConfirmation,
				   TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
	{
		Application->Terminate();
	}
}
//---------------------------------------------------------------------------
void __fastcall TmainMenu::logButtonClick(TObject *Sender)
{
	ShowMessage("Log Button Clicked!") ;
	 if (!Form3) {
		Form3 = new TForm3(this);
	}
	this->Hide();
	Form3->Show();
}
//---------------------------------------------------------------------------

