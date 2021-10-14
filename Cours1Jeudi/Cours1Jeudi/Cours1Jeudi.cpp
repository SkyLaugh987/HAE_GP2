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

int add(int a, int b) { //avec que des +1,-1, return, apppels recursifs{
	if (b == 0)
		return a;
	else if (b > 0)
		return 1 + add(a, b - 1);
	else
		return -1 + add(a, b + 1);
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

int mulExplicit(int a, int b, int tmpRes) {
	if (b == 0) return tmpRes;
	if (a == 0) return tmpRes;
	if (b < 0)
		return mulExplicit(-a, -b, tmpRes);
	else
		return mulExplicit(a, b - 1, a + tmpRes);
		//return add(a, mul(a, b - 1));
}

int divInt(int a, int b) {

	if (a == 0) return 0;
	if (b == 1) return a;
	if (b == 0) throw "division by zero";
	if (a < 0)  return sub(0, divInt(sub(0, a), b));
	if (a < b)  return 0;
	return 1 + divInt(sub(a, b), b);
}

int divIntExplicit(int a, int b, int tmpRes) {

	if (a == 0) return 0 + tmpRes;
	if (b == 1) return a + tmpRes;
	if (b == 0) throw "division by zero";

	if (a < 0)
		//........
		//return sub(0, divInt(sub(0, a), b));
	if (a < b)  return 0 + tmpRes;
	//.........
	//return 1 + divInt(sub(a, b), b);
}

int mod(int a, int b){// rest de div
	if (a == 0) return 0;

	if (a < 0) {

		return - mod(sub(a, b), b);
	}
	else {
		if (a < b)
			return a;
		else 
			return mod(sub(a, b), b);		
	}
}

int mod2(int a, int b) {// rest de div
	return a - divInt(a, b) * b;
}

int sqr(int a) {
	return mul(a, a);
}


int lenManhattan(int vecX, int vecY) {
	return add(vecX, vecY);
}

int RStrlen(const char* a) {
	if (nullptr == a) return 0;
	else if (*a == 0) return 0;
	else
		return 1 + RStrlen(a + 1);
	

}

void RStrcpy(char*dst, const char*src) {
	if (nullptr == src) return;
	if (nullptr == dst) return;
	if (*src == 0) return;

	dst[0] = src[0];
	dst++;
	src++;
	RStrcpy(dst, src);
}

void RStrncpy(char*dst, const char*src, int nChars) {
	if (src == nullptr) return;//src = ptr
	if (dst == nullptr) return;
	if (*src == 0)return;//*src = src[]
	if (nChars == 0);
	dst[0] = src[0];
	dst++;
	src++;
	RStrncpy(dst, src, nChars - 1);
}
void ZeroMemory(void* ptr, int nByte) {
	char* mem = (char*)ptr;
	if (mem == nullptr) return;
	if (!nByte) return;
	//if (*ptr != NULL) return;
	mem[0] = 0;
	mem++;

	ZeroMemory(ptr, nByte - 1);
}
void RMemcpy(void* dst, const void* src, int nByte) {
	if (!dst) return;
	if (!src) return;
	if (!nByte) return;
	char* bdst = (char*)dst;
	char* bsrc = (char*)src;

	bdst[0] = bsrc[0];
	bdst++;
	bsrc++;
	RMemcpy(bdst, bsrc, nByte - 1);

}
/*
const char*  RStrChr(const char* str, char token) {
	if (str == nullptr)return;
	if (*str == 0)return;
	if (*str == token)
		return str;
	else 
		return RStrChr(str + 1, token);
	
}
bool IsPrefix(const char* str, const char* sub) {
	if (sub == nullptr) return false;
	if (str == nullptr) return false;

	if (sub[0] == 0) return true;
	if (sub[0] != str[0] ) return false;
	return IsPrefix(str + 1, sub + 1);
}

const char* RStrStr(const char* str, const char* sub) {
	if (str == nullptr)return nullptr;
	if (str[0]) return nullptr;
	if (sub == nullptr)return nullptr;
	RStrlen(sub);
	if (IsPrefix(str, sub) == true)
		return str;
	return RStrStr(str + 1, sub);		
}

char* FindEnd(char* str) {
	if (str == nullptr) return nullptr;

	if (str[0]) {
		return str;
	}
	else {
		return FindEnd(str + 1);
	}
}

const char* RStrCat(char* dst, const char* src) {
	if (dst == nullptr) return nullptr;
	if (src == nullptr) return nullptr;
	char* dstEnd = FindEnd(dst);
	RStrcpy(dstEnd, src);
	return dst;
}
int RstrCmp(const char* a, const char* b) { // 0 les chaines egales, -1 a est inf, 1 b est inf
		if (a == nullptr) return;
		if (b == nullptr) return;
		if (a[0] == 0 && b[0] == 0)
			return 0;
		if (a[0] == b[0]) {
			return RstrCmp(a + 1, b + 1);
		}
		if (*a < *b)
			return -1;
		else 
			return 1;		
}*/

int main()
{
	/*{


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
		const char* toto = StrChr("sapin", 'a');
		const char* tota = StrStr("sapin", "p");
		const char* toti = StrStr("sapin", "n");


		std::cout << "Hello World!\n" << total2 << "\n";

		int brain = add(2, 4);
		int brainfck = add(2, -4);
		int brainfck2 = sub(3, 6);
		int gigabrainfck = sub(3, -6);
		int oui = mul(3, 6);
		int aled = mul(5, -4);
		int oskour = divInt(10, 5);
		int shee = mod2(26, 3);
		const char* canard = "coin";
		RStrlen(canard);
	}*/
	int toto = mulExplicit(2, 5, 0);
	int tota = mulExplicit(2, -5, 0);
	int totu = mulExplicit(2, 5, 0);

	return 0;
}
