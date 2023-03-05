#include <benchmark/benchmark.h>
#include <array>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>

const int CARS = 100000;

struct vector3 {
   float x;
   float y;
   float z;

   vector3(float x, float y, float z)
   {
      this->x = x;
      this->y = y;
      this->z = z;
   }

   vector3 operator*(float scalar) {
      return vector3(this->x * scalar, this->y * scalar, this->z * scalar);
   }

   vector3& operator+=(const vector3& v) {
      this->x += v.x;
      this->y += v.y;
      this->z += v.z;
      return *this;
   }

   friend vector3 operator+(vector3 v1, const vector3& v2) {
      v1 += v2;
      return v1;
   }
};

struct color {
   uint8_t r;
   uint8_t b;
   uint8_t g;
};


class Car {
public:
   vector3 Position = vector3(0,0,0);
   vector3 Direction;
   float Speed;
   std::string Make;
   std::string Model;
   color Color;

public:
   Car(vector3 direction, float speed, std::string make, std::string model, color col) :
      Direction(direction),
      Speed(speed),
      Make(make),
      Model(model),
      Color(col) {}

   inline void UpdatePosition() {
      benchmark::DoNotOptimize(this->Position += this->Direction * this->Speed);
   }
};

class Cars {
public:
   std::vector<vector3> Positions;
   std::vector<vector3> Directions;
   std::vector<float> Speeds;
   std::vector<std::string> Makes;
   std::vector<std::string> Models;
   std::vector<color> Colors;
};

static std::vector<Car> ooCars;
class OOFixture : public benchmark::Fixture
{
public:
   void SetUp(const ::benchmark::State& state)
   {
      for(int i = 0; i < CARS; i++) {
         Car car(vector3(rand() % 1, rand() % 1, rand() % 1), rand() % 10, "ACME", "SuperCar", {255, 255, 255});
         ooCars.push_back(car);
      }
   }
   void TearDown(const ::benchmark::State& state)
   {
   }
};

static Cars doCars;
class DOFixture : public benchmark::Fixture
{
public:
   void SetUp(const ::benchmark::State& state)
   {
      for(int i = 0; i < CARS; i++) {
         doCars.Positions.push_back(vector3(0,0,0));
         doCars.Directions.push_back(vector3(rand() % 1, rand() % 1, rand() % 1));
         doCars.Speeds.push_back(rand() % 10);
         doCars.Makes.push_back("ACME");
         doCars.Models.push_back("SuperCar");
         doCars.Colors.push_back({255,255,255});
      }
   }
   void TearDown(const ::benchmark::State& state)
   {
   }
};

BENCHMARK_F(OOFixture, OOCarsTest)(benchmark::State& st)
{
   for(auto _ : st) {
      benchmark::ClobberMemory();
      for(auto& car : ooCars)
      {
         car.UpdatePosition();
      }
   }
}


BENCHMARK_F(DOFixture, DOCarsTest)(benchmark::State& st)
{
   for(auto _ : st) {
      benchmark::ClobberMemory();
      for(int i = 0; i < CARS; i++)
      {
         benchmark::DoNotOptimize(doCars.Positions[i] += doCars.Directions[i] * doCars.Speeds[i]);
      }
   }
}

BENCHMARK_MAIN();

