#include "StdAfx.h"

#include "SudokuSolver.h"
using namespace engine;

//
//  Main Entry Point
//
int main()
{
    SudokuSolver solver;
    
    solver.ReadFile("Samurai.txt");

    if (solver.Run(1/*first digit*/))
    {
        solver.DisplayMatrix();
        return 0;
    }
    return 1;
}
