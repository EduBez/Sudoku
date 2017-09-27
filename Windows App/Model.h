#ifndef ModelH
    #define ModelH

#include <memory>

#include "Typedefs.h"
#include "SudokuSolver.h"

namespace mvvm {

//
//  Class Model
//
class Model
{
    std::unique_ptr<engine::SudokuSolver> solver_;

public:
    // Ctor
    Model();

    // Dtor
    ~Model() {};

    // Member Functions
    void AddCell  (int number,
                   int row,
                   int col);

    void ClearGrid ();

    void Generate (types::DifficultyLevel level);

    types::Matrix& GetGrid()
        { return solver_->GetGrid(); }

    bool Solve    (int  firstNo,
                   int& backtracks,
                   int& elapsed);
};

}// EndOf namespace
#endif

