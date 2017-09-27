#include "SudokuPCH1.h"
#pragma hdrstop

#include <iostream>
#include <fstream>
using namespace std;

#include "View.h"
#include "ViewModel.h"

using namespace mvvm;
using namespace types;

//
//  Class ViewModel
//

// Ctor
ViewModel::ViewModel(TView* view)
    // Member Initialization List
    : view_  (view)
    , model_ (nullptr)
{
    model_ = make_unique<Model>();
}

void ViewModel::Clear()
{
    for (int row=0; row < 10; ++row) {
        for (int col=0; col < 10; ++col) {
            view_->Grid->Cells[row][col] = "";
        }
    }

    view_->Backtracks->Caption = "";
    view_->Elapsed   ->Caption = "";

    Application->ProcessMessages();
}

void ViewModel::Generate(DifficultyLevel level)
{
    Clear();
    // Apply color to grid cells
    colorize_ = true;

    model_->Generate(level);
    auto mtx = model_->GetGrid();

    for (auto row=0; row < mtx.size1(); ++row)
    {
        for (auto col=0; col < mtx.size2(); ++col)
        {
            if (mtx(row, col) == _) {
                view_->Grid->Cells[col][row] = "";
            }
            else {
                view_->Grid->Cells[col][row] = IntToStr(mtx(row, col));
            }
        }
    }
}

void ViewModel::DrawLines(int             col,
                          int             row,
                          TRect&          rect,
                          TGridDrawState  state)
{
    view_->Grid->Canvas->Pen->Color = clBlack;
    view_->Grid->Canvas->Pen->Width = 3;

    view_->Grid->Canvas->MoveTo(0   , 92);
    view_->Grid->Canvas->LineTo(282 , 92);

    view_->Grid->Canvas->MoveTo(0   , 184);
    view_->Grid->Canvas->LineTo(282 , 184);

    view_->Grid->Canvas->MoveTo(92  , 0);
    view_->Grid->Canvas->LineTo(92  , 282);

    view_->Grid->Canvas->MoveTo(184 , 0);
    view_->Grid->Canvas->LineTo(184 , 282);

    if (!view_->Grid->Cells[col][row].IsEmpty())
    {
        if (colorize_) {
            view_->Grid->Canvas->Brush->Color = clActiveCaption;
        }
        else {
            view_->Grid->Canvas->Brush->Color = clMoneyGreen;
        }

        view_->Grid->Canvas->FillRect(rect);
        view_->Grid->Canvas->TextRect(rect, rect.Left, rect.Top, view_->Grid->Cells[col][row]);
    }

    Application->ProcessMessages();
}

void ViewModel::Open()
{
    if (view_->OpenDialog->Execute())
    {
        Clear();
        // Apply color to grid cells
        colorize_ = true;

        char ch;
        ifstream file(view_->OpenDialog->FileName.c_str());

        // Reset before importing new game
        model_->ClearGrid();

        for (int row=0; row < 9; ++row)
        {
            for (int col=0; col < 9; ++col)
            {
                // Assume text file is a pure ASCII file
                // Just chars representing numbers from 1 to 9
                file >> ch;

                int number = (int)(ch - '0');

                // Store the number in the grid cell
                model_->AddCell(number, row, col);

                if (ch == '.') {
                    view_->Grid->Cells[col][row] = "";
                }
                else {
                    view_->Grid->Cells[col][row] = ch;
                }
            }
        }
        file.close();
    }
}

void ViewModel::Save()
{
    if (view_->SaveDialog->Execute())
    {
        char number;
        ofstream file(view_->SaveDialog->FileName.c_str());

        // Retrieve the data
        Matrix& mtx = model_->GetGrid();

        for (unsigned i=0; i < mtx.size1(); ++i)
        {
            for (unsigned j=0; j < mtx.size2(); ++j)
            {
                auto val = mtx(i, j);
                number = static_cast<char>(val);
                file << number;
            }
            file << endl;
        }

        file << endl;
        file.close();
    }
}

void ViewModel::Solve()
{
    view_->Backtracks->Caption = "";
    view_->Elapsed   ->Caption = "";

    Application->ProcessMessages();

    auto idx   = view_->ComboBox->ItemIndex;
    String num = view_->ComboBox->Items->Strings[idx];

    auto firstNo = StrToInt(num);
    firstNo -= 1;

    int backtracks, elapsed;

    if (model_->Solve(firstNo, backtracks, elapsed))
    {
        view_->Backtracks ->Caption = IntToStr(backtracks);
        view_->Elapsed    ->Caption = IntToStr(elapsed);

        colorize_ = false;
        auto mtx = model_->GetGrid();

        for (auto row=0; row < mtx.size1(); ++row)
        {
            for (auto col=0; col < mtx.size2(); ++col)
            {
                if (view_->Grid->Cells[col][row].IsEmpty()) {
                    view_->Grid->Cells[col][row] = IntToStr(mtx(row, col));
                }
            }
        }
    }
}

