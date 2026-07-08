#ifndef __basic_graph_obj__
#define __basic_graph_obj__

#include <vector>
#include "utils.hpp"

// allowed graph storage type
enum class StoreTypes : char { adjacency_matrix, adjacency_list };

template <typename T>
class BasicGraph : public BaseObject {
protected: // can be visited in sub class
  StoreTypes store_type;

public:
  // 删除拷贝构造函数。子类也使用其自身的拷贝构造函数
  BasicGraph(const BasicGraph<T>& other) = delete;

  // 删除拷贝赋值运算重载，子类也无法使用其自身的拷贝赋值运算符
  BasicGraph& operator=(const BasicGraph<T>& other) = delete;

  // for convenience default construct function
  // sets no signature, fix the size
  BasicGraph(StoreTypes store_type);

  // determine whether the <x,y>/(x,y) exists. `=0` means this is pure virtual function
  virtual bool adjacent(const T& x, const T& y) const = 0;

  // list all edges adjacent to the vertex x
  std::vector<std::vector<T>> neighbors(const T& x) = 0;

  virtual bool insert_vertex(const T& x) = 0;

  virtual bool delete_vertex(const T& x) = 0;

  // raise error if edge exists
  virtual bool add_edge(const T& x, const T& y) = 0;

  virtual bool remove_edge(const T& x, const T& y) = 0;

  // find the first adjacent vertex if exists, else raise error
  virtual std::vector<T> first_neighbor(const T& x) const = 0;

  // find the next adjacent vertex of x after y
  virtual std::vector<T> next_neighbor(const T& x, const T& y) const = 0;

  // return edge weight
  virtual int get_edge_weight(const T& x, const T& y) const = 0;

  // set overwrite edge weight
  virtual bool set_edge_weight(const T& x, const T& y, int weight) = 0;

  virtual std::vector<T> BFS() const = 0;
};

#define MAX_ROWS    10
#define MAX_COLUMNS MAX_ROWS // 2-dim square matrix

template <typename T>
class AdjacencyMatrix : public BasicGraph<T> {
private:
  T* vertices; // store list of vetex
  int length; // length of vertices

  // defaults to -1, represents no vertex;
  // 0, represents no edge but has vertex;
  int edges[MAX_ROWS][MAX_COLUMNS];

public:
  AdjacencyMatrix(StoreTypes store_type);
  ~AdjacencyMatrix();

  // search vertex from vertices, return list index
  int search_vertex(const T& x) const;

  bool adjacent(const T& x, const T& y) const override;
  bool insert_vertex(const T& x) override;
  bool delete_vertex(const T& x) override;
  bool add_edge(const T& x, const T& y) override;
  bool remove_edge(const T& x, const T& y) override;
  std::vector<T> first_neighbor(const T& x) const override;
  std::vector<T> next_neighbor(const T& x, const T& y) const override;
  int get_edge_weight(const T& x, const T& y) const override;
  bool set_edge_weight(const T& x, const T& y, int weight) override;
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
public:
  AdjacencyList(StoreTypes store_type);
  bool adjacent(const T& x, const T& y) override;
  bool insert_vertex(const T& x) override;
  bool delete_vertex(const T& x) override;
  bool add_edge(const T& x, const T& y) override;
  bool remove_edge(const T& x, const T& y) override;
  std::vector<T> first_neighbor(const T& x) override;
  std::vector<T> next_neighbor(const T& x, const T& y) override;
  int get_edge_weight(const T& x, const T& y) override;
  bool set_edge_weight(const T& x, const T& y, int weight) override;
};

#endif