// abstract class graph
// abstract data type specification for graph data structure
// includes methods that are representation independent

#pragma once

#include <sstream>
#include "edge.h"
#include "vertex_iterator.h"

template <class T>
class Graph
{
public:
	virtual ~Graph() {}
	// ADT methods
	// 返回图的顶点树
	virtual int number_of_vertices() const = 0;

	// 返回图的边树
	virtual int number_of_edges() const = 0;

	// 返回边 (i,j) 是否存在
	virtual bool exist_edge(int i, int j) const = 0;

	// 插入一条边
	virtual void insert_edge(Edge<T>* edge) = 0;

	// 删除一条边(i,j)
	virtual void erase_edge(int i, int j) = 0;

	// 返回顶点vertex的度，用于无向图
	virtual int degree(int vertex) const = 0;

	// 返回顶点vertex的入度
	virtual int in_degree(int vertex) const = 0;

	// 返回顶点vertex的出度
	virtual int out_degree(int vertex) const = 0;


	// other methods
	// 当且仅当是有向图时，返回true
	virtual bool directed() const = 0;
	// 当且仅当是加权图时，返回true
	virtual bool weighted() const = 0;
	// 访问指定顶点的相邻节点
	virtual VertexIterator<T>* iterator(int) = 0;
};