
#include"sudoku-generator.h"
#include"sudoku-solution.h"
#include"sudoku-worker.h"


SudokuWorker::SudokuWorker() {}

void SudokuWorker::run(std::atomic<bool>& done) {
  bool doneLocal = false;
  do {
    if(done.load()) {
      return;
    }
    SudokuGenerator sudokuGenerator(SudokuConst::GRADE_MEDIUM);
    doneLocal = sudokuGenerator.generate();
    if(doneLocal) {
      sudokuSolutionInitial = sudokuGenerator.getSolutionInitial();
      sudokuSolutionSolved = sudokuGenerator.getSolutionSolved();
      done.store(true);
    }
  } while(!doneLocal);
}

std::shared_ptr<SudokuSolution> SudokuWorker::getSolutionInitial() {
  return sudokuSolutionInitial;
}

std::shared_ptr<SudokuSolution> SudokuWorker::getSolutionSolved() {
  return sudokuSolutionSolved;
}
