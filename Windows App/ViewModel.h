#ifndef ViewModelH
    #define ViewModelH

#include <Vcl.Grids.hpp>
#include <memory>

#include "Model.h"
#include "Typedefs.h"

using namespace mvvm;
using namespace types;

// Forward class declaration
class TView;

namespace mvvm {

//
//  Class ViewModel
//
class ViewModel
{
    // Data Members
    TView* view_;

    std::unique_ptr<Model> model_;
    bool colorize_;

public:
    // Ctor
    ViewModel(TView* view_);

    // Dtor
    ~ViewModel() {}

    // Member Functions
    void Clear       ();

    void Generate    (types::DifficultyLevel level);

    void DrawLines   (int             col,
                      int             row,
                      TRect&          rect,
                      TGridDrawState  state);

    void Open        ();

    void Save        ();

    void Solve       ();
};

}// EndOf namespace
#endif

