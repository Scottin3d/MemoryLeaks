#include <cassert>
#include <iostream>

//node class
class NodeTest2 {
  //ostream overload
  friend std::ostream &operator<<(std::ostream &Out, const NodeTest2 &N) {
    Out << "N<" << N.Value << ", " << (N.Next != nullptr) << ">";
    return Out;
  }

public:
  static int NodeCount;
  int Value;
  NodeTest2 *Next;

  explicit NodeTest2(int Value = 0, NodeTest2 *Next = nullptr)
      : Value{Value}, Next{Next} {
    ++NodeCount;
    std::cout << "Creating " << *this << ", total created: " << NodeCount << std::endl;
  }
  ~NodeTest2() {
    std::cout << "Deleting: " << *this;
    --NodeCount;
    std::cout << ", nodes remaining: " << NodeCount << std::endl;
  }
};

int NodeTest2::NodeCount = 0;

NodeTest2 *find(NodeTest2 *Start, int Value) {
  assert(Start != nullptr);
  NodeTest2 *Curr = Start;
  while (Curr != nullptr && Curr->Value != Value)
    Curr = Curr->Next;

  return Curr;
}

// insert B after A, return B
NodeTest2 *addAfter(NodeTest2 *A, NodeTest2 *B) {
  assert(A != nullptr && B != nullptr);
  NodeTest2 *C = A->Next;
  A->Next = B;
  B->Next = C;

  return B;
}

// Given the head of the list, find Node with ValB, insert A to come before B
NodeTest2 *addBefore(NodeTest2 *Start, int ValA, int ValB) {
  assert(Start != nullptr);
  NodeTest2 *NodeB = find(Start, ValB);
  auto *NodeA = new NodeTest2(ValA);
  NodeA->Next = NodeB;
  NodeTest2 *Curr = Start;
  while (Curr->Next != NodeB)
    Curr = Curr->Next;
  Curr->Next = NodeA;

  return Start;
}


NodeTest2 *remove(NodeTest2 *Start, NodeTest2 *N) {
  assert(Start != nullptr);
  NodeTest2 *Curr = Start;
  while (Curr != nullptr && Curr->Next != N)
    Curr = Curr->Next;
  if (Curr != nullptr)
    Curr->Next = N->Next;

  return Start;
}

void displayAll(NodeTest2 *N) {
  std::cout << "[";
  if (N != nullptr) {
    std::cout << *N;
    N = N->Next;
  }
  while (N != nullptr) {
    std::cout << ", " << *N;
    N = N->Next;
  }
  std::cout << "]" << std::endl;
}

void test2() {
  std::cout << "part1" << std::endl;
  auto *Head = new NodeTest2(100);
  NodeTest2 *Tail = Head;
  for (int I = 1; I <= 5; ++I) {
    Tail = addAfter(Tail, new NodeTest2(I * I * I));
  }
  displayAll(Head);
  std::cout << "part2" << std::endl;

  addBefore(Head, 7, 8);
  addBefore(Head, 13, 125);
  addBefore(Head, 15, 9);
  addBefore(Head, 17, 11);

  addBefore(Head, 19, 100);
  displayAll(Head);
  std::cout << "part3" << std::endl;

  remove(Head, find(Head, 8));
  remove(Head, find(Head, 77));
  remove(Head, find(Head, 100));
  remove(Head, find(Head, 19));
  displayAll(Head);

  delete Head;
}
