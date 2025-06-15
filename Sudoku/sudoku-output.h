#pragma once

#include"sudoku-const.h"
#include"sudoku-macros.h"
#include<memory>
#include<string>


class SudokuSolution;

class SudokuOutput {
public:
  DISABLE_ALL_CONSTRUCTORS(SudokuOutput)

  static void printSolution(std::shared_ptr<SudokuSolution> sudokuSolution);
  static void printGradingData(int solvedDigits, int solvedFromStart, int solvedNakedSingles, int solvedHiddenSingles, int solvedCheated, int recursionDepthFound);
  static void printAnalyzeHeading();
  static void printGenerateHeading();
  static void printFileHeading(std::string const& name);
  static void printSolutionConclusionSuccess(double grade);
  static void printSolutionConclusionFailure();
};
