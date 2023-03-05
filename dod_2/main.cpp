
#include <array>
#include <cstring>
#include <iostream>
#include <cstdlib>

const int ITERATIONS =8000000;

static std::array<int, ITERATIONS> intArray;
class ListNode {
public:
   ListNode* Next;
   int Value;
   std::array<uint8_t, 32> spacing;
   ListNode(int value, ListNode* next = nullptr) 
   {
      Value = value;
      Next = next;
      memset(&spacing, 0, spacing.size());
   }
};

static ListNode* head = nullptr;
int main(int argc, char** argv) {
   long potential_misses = 0;
   long long distance = 0;

   head = new ListNode(2);
   auto current = head;
   for(int i = 0; i < ITERATIONS; i++)
   {
      current->Next = new ListNode(rand() % 10);
      current = current->Next;
   }
   for(ListNode* current = head; current != nullptr; current = current->Next) 
   {
      current->Value *= current->Value;
      if(abs((long long)current - (long long)current->Next) >= 64) {
         potential_misses++;
      }
      
      distance += abs((long long)current - (long long)current->Next);
   }

   float potentialMissRate  = static_cast<float>(potential_misses) / ITERATIONS;
   float averageDistance = static_cast<float>(distance) / ITERATIONS;

   std::cout << "Potential Misses: " << potential_misses << std::endl;
   std::cout << "Potential Miss Rate: " << potentialMissRate << std::endl;
   std::cout << "Average distance: " << averageDistance << std::endl;
}

