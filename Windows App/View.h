#ifndef MainUnitH
    #define MainUnitH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>

#include <memory>
#include <vector>

#include "ViewModel.h"

//
//  Class TView
//
class TView : public TForm
{
__published:
    TStringGrid*  Grid;

    TButton*      BtnFile;
    TButton*      BtnGen;
    TButton*      BtnRun;

    TOpenDialog*  OpenDialog;
    TSaveDialog*  SaveDialog;

    TPopupMenu*   FileMenu;
    TPopupMenu*   GenMenu;

    TMenuItem*    Clear;
    TMenuItem*    Easy;
    TMenuItem*    Hard;
    TMenuItem*    Medium;
    TMenuItem*    Save;

    TGroupBox*    GroupBox;
    TComboBox*    ComboBox;

    TLabel*       LblBacktracks;
    TLabel*       LblElapse;

    TLabel*       FromNumber;
    TLabel*       Backtracks;
    TLabel*       Elapsed;

    void __fastcall OnClearClick      (TObject* sender);

    void __fastcall OnGenerateClick   (TObject* sender);

    void __fastcall OnGridDrawCell    (TObject*        sender,
                                       int             col,
                                       int             row,
                                       TRect&          rect,
                                       TGridDrawState  state);

    void __fastcall OnMenuItemClick   (TObject* sender);

    void __fastcall OnOpenClick       (TObject* sender);

    void __fastcall OnSaveClick       (TObject* sender);

    void __fastcall OnSolveClick      (TObject* sender);

private:
    // Data Members
    std::unique_ptr<mvvm::ViewModel> viewModel_;
    std::vector<TMenuItem*> menuItems_;

public:
    __fastcall TView(TComponent* owner);
};

extern PACKAGE TView* View;
#endif

