// Copyright 2021 Lasar1k <alf.ivan2002@gmail.com>

#include <searcher.hpp>
#include <iostream>
#include <stdexcept>

#include "boost/filesystem.hpp"

auto example() -> void {
  throw std::runtime_error("not implemented");
}

void Searcher::output_statistics() {
  for (auto& st : statistics) {
    std::cout << "broker: " << std::setw(10) << std::left << st.broker
              << "account:" << std::setw(10) << std::left << st.account
              << "number of files:" << std::setw(10) << std::left
              << st.num_files << "lastdate:" << std::setw(10) << std::left
              << st.date << std::endl;
  }
}

void Searcher::read_directory(std::string directory, bool output_list)
 {
  //Записываем начальный список путей
  for (const boost::filesystem::directory_entry& object :
       boost::filesystem::directory_iterator{directory}) {
    if (is_directory(object)) {
      directories.push_back(object);
    }
  }

  for (auto& element : directories) {
    for (const boost::filesystem::directory_entry& object :
         boost::filesystem::directory_iterator{element}) {
      if (is_directory(object)) {
        directories.push_back(object);
      } else if (boost::filesystem::is_regular_file(object)) {
        std::cmatch m;
        bool checker = false;
        regex_search(object.path().c_str(), m,
                     std::regex("([a-z]+)/balance_([0-9]+)_([0-9]+).txt"));
        if (m[0] != "") {
          if (output_list) {
            std::cout << m[1] << " balance_" << m[2] << "_" << m[3] << ".txt"
                      << std::endl;
          }
          for (auto& st : statistics) {
            if (st.broker == m[1]) {
              if (std::stoi(m[3]) > st.date) {
                st.date = std::stoi(m[3]);
                st.account = m[2];
              }
              checker = true;
              st.num_files++;
            }
          }
          if (!checker) {
            Statistic statistic;
            statistic.broker = m[1];
            statistic.date = std::stoi(m[3]);
            statistic.account = m[2];
            statistic.num_files = 1;
            statistics.push_back(statistic);
          }
        }
        checker = false;
      }
    }
  }
}
