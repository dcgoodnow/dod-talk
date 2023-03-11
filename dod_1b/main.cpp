#include <benchmark/benchmark.h>
#include <array>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <string>

const int ITERATIONS = 2 << 20;

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

static std::array<NamedInt, ITERATIONS> namedIntArray;
class ObjectFixture : public benchmark::Fixture
{
public:
   void SetUp(const ::benchmark::State& state)
   {
      for(int i = 0; i < ITERATIONS; i++)
      {
         namedIntArray[i] = NamedInt(2, "Named Int");
      }
   }
   void TearDown(const ::benchmark::State& state)
   {
   }
};

BENCHMARK_DEFINE_F(ArrayFixture, ArrayTest)(benchmark::State& st)
{
   for(auto _ : st) {
      benchmark::ClobberMemory();
      for(int i = 0; i < st.range(0); i++) {
         benchmark::DoNotOptimize(intArray[i] *= intArray[i]);
      }
   }
}
BENCHMARK_REGISTER_F(ArrayFixture, ArrayTest)->RangeMultiplier(2)->Range(2<<10, 2<<20);

BENCHMARK_DEFINE_F(ObjectFixture, ObjectTest)(benchmark::State& st)
{
   for(auto _ : st) {
      benchmark::ClobberMemory();
      for(int i = 0; i < st.range(0); i++)
      {
         benchmark::DoNotOptimize(namedIntArray[i].Value *= namedIntArray[i].Value);
      }
   }
}

BENCHMARK_REGISTER_F(ObjectFixture, ObjectTest)->RangeMultiplier(2)->Range(2<<10, 2<<20);


BENCHMARK_MAIN();

