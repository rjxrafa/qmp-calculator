//
// Created by Rafa on 5/26/2019.
//

#ifndef UNTITLED_QM_PETRICK_H
#define UNTITLED_QM_PETRICK_H

#include <iostream>
#include <bitset>
#include <set>
#include <vector>
#include <queue>

class qm_petrick {

  struct minterm {
    std::string bits_;
    std::set<int> terms_;
    bool used_;
  };

public:
  qm_petrick(size_t var = 4);
  ~qm_petrick();
  qm_petrick(const qm_petrick &other);
  qm_petrick& operator=(const qm_petrick &other);

  void PrintTable() const;
  inline void PrintMinterms(std::vector<std::vector<qm_petrick::minterm>> &my_vec);
  static bool GetInput(std::string &input, std::string &&question);
  static bool ValidateInput(std::string &input, int &&min, int&&max);
  static bool ValidatePair(std::string &term1, std::string &term2);
  static std::string CreateMask(std::string &term1, std::string &term2);
  int CountBits(std::string &term);
  minterm NewMinterm(int term);

 private:
  uint16_t var_; // amount of variables to use
  std::set<int>  minterms_;
  std::vector<minterm> prime_implicants_;
  std::bitset<10> *table_;  // table to hold all values

  inline void SetTruthTable();
  inline bool AddMinterm(std::string &minterm);
  std::vector<std::vector<qm_petrick::minterm>> GroupMinterms();
  bool CombineMinterms(std::vector<std::vector<minterm>> &minterms);
  void PrintImplicantChart();

};

#endif //UNTITLED_QM_PETRICK_H
