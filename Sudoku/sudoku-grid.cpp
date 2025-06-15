
#include"sudoku-file.h"
#include"sudoku-grid.h"
#include"sudoku-solution.h"
#include<iostream>
#include<sstream>


SudokuGrid::SudokuGrid() 
  : matrix{}
  , rowMask{}
  , colMask{}
  , boxMask{} {}

SudokuGrid::SudokuGrid(const SudokuGrid& sudokuGrid)
  : matrix(sudokuGrid.matrix)
  , rowMask(sudokuGrid.rowMask)
  , colMask(sudokuGrid.colMask)
  , boxMask(sudokuGrid.boxMask) {}

bool SudokuGrid::parse(std::string const& name) {
  SudokuFile sudokuFile(name);
  std::string data;
  if(!sudokuFile.read(&data)) {
    std::cout << "Could not read file" << std::endl;
    return false;
  }
  std::istringstream stream(data);
  std::string line;
  size_t row = 0;
  while(std::getline(stream, line) && row < SudokuConst::SIZE) {
    if(SudokuConst::SIZE != line.size()) {
      std::cout << "Wrong format on line: " << row + 1 << std::endl;
      return false;
    }
    for(size_t col = 0; col < SudokuConst::SIZE; ++col) {
      if(std::isdigit(line[col]) && '0' != line[col]) {
        int digit = line[col] - '0';
        matrix[row][col] = digit;
        int bit = 1 << (digit - 1);
        rowMask[row] |= bit;
        colMask[col] |= bit;
        boxMask[SudokuConst::BOX_MATRIX[row][col]] |= bit;
      }
      else {
        matrix[row][col] = 0;
      }
    }
    ++row;
  }
  return true;
}

void SudokuGrid::set(SudokuSolution const& sudokuSolution) {
  auto const& solutionMatrix = sudokuSolution.matrix;
  matrix = solutionMatrix;
  for(size_t row = 0; row < SudokuConst::SIZE; ++row) {
    for(size_t col = 0; col < SudokuConst::SIZE; ++col) {
      int digit = solutionMatrix[row][col];
      if(0 != digit) {
        int bit = 1 << (digit - 1);
        rowMask[row] |= bit;
        colMask[col] |= bit;
        boxMask[SudokuConst::BOX_MATRIX[row][col]] |= bit;
      }
    }
  }
}
