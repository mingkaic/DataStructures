#include <vector>
#include <algorithm>

template <class T>
class graph
	{
	private:
		std::vector<??> vertices;
	public:
		bool addVertex(T data);
		bool addEdge(T v1, T v2);
		bool removeVertex(T data);
		bool removeEdge(T v1, T v2);
	};
	
template <class T>
bool graph<T>::addVertex(T data)
	{
	vertices.push_back(data);
	}

template <class T>
bool graph<T>::addEdge(T v1, T v2)
	{
	
	for (std::find(vertices.begin(), vertices.end(), v1)
	}

template <class T>
bool graph<T>::removeVertex(T data);

template <class T>
bool graph<T>::removeEdge(T v1, T v2);