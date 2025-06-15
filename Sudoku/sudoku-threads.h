#pragma once

#include"sudoku-macros.h"
#include"sudoku-threads.h"
#include <atomic>


class SudokuThreads {
public:
  SudokuThreads();
  DISABLE_ASSIGN_AND_MOVE(SudokuThreads)

  void run();
  std::shared_ptr<SudokuSolution> getSolutionInitial();
  std::shared_ptr<SudokuSolution> getSolutionSolved();
private:
  std::atomic<bool> done{false};
  std::shared_ptr<SudokuSolution> sudokuSolutionInitial;
  std::shared_ptr<SudokuSolution> sudokuSolutionSolved;
};
