#pragma once

#include"sudoku-macros.h"
#include<string>


class SudokuFile {
public:
  SudokuFile(std::string const& fileName);
  DISABLE_COPY_AND_MOVE(SudokuFile)

  bool read(std::string* data);
private:
  std::string fileName;
};
