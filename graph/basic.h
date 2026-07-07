#ifndef __basic_graph_obj__
#define __basic_graph_obj__

#include "utils.hpp"

// allowed graph storage type
enum class StoreTypes : char { adjacency_matrix, adjacency_list };

template <typename T>
class BasicGraph : public BaseObject {
protected: // can be visited in sub class
  StoreTypes store_type;

public:
  BasicGraph(const BasicGraph<T>& other) = delete; // 删除拷贝构造函数
  BasicGraph& operator=(const BasicGraph<T>& other) = delete; // 删除拷贝赋值运算重载

  // for convenience default construct function
  // sets no signature, fix the size
  BasicGraph(StoreTypes store_type);

  // determine whether the <x,y>/(x,y) exists
  bool Adjecent(T x1, T x2);

  // list all edges adjacent to the vertex x
  std::string Nerghbors(T x); //TODO
};

#define MAX_ROWS    10
#define MAX_COLUMNS MAX_ROWS // 2-dim square matrix

template <typename T>
class AdjacencyMatrix : public BasicGraph<T> {
private:
  T* vertices; // store list of vetex
  T edges[MAX_ROWS][MAX_COLUMNS];
};

template <typename T>
struct VertexNode {
  T data;
  struct VertexNode<T>* next_vertex;
};

template <typename T>
class AdjacencyList : public BasicGraph<T> {
private:
  VertexNode<T>* vertices; // store list of vetex
};

#endif