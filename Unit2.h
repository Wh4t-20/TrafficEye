//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>

// Include headers for forms you interact with
#include "Unit1.h" // Assuming Unit1.h defines TForm1 (your main menu)
#include "Unit4.h" // Assuming Unit4.h defines TForm4 (your search results form)

// You might not strictly need all these FireDAC/DB includes in the H file,
// but they don't hurt if you are unsure which components are on Form2 itself.
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TButton *searchViolation;
	TButton *searchLocation;
	TButton *searchTime;
	TButton *searchDate;
	TButton *backButton;
	TButton *searchPlate;
	TImage *Image2;
	void __fastcall backButtonClick(TObject *Sender);
	void __fastcall searchViolationClick(TObject *Sender);
	void __fastcall searchTimeClick(TObject *Sender);
	void __fastcall searchLocationClick(TObject *Sender);
	void __fastcall searchDateClick(TObject *Sender);
	void __fastcall searchPlateClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
