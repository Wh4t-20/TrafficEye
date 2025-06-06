#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "Unit1.h"
#include "Unit6.h"
#include <vector>
#include <algorithm>
#include <cmath>

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm5 *Form5;

__fastcall TForm5::TForm5(TComponent* Owner)
    : TForm(Owner)
{
	SetupCharts();
    LoadChartData();
}
void __fastcall TForm5::FormShow(TObject *Sender)
{
    LoadChartData();
}


void TForm5::SetupCharts()
{
    // Create and configure bar series for locationChart
    LocationBarSeries = new TBarSeries(locationChart);  // Use existing locationChart component
    locationChart->AddSeries(LocationBarSeries);

    LocationBarSeries->Marks->Visible = true;
    LocationBarSeries->SeriesColor = clBlue;
    LocationBarSeries->Title = "Violations by Location";

    locationChart->Title->Text->Clear();
    locationChart->Title->Text->Add("Violations by Location");
    locationChart->Legend->Visible = false;
    locationChart->View3D = false;
    locationChart->BackWall->Brush->Color = TColor(0xF0F0F0);
    locationChart->LeftAxis->Title->Caption = "Count";
    locationChart->BottomAxis->Title->Caption = "Location";

    // Create and configure bar series for violationsChart
	ViolationsBarSeries = new TBarSeries(violationsChart);  // Use existing violationsChart component
    violationsChart->AddSeries(ViolationsBarSeries);

    ViolationsBarSeries->Marks->Visible = true;
    ViolationsBarSeries->SeriesColor = clRed;
    ViolationsBarSeries->Title = "Violations by Type";

    violationsChart->Title->Text->Clear();
    violationsChart->Title->Text->Add("Violations by Type");
    violationsChart->Legend->Visible = false;
    violationsChart->View3D = false;
    violationsChart->BackWall->Brush->Color = TColor(0xF0F0F0);
    violationsChart->LeftAxis->Title->Caption = "Count";
    violationsChart->BottomAxis->Title->Caption = "Violation";
}

void TForm5::LoadChartData()
{
    LocationBarSeries->Clear();
    ViolationsBarSeries->Clear();

    FDQuery1->Close();
        FDQuery1->SQL->Text = "SELECT COUNT(*) AS total FROM LOGVIOLATION";
        FDQuery1->Open();
        int totalViolations = FDQuery1->FieldByName("total")->AsInteger;

        // Show total violations in label
        TotalLabel->Caption = "Total Violations: " + IntToStr(totalViolations);

    FDQuery1->Close();
    FDQuery1->SQL->Text = "SELECT LOCATION, COUNT(*) AS count FROM LOGVIOLATION GROUP BY LOCATION ORDER BY count DESC LIMIT 5";
    FDQuery1->Open();

    while (!FDQuery1->Eof)
    {
        String loc = FDQuery1->FieldByName("LOCATION")->AsString;
        int cnt = FDQuery1->FieldByName("count")->AsInteger;
        LocationBarSeries->Add(cnt, loc, clBlue);
        FDQuery1->Next();
    }

    FDQuery1->Close();
    FDQuery1->SQL->Text = "SELECT VIOLATION, COUNT(*) AS count FROM LOGVIOLATION GROUP BY VIOLATION ORDER BY count DESC LIMIT 5";
    FDQuery1->Open();

    while (!FDQuery1->Eof)
    {
        String violation = FDQuery1->FieldByName("VIOLATION")->AsString;
        int cnt = FDQuery1->FieldByName("count")->AsInteger;
        ViolationsBarSeries->Add(cnt, violation, clRed);
        FDQuery1->Next();
    }
}

// Example event handler for a button click
void __fastcall TForm5::Button1Click(TObject *Sender)
{
    this->Hide();
    // Assuming mainMenu is declared somewhere
    mainMenu->Show();
}

void __fastcall TForm5::DataClick(TObject *Sender)
{
	this->Hide();
	Form6->Show();
	Form6->LoadData();
}

void __fastcall TForm5::summaryClick(TObject *Sender)
{
	ShowMessage("You're already viewing the summary (chart) screen.");
}
void __fastcall TForm5::FormActivate(TObject *Sender)
{
	LoadChartData(); // Ensure refresh every time it gets focus
}







