#ifndef SudokuSolverH
    #define SudokuSolverH

#include "Typedefs.h"

namespace engine {

//
//  Class SudokuSolver
//
class SudokuSolver
{
    // Data Members
    types::Matrix mtx_;
    types::Matrix mcopy_;

    std::vector<int> digits_;

    int backtracks_;
    bool solved_;

    // Member Functions
    bool AvailableOnCol    (int col,
                            int num);

    bool AvailableOnRow    (int row,
                            int num);

    bool AvailableOnRegion  (int row,
                             int col,
                             int num);

    bool CheckConstraints  (types::Cell& cell,
                            int          num);

    bool FindEmptyCell     (types::Cell& cell);

    bool Solve             ();

public:
    // Ctor
    SudokuSolver();

    // Dtor
    ~SudokuSolver() {};

    void AddCell  (int num,
                   int row,
                   int col);

    void ClearGrid ();

    types::Matrix& GetGrid()
        { return mtx_; }

    void Generate (types::DifficultyLevel level);

    bool Run      (int  firstNo,
                   int& backtracks,
                   int& elapsed);
};

}// EndOf namespace
#endif

