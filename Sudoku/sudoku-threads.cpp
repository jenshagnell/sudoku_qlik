
#include"sudoku-worker.h"
#include"sudoku-threads.h"
#include<atomic>
#include<condition_variable>
#include<mutex>
#include<thread>
#include<vector>


SudokuThreads::SudokuThreads() {}

void SudokuThreads::run() {
  std::atomic<int> completedIndex{-1};
  std::condition_variable cv;
  std::mutex mtx;
  std::vector<std::thread> threads;
  std::vector<std::unique_ptr<SudokuWorker>> workers;
  unsigned int numThreads = std::thread::hardware_concurrency();

  for(unsigned int i = 0; i < numThreads; ++i) {
    workers.emplace_back(std::make_unique<SudokuWorker>());
    threads.emplace_back([&, id = i](SudokuWorker& sudokuWorker) {
      sudokuWorker.run(done);
      int expected = -1;
      if(completedIndex.compare_exchange_strong(expected, id)) {
        cv.notify_one();
      }
    }, std::ref(*workers.back()));
  }

  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [&] { return completedIndex.load() != -1; });

  for(auto& thread: threads) {
    if(thread.joinable()) {
      thread.join();
    }
  }
  sudokuSolutionInitial = workers[completedIndex.load()]->getSolutionInitial();
  sudokuSolutionSolved = workers[completedIndex.load()]->getSolutionSolved();
}

std::shared_ptr<SudokuSolution> SudokuThreads::getSolutionInitial() {
  return sudokuSolutionInitial;
}

std::shared_ptr<SudokuSolution> SudokuThreads::getSolutionSolved() {
  return sudokuSolutionSolved;
}
