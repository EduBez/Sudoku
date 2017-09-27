#include "StdAfx.h"

#include "SudokuSolver.h"
#include "Typedefs.h"

using namespace engine;
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
    for (unsigned row=0; row < mtx_.size1(); ++row)
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
    for (unsigned col=0; col < mtx_.size2(); ++col)
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

void SudokuSolver::DisplayMatrix()
{
    cout << "Number of Backtracks: "
         << backtracks_ << endl << endl;

    for (unsigned i = 0; i < mtx_.size1(); ++i)
    {
        for (unsigned j=0; j < mtx_.size2(); ++j)
        {
            cout << "(" << i << ", " << j << ") = ";
            cout << mtx_(i, j) << endl;
        }
        cout << endl;
    }
}

bool SudokuSolver::FindEmptyCell(Cell& cell)
{
    for (unsigned row=0; row < mtx_.size1(); ++row)
    {
        for (unsigned col=0; col < mtx_.size2(); ++col)
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

            if (Solve())  {
                return true;
            }

            backtracks_ += 1;
            mtx_(row, col) = _;
        }
    }
    return false;
}

void SudokuSolver::ReadFile(std::string file)
{
    char ch = 0;
    ifstream ifs(file);

    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            // Assume text ifs is a pure ASCII ifs
            // Just chars representing numbers from 1 to 9

            ifs >> ch;

            int number = (int)(ch - '0');
            AddCell(number, row, col);
        }
    }
    ifs.close();
}


bool SudokuSolver::Run(int firstNo)
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
    solved_ = Solve();

    return solved_;
}
