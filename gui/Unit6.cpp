//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit6.h"
#include "Unit5.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm6 *Form6;

//---------------------------------------------------------------------------

__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
	// Link dataset and datasource
	DataSource2->DataSet = FDQuery2;
	DBGrid2->DataSource = DataSource2;
}

//---------------------------------------------------------------------------

void __fastcall TForm6::FormShow(TObject *Sender)
{
	LoadData();
}

//---------------------------------------------------------------------------

void TForm6::LoadData()
{
	try {
		if (!FDConnection2->Connected)
			FDConnection2->Connected = true;

		FDQuery2->Close();
		FDQuery2->SQL->Text = "SELECT * FROM LOGVIOLATION";
		FDQuery2->Open();
	}
	catch (const Exception &e) {
		ShowMessage("Database Error: " + e.Message);
	}
}

//---------------------------------------------------------------------------

void __fastcall TForm6::Button1Click(TObject *Sender)
{
	this->Hide();
	mainMenu->Show();
}

//---------------------------------------------------------------------------

void __fastcall TForm6::dataButtonClick(TObject *Sender)
{
	LoadData();
	ShowMessage("Full database loaded.");
}

//---------------------------------------------------------------------------

void __fastcall TForm6::summaryButtonClick(TObject *Sender)
{
	this->Hide();
	Form5->Show();
}
void __fastcall TForm6::DBGrid2DrawColumnCell(TObject *Sender, const TRect &Rect,
	int DataCol, TColumn *Column, TGridDrawState State)
{
	if (Column->Field->DataType == ftMemo || Column->Field->DataType == ftWideMemo) {
		DBGrid2->Canvas->FillRect(Rect);
		String text = Column->Field->AsString;
		DBGrid2->Canvas->TextRect(Rect, Rect.Left + 2, Rect.Top + 2, text);
	}
	else {
		DBGrid2->DefaultDrawColumnCell(Rect, DataCol, Column, State);
	}
}


//---------------------------------------------------------------------------


