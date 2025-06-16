
#include"sudoku-analyzer.h"
#include"sudoku-const.h"
#include"sudoku-generator.h"
#include"sudoku-grader.h"
#include"sudoku-output.h"
#include"sudoku-solution.h"


SudokuGenerator::SudokuGenerator(size_t grade)
  : grade(grade) {
  std::random_device seedSource;
  randomGenerator.seed(seedSource());
}

bool SudokuGenerator::generate() {
  generateCellValues(0, 0);
  sudokuSolutionSolved = std::make_shared<SudokuSolution>(*sudokuSolutionInitial);
  removeCellValues();

  SudokuGrid sudokuGrid;
  sudokuGrid.set(*sudokuSolutionInitial);
  SudokuAnalyzer sudokuAnalyzer(sudokuGrid);
  if(sudokuAnalyzer.run()) {
    SudokuGrader sudokuGrader(sudokuGrid, sudokuAnalyzer.getSudokuSolution());
    double rating = sudokuGrader.run();
    return SudokuConst::GRADE_LIMITS[grade][SudokuConst::GRADE_LIMIT_LOWER] <= rating && rating <= SudokuConst::GRADE_LIMITS[grade][SudokuConst::GRADE_LIMIT_UPPER];
  }
  return false;
}

std::shared_ptr<SudokuSolution> SudokuGenerator::getSolutionInitial() {
  return sudokuSolutionInitial;
}

std::shared_ptr<SudokuSolution> SudokuGenerator::getSolutionSolved() {
  return sudokuSolutionSolved;
}

bool SudokuGenerator::generateCellValues(size_t startRow, size_t startCol) {
  ++recursionDepth;
  for(size_t row = startRow; row < SudokuConst::SIZE; ++row) {
    for(size_t col = (row == startRow ? startCol : 0); col < SudokuConst::SIZE; ++col) {
      if(0 == sudokuGrid.matrix[row][col]) {
        std::array<int, SudokuConst::SIZE> shuffledDigits = SudokuConst::BASE_DIGITS;
        std::shuffle(shuffledDigits.begin(), shuffledDigits.end(), randomGenerator);
        for(int digit : shuffledDigits) {
          int bit = 1 << (digit - 1);
          if(!(sudokuGrid.rowMask[row] & bit) && !(sudokuGrid.colMask[col] & bit) && !(sudokuGrid.boxMask[SudokuConst::BOX_MATRIX[row][col]] & bit)) {
            sudokuGrid.rowMask[row] |= bit;
            sudokuGrid.colMask[col] |= bit;
            sudokuGrid.boxMask[SudokuConst::BOX_MATRIX[row][col]] |= bit;
            sudokuGrid.matrix[row][col] = digit;
            if(generateCellValues(row, col)) {
              if(!sudokuSolutionInitial) {
                recursionDepthFound = recursionDepth;
                sudokuSolutionInitial = std::make_shared<SudokuSolution>(sudokuGrid, recursionDepthFound);
              }
              --recursionDepth;
              return true;
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

void SudokuGenerator::removeCellValues() {
  auto& matrix = sudokuSolutionInitial->matrix;
  size_t rmCells = SudokuConst::KEEP_CELLS_GRADE[grade];
  if(1 == rmCells % 2) {
    matrix[SudokuConst::MIDDLE_CELL_INDEX][SudokuConst::MIDDLE_CELL_INDEX] = 0;
    --rmCells;
  }
  std::uniform_int_distribution<int> rowDist(0, SudokuConst::MIDDLE_CELL_INDEX);
  std::uniform_int_distribution<int> colDist(0, SudokuConst::SIZE_INDEX);
  while(rmCells > 0) {
    size_t row, col;
    do {
      row = rowDist(randomGenerator);
      col = colDist(randomGenerator);
    } while (row == SudokuConst::MIDDLE_CELL_INDEX && col == SudokuConst::MIDDLE_CELL_INDEX || 0 == matrix[row][col]);
    if (SudokuConst::MIDDLE_CELL_INDEX == row) {
      size_t mirroredCol = SudokuConst::SIZE_INDEX - col;
      matrix[row][col] = 0;
      matrix[row][mirroredCol] = 0;
      matrix[col][row] = 0;
      matrix[mirroredCol][row] = 0;
    }
    else if (SudokuConst::MIDDLE_CELL_INDEX == col) {
      size_t mirroredRow = SudokuConst::SIZE_INDEX - row;
      matrix[row][col] = 0;
      matrix[mirroredRow][col] = 0;
      matrix[col][row] = 0;
      matrix[col][mirroredRow] = 0;
    }
    else if(4 == SudokuConst::BOX_MATRIX[row][col]) {
      size_t localRow = row - SudokuConst::BOX_SIZE;
      size_t localCol = col - SudokuConst::BOX_SIZE;
      size_t mirroredRow = SudokuConst::BOX_SIZE_DOUBLE_INDEX - localRow;
      size_t mirroredCol = SudokuConst::BOX_SIZE_DOUBLE_INDEX - localCol;
      matrix[row][col] = 0;
      matrix[mirroredRow][col] = 0;
      matrix[row][mirroredCol] = 0;
      matrix[mirroredRow][mirroredCol] = 0;
    }
    else {
      size_t localRow = row;
      size_t localCol = col;
      size_t mirroredRow = SudokuConst::SIZE_INDEX - row;
      size_t mirroredCol = SudokuConst::SIZE_INDEX - col;
      matrix[row][col] = 0;
      matrix[mirroredRow][col] = 0;
      matrix[row][mirroredCol] = 0;
      matrix[mirroredRow][mirroredCol] = 0;
    }
    rmCells -= 4;
  }
}
