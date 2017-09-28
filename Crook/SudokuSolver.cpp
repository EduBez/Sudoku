#include "StdAfx.h"

#include <algorithm>
#include <sstream>
using namespace std;

#include "SudokuSamurai.h"
#include "SudokuSolver.h"

using namespace data;
using namespace engine;
using namespace types;
using namespace boost::numeric::ublas;

//
//  Class SudokuSolver
//

// Ctor
SudokuSolver::SudokuSolver()
{
    SudokuSamurai samurai;
    // Retrieve a pre-created Sudoku board
    mtx_ = samurai.GetData();

    // Define 3x3 block ranges
    v3by3_ =
    {
        // In matrix_range<> the 1st range are Rows
        // and the 2nd range are Cols

        { MatrixRange(mtx_, range(0, 3), range(0, 3)) },
        { MatrixRange(mtx_, range(3, 6), range(0, 3)) },
        { MatrixRange(mtx_, range(6, 9), range(0, 3)) },

        { MatrixRange(mtx_, range(0, 3), range(3, 6)) },
        { MatrixRange(mtx_, range(3, 6), range(3, 6)) },
        { MatrixRange(mtx_, range(6, 9), range(3, 6)) },

        { MatrixRange(mtx_, range(0, 3), range(6, 9)) },
        { MatrixRange(mtx_, range(3, 6), range(6, 9)) },
        { MatrixRange(mtx_, range(6, 9), range(6, 9)) }
    };
}

void SudokuSolver::DisplayMatrix()
{
    for (unsigned i=0; i < mtx_.size1(); ++i)
    {
        for (unsigned j=0; j < mtx_.size2(); ++j)
        {
            auto r1 = mtx_(i, j).begin();
            auto r2 = mtx_(i, j).end();

            cout << "(" << i << ", " << j << ") = ";

            stringstream ss;
            for_each(r1, r2, [&](int i){ss << i << " ";});
            
            cout << ss.str() << endl;
        }
        cout << endl;
    }

    cout << "------------------------------------------------------------------------------------------------------" << endl;


}

int SudokuSolver::CountOfFilledCells()
{
    return count_if(mtx_.data().begin(), mtx_.data().end(), [](SingleCell& cell)
        {return (cell.size() == 1);});
}

void SudokuSolver::ReplaceEmptyCells()
{
    SingleCell sc{1,2,3,4,5,6,7,8,9};
    
    for_each(mtx_.data().begin(), mtx_.data().end(),
        [&](SingleCell& cell){if (cell[0] == _) cell = sc;});
}

bool SudokuSolver::Start()
{
    ReplaceEmptyCells();

    SweepBlock3By3(PredEqualTo());

    bool s= Solve();

DisplayMatrix();

return s;
}

bool SudokuSolver::Solve()
{
    // Count the filled cells
    auto count = CountOfFilledCells();

    if (count == 81) {
        return true;
    }

    while (true)
    {
        SweepByRowsAndCols();

        auto filled = CountOfFilledCells();

        if (filled > count)
        {
            count = filled;
        }
        else break;
    }

    // Re-count the filled cells
    auto filled = CountOfFilledCells();

    // No improvement, the count of cells is the same    
    if (filled == count && filled != 81)
    {
        SingleCell coll;

        // Iterate over all Rows
        for (unsigned i=0; i < mtx_.size1(); ++i)
        {
            // Project a row range
            bnu::matrix_row<MatrixCells> mr(mtx_, i);

            SweepAndRemoveByForce(mr);
        }

        // The count of cells increased
        if (CountOfFilledCells() > filled) {
            return Solve();
        }

        // Iterate over all Cols
        for (unsigned i=0; i < mtx_.size2(); ++i)
        {
            // Project a row range
            bnu::matrix_column<MatrixCells> mr(mtx_, i);

            SweepAndRemoveByForce(mr);
        }

        // The count of cells increased
        if (CountOfFilledCells() > filled) {
            return Solve();
        }

        SweepBlock3By3XX();

        // The count of cells increased
        if (CountOfFilledCells() > filled) {
            return Solve();
        }
    }

    return true;
}

void SudokuSolver::SweepByRowsAndCols()
{
    // Iterate over all Rows
    for (unsigned i=0; i < mtx_.size1(); ++i)
    {
        // Project a row range
        bnu::matrix_row<MatrixCells> mr(mtx_, i);
        SweepAndRemove(mr);
    }

    // Iterate over all Columns
    for (unsigned i=0; i < mtx_.size2(); ++i)
    {
        // Project a column range
        bnu::matrix_column<MatrixCells> mr(mtx_, i);
        SweepAndRemove(mr);
    }
}















void SudokuSolver::SweepBlock3By3XX()
{
    // For all 9 (3x3) squares
    for (auto& it : v3by3_)
    {
        types::SingleCell coll;
        int counter = 0;

        // First 3x3 block iteration
        for (unsigned i = 0; i < it.size1(); ++i)
        {
            for (unsigned j = 0; j < it.size2(); ++j)
            {
                types::SingleCell cell = it(i, j);

                if (cell.size() > 1)
                {
                    counter += 1;
                }
            }
        }

        // CONDICAO 1
        if (counter >= 1)
        {
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////

        for (unsigned i = 0; i < it.size1(); ++i)
        {
            for (unsigned j = 0; j < it.size2(); ++j)
            {
                types::SingleCell cell = it(i, j);

                if (cell.size() == 1)
                {
                    std::copy(begin(cell), end(cell), back_inserter(coll));
                }
            }
        }

        for (unsigned i = 0; i < it.size1(); ++i)
        {
            for (unsigned j = 0; j < it.size2(); ++j)
            {
                types::SingleCell& cell = it(i, j);

                if (cell.size() > 1)
                {
                    std::sort(begin(cell), end(cell));
                    std::sort(begin(coll), end(coll));

                    auto lb = [&](auto val)
                    {
                        auto it = coll.begin();

                        while (it != end(coll) && *it < val)
                        {
                            ++it;
                        }
                        return (it != end(coll) && *it == val);
                    };
                    cell.erase(remove_if(begin(cell), end(cell), lb), end(cell));
                }
            }
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
    }








    // For all 9 (3x3) squares
    for (auto& it : v3by3_)
    {
        types::SingleCell coll;

        #if 1
        int counter = 0;

        // First 3x3 block iteration
        for (unsigned i = 0; i < it.size1(); ++i)
        {
            for (unsigned j = 0; j < it.size2(); ++j)
            {
                types::SingleCell cell = it(i, j);
                
                if (cell.size() > 1)
                {
                    counter +=1;
                }
            }
        }

        // CONDICAO 1
        if (counter > 1)
        {
            for (unsigned i = 0; i < it.size1(); ++i)
            {
                for (unsigned j = 0; j < it.size2(); ++j)
                {
                    types::SingleCell cell = it(i, j);

                    if (cell.size() > 1)
                    {
                        std::copy(begin(cell), end(cell), back_inserter(coll));
                    }
                }
            }

/////////////////////////////////////////////////////////////////////////////////////////////
            // Collection must be sorted
            std::sort(begin(coll), end(coll));

            std::map<int, int> bag;

            for (auto i : coll)
            {
                bag[count(begin(coll), end(coll), i)] = i;
            }

            bool flag = false;
            for (auto it = bag.begin(); it != bag.end(); ++it)
            {
                if (it->first == 1)
                {
                    flag = true;
                }
            }

            if (flag == true)
            {
                for (unsigned i = 0; i < it.size1(); ++i)
                {
                    for (unsigned j = 0; j < it.size2(); ++j)
                    {
                        types::SingleCell cell = it(i, j);

                        auto found = std::find(begin(cell), end(cell), bag[1]);

                        if (found != end(cell))
                        {
                            cell = { bag[1] };
                        }
                    }
                }
            }
        }
        // CONDICAO 2
        if (counter == 1)
        {
            // First 3x3 block iteration
            for (unsigned i = 0; i < it.size1(); ++i)
            {
                for (unsigned j = 0; j < it.size2(); ++j)
                {
                    types::SingleCell cell = it(i, j);

                    if (cell.size() == 1)
                    {
                        std::copy(begin(cell), end(cell), back_inserter(coll));
                    }
                }
            }

////////////////////////////////////////////////////////////////

            for (unsigned i = 0; i < it.size1(); ++i)
            {
                for (unsigned j = 0; j < it.size2(); ++j)
                {
                    types::SingleCell cell = it(i, j);

std::sort(begin(cell), end(cell));
std::sort(begin(coll), end(coll));

                    if (cell.size() > 1)
                    {
                        auto lb = [&](auto val)
                        {
                            auto it = coll.begin();

                            while (it != end(coll) && *it < val)
                            {
                                ++it;
                            }
                            return (it != end(coll) && *it == val);
                        };
                        cell.erase(remove_if(begin(cell), end(cell), lb), end(cell));
                     }
                }
            }
        }
        #endif
    }
}




