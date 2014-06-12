//---------------------------------------------------------------------------

#ifndef ThSortH
#define ThSortH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TThreadSortForm : public TForm
{
__published:	// IDE-managed Components
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TPaintBox *QuickSortBox;
	TPaintBox *SelectionSortBox;
	TButton *StartBtn;
	TPaintBox *BubbleSortBox;
	void __fastcall StartBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BubbleSortBoxPaint(TObject *Sender);
	void __fastcall SelectionSortBoxPaint(TObject *Sender);
	void __fastcall QuickSortBoxPaint(TObject *Sender);
private:	// User declarations
        int ThreadsRunning;
        void __fastcall RandomizeArrays();
        void __fastcall ThreadDone(TObject *Sender);
public:		// User declarations
	__fastcall TThreadSortForm(TComponent* Owner);
        void __fastcall PaintArray(TPaintBox *Box, DynamicArray<int> A);
};
//---------------------------------------------------------------------------
extern PACKAGE TThreadSortForm *ThreadSortForm;
//---------------------------------------------------------------------------
#endif
