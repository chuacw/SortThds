// Ported by Chee Wee, Singapore, from Kylix to Delphi 2006
//$$---- Thread CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SortThds.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TestThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void PaintLine(TCanvas *Canvas, int I, int Len)
{
  TPoint points[2];
  points[0].x = 0;
  points[0].y = I*2+1;
  points[1].x = Len;
  points[1].y = I*2+1;
  // Canvas->PolyLine([Point(0, I * 2 + 1), Point(Len, I * 2 + 1)]);
  Canvas->Polyline(points, 1);
};
//---------------------------------------------------------------------------

__fastcall TSortThread::TSortThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------

__fastcall TSortThread::TSortThread(TPaintBox *Box, DynamicArray<int> &SortArray): TThread(true)
{
  FBox = Box;
  FSortArray = &SortArray;
  FSize = SortArray.Length;
  FreeOnTerminate = true;
  Resume();
}
//---------------------------------------------------------------------------

void __fastcall TSortThread::DoVisualSwap()
{
    FBox->Canvas->Pen->Color = FBox->Color;
    PaintLine(FBox->Canvas, FI, FA);
    PaintLine(FBox->Canvas, FJ, FB);
    FBox->Canvas->Pen->Color = clRed;
    PaintLine(FBox->Canvas, FI, FB);
    PaintLine(FBox->Canvas, FJ, FA);
}
//---------------------------------------------------------------------------

void __fastcall TSortThread::VisualSwap(int A, int B, int I, int J)
{
  FA = A;
  FB = B;
  FI = I;
  FJ = J;
  Synchronize(&DoVisualSwap);
}
//---------------------------------------------------------------------------

void __fastcall TSortThread::Execute()
{
 Sort(*FSortArray);
}
//---------------------------------------------------------------------------

void __fastcall TBubbleSort::Sort(DynamicArray<int> &A)
{
  int T;

  for(int I = A.High; I>=A.Low; I--)
    for(int J = A.Low; J<=A.High-1; J++)
      if (A[J] > A[J + 1])
      {
        VisualSwap(A[J], A[J + 1], J, J + 1);
        T = A[J];
        A[J] = A[J + 1];
        A[J + 1] = T;
        if (Terminated) return;
      }
}
//---------------------------------------------------------------------------

void __fastcall TSelectionSort::Sort(DynamicArray<int> &A)
{
  int T;

  for(int I = A.Low; I<=A.High-1; I++)
    for(int J = A.High; J>=I+1; J--)
      if (A[I] > A[J])
      {
        VisualSwap(A[I], A[J], I, J);
        T = A[I];
        A[I] = A[J];
        A[J] = T;
        if (Terminated) return;
      }

}
//---------------------------------------------------------------------------

void __fastcall TQuickSort::QuickSort(DynamicArray<int> &A, int iLo, int iHi)
{

    int Lo, Hi, Mid, T;

    Lo = iLo;
    Hi = iHi;
    Mid = A[(Lo + Hi) / 2];
    do
    {
      while (A[Lo] < Mid) Lo++;
      while (A[Hi] > Mid) Hi--;
      if (Lo <= Hi)
      {
        VisualSwap(A[Lo], A[Hi], Lo, Hi);
        T = A[Lo];

        A[Lo++] = A[Hi];
        A[Hi--] = T;
      }
    }
    while (Lo <= Hi);
    if (Hi > iLo) QuickSort(A, iLo, Hi);
    if (Lo < iHi) QuickSort(A, Lo, iHi);
    if (Terminated) return;
}
//---------------------------------------------------------------------------

void __fastcall TQuickSort::Sort(DynamicArray<int> &A)
{
  QuickSort(A, A.Low, A.High);
}
//---------------------------------------------------------------------------
