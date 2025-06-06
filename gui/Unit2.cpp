// Unit2.cpp
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h" // Include Unit1.h if Form1 is your main menu
#include "Unit2.h"
#include "Unit4.h" // Include Unit4.h to use Form4
#include <Vcl.Dialogs.hpp> // Required for InputBox

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	Image1->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::backButtonClick(TObject *Sender)
{
    this->Hide();
	mainMenu->Show();
}
//---------------------------------------------------------------------------



void __fastcall TForm2::searchViolationClick(TObject *Sender)
{
	String violation = InputBox(L"Search Violation", L"Enter violation keyword:", L"");
	if (!violation.IsEmpty()) {
		if (Form4 && Form4->SearchAndDisplay(L"VIOLATION", violation.UpperCase())) {
			this->Hide();
		}
	}
}


//---------------------------------------------------------------------------

void __fastcall TForm2::searchTimeClick(TObject *Sender)
{
	String time = InputBox("Enter Time", "Time (HH:MM):", "");
    if (!time.IsEmpty()) {
        Form4->SearchAndDisplay("TIME", time);
		this->Hide();
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm2::searchLocationClick(TObject *Sender)
{
    String location = InputBox("Enter Location", "Location:", "");
    if (!location.IsEmpty()) {
        Form4->SearchAndDisplay("LOCATION", location);
		this->Hide();
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm2::searchDateClick(TObject *Sender)
{
    String date = InputBox("Enter Date", "Date (MM/DD/YYYY):", ""); // Changed prompt to MM/DD/YYYY for consistency
    if (!date.IsEmpty()) {
        Form4->SearchAndDisplay("DATE", date);
		this->Hide();
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm2::searchPlateClick(TObject *Sender)
{
    String plate = InputBox("Search by Plate", "Enter plate number (e.g., ABC-1234):", "");

    if (!plate.IsEmpty())
    {
        Form4->SearchAndDisplay("PLATE", plate.UpperCase()); // plate.UpperCase() is a good idea!
		this->Hide();
    }
}
//---------------------------------------------------------------------------
