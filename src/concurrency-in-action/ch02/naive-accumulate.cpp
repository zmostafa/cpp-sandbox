#include <functional>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>

constexpr unsigned long MIN_PER_THREAD = 25;

template<typename Iterator, typename T> struct accunulate_block
{
  void operator()(Iterator first, Iterator last, T &result) const { result = std::accumulate(first, last, result); }
};

template<typename Iterator, typename T> T parallel_accumulate(Iterator first, Iterator last, T init)
{
  unsigned long const length = std::distance(first, last);
  if (!length) { return init; }

  unsigned long const max_threads = (length + MIN_PER_THREAD - 1) / MIN_PER_THREAD;
  unsigned long const hardware_threads = std::thread::hardware_concurrency();
  unsigned long const num_of_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length / num_of_threads;

  std::vector<T> results(num_of_threads);
  std::vector<std::thread> threads(num_of_threads - 1);
  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_of_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(accunulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }

  // handle even numbers of elements in the current thread
  accunulate_block<Iterator, T>()(block_start, last, results[num_of_threads - 1]);

  for (auto &entry : threads) { entry.join(); }

  return std::accumulate(results.begin(), results.end(), init);
}
