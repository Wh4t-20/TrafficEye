//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
#include "Unit5.h"
#include "Unit3.h"
#include "Unit4.h"
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

	this->Hide();
	Form3->Show();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TmainMenu::searchButtonClick(TObject *Sender)
{

	this->Hide();
	Form2->Show();
}
//---------------------------------------------------------------------------



void __fastcall TmainMenu::loadButtonClick(TObject *Sender)
{

	this->Hide();
	Form5->Show();
}
//---------------------------------------------------------------------------

