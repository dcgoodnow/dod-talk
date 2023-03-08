#include <array>
#include <cstring>
#include <iostream>
#include <cstdlib>

class ListNode {
public:
   ListNode* Next;
   int Value;
   ListNode(int value, ListNode* next = nullptr) 
   {
      Value = value;
      Next = next;
   }
   
};
class NamedInt {
public:
   int Value;
   std::string Name;
   NamedInt() {
      Value = 0;
      Name = "";
   }
   NamedInt(int value, std::string name)
   {
      this->Value = value;
      this->Name = name;
   }
};
struct BoxedInt {
   int Value;
};

int main(int argc, char** argv) {
   std::cout << "Size of int: " << sizeof(int) << std::endl;
   std::cout << "Size of ListNode: " << sizeof(ListNode) << std::endl;
   std::cout << "Size of NamedInt: " << sizeof(NamedInt) << std::endl;
   std::cout << "Size of BoxedInt: " << sizeof(BoxedInt) << std::endl;
   std::cout << "Size of string: " << sizeof(std::string) << std::endl;
}
