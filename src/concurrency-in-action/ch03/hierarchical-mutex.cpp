#include <mutex>
#include <stdexcept>

class hierarchical_mutex
{
  std::mutex internal_mutex;
  unsigned long const hierarchy_value;
  unsigned long previous_hierarchy_value;// NOLINT
  static thread_local unsigned long this_thread_hirearchy_value;// NOLINT

  void check_for_hierarchy_violationn() const
  {
    if (this_thread_hirearchy_value <= hierarchy_value) { throw std::logic_error("mutex hierarchy violated"); }
  }

  void update_hierarchy_value()
  {
    previous_hierarchy_value = this_thread_hirearchy_value;
    this_thread_hirearchy_value = hierarchy_value;
  }

public:
  explicit hierarchical_mutex(unsigned long value) : hierarchy_value(value), previous_hierarchy_value(0) {}

  void lock()
  {
    check_for_hierarchy_violationn();
    internal_mutex.lock();
    update_hierarchy_value();
  }

  void unlock()
  {
    if (this_thread_hirearchy_value != hierarchy_value) { throw std::logic_error("mutex hirearchy violated"); }
    this_thread_hirearchy_value = previous_hierarchy_value;
    internal_mutex.unlock();
  }

  bool try_lock()
  {
    check_for_hierarchy_violationn();
    if (!internal_mutex.try_lock()) { return false; }
    update_hierarchy_value();
    return true;
  }
};

thread_local unsigned long hierarchical_mutex::this_thread_hirearchy_value(ULONG_MAX);// NOLINT


// Sample code that usese hierarchical_mutex

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);
hierarchical_mutex other_mutex(6000);

int do_low_level_stuff();
int low_level_func()
{
  std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
  return do_low_level_stuff();
}

void high_level_stuff(int some_param);
void high_level_func()
{
  std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
  high_level_stuff(low_level_func());
}

void thread_a() { high_level_func(); }

void do_other_stuff();
void other_stuff()
{
  high_level_func();
  do_other_stuff();
}
void thread_b()
{
  std::lock_guard<hierarchical_mutex> lk(other_mutex);
  other_stuff();
}
