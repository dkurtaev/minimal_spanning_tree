#include <vector>

#include "gtest/gtest.h"

#include "test/macros.hpp"
#include "include/kruskal_method.hpp"
#include "include/random_spanning_tree.hpp"

TEST(KruskalMethod, spanning_tree_correctness) {
  static const unsigned kNumGenerations = 10000;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;

  std::vector<float> weights;
  std::vector<unsigned> spanning_tree;
  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    GenGraph(n_nodes, &weights);
    KruskalMethod::Process(n_nodes, weights, &spanning_tree);
    ASSERT_EQ(spanning_tree.size(), n_nodes - 1);
    ASSERT_TRUE(CheckEdgesUniqueness(weights.size(), spanning_tree));
  }
}

TEST(KruskalMethod, is_better_than_random) {
  static const unsigned kNumGenerations = 10000;
  static const unsigned kMinNumNodes = 3;
  static const unsigned kMaxNumNodes = 25;
  static const float kZeroLimit = 1e-6f;

  std::vector<float> weights;
  std::vector<unsigned> spanning_tree;
  for (unsigned iter = 0; iter < kNumGenerations; ++iter) {
    int n_nodes = rand() % (kMaxNumNodes - kMinNumNodes + 1) + kMinNumNodes;
    GenGraph(n_nodes, &weights);

    KruskalMethod::Process(n_nodes, weights, &spanning_tree);
    float kruskal_spanning_tree_cost = ComputeTreeCost(weights, spanning_tree);

    RandomSpanningTree::Process(n_nodes, weights, &spanning_tree);
    float random_spanning_tree_cost = ComputeTreeCost(weights, spanning_tree);

    ASSERT_LT(kruskal_spanning_tree_cost - random_spanning_tree_cost,
              kZeroLimit);
  }
}