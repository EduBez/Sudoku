#pragma once

#include "StdAfx.h"
#include "Typedefs.h"

namespace bnu = boost::numeric::ublas;

namespace engine {

//
//  Class Predicate
//
template <typename T>
class Predicate
{
    types::SingleCell* coll_;
    T pred_;

public:
    // Default Ctor
    Predicate() {}

    // Ctor
    Predicate(types::SingleCell* coll)
        // Member Initialization List
        : coll_(coll)
    {}

    void SetColl(types::SingleCell* coll)
        {coll_ = coll;}

    bool operator ()(int val)
    {
        auto& coll = *coll_;
        auto it = coll.begin();

        while (it != end(coll) && *it < val) {
            ++it;
        }
        return (it != end(coll) && pred_(*it, val));
    }
};

//
//  Class SudokuSolver
//
class SudokuSolver
{
    using PredEqualTo    = Predicate<std::equal_to<int>>;
    using PredNotEqualTo = Predicate<std::not_equal_to<int>>;

    // Data Members
    types::MatrixCells mtx_;
    types::VectorRange v3by3_;

    // Member Functions
    void DisplayMatrix         ();

    int  CountOfFilledCells    ();

    void ReplaceEmptyCells     ();

    template <typename T>
    void SweepBlock3By3        (T pred);
    void SweepBlock3By3XX      ();

    void SweepByRowsAndCols    ();

    template <typename T>
    void SweepAndRemove        (T& mr);

    template <typename T>
    void SweepAndRemoveByForce (T& mr);

    bool Solve                 ();

public:
    // Ctor
    SudokuSolver();

    // Dtor
    ~SudokuSolver() {};

    bool Start();
};

template <typename T>
void SudokuSolver::SweepBlock3By3(T pred)
{
    SingleCell coll;

    // For all 9 (3x3) squares
    for (auto& it : v3by3_)
    {
        coll.clear();

        // First 3x3 block iteration
        for (unsigned i = 0; i < it.size1(); ++i)
        {
            for (unsigned j = 0; j < it.size2(); ++j)
            {
                SingleCell cell = it(i, j);

                if (cell.size() == 1) {
                    coll.push_back(cell[0]);
                }
            }
        }

        if (coll.size())
        {
            // Collection must be sorted
            std::sort(std::begin(coll), std::end(coll));

            for (unsigned i = 0; i < it.size1(); ++i)
            {
                for (unsigned j = 0; j < it.size2(); ++j)
                {
                    auto& cell = it(i, j);
                    // Cell must be sorted
                    std::sort(begin(cell), end(cell));

                    if (cell.size() > 1)
                    {
                        pred.SetColl(&coll);
                        cell.erase(remove_if(begin(cell), end(cell), pred), end(cell));
                    }
                }
            }
        }
    }
}



















template <typename T>
void SudokuSolver::SweepAndRemove(T& mr)
{
    types::SingleCell coll;

    std::for_each(mr.begin(), mr.end(), [&](auto& cell)
        {if (cell.size() == 1) coll.push_back(cell[0]);});

    if (coll.size())
    {
        // Collection must be sorted
        std::sort(begin(coll), end(coll));

        // Iterate over all cells in this range
        for (auto& cell : mr)
        {
            if (cell.size() > 1)
            {
                // Cell must be sorted
                std::sort(begin(cell), end(cell));

                PredEqualTo pred(&coll);
                cell.erase(remove_if(begin(cell), end(cell), pred), end(cell));
            }
        }
    }
}

template <typename T>
void SudokuSolver::SweepAndRemoveByForce(T& mr)
{
    types::SingleCell coll;

    for (auto cell : mr)
    {
        if (cell.size() > 1)
        {
            std::for_each(begin(cell), end(cell),
            [&](auto& i){coll.push_back(i); });
        }
    }

    if (coll.size())
    {
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

if (flag == false) return;

        // Iterate over all cells in this range
        for (auto& cell : mr)
        {
            if (cell.size() > 1)
            {
                // Cell must be sorted
                std::sort(begin(cell), end(cell));
                
                if (find(begin(cell), end(cell), bag[1]) != end(cell))
                {
                    cell = std::vector<int>{ bag[1] };
                }
            }
        }
    }
}

}// EndOf namespace
