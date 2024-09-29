#pragma once

#include "edge.h"
#include "u_exception.h"

class UnweightedEdge : public Edge<bool>
{
public:
	UnweightedEdge(int v1, int v2) : v1(v1), v2(v2) {};
	~UnweightedEdge() {};
	int vertex1() const override { return v1; };
	int vertex2() const override { return v2; };
	bool weight() const override { throw UndefinedMethodException("weight"); };

private:
	int v1;
	int v2;
};