
#include"sudoku-file.h"
#include<cassert>
#include<filesystem>
#include<fstream>
#include<iostream>


SudokuFile::SudokuFile(std::string const& fileName) 
  : fileName(fileName) {}

bool SudokuFile::read(std::string* data) {
  assert(nullptr != data);
  std::ifstream file(std::filesystem::path("../data") / (fileName + ".txt"));
  if(!file) {
    return false;
  }
  *data = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return true;
}

