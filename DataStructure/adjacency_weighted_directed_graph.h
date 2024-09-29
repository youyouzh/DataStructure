// 使用邻接矩阵描述的加权有向图

#pragma once

#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"
#include "u_exception.h"
#include "helper.h"

template <class T>
class AdjacencyWeightedDirectedGraph : public Graph<T>
{
public:
	AdjacencyWeightedDirectedGraph(int number_of_vertices = 0, T no_edge = 0);

	~AdjacencyWeightedDirectedGraph() override;
	int number_of_vertices() const override;
	int number_of_edges() const override;
	bool exist_edge(int i, int j) const override;
	void insert_edge(Edge<T>* edge) override;
	void erase_edge(int i, int j) override;
	int degree(int vertex) const override;
	int in_degree(int vertex) const override;
	int out_degree(int vertex) const override;
	bool directed() const override;
	bool weighted() const override;
	VertexIterator<T>* iterator(int vertex) override;

	void check_vertex(int vertex) const;
	void output(std::ostream&) const;

	class Iterator : public VertexIterator<T>
	{
	public:
		Iterator(T* row, T no_edge, int number_of_vertices)
		{
			this->row = row;
			this->no_edge = no_edge;
			this->vertex_number = number_of_vertices;
			this->current_vertex = 1;
		}
		~Iterator(){}

		// Return next vertex if any. Return 0 if no next vertex.
		int next() override
		{
			// find next adjacent vertex
			for (auto j = current_vertex; j <= vertex_number; j++)
			{
				if (row[j] != no_edge)
				{
					current_vertex = j + 1;
					return j;
				}
			}
			// no next adjacent vertex
			current_vertex = vertex_number + 1;
			return 0;
		}

		int next(T &weight) override
		{
			// find next adjacent vertex
			for (auto j = current_vertex; j <= vertex_number; j++)
			{
				current_vertex = j + 1;
				weight = row[j];
				return j;
			}
			// no next adjacent vertex
			current_vertex = vertex_number + 1;
			return 0;
		}

	protected:
		T* row;
		T no_edge;
		int vertex_number;
		int current_vertex;
	};

protected:
	// 定点个数
	int vertex_number;
	// 边个数
	int edge_number;
	// 邻接数组
	T **data;
	// 表示不存在的边
	T no_edge;
};

template <class T>
AdjacencyWeightedDirectedGraph<T>::AdjacencyWeightedDirectedGraph(int number_of_vertices, T no_edge)
{
	if (number_of_vertices < 0)
	{
		throw IllegalParameterValueException("number of vertices must be >= 0");
	}
	this->vertex_number = number_of_vertices;
	this->no_edge = no_edge;
	this->edge_number = 0;

	make_2d_array(this->data, vertex_number + 1, vertex_number + 1);
	// 初始化邻接矩阵
	for (auto i = 1; i <= vertex_number; i++)
	{
		for (auto j = 1; j <= vertex_number; j++)
		{
			this->data[i][j] = no_edge;
		}
	}
}

template <class T>
AdjacencyWeightedDirectedGraph<T>::~AdjacencyWeightedDirectedGraph()
{
	delete_2d_array(data, vertex_number + 1);
}

template <class T>
int AdjacencyWeightedDirectedGraph<T>::number_of_vertices() const
{
	return vertex_number;
}

template <class T>
int AdjacencyWeightedDirectedGraph<T>::number_of_edges() const
{
	return edge_number;
}

template <class T>
bool AdjacencyWeightedDirectedGraph<T>::exist_edge(int i, int j) const
{
	if (i < 1 || j < 1 || i > vertex_number || j > vertex_number || data[i][j] == no_edge)
	{
		return false;
	}
	return true;
}

template <class T>
void AdjacencyWeightedDirectedGraph<T>::insert_edge(Edge<T>* edge)
{
	int v1 = edge->vertex1();
	int v2 = edge->vertex2();

	if (v1 < 1 || v2 < 1 || v1 > vertex_number || v2 > vertex_number || v1 == v2)
	{
		std::ostringstream s;
		s << "(" << v1 << "," << v2 << ") is not a permissible edge";
		throw IllegalParameterValueException(s.str());
	}
	// add new edge
	if (data[v1][v2] == no_edge)
	{
		edge_number++;
	}
	data[v1][v2] == edge->weight();
}

template <class T>
void AdjacencyWeightedDirectedGraph<T>::erase_edge(int i, int j)
{
	if (i < 1 || j < 1 || i > vertex_number || j > vertex_number || data[i][j] != no_edge)
	{
		data[i][j] = no_edge;
		edge_number--;
	}
}

template <class T>
int AdjacencyWeightedDirectedGraph<T>::degree(int vertex) const
{
	throw UndefinedMethodException("degree() undefined");
}

template <class T>
int AdjacencyWeightedDirectedGraph<T>::in_degree(int vertex) const
{
	// check the vertex
	check_vertex(vertex);

	// count in edges at vertex
	auto degree = 0;
	for (auto j = 0; j <= vertex_number; j++)
	{
		if (data[j][vertex] != no_edge)
		{
			degree++;
		}
	}
	return degree;
}

template <class T>
int AdjacencyWeightedDirectedGraph<T>::out_degree(int vertex) const
{
	// check the vertex
	check_vertex(vertex);

	// count in edges at vertex
	auto degree = 0;
	for (auto j = 0; j <= vertex_number; j++)
	{
		if (data[vertex][j] != no_edge)
		{
			degree++;
		}
	}
	return degree;
}

template <class T>
bool AdjacencyWeightedDirectedGraph<T>::directed() const
{
	return true;
}

template <class T>
bool AdjacencyWeightedDirectedGraph<T>::weighted() const
{
	return true;
}

template <class T>
VertexIterator<T>* AdjacencyWeightedDirectedGraph<T>::iterator(int vertex)
{
}

template <class T>
void AdjacencyWeightedDirectedGraph<T>::check_vertex(int vertex) const
{
	if (vertex < 1 || vertex > this->vertex_number)
	{
		std::ostringstream s;
		s << "no vertex" << vertex;
		throw IllegalParameterValueException(s.str());
	}
}

template <class T>
void AdjacencyWeightedDirectedGraph<T>::output(std::ostream&) const
{
	for (auto i = 1; i <= vertex_number; i++)
	{
		
	}
}
