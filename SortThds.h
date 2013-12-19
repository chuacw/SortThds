//$$---- Thread HDR ----
//---------------------------------------------------------------------------

#ifndef SortThdsH
#define SortThdsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TSortThread : public TThread
{
private:
        TPaintBox *FBox;
        DynamicArray<int> *FSortArray;
        int FSize, FA, FB, FI, FJ;
protected:
        void __fastcall Execute();
        virtual void __fastcall Sort(DynamicArray<int> &A) = 0;
        void __fastcall DoVisualSwap();
        void __fastcall VisualSwap(int A, int B, int I, int J);
public:
        __fastcall TSortThread(bool CreateSuspended);
        __fastcall TSortThread(TPaintBox *Box, DynamicArray<int> &SortArray);
};

class TBubbleSort : public TSortThread
{
protected:
        virtual void __fastcall Sort(DynamicArray<int> &A);
public:
        __fastcall TBubbleSort(TPaintBox *Box, DynamicArray<int> &SortArray): TSortThread(Box, SortArray) {};
};

class TSelectionSort : public TSortThread
{
protected:
        virtual void __fastcall Sort(DynamicArray<int> &A);
public:
        __fastcall TSelectionSort(TPaintBox *Box, DynamicArray<int> &SortArray): TSortThread(Box, SortArray) {};
};

class TQuickSort : public TSortThread
{
protected:
        void __fastcall QuickSort(DynamicArray<int> &A, int iLo, int iHi);
        virtual void __fastcall Sort(DynamicArray<int> &A);
public:
        __fastcall TQuickSort(TPaintBox *Box, DynamicArray<int> &SortArray): TSortThread(Box, SortArray) {};
};

void PaintLine(TCanvas *Canvas, int I, int Len);
//---------------------------------------------------------------------------
#endif
