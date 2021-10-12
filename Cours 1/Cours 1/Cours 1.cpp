#include <iostream>
#include <cstdio>
#include <functional>

#include "IntArray.h"

void Memcpy(char* dst, const char* src, int len) {
	//pour les len et chars de src, les copier dans dst
	for (size_t i = 0; i < len; i++)
	{
		dst[i] = src[i];
	}
}

void MemcpyWhile(char* dst, const char* src, int len) {
	while (--len)
	{
		*dst++ = *src++;
	}
}
const char* StrChr(const char* grange, char chat) {
	while (*grange)
	{
		if (*grange == chat) 
			return grange;
		grange++;		
	}
	return nullptr;
}

const char * StrStr(const char * a, const char* b) {
	
	int len = strlen(b);
	while (*a)
	{
		bool found = true;
		for (size_t i = 0; i < len; i++)
		{
			if (a[i] != b[i]) {
				a++;
				found = false;
				break;
			}

			return a;
		}
		if (found)
			return a;
	}
	return nullptr;
}

int add(int a, int b) {
	if (b == 0) return a;
	else if (b > 0)
		return 1 + add(a, b - 1);
	else
		return - 1 + add(a, b - 1);	
}

int sub(int a, int b) {
	return add(a, -b);
}

int mul(int a, int b) {
	if (b == 0) return 0;
	if (a == 0) return 0;
	if (b < 0)
		return  -mul(a, -b);
	else
		return  add(a, mul(a, b - 1));
}
int divInt(int a, int b) {
	if (a == 0) return 0;
	if (b == 0)
		throw "interdit";
	if (b == 1) return a;
	if (a < b) return 0;
	if (a < 0)
		return sub(0, divInt(sub(0, a), b));
	else 
		return 1 + divInt(sub(a, b), b);


}

int mod(int a, int b);// rest de div





int main()
{
	IntArray sapin(3);
	for (int i = 0; i < sapin.size; ++i)
		sapin.set(i, i * i);
	std::function<void(int)> foo = [](int value) {
		printf("%d\n", value);
	};
	sapin.iter(foo);

	double total = sapin.sum();
	double total2 = sapin.sumCapture();

	int s[4] = { 0,1,2,3 };
	int t[4] = { 0,0,0,0 };
	IntArray* maCopie = IntArray::fromArray(s, 4);
	MemcpyWhile((char*)s, (char*)t, 4 * sizeof(int));
	for (size_t i = 0; i < 4; i++)
	{
		printf("%d\n", s[i]);
	}
	const char* toto = StrChr("sapin", 'a' );
	const char* tota = StrStr("sapin", "p");
	const char* toti = StrStr("sapin", "n");


	std::cout << "Hello World!\n" << total2 << "\n" ;

	int brain = add(2, 4);
	int brainfck = add(2, -4);
	int brainfck2 = sub(3, 6);
	int gigabrainfck = sub(3, -6);
	int oui = mul(3, 6);
	int aled = mul(5, -4);
	int oskour = divInt(10, 5);
}



