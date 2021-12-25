// Copyright 2021 Lasar1k <alf.ivan2002@gmail.com>

#ifndef INCLUDE_SEARCHER_HPP_
#define INCLUDE_SEARCHER_HPP_

#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "boost/filesystem.hpp"

void example();

struct Statistic {
  int date;
  std::string account;
  std::string broker;
  int num_files;
};
class Searcher {
 private:
  std::vector<std::string> files;
  std::vector<boost::filesystem::path> directories;
  std::vector<Statistic> statistics;

 public:
  void read_directory(std::string directory, bool output_list);
  void output_statistics();
};

#endif  // INCLUDE_SEARCHER_HPP_