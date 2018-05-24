cmake_minimum_required(VERSION 3.1)

project(Sudoku)

set_embt_target(VCL)

add_executable(Sudoku
             , Sudoku.cpp
             , Model.cpp
             , Model.h
             , SudokuHelper.cpp
             , SudokuHelper.h
             , SudokuSolver.cpp
             , SudokuSolver.h
             , Typedefs.cpp
             , Typedefs.h
             , View.cpp
             , View.h
             , ViewModel.h
             , ViewModel.cpp
             , SudokuPCH1.h)


