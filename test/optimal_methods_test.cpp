#include <math.h>

#include <vector>

#include "gtest/gtest.h"

#include "test/macros.hpp"
#include "include/boruvka_method.hpp"
#include "include/kruskal_method.hpp"

// Check that optimal methods returns spanning trees with similar weighs sum.
TEST(OptimalMethods, equals_costs) {
  static const unsigned kNumGenerations = 10000;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;
  static const float kZeroLimit = 1e-6f;

  std::vector<float> weights;
  std::vector<unsigned> spanning_tree;
  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    GenGraph(n_nodes, &weights);

    BoruvkaMethod::Process(n_nodes, weights, &spanning_tree);
    float boruvka_spanning_tree_cost = ComputeTreeCost(weights, spanning_tree);

    KruskalMethod::Process(n_nodes, weights, &spanning_tree);
    float kruskal_spanning_tree_cost = ComputeTreeCost(weights, spanning_tree);

    ASSERT_LT(fabs(kruskal_spanning_tree_cost - boruvka_spanning_tree_cost),
              kZeroLimit);
  }
}