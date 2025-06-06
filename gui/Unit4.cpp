//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit4.h"
#include "Unit2.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm4 *Form4;

//---------------------------------------------------------------------------

__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	DataSource1->DataSet = FDQuery1;
	DBGrid1->DataSource = DataSource1;
}

//---------------------------------------------------------------------------

bool __fastcall TForm4::SearchAndDisplay(const String& field, const String& value)
{
	if (!FDConnection1->Connected)
		FDConnection1->Connected = true;

	if (field != "PLATE" && field != "VIOLATION" && field != "TIME" &&
		field != "DATE" && field != "LOCATION")
	{
		ShowMessage("Invalid search field.");
		return false;
	}

	try {
		FDQuery1->Close();
		FDQuery1->SQL->Text = "SELECT * FROM LOGVIOLATION WHERE " + field + " LIKE :val";
		FDQuery1->ParamByName("val")->AsString = "%" + value + "%";
		FDQuery1->Open();

		if (FDQuery1->IsEmpty()) {
			ShowMessage("No results found for " + field + ": " + value);
			return false;
		}
		else {
			this->Show();
			return true;
		}
	}
	catch (const Exception& e) {
		ShowMessage("Database error: " + e.Message);
	}
}

//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
	this->Hide();
	Form2->Show();
}

//---------------------------------------------------------------------------
// Renders MEMO fields (e.g., VIOLATION) as normal text in the DBGrid
void __fastcall TForm4::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
	int DataCol, TColumn *Column, TGridDrawState State)
{
	if (Column->Field->DataType == ftMemo || Column->Field->DataType == ftWideMemo)
	{
		DBGrid1->Canvas->FillRect(Rect);
		String text = Column->Field->AsString;
		DBGrid1->Canvas->TextRect(Rect, Rect.Left + 2, Rect.Top + 2, text);
	}
	else
	{
		DBGrid1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
	}
}






