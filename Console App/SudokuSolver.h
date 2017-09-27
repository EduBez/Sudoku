#pragma once
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

    bool AvailableOnRange  (int row,
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

    void AddCell       (int num,
                        int row,
                        int col);

    void ClearGrid     ();

    void DisplayMatrix ();

    types::Matrix& GetGrid()
        { return mtx_; }

    void ReadFile (std::string file);

    bool Run      (int  firstNo);
                   
};

}// EndOf namespace
