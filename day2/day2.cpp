#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> extract_words(const std::string &str) {
  std::istringstream iss(str);
  std::vector<std::string> words;
  std::string word;

  while (iss >> word) {
    words.push_back(word);
  }
  return words;
}

std::vector<int> string_list_to_int_list(std::vector<std::string> str_list) {
  std::vector<int> int_list;

  for (int i = 0; i < str_list.size(); i++) {
    int converted_int = std::stoi(str_list[i]);
    int_list.push_back(converted_int);
  }
  return int_list;
}

bool is_safe(std::vector<int> &reports) {
  bool ascending = true;
  bool descending = true;

  for (size_t i = 1; i < reports.size(); i++) {
    int diff = reports[i] - reports[i - 1];
    if (std::abs(diff) > 3 || std::abs(diff) < 1) {
      return false;
    }
    if (diff > 0) {
      descending = false;
    } else if (diff < 0) {
      ascending = false;
    }
  }

  return ascending || descending;
}

bool is_safe_with_dampener(std::vector<int> &reports) {
  for (size_t i = 0; i < reports.size(); i++) {
    std::vector<int> modified_reports = reports;

    modified_reports.erase(modified_reports.begin() + i);

    if (is_safe(modified_reports)) {
      return true;
    }
  }
  return false;
}

int main() {

  std::ifstream myfile;
  myfile.open("input");
  std::string myline;
  std::vector<int> list1;
  std::vector<int> list2;
  int count = 0;

  if (myfile.is_open()) {
    std::string line;
    while (myfile) {
      std::getline(myfile, line);
      if (myfile.eof()) {
        break;
      }
      std::vector<std::string> lista = extract_words(line);
      std::vector<int> lista_ints = string_list_to_int_list(lista);
      bool safe = is_safe_with_dampener(lista_ints);
      if (safe) {
        count++;
      }
    }
  }
  std::cout << count;
  return 0;
}
