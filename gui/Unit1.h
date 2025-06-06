	//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//#include "Unit2.h"
//---------------------------------------------------------------------------
// Remove this line: class TForm2:
class TmainMenu : public TForm
{
__published:	// IDE-managed Components
	TButton *logButton;
	TButton *searchButton;
	TButton *loadButton;
	TButton *exitButton;
	TImage *Image1;
	void __fastcall exitButtonClick(TObject *Sender);
	void __fastcall logButtonClick(TObject *Sender);
	void __fastcall searchButtonClick(TObject *Sender);
	void __fastcall loadButtonClick(TObject *Sender);
private:
   //	logPanel *logPanel;	// User declarations
public:		// User declarations
	__fastcall TmainMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmainMenu *mainMenu;
//---------------------------------------------------------------------------
#endif
