
#include"sudoku-const.h"
#include"sudoku-grader.h"
#ifdef _VEBOSE
#include"sudoku-output.h"
#endif
#include"sudoku-solution.h"


SudokuGrader::SudokuGrader(SudokuGrid const& sudokuGrid, std::shared_ptr<SudokuSolution> sudokuSolution)
  : sudokuGrid(sudokuGrid)
  , sudokuSolution(sudokuSolution)
  , allowedMasks{} {}

double SudokuGrader::run() {
  auto& sudokuGridMatrix = sudokuGrid.matrix;
  for(size_t row = 0; row < SudokuConst::SIZE; ++row) {
    for(size_t col = 0; col < SudokuConst::SIZE; ++col) {
      if(0 == sudokuGridMatrix[row][col]) {
        findAllowedValues(row, col);
      }
      else {
        ++solvedDigits;
        ++solvedFromStart;
      }
    }
  }

  size_t previousSolvedDigits = 0;
  while(previousSolvedDigits != solvedDigits && SudokuConst::NBR_OF_CELLS != solvedDigits) {
    previousSolvedDigits = solvedDigits;
    if(!findNakedSingle()) {
      if(!findHiddenSingle()) {
        cheatUseSolved();
        // Of course to make it more accurate you must do more advanced analyzes.
      }
    }
  }
#ifdef _VEBOSE
  SudokuOutput::printGradingData(solvedDigits, solvedFromStart, solvedNakedSingles, solvedHiddenSingles, solvedCheated, sudokuSolution->recursionDepthFound);
#endif
  double grade = 2 * (1.5 * (81 - solvedFromStart) + 1.0 * solvedNakedSingles + 1.0 * solvedHiddenSingles + 1.5 * solvedCheated) + sudokuSolution->recursionDepthFound;
  return grade;
}

void SudokuGrader::findAllowedValues(size_t rowPos, size_t colPos) {
  auto& sudokuGridMatrix = sudokuGrid.matrix;
  uint16_t allowedMask = 0;
  for(size_t row = 0; row < SudokuConst::SIZE; ++row) {
    if(0 != sudokuGridMatrix[row][colPos]) {
      allowedMask |= (1 << (sudokuGridMatrix[row][colPos] - 1));
    }
  }
  for(size_t col = 0; col < SudokuConst::SIZE; ++col) {
    if(0 != sudokuGridMatrix[rowPos][col]) {
      allowedMask |= (1 << (sudokuGridMatrix[rowPos][col] - 1));
    }
  }
  size_t boxId = SudokuConst::BOX_MATRIX[rowPos][colPos];
  size_t boxStartR = SudokuConst::BOX_START_ROW[boxId];
  size_t boxStartC = SudokuConst::BOX_START_COL[boxId];
  for(size_t i = 0; i < SudokuConst::BOX_SIZE; ++i) {
    for(size_t j = 0; j < SudokuConst::BOX_SIZE; ++j) {
      if(0 != sudokuGridMatrix[boxStartR + i][boxStartC + j]) {
        allowedMask |= (1 << (sudokuGridMatrix[boxStartR + i][boxStartC + j] - 1));
      }
    }
  }
  allowedMasks[rowPos][colPos] = allowedMask;
}

void SudokuGrader::updateAllowedMasks(size_t row, size_t col, int value) {
  uint16_t bit = (1 << (value - 1));  
  for(size_t c = 0; c < SudokuConst::SIZE; ++c) {
    allowedMasks[row][c] &= ~bit;
  }
  for (size_t r = 0; r < SudokuConst::SIZE; ++r) {
    allowedMasks[r][col] &= ~bit;
  }
  size_t boxId = SudokuConst::BOX_MATRIX[row][col];
  size_t boxStartR = SudokuConst::BOX_START_ROW[boxId];
  size_t boxStartC = SudokuConst::BOX_START_COL[boxId];
  for(size_t i = 0; i < SudokuConst::BOX_SIZE; ++i) {
    for(size_t j = 0; j < SudokuConst::BOX_SIZE; ++j) {
      allowedMasks[boxStartR + i][boxStartC + j] &= ~bit;
    }
  }
}

bool SudokuGrader::findNakedSingle() {
  auto& sudokuGridMatrix = sudokuGrid.matrix;
  for(size_t row = 0; row < SudokuConst::SIZE; ++row) {
    for(size_t col = 0; col < SudokuConst::SIZE; ++col) {
      uint16_t mask = allowedMasks[row][col];
      if(0 != mask && ((mask & (mask - 1)) == 0)) {
        ++solvedDigits;
        ++solvedNakedSingles;
        int value = 1;
        while(!(mask & 1)) {
          mask >>= 1;
          ++value;
        }
        sudokuGridMatrix[row][col] = value;
        updateAllowedMasks(row, col, value);
        return true;
      }
    }
  }
  return false;
}

bool SudokuGrader::findHiddenSingle() {
  auto& sudokuGridMatrix = sudokuGrid.matrix;
  for(size_t row = 0; row < SudokuConst::SIZE; ++row) {
    for(size_t col = 0; col < SudokuConst::SIZE; ++col) {
      if(0 == sudokuGridMatrix[row][col]) {
        for(int digit = 1; digit <= SudokuConst::SIZE; ++digit) {
          uint16_t bit = (1 << (digit - 1));
          if(!(allowedMasks[row][col] & bit)) {
            continue;
          }
          size_t rowCount = 0;
          size_t colCount = 0;
          size_t boxCount = 0;
          for(size_t c = 0; c < SudokuConst::SIZE; ++c) {
            if(allowedMasks[row][c] & bit) {
              ++rowCount;
            }
          }
          for(size_t r = 0; r < SudokuConst::SIZE; ++r) {
            if(allowedMasks[r][col] & bit) {
              ++colCount;
            }
          }
          size_t boxId = SudokuConst::BOX_MATRIX[row][col];
          size_t boxStartRow = SudokuConst::BOX_START_ROW[boxId];
          size_t boxStartCol = SudokuConst::BOX_START_COL[boxId];
          for(size_t i = 0; i < SudokuConst::BOX_SIZE; ++i) {
            for(size_t j = 0; j < SudokuConst::BOX_SIZE; ++j) {
              size_t r = boxStartRow + i;
              size_t c = boxStartCol + j;
              if(allowedMasks[r][c] & bit) {
                ++boxCount;
              }
            }
          }
          if(1 == rowCount || 1 == colCount || 1 == boxCount) {
            ++solvedDigits;
            ++solvedHiddenSingles;
            sudokuGridMatrix[row][col] = digit;
            updateAllowedMasks(row, col, digit);
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool SudokuGrader::cheatUseSolved() {
  auto const& sudokuSolutionMatrix = sudokuSolution->matrix;
  auto& sudokuGridMatrix = sudokuGrid.matrix;
  for(size_t row = 0; row < SudokuConst::SIZE; ++row) {
    for(size_t col = 0; col < SudokuConst::SIZE; ++col) {
      if(0 == sudokuGrid.matrix[row][col]) {
        ++solvedDigits;
        ++solvedCheated;
        int digit = sudokuSolutionMatrix[row][col];
        sudokuGrid.matrix[row][col] = digit;
        updateAllowedMasks(row, col, digit);
        return true;
      }
    }
  }
  return false;
}
