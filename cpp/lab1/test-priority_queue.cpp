#include "priority_queue.h"
#include <gtest/gtest.h>

TEST(PriorityQueue, TestNullSize)
{
  Priority_queue<int, std::vector> queue;
  EXPECT_EQ(queue.getSize(), 0);
  EXPECT_TRUE(queue.isEmpty());
  try
  {
    queue.pop();
    EXPECT_TRUE(false);
  }
  catch (std::runtime_error &e)
  {
    EXPECT_TRUE(true);
  }
}

TEST(PriorityQueue, TestRandom)
{
  Priority_queue<int, std::vector> queue;
  std::vector<int> result;
  int size_queue = std::rand() % 1000;
  for (int i = 0; i < size_queue; ++i)
  {
    int value = (i % 2 == 0) ? std::rand() : (-1) * std::rand();
    queue.push(value);
    result.push_back(value);
  }
  std::sort(result.begin(), result.end());
  for (int i = result.size() - 1; i >= 0; --i)
  {
    EXPECT_EQ(result[i], queue.top());
    EXPECT_EQ(result[i], queue.pop());
    EXPECT_EQ(--size_queue, queue.getSize());
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}