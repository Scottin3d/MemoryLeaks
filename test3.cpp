#include <cassert>
#include <iostream>
#include <vector>
#include <string>

class StringT3 {
public:
  std::string *MyStrings = new std::string[3];

  StringT3() = default;

  //add copy constructor
  StringT3(const StringT3& Copy) {
    MyStrings[0] = Copy.MyStrings[0];
    MyStrings[1] = Copy.MyStrings[1];
    MyStrings[2] = Copy.MyStrings[2];
    std::cout << "Created copy " << MyStrings[0] << MyStrings[1] << MyStrings[2] << std::endl;
  }

  //default constructor
  StringT3(std::string A, std::string B, std::string C) {
    MyStrings[0] = A; // NOLINT - not using move
    MyStrings[1] = B; // NOLINT - not using move
    MyStrings[2] = C; // NOLINT - not using move
    std::cout << "Created " << MyStrings[0] << MyStrings[1] << MyStrings[2] << std::endl;
  }

  //destructor
  ~StringT3() {
    std::cout << "Deleting " << MyStrings[0] << MyStrings[1] << MyStrings[2] << std::endl;
    delete[] MyStrings; //add
  }

  //add equals overload
  StringT3& operator = (const StringT3& Copy) {
    this->MyStrings[0] = Copy.MyStrings[0];
    this->MyStrings[1] = Copy.MyStrings[1];
    this->MyStrings[2] = Copy.MyStrings[2];

    return *this;
  }
};

void test3() {
  StringT3 S1("a", "b", "c");
  StringT3 T1;
  T1 = S1;
  StringT3 U1(S1);
  U1.MyStrings[0] = "q";

  auto *S2ptr = new StringT3("w", "x", "y"); //heap
  StringT3 *T2ptr;
  T2ptr = S2ptr;

  std::vector<StringT3> V1;
  V1.push_back(S1);
  V1.push_back(T1);
  V1.push_back(U1);

  std::vector<StringT3*> V2;
  V2.push_back(S2ptr);
  V2.push_back(T2ptr);

  delete S2ptr;

  std::cout << "test3 is done" << std::endl;
}