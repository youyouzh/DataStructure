// edge in a weighted graph

#pragma once

#include "edge.h"
#include <sstream>

template <class T>
class WeightedEdge : public Edge<T>
{
public:
	WeightedEdge() {};
	WeightedEdge(int v1, int v2, T weight) : v1(v1), v2(v2), w(weight) {};
	~WeightedEdge() {};

	int vertex1() const override { return v1; };
	int vertex2() const override { return v2; };
	T weight() const override { return w; };
	operator T() const { return w; };
	void output(std::ostream& out) const { out << "(" << v1 << "," << w << "," << v2 << ")"; }

private:
	int v1;
	int v2;
	T w;
};

template <class T>
std::ostream& operator<<(std::ostream& out, const WeightedEdge<T>& x)
{
	x.output(out);
	return out;
}