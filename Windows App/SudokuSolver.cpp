#include "SudokuPCH1.h"
#pragma hdrstop

#include <DateUtils.hpp>
#include <System.DateUtils.hpp>

#include "SudokuSolver.h"
#include "SudokuHelper.h"

using namespace engine;
using namespace helper;
using namespace std;
using namespace types;

namespace bnu = boost::numeric::ublas;

//
//  Class SudokuSolver
//

// Ctor
SudokuSolver::SudokuSolver()
{
    mtx_ = Matrix(9, 9);
}

void SudokuSolver::AddCell(int num, int row, int col)
{
    if (num == -2) {
        mtx_(row, col) = _;
    }
    else {
        mtx_(row, col) = num;
    }
}

bool SudokuSolver::AvailableOnCol(int col, int num)
{
    for (auto row=0; row < mtx_.size1(); ++row)
    {
        if (mtx_(row, col) == num) {
            return false;
        }
    }
    return true;

    #if 0 // Slower
    bnu::matrix_column<Matrix> mr(mtx_, col);
    return find_if(mr.begin(), mr.end(), [&](int i){return i==num;}) != mr.end();
    #endif
}

bool SudokuSolver::AvailableOnRow(int row, int num)
{
    for (auto col=0; col < mtx_.size2(); ++col)
    {
        if (mtx_(row, col) == num) {
            return false;
        }
    }
    return true;

    #if 0 // Slower
    bnu::matrix_row<Matrix> mr(mtx_, row);
    return find_if(mr.begin(), mr.end(), [&](int i){return i==num;}) != mr.end();
    #endif
}

bool SudokuSolver::AvailableOnRange(int row, int col, int num)
{
    for (int r=0; r < 3; ++r)
    {
        for (int c=0; c < 3; ++c)
        {
            auto i = r + row;
            auto j = c + col;

            if (mtx_(i, j) == num) {
                return false;
            }
        }
    }
    return true;
}

void SudokuSolver::ClearGrid()
{
    mtx_.clear();
    mcopy_.clear();

    solved_ = false;
}

bool SudokuSolver::CheckConstraints(Cell& cell, int num)
{
    auto row = get<0>(cell);
    auto col = get<1>(cell);

    auto r = row - row % 3;
    auto c = col - col % 3;

    bool result = AvailableOnRow   (row , num) &&
                  AvailableOnCol   (col , num) &&
                  AvailableOnRange (r, c, num);

    return result;
}

bool SudokuSolver::FindEmptyCell(Cell& cell)
{
    for (auto row=0; row < mtx_.size1(); ++row)
    {
        for (auto col=0; col < mtx_.size2(); ++col)
        {
            if (mtx_(row, col) == _)
            {
                get<0>(cell) = row;
                get<1>(cell) = col;

                return true;
            }
        }
    }
    return false;
}

void SudokuSolver::Generate(DifficultyLevel level)
{
    ClearGrid();

    SudokuHelper helper(mtx_, level);
    helper.Generate();
}

bool SudokuSolver::Solve()
{
    Cell cell;

    if (!FindEmptyCell(cell)) {
        return true;
    }

    for (auto num : digits_)
    {
        if (CheckConstraints(cell, num))
        {
            auto row = get<0>(cell);
            auto col = get<1>(cell);

            mtx_(row, col) = num;

            if (Solve()) {
                return true;
            }

            backtracks_ += 1;
            mtx_(row, col) = _;
        }
    }
    return false;
}

bool SudokuSolver::Run(int firstNo, int& backtracks, int& elapsed)
{
    if (solved_) {
        // Already solved, work on the copy
        mtx_ = mcopy_;
    }
    else {
        // Make a copy before solving
        mcopy_ = mtx_;
    }

    digits_ = {1,2,3,4,5,6,7,8,9};
    rotate(begin(digits_), begin(digits_) + firstNo, end(digits_));

    backtracks_ = 0;
    auto start = Now();

    solved_ = Solve();
    backtracks = backtracks_;

    elapsed = MilliSecondOfTheMinute(Now() - start);
    return solved_;
}

