#include <benchmark/benchmark.h>
#include <array>
#include <cstring>
#include <iostream>
#include <cstdlib>

const int ITERATIONS =8000000;

static std::array<int, ITERATIONS> intArray;
class ArrayFixture : public benchmark::Fixture
{
public:
   void SetUp(const ::benchmark::State& state)
   {
      memset(&intArray, 2, intArray.size());
   }
   void TearDown(const ::benchmark::State& state)
   {
   }
};

class ListNode {
public:
   ListNode* Next;
   int Value;
   std::array<int, 64> spacing;
   ListNode(int value, ListNode* next = nullptr) 
   {
      Value = value;
      Next = next;
      memset(&spacing, 0, spacing.size());
   }
};
static ListNode* head = nullptr;
class ListFixture : public benchmark::Fixture
{
public:
   void SetUp(const ::benchmark::State& state)
   {
      head = new ListNode(2);
      auto current = head;
      for(int i = 0; i < ITERATIONS; i++)
      {
         current->Next = new ListNode(2);
         current = current->Next;
      }
   }
   void TearDown(const ::benchmark::State& state)
   {
      auto current = head;
      while(current != nullptr)
      {
         auto temp = current;
         current = current->Next;
         delete(temp);
      }
   }
};

BENCHMARK_F(ArrayFixture, ArrayTest)(benchmark::State& st)
{
   for(auto _ : st) {
      benchmark::ClobberMemory();
      for(int i = 0; i < intArray.size(); i++) {
         benchmark::DoNotOptimize(intArray[i] *= intArray[i]);
      }
   }
}

BENCHMARK_F(ListFixture, ListTest)(benchmark::State& st)
{
   for(auto _ : st) {
      benchmark::ClobberMemory();
      for(ListNode* current = head; current != nullptr; current = current->Next)
      {
         benchmark::DoNotOptimize(current->Value *= current->Value);
      }
   }
}

BENCHMARK_MAIN();

