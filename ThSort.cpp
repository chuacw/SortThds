//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ThSort.h"
#include "SortThds.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TThreadSortForm *ThreadSortForm;

bool ArraysRandom;
DynamicArray<int> BubbleSortArray, SelectionSortArray, QuickSortArray;
//---------------------------------------------------------------------------
__fastcall TThreadSortForm::TThreadSortForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TThreadSortForm::StartBtnClick(TObject *Sender)
{
  RandomizeArrays();
  ThreadsRunning = 3;

  BubbleSortBox->Invalidate();
  (new TBubbleSort(BubbleSortBox, BubbleSortArray))->OnTerminate = ThreadDone;

  SelectionSortBox->Invalidate();
  (new TSelectionSort(SelectionSortBox, SelectionSortArray))->OnTerminate = ThreadDone;

  QuickSortBox->Invalidate();
  (new TQuickSort(QuickSortBox, QuickSortArray))->OnTerminate = ThreadDone;

  StartBtn->Enabled = False;
}
//---------------------------------------------------------------------------

void __fastcall TThreadSortForm::FormCreate(TObject *Sender)
{
  RandomizeArrays();
}
//---------------------------------------------------------------------------

void __fastcall TThreadSortForm::PaintArray(TPaintBox *Box, DynamicArray<int> A)
{

  Box->Canvas->Pen->Color = clRed;
  for (int i = 0; i < A.Length; i++)
    PaintLine(Box->Canvas, i, A[i]);
}
//---------------------------------------------------------------------------
void __fastcall TThreadSortForm::BubbleSortBoxPaint(TObject *Sender)
{
  PaintArray(BubbleSortBox, BubbleSortArray);
}
//---------------------------------------------------------------------------

void __fastcall TThreadSortForm::SelectionSortBoxPaint(TObject *Sender)
{
  PaintArray(SelectionSortBox, SelectionSortArray);
}
//---------------------------------------------------------------------------

void __fastcall TThreadSortForm::QuickSortBoxPaint(TObject *Sender)
{
  PaintArray(QuickSortBox, QuickSortArray);
}
//---------------------------------------------------------------------------

void __fastcall TThreadSortForm::RandomizeArrays()
{
  if (!ArraysRandom)
  {
    BubbleSortArray.Length = 115;
    SelectionSortArray.Length = 115;
    QuickSortArray.Length = 115;
    Randomize();
    for (int I = 0; I < BubbleSortArray.Length; I++)
      BubbleSortArray[I] = rand() % 170;
    SelectionSortArray = BubbleSortArray.Copy();
    QuickSortArray = BubbleSortArray.Copy();
    ArraysRandom = true;
    Repaint();
  }
}
//---------------------------------------------------------------------------

void __fastcall TThreadSortForm::ThreadDone(TObject *Sender)
{
  if (--ThreadsRunning == 0)
  {
    StartBtn->Enabled = True;
    ArraysRandom = False;
  }
}

//---------------------------------------------------------------------------


