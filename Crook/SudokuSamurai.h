#pragma once
#include "Typedefs.h"

namespace data {

//
//  Class SudokuSamurai
//
class SudokuSamurai
{
    types::MatrixCells mtx_;

public:
    // Ctor
    SudokuSamurai();
    // Dtor       
    ~SudokuSamurai() {}

    // Member Function
    types::MatrixCells& GetData()
        {return mtx_;}
};

}// EndOf namespace
