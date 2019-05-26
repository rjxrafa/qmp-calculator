//
// Created by Rafa on 5/26/2019.
//

#ifndef UNTITLED_QM_PETRICK_H
#define UNTITLED_QM_PETRICK_H

#include <iostream>
#include <bitset>
#include <vector>

class qm_petrick {

public:
  qm_petrick(size_t var = 4);
  ~qm_petrick();
  qm_petrick(const qm_petrick &other);
  qm_petrick& operator=(const qm_petrick &other);

  void PrintTable() const;
  bool GetInput(std::string &input, std::string &&question);

 private:
  uint8_t var_;                         // amount of variables to use

  std::bitset<10> *table_;  // table to hold all values

  void SetTruthTable();
};

#endif //UNTITLED_QM_PETRICK_H
