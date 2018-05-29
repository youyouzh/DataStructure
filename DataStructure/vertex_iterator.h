// abstract class for graph vertex iterator

#pragma once

template <class T>
class VertexIterator
{
public:
	virtual ~VertexIterator() {}

	virtual int next() = 0;
	virtual int next(T&) = 0;
};