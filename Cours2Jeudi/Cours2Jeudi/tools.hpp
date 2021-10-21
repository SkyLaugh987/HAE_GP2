#pragma once
#include <chrono>
#include <ctime>
#include <stdint.h>
#include <cstdlib>

using namespace std;
using namespace std::chrono;


double getTimeStamp()
{
std::chrono::nanoseconds ns =
duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
return ns.count() / 1000000000.0;
}
