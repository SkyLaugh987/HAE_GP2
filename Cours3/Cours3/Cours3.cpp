#include "List.hpp"
#include <stdio.h>
#include <vector>

typedef List<double> ListD;
typedef List<float> ListF;
typedef List<int> ListI;
typedef List<std::string> ListS;


int main() {
	ListD* v0 = new ListD(66);
	auto* v1 = new ListD(54);
	auto* v2 = new ListD(27);
	auto* v3 = new ListD(10);

	ListF* f0 = new ListF(76.0f);
	ListI* i0 = new ListI(50);
	ListS* s0 = new ListS("69");
	s0->push_first("96");
	s0->remove("69");

	std::vector<double> vd = { 0.0,1.0,2.0 };
	vd.push_back(10);
	for (int i = 0; i < vd.size(); i++)
	{
		printf("%f ", vd[i]);
	}
	printf("\n---------------------------\n");
	for (auto f : vd)
	{
		printf("%f", f);

	}
	printf("\n---------------------------\n");

	for (auto iter = vd.begin(); iter != vd.end();)
	{
		printf("%f", iter);
		if (*iter == 1.0)
			iter = vd.erase(iter);
		else iter++;
	}
	printf("\n---------------------------\n");

	return 0;
}