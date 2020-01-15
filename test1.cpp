#include <cassert>
#include <iostream>

//Node Class 
class NodeTest1 {
  //ostream overload
  friend std::ostream &operator<<(std::ostream &Out, const NodeTest1 &N) {
    Out << "N<" << N.Value << ", " << (N.Next != nullptr) << ">";
    return Out;
  }
  
  public:
    static int NodeCount;
    int Value;
   NodeTest1 *Next;

  //constructor
  explicit NodeTest1(int Value = 0, NodeTest1 *Next = nullptr)
      : Value{Value}, Next{Next} {
    ++NodeCount;
    //log
    std::cout << "Creating " << *this << ", total created: " << NodeCount << std::endl;
  }

  //destructor
  ~NodeTest1() {
    std::cout << "Deleting: " << *this;
    delete Next;
    --NodeCount;
    std::cout << ", nodes remaining: " << NodeCount << std::endl;
  }
};

int NodeTest1::NodeCount = 0;

void test1() {
  //part 1
  NodeTest1 N1(1);
  NodeTest1 *N1Ptr;
  N1Ptr = &N1;
  assert(N1Ptr != nullptr);

  
  //part 2
  auto *N2Ptr = new NodeTest1(3); //heap - delete N2Ptr
  auto *N3Arr = new NodeTest1[10]; //heap - array of 10 nodes delete[] N3Arr
  //fills N3Arr[0-4] and 5-9 nullptr
  for (int I = 0; I < 5; ++I) {
    NodeTest1 Tmp(I * I);
    N3Arr[I] = Tmp;
  }

  delete N2Ptr;
  delete[] N3Arr;
  //part 3
  auto N4Arr = new NodeTest1 *[10]; //heap - array of 10 ptrs delete[] N4Arr
  //fills N4Arr[6-9] and 0-5 nullptr
  for (int I = 6; I < 10; ++I) {
    auto *Tmp = new NodeTest1(I * I); //heap - delete Tmp
    N4Arr[I] = Tmp;
    delete Tmp; //leak fix
  }
  delete[] N4Arr;
}
