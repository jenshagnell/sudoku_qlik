#pragma once

#include"sudoku-macros.h"
#include<array>


template<size_t value>
constexpr size_t ENSURE_DIVISION_WITH_2() {
  static_assert(value % 2 == 0, "value is not divisible by 2!");
  return value;
}

template<size_t value>
constexpr size_t ENSURE_DIVISION_WITH_4() {
  static_assert(value % 4 == 0, "value is not divisible by 4!");
  return value;
}

template<size_t size>
constexpr std::array<int, size> generateBaseDigits() {
  std::array<int, size> digits{};
  for(int i = 0; i < size; ++i) {
    digits[i] = i + 1;
  }
  return digits;
};

class SudokuConst {
public:
  DISABLE_ALL_CONSTRUCTORS(SudokuConst)

  static constexpr size_t SIZE = 9;
  static constexpr size_t SIZE_INDEX = SIZE - 1;
  static constexpr size_t BOX_SIZE = 3;
  static constexpr size_t BOX_SIZE_DOUBLE = 2 * BOX_SIZE;
  static constexpr size_t BOX_SIZE_DOUBLE_INDEX = BOX_SIZE_DOUBLE - 1;
  static constexpr size_t NBR_OF_CELLS = SIZE * SIZE;
  static constexpr size_t MIDDLE_CELL_INDEX = SIZE / 2;

  static constexpr size_t BOX_MATRIX[SIZE][SIZE] = { // std::array ???
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {6, 6, 6, 7, 7, 7, 8, 8, 8},
    {6, 6, 6, 7, 7, 7, 8, 8, 8},
    {6, 6, 6, 7, 7, 7, 8, 8, 8}
  };
  static constexpr size_t BOX_START_ROW[SIZE] = {0, 0, 0, 3, 3, 3, 6, 6, 6}; // std::array ???
  static constexpr size_t BOX_START_COL[SIZE] = {0, 3, 6, 0, 3, 6, 0, 3, 6}; // std::array ???
  static constexpr int FULL_MASK = (1 << SudokuConst::SIZE) - 1;

  static constexpr size_t GRADE_EASY = 0;
  static constexpr size_t GRADE_MEDIUM = 1;
  static constexpr size_t GRADE_HARD = 2;
  static constexpr size_t GRADE_SAMURAI = 3;
  static constexpr size_t KEEP_CELLS_GRADE[4] = {
    NBR_OF_CELLS - ENSURE_DIVISION_WITH_4<24>(),
    NBR_OF_CELLS - ENSURE_DIVISION_WITH_4<28>(),
    NBR_OF_CELLS - ENSURE_DIVISION_WITH_2<32>(),
    NBR_OF_CELLS - ENSURE_DIVISION_WITH_2<32>()
  };
  static constexpr size_t GRADE_LIMIT_LOWER = 0;
  static constexpr size_t GRADE_LIMIT_UPPER = 1;
  static constexpr size_t GRADE_LIMITS[4][2] = { {0, 210}, {210, 310}, {310, 335}, {335, 400} };

  static constexpr std::array<int, SIZE> BASE_DIGITS = generateBaseDigits<SIZE>();
};

