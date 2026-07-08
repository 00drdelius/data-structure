// adjacency matrix, 邻接矩阵实现图
// _impl.h，用于实现模板类的

#ifndef __adjacency_matrix_impl__
#define __adjacency_matrix_impl__

#include <vector>
#include "graph/basic.h"
#include "utils.hpp"

template <typename T>
AdjacencyMatrix<T>::AdjacencyMatrix(StoreTypes store_type) : BasicGraph<T>(store_type) {
  std::cout << "Initialized adjacency matrix with default size: "
            << "( " << MAX_ROWS << ", " << MAX_COLUMNS << ")" << std::endl;
  vertices = new T[MAX_ROWS]();
  length = 0;

  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < MAX_COLUMNS; j++) {
      edges[i][j] = -1;
    }
  }
}

template <typename T>
int AdjacencyMatrix<T>::search_vertex(const T& x) const {
  for (int i = 0; i < MAX_ROWS; i++) {
    if (vertices[i] == x) {
      return i;
    }
  }
  return -1;
}

// x##_index= ${传入x的变量名}_index
#define search_double_with_assert(x, y)               \
  int x##_index = search_vertex(x);                   \
  int y##_index = search_vertex(y);                   \
  assert(x##_index != -1, "vertex x does not exist"); \
  assert(y##_index != -1, "vertex y does not exist");

// 外部实现不用加 override，其只能用在类定义内部的成员函数声明中
template <typename T>
bool AdjacencyMatrix<T>::adjacent(const T& x, const T& y) {
  //   int x_index = search_vertex(x); // O(n)
  //   int y_index = search_vertex(y); // O(n)
  //   assert(x_index != -1, "vertex x does not exist");
  //   assert(y_index != -1, "vertex y does not exist");
  search_double_with_assert(x, y);

  int edge_weight = edges[x_index][y_index];

  return edge_weight != 0;
}

template <typename T>
bool AdjacencyMatrix<T>::insert_vertex(const T& x) {
  assert(length != MAX_ROWS, "Graph is full");

  int exists_index = search_vertex(x);
  assert(exists_index == -1, "This value of vertex already exists");

  vertices[length] = x;
  for (int j = 0; j <= length; j++) {
    edges[length][j] = 0;
  }
  for (int i = 0; i <= length; i++) {
    edges[i][length] = 0;
  }
  length++;
  return true;
}

template <typename T>
bool AdjacencyMatrix<T>::delete_vertex(const T& x) {
  assert(length != 0, "Graph is empty");

  int exists_index = search_vertex(x);

  if (length == 1) {
    // length==1 performs differently
    vertices[exists_index] = 0;
    length--; // logically remove it
    return true;
  }
  // delete from list of vertices
  for (int i = length - 1; i > exists_index; i--) {
    vertices[i - 1] = vertices[i];
  }

  // delete from matrix
  // iterate row reversely from the end to the deleted index
  for (int i = length - 1; i > exists_index; i--) {
    // iterate the whole column
    for (int j = 0; j < length; j++) {
      edges[i - 1][j] = edges[i][j];
    }
  }
  // iterate column reversely from the end to the deleted index
  for (int j = length - 1; j > exists_index; j--) {
    for (int i = 0; i < length; i++) {
      // iterate the whole row
      edges[i][j - 1] = edges[i][j];
    }
  }
  length--;
  return true;
}

template <typename T>
bool AdjacencyMatrix<T>::add_edge(const T& x, const T& y) {
  search_double_with_assert(x, y);
  edges[x_index][y_index] = 1;
  return true;
}

template <typename T>
bool AdjacencyMatrix<T>::remove_edge(const T& x, const T& y) {
  search_double_with_assert(x, y);
  edges[x_index][y_index] = -1;
  return true;
}

// returning {-1,-1} means there's no first neighbor
template <typename T>
std::vector<T> AdjacencyMatrix<T>::first_neighbor(const T &x){
    int search_index = search_vertex(x);

    for(int j=0;j<length;j++){
        int weight = edges[search_index][j];
        if (weight!=-1 && weight!=0){
            return {search_index, j};
        }
    }
    return {-1, -1};
}

#endif