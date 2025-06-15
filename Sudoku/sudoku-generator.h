#pragma once

#include"sudoku-grid.h"
#include"sudoku-macros.h"
#include<random>


class SudokuSolution;

class SudokuGenerator {
public:
  SudokuGenerator(size_t grade);
  DISABLE_COPY_AND_MOVE(SudokuGenerator)

  bool generate();
  std::shared_ptr<SudokuSolution> getSolutionInitial();
  std::shared_ptr<SudokuSolution> getSolutionSolved();
private:
  bool generateCellValues(size_t startRow, size_t startCol);
  void removeCellValues();

  size_t grade;
  SudokuGrid sudokuGrid;

  std::mt19937 randomGenerator;
  
  std::shared_ptr<SudokuSolution> sudokuSolutionSolved;
  std::shared_ptr<SudokuSolution> sudokuSolutionInitial;
  int recursionDepth = 0;
  int recursionDepthFound = 0;
};
