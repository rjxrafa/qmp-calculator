#include <iostream>
#include "qm_petrick.h"

int main() {

//  qm_petrick a;

  std::bitset<5> d("00000"); // 00001
  std::bitset<5> b("00011"); // 00001
  std::bitset<5> c = 0;

  c = d^b;

  /**
   * XOR essentially gives us 1 for every bit difference between two bits. So we use this for
   * our algorithm:
   *
   *
   * 1)
   * 1) A XOR B = C // if A.mask == B.mask
   * 2) If (XOR.count() == 1), then add  to new group.
   * 3) Create a Mask (~C)
   * 4) Use the new bitset as a mask.
   *
   * 4) Check the mask first, if they are the same, then add to new group
   * 5) XOR the two bitsets, then OR
   */

  std::cout << c;

  getchar();
  return 0;
}