//
// Created by Rafa on 5/26/2019.
//

#include "qm_petrick.h"
qm_petrick::qm_petrick(size_t var): var_(var) {
  std::string input;

  while (1) {
    if(GetInput(input, "How many variables would you like? (2-10): "))
      try {
        if (stoi(input) > 1 && stoi(input) <= 10) {
          break;
        } else {
          std::cout << "Invalid input, please try again.\n";
        }
      } catch(...) {
        std::cout << "Invalid input, please try again.\n";
      }
    else
      exit(1);
  }

  var_ = stoi(input);
  table_ = new std::bitset<10>[1 << var]; // Fill table with new bitsets

  SetTruthTable(); // Assign values to all rows in the truth table

}

void qm_petrick::PrintTable() const {
  for (size_t i = 0; i < (1 << var_); ++i) {
    std::cout << i << ": " << table_[i].to_string() << "\n";
  }
}

qm_petrick::~qm_petrick() {

}
qm_petrick::qm_petrick(const qm_petrick &other) {

}
qm_petrick &qm_petrick::operator=(const qm_petrick &other) {
//  return <#initializer#>;
}
bool qm_petrick::GetInput(std::string &input, std::string &&question) {

  std::cout << question;
  getline(std::cin, input);
  fflush(stdin);

  return !input.empty();
}

void qm_petrick::SetTruthTable() {
  for (size_t i = 0; i < (1 << var_); ++i) {
    table_[i] = i;
  }
  PrintTable();
}
