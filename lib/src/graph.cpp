#include "include/graph.hpp"

#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "glog/logging.h"

GraphEdge::GraphEdge(unsigned id, unsigned first_node_id,
                     unsigned second_node_id, float weight)
  : id(id), weight(weight) {
  nodes[0] = first_node_id;
  nodes[1] = second_node_id;
}

// Graph::Graph(unsigned n_nodes, const std::vector<float>& weights)
//   : n_nodes_(n_nodes), weights_(weights) {}

Graph::Graph(const std::string& file_path) {
  std::ifstream file(file_path.c_str());
  CHECK(file.is_open());

  unsigned n_edges;
  file >> n_nodes_;
  file >> n_edges;
  edges_.resize(n_edges);
  for (unsigned i = 0; i < n_edges; ++i) {
    edges_[i].id = i;
    file >> edges_[i].nodes[0];
    file >> edges_[i].nodes[1];
    file >> edges_[i].weight;
  }
  file.close();
}

// void Graph::WriteDot(const std::string& file_path) const {
//   std::ofstream file(file_path.c_str());
//   file << "graph {\n";
//
//   unsigned offset = 0;
//   for (unsigned i = 1; i < n_nodes_; ++i) {
//     for (unsigned j = i; j < n_nodes_; ++j) {
//       float weight = weights_[offset++];
//       if (weight == 0.0f) continue;
//
//       std::ostringstream ss;
//       ss << i << "--" << j + 1 << "[label=\"" << weight << "\"];\n";
//       file << ss.str();
//     }
//   }
//   file << "}\n";
//   file.close();
// }

void Graph::GetEdges(std::vector<GraphEdge>* edges) const {
  edges->resize(edges_.size());
  std::copy(edges_.begin(), edges_.end(), edges->begin());
}

unsigned Graph::GetNumberNodes() const {
  return n_nodes_;
}
