

#pragma		once

#include	"LinkedList.hpp"

//	Type & Typedefs

typedef 	int 	ret_t;

template<typename _T>
using P_COMPARE_FUNC = ret_t(*)(_T, _T);

template<typename _T>
class Graph
{

private:

	class Edge;	
	class Vertex;

	class 	Edge
	{
	private:
		Vertex* vertex;
		size_t 	weight;

		Edge() : vertex(NULL), weight(0) {}
		Edge(Vertex* vertex) : vertex(vertex), weight(0) {}
		Edge(Vertex* vertex, size_t weight) : vertex(vertex), weight(weight) {};
		~Edge() {}

		template<typename _T>
		friend class Graph;
	};

	class 	Vertex
	{
	private:
		_T data;
		LinkedList<Edge*> *edges;

		Vertex() : _T((_T)0), edges(NULL) {}
		Vertex(_T data) : data(data) { edges = new LinkedList<Edge*>(); };

		~Vertex() { delete(edges); }

		template<typename _T>
		friend class Graph;		

	public:		
		size_t size() { return(edges->size()); }

		_T 	operator[] (int index) { return( (*edges)[index]->vertex->data ); }
		_T	operator*(Vertex* v) {	std::out << "Hello\n"; }
		
		_T 	GetData() const { return(data); }
	};

	LinkedList<Vertex*> *vertices;

public:

	Graph() { vertices = new LinkedList<Vertex*>(); }
	~Graph() { delete(vertices); }

	ret_t 	AddVertex(_T data);
	ret_t 	AddEdge(_T v1, _T v2, size_t weight, P_COMPARE_FUNC<_T> compare_proc);
	ret_t 	AddDirectedEdge(_T v1, _T v2, size_t weight, P_COMPARE_FUNC<_T> compare_proc);

	size_t	size() const { return( vertices->size() ); }

	Vertex* operator[](int index) {	return( (*vertices)[index] ); }
};

template<typename _T>
ret_t 	Graph<_T>::AddVertex(_T data)
{
	return(vertices->listInsertBack( new Vertex(data) ));
}

template<typename _T>
ret_t 	Graph<_T>::AddEdge(_T v1, _T v2, size_t weight, P_COMPARE_FUNC<_T> compare_proc)
{
	Vertex* vertex1 = NULL;
	Vertex* vertex2 = NULL;

	if( SUCCESS == compare_proc(v1, v2) )
		return(FAILURE);

	for( int i = 0; i < vertices->size(); ++i)
	{
		if( SUCCESS == compare_proc( (*vertices)[i]->data, v1 ) )
		{
			vertex1 = (*vertices)[i];
			break;
		}
	}
	if( NULL == vertex1 )
		return(FAILURE);

	for(int i = 0; i < vertices->size(); ++i)
	{
		if( SUCCESS == compare_proc( (*vertices)[i]->data, v2 ) )
		{
			vertex2 = (*vertices)[i];
			break;
		}
	}
	if( NULL == vertex2 )
		return(FAILURE);

	for( int i = 0; i < vertex1->size(); ++i )
		if( SUCCESS == compare_proc((*vertex1)[i], vertex2->data) )
			return(FAILURE);

	for( int i = 0; i < vertex2->size(); ++i )
		if( SUCCESS == compare_proc((*vertex2)[i], vertex1->data) )
			return(FAILURE);

	vertex1->edges->listInsertBack( new Edge(vertex2, weight) );
	vertex2->edges->listInsertBack( new Edge(vertex1, weight) );

	return(SUCCESS);
}

template<typename _T>
ret_t 	Graph<_T>::AddDirectedEdge(_T v1, _T v2, size_t weight, P_COMPARE_FUNC<_T> compare_proc)
{
	Vertex* vertex1 = NULL;
	Vertex* vertex2 = NULL;

	if( SUCCESS == compare_proc(v1, v2) )
		return(FAILURE);

	for( int i = 0; i < vertices->size(); ++i)
	{
		if( SUCCESS == compare_proc( (*vertices)[i]->data, v1 ) )
		{
			vertex1 = (*vertices)[i];
			break;
		}
	}
	if( NULL == vertex1 )
		return(FAILURE);

	for(int i = 0; i < vertices->size(); ++i)
	{
		if( SUCCESS == compare_proc( (*vertices)[i]->data, v2 ) )
		{
			vertex2 = (*vertices)[i];
			break;
		}
	}
	if( NULL == vertex2 )
		return(FAILURE);

	for( int i = 0; i < vertex1->size(); ++i )
		if( SUCCESS == compare_proc((*vertex1)[i], vertex2->data) )
			return(FAILURE);

	for( int i = 0; i < vertex2->size(); ++i )
		if( SUCCESS == compare_proc((*vertex2)[i], vertex1->data) )
			return(FAILURE);

	vertex1->edges->listInsertBack( new Edge(vertex2, weight) );
	
	return(SUCCESS);
}
