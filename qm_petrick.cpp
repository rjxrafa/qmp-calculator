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

  while (GetInput(input, "\nEnter minterm (Type enter when done): ")) {
    if (ValidateInput(input, 0, (1<<var_)-1))
      AddMinterm(input);

    printf("Your minterms: \n");
    for (auto &x: minterms_)
      printf("%d ", x);
  }

  auto minterm_groups = GroupMinterms();
  while (CombineMinterms(minterm_groups)) {
    PrintMinterms(minterm_groups);
  };

  std::cout << "DONEEE\n";
  if (!prime_implicants_.empty()) {
    std::cout << "Prime implicants: \n";
    for (auto &x : prime_implicants_)  {
      for (auto &y : x.terms_) {
        printf("%d ", y);
      }
      printf("\n");
    }
  }

  PrintImplicantChart();
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

qm_petrick::minterm qm_petrick::NewMinterm(int term) {

  minterm temp;

  temp.bits_ = table_[term].to_string();
  temp.terms_.insert(term);
  temp.used_ = false;


  return temp;
}

void qm_petrick::PrintMinterms(std::vector<std::vector<qm_petrick::minterm>> &v) {

  printf("Current minterms: \n");
  for (auto &x: v) {
    printf("Group %d:\n", CountBits(x.at(0).bits_));
    for (auto &y : x) {
      for (auto &z : y.terms_) {
        printf("%d ", z);
      }
      printf("\n");
    }
    printf("\n");
  }
  printf("\n");

}

std::vector<std::vector<qm_petrick::minterm>> qm_petrick::GroupMinterms() {
  std::vector<std::vector<minterm>> groups(10);

  // This procedure will group the minterms to their respective bit group.
  for (auto &x: minterms_) {
    groups[table_[x].count()].push_back(std::move(NewMinterm(x)));
  }

  for (auto it = groups.begin(); it != groups.end(); ) {
    if (it->empty())
      groups.erase(it);
    else
      ++it;
  }

  for (auto &x : groups) {
    printf("Group %d: \n", CountBits(x.at(0).bits_));
    for (auto &y : x)
      for (auto &z : y.terms_)
        printf("%d ", z);
    printf("\n");
  }

  return groups;
}

bool qm_petrick::CombineMinterms(std::vector<std::vector<minterm>> &minterms) {
  // todo : set used to false when going in here
  std::vector<std::vector<minterm>> new_group;

  /** Sets all of the used flags to false **/
  for (auto &group : minterms)
    for(auto &terms : group)
      terms.used_ = false;

  for (auto group = minterms.begin(); group != minterms.end()-1 ; ++group) { // for every group in terms
    std::vector<minterm> temp_group; // create a vector to hold potential group
    for (auto &term1 : *group) { // for every minterm in the group
      for (auto &term2 : *(group + 1)) {// compare to every minterm in the other group
        if (ValidatePair(term1.bits_, term2.bits_)) {
          minterm temp;

          temp.bits_ = CreateMask(term1.bits_, term2.bits_);

          for (auto &x: term1.terms_)
            temp.terms_.insert(x);

          for (auto &x: term2.terms_)
            temp.terms_.insert(x);

          term1.used_ = true;
          term2.used_ = true;

          /** Checking for dupes **/
          bool dupe = false;
          for (auto &x: temp_group)
            if (x.terms_ == temp.terms_)
              dupe = true;

          if (!dupe)
            temp_group.push_back(std::move(temp));
        }
      }
    }

    if (!temp_group.empty())
      new_group.push_back(std::move(temp_group));

  }

  /** Add prime implicants **/
  for (auto &x : minterms) {
    for (auto &y : x) {
      if (!y.used_)
        prime_implicants_.push_back(y);
    }
  }

  minterms = new_group;

  if (minterms.size() <= 1) {
    for (auto &x : minterms) {
      for (auto &y : x) {
        if (!y.used_)
          prime_implicants_.push_back(y);
      }
    }
    return false;
  }
  else
    return true;

}
bool qm_petrick::ValidatePair(std::string &term1, std::string &term2) {

  unsigned int count = 0;
  for (unsigned int i = 0; i < term1.length(); ++i) {
    if (term1[i] != term2[i])
      ++count;
  }

  return count <= 1;
}

std::string qm_petrick::CreateMask(std::string &term1, std::string &term2) {

  std::string output;
  for (unsigned int i = 0; i < term1.length(); ++i) {
    if (term1[i] == term2[i])
      output += term1[i];
    else
      output += '-';
  }

  return output;
}

int qm_petrick::CountBits(std::string &term) {

  int count = 0;
  for (unsigned int i = 0; i < term.length(); ++i)
    if (term[i] == '1')
      ++count;

  return count;
}

void qm_petrick::PrintImplicantChart() {

//  printf("%11s", "");
  for (auto &x : minterms_) {
    printf("%5d", x);
  }
  printf("\n");
  for (auto &x : prime_implicants_) {
    for (auto &y : minterms_) {
      printf ("%5s", x.terms_.count(y) > 0 ? "x" : "");
    }

    printf("   | ");
    for (auto &z : x.terms_)
      printf("%d ", z);

    printf(" \n");
//    printf("| %s\n", x.bits_.c_str());
  }
}

