#include <algorithm>
#include <list>
#include <mutex>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
  // c++14
  std::lock_guard<std::mutex> guard(some_mutex);
  // c++17
  std::lock_guard guard_(some_mutex);
  some_list.emplace_back(new_value);
}

bool list_contains(int value_to_find)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}
