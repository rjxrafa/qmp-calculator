//
// Created by Rafa on 5/26/2019.
//

#include <algorithm>
#include "qm_petrick.h"
qm_petrick::qm_petrick(size_t var): var_(var) {
  std::string input;

  while (1) {
    if (GetInput(input, "How many variables would you like? (2-10): "))
      if (ValidateInput(input, 2, 10))
        break;
  }

  var_ = stoi(input);
  table_ = new std::bitset<10>[1 << var_]; // Fill table with new bitsets

  SetTruthTable(); // Assign values to all rows in the truth table

  while (GetInput(input, "Enter minterm (Type enter when done): ")) {
    if (ValidateInput(input, 0, (1<<var_)-1))
      AddMinterm(input);

    PrintMinterms();
  }

  GroupMinterms(minterms_);

}

void qm_petrick::PrintTable() const {
  for (size_t i = 0; i < (1 << var_); ++i) {
    std::string temp = table_[i].to_string();
    printf("%4d : %s\n", i, temp.c_str());
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

inline bool qm_petrick::AddMinterm(std::string &minterm) {

  if(!minterms_.insert(stoi(minterm)).second) {
    printf("Item not inserted!\n");
    return false;

  }
  return true;
}

bool qm_petrick::ValidateInput(std::string &input, int &&min, int &&max) {
  try{
    if (stoi(input) >= min && stoi(input) <=max) {
      return true;
    } else {
      printf("Out of range! Please try again.\n");
      return false;
    }
  } catch(...) {
    printf("Invalid input, please try again.\n");
    return false;
  }
}

qm_petrick::minterm qm_petrick::NewMinterm(int &&term) {

  minterm temp;

  temp.mask_ = 1023;
  temp.bits_ = 0;
  temp.terms_.insert(term);
  temp.used_ = false;

  return temp;
}

void qm_petrick::PrintMinterms() {

  printf("Current minterms: ");
  for (auto &x: minterms_) {
    printf("%d ", x);
  }
  printf("\n");

}

std::vector<std::vector<int>> qm_petrick::GroupMinterms(std::set<int> &minterms) {
  std::vector<std::vector<int>> groups(10);
  std::set<int> group;

  for (auto x: minterms)
    groups[table_[x].count()].push_back(x);

  for (auto it = groups.begin(); it != groups.end(); ) {
    if (it->empty())
      groups.erase(it);
    else
      ++it;
  }

  for (auto &x : groups) {
    printf("Group %d: \n", table_[x.at(0)].count());
    for (auto &y : x)
      printf("%d ", y);
    printf("\n");
  }

  return groups;
}

void qm_petrick::CombineMinterms(std::vector<std::vector<int>> &minterms) {

  std::vector<std::vector<minterm>> new_group;

  for (auto group = minterms.begin(); group != minterms.end()-1 ; ++group) { // for every group
    std::vector<minterm> temp_group; // create a vector to hold potential group
    for (auto &term1 : *group) { // for every minterm in the group
      for (auto &term2 : *(group + 1)) {// compare to every minterm in the other group
        if ((table_[term1] ^ table_[term2]).count()==1) {
          minterm temp;
          temp.mask_ = (table_[term1] ^ table_[term2]);
          temp.terms_.insert(term1);
          temp.terms_.insert(term2);
          temp.used_ = false;
          temp_group.push_back(temp);
        }
      }
    }
    if (!temp_group.empty())
      new_group.push_back(temp_group);

  }

}

