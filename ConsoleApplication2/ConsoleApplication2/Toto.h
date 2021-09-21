#pragma once

class A 
{

};
struct Toto : public A
{
public: 
	float x = 0.0f;
};

template<typename MaClasse>
class Foo {
	MaClasse* ptr = nullptr;
};
typedef Foo<float> B;