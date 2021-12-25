#include <searcher.hpp>

using namespace std;

int main() {
  Searcher searcher;
  searcher.read_directory("../misc/ftp", false);
  searcher.output_statistics();
}