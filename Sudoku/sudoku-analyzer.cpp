
#include"sudoku-analyzer.h"
#include"sudoku-const.h"
#include"sudoku-grid.h"
#include"sudoku-output.h"


SudokuAnalyzer::SudokuAnalyzer(SudokuGrid const& sudokuGrid)
  : sudokuGrid(sudokuGrid) {}

bool SudokuAnalyzer::run() {
  verify(0, 0);
  return 1 == foundSolutions;
}

std::shared_ptr<SudokuSolution> SudokuAnalyzer::getSudokuSolution() const {
  return sudokuSolution;
}

bool SudokuAnalyzer::verify(size_t startRow, size_t startCol) {
  ++recursionDepth;
  for(size_t row = startRow; row < SudokuConst::SIZE; ++row) {
    for(size_t col = (row == startRow ? startCol : 0); col < SudokuConst::SIZE; ++col) {
      if(0 == sudokuGrid.matrix[row][col]) {
        for(int digit = 1; digit <= SudokuConst::SIZE; ++digit) {
          int bit = 1 << (digit - 1);
          if(!(sudokuGrid.rowMask[row] & bit) && !(sudokuGrid.colMask[col] & bit) && !(sudokuGrid.boxMask[SudokuConst::BOX_MATRIX[row][col]] & bit)) {
            sudokuGrid.rowMask[row] |= bit;
            sudokuGrid.colMask[col] |= bit;
            sudokuGrid.boxMask[SudokuConst::BOX_MATRIX[row][col]] |= bit;
            sudokuGrid.matrix[row][col] = digit;
            if(verify(row, col)) {
              recursionDepthFound = recursionDepth;
              if(1 == ++foundSolutions) {
                sudokuSolution = std::make_shared<SudokuSolution>(sudokuGrid, recursionDepthFound);
              }
            }
            if(2 <= foundSolutions) {
              --recursionDepth;
              return false;
            }
            sudokuGrid.rowMask[row] ^= bit;
            sudokuGrid.colMask[col] ^= bit;
            sudokuGrid.boxMask[SudokuConst::BOX_MATRIX[row][col]] ^= bit;
            sudokuGrid.matrix[row][col] = 0;
          }
        }
        --recursionDepth;
        return false;
      }
    }
  }
  --recursionDepth;
  return true;
}
