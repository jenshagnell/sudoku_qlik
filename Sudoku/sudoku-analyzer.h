#pragma once

#include"sudoku-macros.h"
#include"sudoku-grid.h"
#include"sudoku-solution.h"
#include<memory>


class SudokuSolution;

class SudokuAnalyzer {
public:
  SudokuAnalyzer(SudokuGrid const& sudokuGrid);
  DISABLE_COPY_AND_MOVE(SudokuAnalyzer)

  bool run();
  std::shared_ptr<SudokuSolution> getSudokuSolution() const;
private:
  bool verify(size_t startRow, size_t startCol);

  SudokuGrid sudokuGrid;

  std::shared_ptr<SudokuSolution> sudokuSolution;
  int recursionDepth = 0;
  int recursionDepthFound = 0;
  int foundSolutions = 0;
};
