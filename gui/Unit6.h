//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.Phys.SQLite.hpp>
#include <FireDAC.Phys.SQLiteDef.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.SQLiteWrapper.Stat.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.ExprFuncs.hpp>

//---------------------------------------------------------------------------

class TForm6 : public TForm
{
__published:
	TDBGrid *DBGrid2;
	TFDQuery *FDQuery2;
	TDataSource *DataSource2;
	TFDConnection *FDConnection2;
	TButton *dataButton;
	TButton *summaryButton;
	TButton *Button1;
	TLabel *DATA;
	TImage *Image1;
	TImage *Image2;

	void __fastcall dataButtonClick(TObject *Sender);
	void __fastcall summaryButtonClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DBGrid2DrawColumnCell(TObject *Sender, const TRect &Rect,
		int DataCol, TColumn *Column, TGridDrawState State);

private:

public:
	__fastcall TForm6(TComponent* Owner);
	void LoadData();
};


//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
