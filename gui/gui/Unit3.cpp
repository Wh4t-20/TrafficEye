//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit3.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

bool isEditing = false;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
    verifyLabel->Hide();
    editButton->Hide();
    saveButton->Hide();
}

//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
    this->Hide();
    mainMenu->Show();
}

//---------------------------------------------------------------------------

bool ValidatePlateNumber(const String &plateNumber)
{
    if (plateNumber.Length() != 8) return false;

	for (int i = 1; i <= 3; i++) {
		wchar_t ch = plateNumber[i];
		if (!((ch >= L'A' && ch <= L'Z') || (ch >= L'a' && ch <= L'z'))) return false;
	}

	if (plateNumber[4] != L'-') return false;

	for (int i = 5; i <= 8; i++) {
		wchar_t ch = plateNumber[i];
		if (!(ch >= L'0' && ch <= L'9')) return false;
	}

	return true;
}

bool ValidateDate(const String &date)
{
	if (date.Length() != 10) return false;

	wchar_t ch1 = date[1], ch2 = date[2];
	if (!(ch1 >= L'0' && ch1 <= L'9') || !(ch2 >= L'0' && ch2 <= L'9')) return false;
	if (date[3] != L'/') return false;

	wchar_t ch4 = date[4], ch5 = date[5];
	if (!(ch4 >= L'0' && ch4 <= L'9') || !(ch5 >= L'0' && ch5 <= L'9')) return false;
	if (date[6] != L'/') return false;

	for (int i = 7; i <= 10; i++) {
		wchar_t ch = date[i];
		if (!(ch >= L'0' && ch <= L'9')) return false;
	}

	int month = StrToIntDef(date.SubString(1, 2), 0);
	int day = StrToIntDef(date.SubString(4, 2), 0);
	int year = StrToIntDef(date.SubString(7, 4), 0);

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (year < 1900 || year > 2100) return false;

    if (month == 2 && day > 29) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

    return true;
}

bool ValidateTime(const String &time)
{
    if (time.Length() != 5) return false;

    wchar_t ch1 = time[1], ch2 = time[2];
    if (!(ch1 >= L'0' && ch1 <= L'9') || !(ch2 >= L'0' && ch2 <= L'9')) return false;
    if (time[3] != L':') return false;

    wchar_t ch4 = time[4], ch5 = time[5];
    if (!(ch4 >= L'0' && ch4 <= L'9') || !(ch5 >= L'0' && ch5 <= L'9')) return false;

    int hour = StrToIntDef(time.SubString(1, 2), -1);
    int minute = StrToIntDef(time.SubString(4, 2), -1);

    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;

    return true;
}

void __fastcall TForm3::addButtonClick(TObject *Sender)
{
    static int clickCount = 0;

    String inputText = inputBox->Text.Trim();
    if (inputText.IsEmpty()) {
        ShowMessage("Input cannot be empty.");
        return;
    }

    bool isValid = true;
    String errorMessage = "";

    switch (clickCount) {
		case 0: // Plate Number
            if (!ValidatePlateNumber(inputText)) {
                isValid = false;
                errorMessage = "Invalid plate number format. Please use LLL-DDDD format (e.g., ABC-1234).";
            } else {
                // Convert plate number to uppercase
                inputText = inputText.UpperCase();
            }
            break;
        case 1: // Date
            if (!ValidateDate(inputText)) {
                isValid = false;
                errorMessage = "Invalid date format. Please use MM/DD/YYYY format (e.g., 12/25/2024).";
            }
            break;
        case 2: // Time
            if (!ValidateTime(inputText)) {
                isValid = false;
                errorMessage = "Invalid time format. Please use HH:MM in 24-hour format (e.g., 14:30).";
            }
			break;
		case 3: // Location - any string is valid
		case 4: // Violation Type - any string is valid
            break;
    }

    if (!isValid) {
		ShowMessage(errorMessage);
		return;
	}

	if (clickCount == 0) {
		inputText = inputText.UpperCase();
    }
    listBox->Items->Add(inputText);
	inputBox->Text = "";

    verifyLabel->Hide();
    editButton->Hide();
    saveButton->Hide();

    clickCount++;
    switch (clickCount) {
        case 1:
            promptLabel->Caption = "Enter Date:";
            formatLabel->Caption = "MM/DD/YYYY";
            break;
        case 2:
            promptLabel->Caption = "Enter Time:";
            formatLabel->Caption = "HH:MM (24 Hour Format)";
            break;
        case 3:
            promptLabel->Caption = "Enter Location:";
            formatLabel->Caption = "Barangay/Municipality or City";
            break;
        case 4:
            promptLabel->Caption = "Enter Violation Type:";
            formatLabel->Caption = "";
            break;
        default:
            promptLabel->Caption = "All done!";
            verifyLabel->Show();
            editButton->Show();
            saveButton->Show();
            clickCount = 0;
            break;
    }

    if (isEditing) {
        if (MessageDlg("You've finished editing. Do you want to save the changes?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
			saveButtonClick(Sender);
		}
		isEditing = false;
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm3::saveButtonClick(TObject *Sender)
{
    try {
        if (listBox->Items->Count < 5) {
            ShowMessage("Not enough information to save a complete record.");
            return;
        }

        for (int i = 0; i < listBox->Items->Count; i += 5) {
            if (i + 4 >= listBox->Items->Count) break;

            String plate     = listBox->Items->Strings[i];      // 0
            String date      = listBox->Items->Strings[i + 1];  // 1
            String time      = listBox->Items->Strings[i + 2];  // 2
            String location  = listBox->Items->Strings[i + 3];  // 3
            String violation = listBox->Items->Strings[i + 4];  // 4

            FDQuery1->SQL->Text =
				"INSERT INTO LOGVIOLATION (PLATE, DATE, TIME, LOCATION, VIOLATION) "
				"VALUES (:plate, :date, :time, :location, :violation)";

			FDQuery1->ParamByName("plate")->AsString = plate;
			FDQuery1->ParamByName("date")->AsString     = date;
			FDQuery1->ParamByName("time")->AsString  = time;
			FDQuery1->ParamByName("location")->AsString      = location;
			FDQuery1->ParamByName("violation")->AsString      = violation;

            FDQuery1->ExecSQL();
        }

        ShowMessage("Data successfully saved to the database.");

        listBox->Items->Clear();
        this->Hide();
        mainMenu->Show();

    } catch (Exception &e) {
        ShowMessage("Database save error: " + e.Message);
	}
}


//---------------------------------------------------------------------------

void __fastcall TForm3::editButtonClick(TObject *Sender)
{
	if (listBox->ItemIndex >= 0) {
		isEditing = true;

		inputBox->Text = listBox->Items->Strings[listBox->ItemIndex];

		listBox->Items->Delete(listBox->ItemIndex);

		int selectedIndex = listBox->ItemIndex;
        int itemPosition = selectedIndex % 5;
        switch (itemPosition) {
            case 0:
                promptLabel->Caption = "Enter Plate Number:";
                formatLabel->Caption = "LLL-DDDD";
                break;
            case 1:
                promptLabel->Caption = "Enter Date:";
                formatLabel->Caption = "MM/DD/YYYY";
                break;
            case 2:
                promptLabel->Caption = "Enter Time:";
                formatLabel->Caption = "HH:MM (24 Hour Format)";
                break;
            case 3:
                promptLabel->Caption = "Enter Location:";
                formatLabel->Caption = "Barangay/Municipality or City";
                break;
            case 4:
                promptLabel->Caption = "Enter Violation Type:";
                formatLabel->Caption = "";
                break;
        }
    } else {
        ShowMessage("Please select an item to edit.");
    }
}

//---------------------------------------------------------------------------


