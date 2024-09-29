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
	// ����ͼ�Ķ�����
	virtual int number_of_vertices() const = 0;

	// ����ͼ�ı���
	virtual int number_of_edges() const = 0;

	// ���ر� (i,j) �Ƿ����
	virtual bool exist_edge(int i, int j) const = 0;

	// ����һ����
	virtual void insert_edge(Edge<T>* edge) = 0;

	// ɾ��һ����(i,j)
	virtual void erase_edge(int i, int j) = 0;

	// ���ض���vertex�Ķȣ���������ͼ
	virtual int degree(int vertex) const = 0;

	// ���ض���vertex�����
	virtual int in_degree(int vertex) const = 0;

	// ���ض���vertex�ĳ���
	virtual int out_degree(int vertex) const = 0;


	// other methods
	// ���ҽ���������ͼʱ������true
	virtual bool directed() const = 0;
	// ���ҽ����Ǽ�Ȩͼʱ������true
	virtual bool weighted() const = 0;
	// ����ָ����������ڽڵ�
	virtual VertexIterator<T>* iterator(int) = 0;
};