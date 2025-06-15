
#include"sudoku-grid.h"
#include"sudoku-solution.h"


SudokuSolution::SudokuSolution(SudokuGrid const& sudokuGrid, int recursionDepthFound)
  : matrix(sudokuGrid.matrix)
  , recursionDepthFound(recursionDepthFound) {}
