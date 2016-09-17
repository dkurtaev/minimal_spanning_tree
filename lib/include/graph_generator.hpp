#ifndef INCLUDE_GRAPH_GENERATOR_HPP_
#define INCLUDE_GRAPH_GENERATOR_HPP_

#include <vector>

#include "include/graph.hpp"

class GraphGenerator {
 public:
  static void GenGraph(unsigned n_nodes, unsigned n_edges, float min_weight,
                       float max_weight, std::vector<Edge>* edges);

  // Graph with random number of edges.
  static void GenGraph(unsigned n_nodes, std::vector<Edge>* edges);

  // Graph with random number of nodes and edges.
  static unsigned GenGraph(unsigned min_n_nodes, unsigned max_n_nodes,
                           std::vector<Edge>* edges);

  static bool GraphParametersIsCorrect(unsigned n_nodes, unsigned n_edges);

 private:
  // Add edges for graph connectivity.
  static void GenPath(unsigned n_nodes, float min_weight, float max_weight,
                      std::vector<Edge>* edges);

  static float RandWeight(float min_weight, float max_weight,
                          unsigned n_bins = 51);

  static unsigned GetEdgeHash(unsigned from, unsigned to, unsigned n_nodes);
};

#endif  // INCLUDE_GRAPH_GENERATOR_HPP_
