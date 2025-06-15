#pragma once

#include"sudoku-macros.h"
#include"sudoku-solution.h"
#include<atomic>
#include<memory>


class SudokuWorker {
public:
  SudokuWorker();
  DISABLE_ASSIGN_AND_MOVE(SudokuWorker)

  void run(std::atomic<bool>& done);
  std::shared_ptr<SudokuSolution> getSolutionInitial();
  std::shared_ptr<SudokuSolution> getSolutionSolved();
private:
  std::shared_ptr<SudokuSolution> sudokuSolutionInitial;
  std::shared_ptr<SudokuSolution> sudokuSolutionSolved;
};
