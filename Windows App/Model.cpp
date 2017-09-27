#include "SudokuPCH1.h"
#pragma hdrstop

#include "Model.h"
#include "SudokuSolver.h"

using namespace engine;
using namespace mvvm;
using namespace types;
using namespace std;

//
//
//  Class Model

// Ctor
Model::Model()
    // Member Intialization List
    : solver_(nullptr)
{
    solver_ = make_unique<SudokuSolver>();
}

void Model::AddCell(int number, int row, int col)
{
    solver_->AddCell(number, row, col);
}

void Model::ClearGrid()
{
    solver_->ClearGrid();
}

void Model::Generate(DifficultyLevel level)
{
    solver_->Generate(level);
}

bool Model::Solve(int firstNo, int& backtracks, int& elapsed)
{
    return solver_->Run(firstNo, backtracks, elapsed);
}

