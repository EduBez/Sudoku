#ifndef SudokuHelperH
    #define SudokuHelperH

#include "Typedefs.h"

namespace helper {

//
//  Class SudokuHelper
//
class SudokuHelper
{
    // Data Members
    types::Matrix& mtx_;
    types::DifficultyLevel level_;

    // Member Functions
    void ApplyMask       ();

    void GenerateByShift ();

public:
    // Ctor
    SudokuHelper(types::Matrix& mtx,
                 types::DifficultyLevel level);

    // Dtor
    ~SudokuHelper() {};

    void Generate ();
};

}// EndOf namespace
#endif

