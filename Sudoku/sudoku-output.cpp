
#include"sudoku-output.h"
#include"sudoku-solution.h"
#include<iostream>


void SudokuOutput::printSolution(std::shared_ptr<SudokuSolution> sudokuSolution) {
  auto const& matrix = sudokuSolution->matrix;
  std::cout << std::endl;
  for(size_t row = 0; row < SudokuConst::SIZE; ++row) {
    if(row % SudokuConst::BOX_SIZE == 0 && row > 0) {
      std::cout << "---------------------\n";
    }
    for(size_t col = 0; col < SudokuConst::SIZE; ++col) {
      if(col % SudokuConst::BOX_SIZE == 0 && col > 0) {
        std::cout << "| ";
      }
      if(matrix[row][col] == 0) {
        std::cout << ". ";
      }
      else {
        std::cout << matrix[row][col] << " ";
      }
    }
    std::cout << std::endl;
  }
}

void SudokuOutput::printGradingData(int solvedDigits, int solvedFromStart, int solvedNakedSingles, int solvedHiddenSingles, int solvedCheated, int recursionDepthFound) {
std::cout << solvedFromStart << " solved from start." << std::endl;
  std::cout << solvedNakedSingles << " naked singles found." << std::endl;
  std::cout << solvedHiddenSingles << " hidden singles found." << std::endl;
  std::cout << solvedCheated << " copies from solution done." << std::endl;
  std::cout << recursionDepthFound << std::endl;
}

void SudokuOutput::printAnalyzeHeading() {
  std::cout << "======================" << std::endl;
  std::cout << "===    " << "ANALYZE " << "    ===" << std::endl;
  std::cout << "======================" << std::endl;
}

void SudokuOutput::printGenerateHeading() {
  std::cout << "======================" << std::endl;
  std::cout << "===    " << "GENERATE" << "    ===" << std::endl;
  std::cout << "======================" << std::endl;
}

void SudokuOutput::printFileHeading(std::string const& name) {
  std::cout << "----------------------" << std::endl;
  std::cout << "--- " << name << std::endl;
  std::cout << "----------------------" << std::endl;
}

void SudokuOutput::printSolutionConclusionSuccess(double grade) {
  std::cout << "There is only one solution." << std::endl;
  std::cout << "Grade: " << grade << std::endl;
}

void SudokuOutput::printSolutionConclusionFailure() {
  std::cout << "There are more than one solution." << std::endl;
}
