#include "SudokuPCH1.h"
#pragma hdrstop

#include "View.h"
#include "ViewModel.h"

using namespace std;
using namespace mvvm;

#pragma package(smart_init)
#pragma resource "*.dfm"
TView* View;

//
//  Class TView
//
__fastcall TView::TView(TComponent* owner)
    // Member Initialization List
    : TForm(owner)
{
    menuItems_ = vector<TMenuItem*> {Easy, Medium, Hard};
    viewModel_ = make_unique<ViewModel>(this);
}

void __fastcall TView::OnClearClick(TObject* sender)
{
    viewModel_->Clear();
}

void __fastcall TView::OnGenerateClick(TObject* sender)
{
    DifficultyLevel level;

    for (auto i : menuItems_) {
        if (i->Checked)
        {
            level = static_cast<DifficultyLevel>(i->Tag);
            break;
        }
    }

    viewModel_->Generate(level);
}

void __fastcall TView::OnGridDrawCell(TObject*        sender,
                                      int             col,
                                      int             row,
                                      TRect&          rect,
                                      TGridDrawState  state)
{
    viewModel_->DrawLines(col, row, rect, state);
}

void __fastcall TView::OnMenuItemClick(TObject* sender)
{
    // Uncheck all menu items
    for (auto i : menuItems_) {
        i->Checked = false;
    }
    // Retrieve selected menu item tag
    int i = dynamic_cast<TMenuItem*>(sender)->Tag;
    // Check menu
    menuItems_[i]->Checked = true;
}

void __fastcall TView::OnOpenClick(TObject* sender)
{
    viewModel_->Open();
}

void __fastcall TView::OnSaveClick(TObject* sender)
{
    viewModel_->Save();
}

void __fastcall TView::OnSolveClick(TObject* sender)
{
    viewModel_->Solve();
}

