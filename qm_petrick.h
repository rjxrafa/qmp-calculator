//
// Created by Rafa on 5/26/2019.
//

#ifndef UNTITLED_QM_PETRICK_H
#define UNTITLED_QM_PETRICK_H

#include <iostream>
#include <bitset>
#include <set>
#include <vector>

class qm_petrick {

  struct minterm {
    std::bitset<10> bits_;
    std::bitset<10> mask_;
    std::set<int> terms_;
    bool used_;

  };

public:
  qm_petrick(size_t var = 4);
  ~qm_petrick();
  qm_petrick(const qm_petrick &other);
  qm_petrick& operator=(const qm_petrick &other);

  void PrintTable() const;
  inline void PrintMinterms();
  static bool GetInput(std::string &input, std::string &&question);
  static bool ValidateInput(std::string &input, int &&min, int&&max);
  inline minterm NewMinterm(int &&term);

 private:
  uint16_t var_; // amount of variables to use
  std::set<int>  minterms_;
  std::bitset<10> *table_;  // table to hold all values

  inline void SetTruthTable();
  inline bool AddMinterm(std::string &minterm);
  inline std::vector<std::vector<int>> GroupMinterms(std::set<int> &minterms);
  inline void CombineMinterms(std::vector<std::vector<int>> &minterms);

};

#endif //UNTITLED_QM_PETRICK_H
