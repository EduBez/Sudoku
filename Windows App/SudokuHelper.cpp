#include "SudokuPCH1.h"
#pragma hdrstop

#include <stdlib>
#include <time.h>

#include <algorithm>
#include <random>
using namespace std;

#include "SudokuHelper.h"
using namespace helper;
using namespace types;

//
//  Class SudokuHelper
//

// Ctor
SudokuHelper::SudokuHelper(Matrix& mtx, DifficultyLevel level)
    // Member Initialization List
    : mtx_   (mtx)
    , level_ (level)
{
}

void SudokuHelper::Generate()
{
    GenerateByShift();
    ApplyMask();
}

void SudokuHelper::GenerateByShift()
{
    vector<int> digits{1,2,3,4,5,6,7,8,9};
    auto line = digits;

    default_random_engine rng((random_device())());
    // Randomicaly shuffle the digits
    shuffle(begin(line), end(line), rng);

    auto line_1 = line;
    rotate(begin(line), begin(line) + 3, end(line));
    auto line_2 = line;
    rotate(begin(line), begin(line) + 3, end(line));
    auto line_3 = line;

    rotate(begin(line), begin(line) + 1, end(line));
    auto line_4 = line;
    rotate(begin(line), begin(line) + 3, end(line));
    auto line_5 = line;
    rotate(begin(line), begin(line) + 3, end(line));
    auto line_6 = line;

    rotate(begin(line), begin(line) + 1, end(line));
    auto line_7 = line;
    rotate(begin(line), begin(line) + 3, end(line));
    auto line_8 = line;
    rotate(begin(line), begin(line) + 3, end(line));
    auto line_9 = line;

    Lines lines {line_1, line_2, line_3, line_4, line_5,
                 line_6, line_7, line_8, line_9};

    int row = 0;
    for (auto line : lines)
    {
        for (auto idx=0; idx < 9; ++idx) {
            mtx_(row, idx) = line[idx];
        }
        row += 1;
    }
}

void SudokuHelper::ApplyMask()
{
    if (level_ == DifficultyLevel::Easy)
    {
        mtx_(0, 1) = _;  mtx_(0, 3) = _;  mtx_(0, 7) = _;
        mtx_(1, 0) = _;  mtx_(0, 5) = _;  mtx_(1, 6) = _;
        mtx_(1, 2) = _;  mtx_(1, 4) = _;  mtx_(1, 8) = _;
        mtx_(2, 1) = _;  mtx_(2, 3) = _;  mtx_(2, 7) = _;
                         mtx_(2, 5) = _;

        mtx_(3, 0) = _;  mtx_(3, 4) = _;  mtx_(3, 6) = _;
        mtx_(3, 2) = _;  mtx_(4, 3) = _;  mtx_(3, 8) = _;
        mtx_(4, 1) = _;  mtx_(4, 4) = _;  mtx_(4, 7) = _;
        mtx_(5, 0) = _;  mtx_(4, 5) = _;  mtx_(5, 6) = _;
        mtx_(5, 2) = _;  mtx_(5, 4) = _;  mtx_(5, 8) = _;

        mtx_(6, 1) = _;  mtx_(6, 3) = _;  mtx_(6, 7) = _;
        mtx_(7, 0) = _;  mtx_(6, 5) = _;  mtx_(7, 6) = _;
        mtx_(7, 2) = _;  mtx_(7, 4) = _;  mtx_(7, 8) = _;
        mtx_(8, 1) = _;  mtx_(8, 3) = _;  mtx_(8, 7) = _;
                         mtx_(8, 5) = _;
    }
    else if (level_ == DifficultyLevel::Medium)
    {
        mtx_(0, 1) = _;  mtx_(0, 3) = _;  mtx_(0, 6) = _;
        mtx_(0, 2) = _;  mtx_(0, 5) = _;  mtx_(0, 7) = _;
        mtx_(1, 0) = _;  mtx_(1, 3) = _;  mtx_(1, 7) = _;
        mtx_(1, 1) = _;  mtx_(1, 5) = _;  mtx_(1, 8) = _;
        mtx_(2, 0) = _;  mtx_(2, 3) = _;  mtx_(2, 8) = _;
                         mtx_(2, 5) = _;

        mtx_(3, 0) = _;  mtx_(3, 4) = _;  mtx_(3, 8) = _;
        mtx_(4, 0) = _;  mtx_(4, 4) = _;  mtx_(4, 6) = _;
        mtx_(4, 1) = _;  mtx_(5, 4) = _;  mtx_(4, 7) = _;
        mtx_(4, 2) = _;  mtx_(6, 3) = _;  mtx_(4, 8) = _;
        mtx_(5, 0) = _;  mtx_(6, 5) = _;  mtx_(5, 8) = _;

        mtx_(6, 0) = _;  mtx_(7, 3) = _;  mtx_(6, 8) = _;
        mtx_(7, 0) = _;  mtx_(7, 5) = _;  mtx_(7, 7) = _;
        mtx_(7, 1) = _;  mtx_(8, 3) = _;  mtx_(7, 8) = _;
        mtx_(8, 1) = _;  mtx_(8, 5) = _;  mtx_(8, 6) = _;
        mtx_(8, 2) = _;                   mtx_(8, 7) = _;
    }
    else if (level_ == DifficultyLevel::Hard)
    {
        mtx_(0, 1) = _;  mtx_(0, 3) = _;  mtx_(0, 6) = _;
        mtx_(0, 2) = _;  mtx_(0, 4) = _;  mtx_(0, 7) = _;
        mtx_(1, 1) = _;  mtx_(0, 5) = _;  mtx_(1, 7) = _;
        mtx_(1, 2) = _;  mtx_(1, 3) = _;  mtx_(1, 8) = _;
        mtx_(2, 0) = _;  mtx_(1, 5) = _;  mtx_(2, 6) = _;
                         mtx_(2, 3) = _;
                         mtx_(2, 5) = _;
        mtx_(3, 0) = _;                   mtx_(3, 6) = _;
        mtx_(4, 0) = _;  mtx_(3, 5) = _;  mtx_(3, 7) = _;
        mtx_(4, 1) = _;  mtx_(4, 3) = _;  mtx_(3, 8) = _;
        mtx_(5, 0) = _;  mtx_(4, 4) = _;  mtx_(4, 7) = _;
        mtx_(5, 1) = _;  mtx_(4, 5) = _;  mtx_(4, 8) = _;
        mtx_(5, 2) = _;  mtx_(5, 3) = _;  mtx_(5, 8) = _;

        mtx_(6, 0) = _;  mtx_(6, 3) = _;  mtx_(6, 6) = _;
        mtx_(7, 1) = _;  mtx_(6, 4) = _;  mtx_(7, 7) = _;
        mtx_(7, 2) = _;  mtx_(6, 5) = _;  mtx_(7, 8) = _;
        mtx_(8, 1) = _;  mtx_(7, 5) = _;  mtx_(8, 6) = _;
        mtx_(8, 2) = _;  mtx_(8, 4) = _;  mtx_(8, 7) = _;
                         mtx_(8, 5) = _;
    }
}

