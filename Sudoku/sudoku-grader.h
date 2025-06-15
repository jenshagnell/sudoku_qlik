#pragma once

#include"sudoku-grader.h"
#include"sudoku-grid.h"
#include"sudoku-macros.h"
#include<array>
#include<memory>


class SudokuSolution;

class SudokuGrader {
public:
  SudokuGrader(SudokuGrid const& sudokuGrid, std::shared_ptr<SudokuSolution> sudokuSolution);
  DISABLE_COPY_AND_MOVE(SudokuGrader)

  double run();
private:
  void findAllowedValues(size_t row, size_t col);
  void updateAllowedMasks(size_t row, size_t col, int value);

  bool findNakedSingle();
  bool findHiddenSingle();
  bool cheatUseSolved();

  SudokuGrid sudokuGrid;
  std::shared_ptr<SudokuSolution> sudokuSolution;

  std::array<std::array<int, SudokuConst::SIZE>, SudokuConst::SIZE> allowedMasks;
  int solvedDigits = 0;
  int solvedFromStart = 0;
  int solvedNakedSingles = 0;
  int solvedHiddenSingles = 0;
  int solvedCheated = 0;
};
