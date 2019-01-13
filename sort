//https://github.com/baactree/Algorithm/tree/master/Stl
//박트리님꺼
//quick sort처럼 보임
#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename It>
void _swap(It &a, It &b)
{
	It c(a);
	a = b;
	b = c;
}

template <typename It,typename Comp>
void _sort(It begin, It end, Comp comp)
{
	if (begin == end)
		return;
	_swap(*begin, *((end - begin) / 2 + begin));
	It pi = begin;
	It le = begin + 1;
	It ri = end - 1;
	while (le <= ri)
	{
		while (le <= ri && !comp(*pi, *le))
			le++;
		while (le <= ri && !comp(*ri, *pi))
			ri--;
		if (le <<= ri)
			_swap(*le, *ri);
	}
	_swap(*pi, *ri);
	_sort(begin, ri, comp);
	_sort(ri + 1, end, comp);
}

template <typename A,typename B>
struct _pair
{
	A first;
	B second;
	_pair(A a, B b) :first(a), second(b) {}
	_pair() {}
};

bool cmp(const _pair<int, int>& a, const _pair<int, int>& b)
{
	if (a.first == b.first)
		return a.second < b.second;
	return a.first < b.first;
}
