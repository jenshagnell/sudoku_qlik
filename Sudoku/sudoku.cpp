
#include"sudoku.h"
#include"sudoku-analyzer.h"
#include"sudoku-generator.h"
#include"sudoku-grader.h"
#include"sudoku-grid.h"
#include"sudoku-output.h"
#include"sudoku-threads.h"


Sudoku::Sudoku() {}

void Sudoku::run() {
  SudokuOutput::printAnalyzeHeading();
  std::vector<std::string> sudokuNames = {"easy", "medium", "hard", "samurai", "multiple"};
  for(const auto& sudokuName: sudokuNames) {
    SudokuOutput::printFileHeading(sudokuName);
    SudokuGrid sudokuGrid;
    if(sudokuGrid.parse(sudokuName)) {
      SudokuAnalyzer sudokuAnalyzer(sudokuGrid);
      if(sudokuAnalyzer.run()) {
        SudokuGrader sudokuGrader(sudokuGrid, sudokuAnalyzer.getSudokuSolution());
        double grade = sudokuGrader.run();
        SudokuOutput::printSolutionConclusionSuccess(grade);
        SudokuOutput::printSolution(sudokuAnalyzer.getSudokuSolution());
      }
      else {
        SudokuOutput::printSolutionConclusionFailure();
      }
    }
  }
  SudokuOutput::printGenerateHeading();
  SudokuThreads sudokuThreads;
  sudokuThreads.run();
  SudokuOutput::printSolution(sudokuThreads.getSolutionInitial());
  SudokuOutput::printSolution(sudokuThreads.getSolutionSolved());
}
