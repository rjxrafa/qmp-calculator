#include <iostream>
#include "qm_petrick.h"

bool GetInput(std::string &input, std::string &&question) {

  printf("%s", question.c_str());
  getline(std::cin, input);
  fflush(stdin);

  return (tolower(input[0]) == 'y');
}

int main() {
//
  std::string input;

  do {
    qm_petrick a;
  } while (GetInput(input, "Would you like to go again?\n"));


  return 0;
}

