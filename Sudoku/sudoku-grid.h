#pragma once

#include"sudoku-const.h"
#include"sudoku-macros.h"
#include<array>
#include<string>

class SudokuSolution;


class SudokuGrid {
public:
  SudokuGrid();
  SudokuGrid(const SudokuGrid&);
  DISABLE_ASSIGN_AND_MOVE(SudokuGrid)

  bool parse(std::string const& name);
  void set(SudokuSolution const& sudokuSolution);

  std::array<std::array<int, SudokuConst::SIZE>, SudokuConst::SIZE> matrix;
  std::array<int, SudokuConst::SIZE> rowMask;
  std::array<int, SudokuConst::SIZE> colMask;
  std::array<int, SudokuConst::SIZE> boxMask;
};
