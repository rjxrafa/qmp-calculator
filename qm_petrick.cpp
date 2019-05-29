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

//  std::vector <std::pair<std::bitset<10>, bool>> temp;
//  for (auto x : minterms_) {
//    temp.push_back(make_pair(table_[x], true));
//  }


  GroupMinterms(minterms_);
//  GroupMinterms(implicants_);


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

void qm_petrick::PrintMinterms() {

  printf("Current minterms: ");
  for (auto x: minterms_) {
    printf("%d ", x);
  }
  printf("\n");

}

std::vector<std::vector<int>> qm_petrick::GroupMinterms(std::set<int> &minterms) {
  std::vector<std::vector<int>> groups(10);
  std::set<int> group;

  for (auto x: minterms)
    groups[table_[x].count()].push_back(x);

  return groups;
}

//void qm_petrick::GroupMinterms(std::vector<std::bitset<10>, bool> &implicants) {

//  int8_t current_size = -1;
//
//  std::vector<std::vector<std::pair<std::bitset<10>, bool>>> groups; // represents all the groups
//  std::vector<std::pair<std::bitset<10>, bool>> group;               // represents one group
//
//  for (auto x: implicants) {
//    if (x.first.count() > current_size) {
//      group.push_back(x);
//      groups.push_back(group); // add new group to groups
//      group.clear();           // start new group
//
//      ++current_size;
//    }
//    else
//      group.push_back(x); // add to current group
//  }
//
//
//  for (const auto x : groups) {
//    for (const auto y: x) {
//      std::string temp = y.first.to_string();
//      printf("%s\n", temp.c_str());
//    }
//  }
//  implicants_.push_back(groups);


//}

void qm_petrick::CombineMinterms(std::vector<std::pair<std::bitset<10>, bool>> &implicants) {

  for (const auto x : implicants) {
    std::cout << x.first.to_string() << " : ";
    std::cout << std::boolalpha << x.second;
    std::cout << "\n";
  }


}

