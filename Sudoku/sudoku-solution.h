#pragma once

#include"sudoku-const.h"
#include<array>

class SudokuGrid;


class SudokuSolution {
public:
  SudokuSolution(SudokuGrid const& sudokuGrid, int recursionDepthFound);

  std::array<std::array<int, SudokuConst::SIZE>, SudokuConst::SIZE> matrix;
  int recursionDepthFound;
};
