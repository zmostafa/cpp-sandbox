#include <algorithm>
#include <thread>
#include <utility>

// One of the proposals for C++17 was for a joining_thread class that would be similar to std::thread, except that it
// would automatically join in the destructor much like scoped_thread does. This didn’t get consensus in the committee,
// so it wasn’t accepted into the standard (though it’s still on track for C++20 as std::jthread)

class joining_thread
{
public:
  joining_thread() noexcept = default;
  template<typename Callable, typename... Args>
  explicit joining_thread(Callable &&func, Args &&...args)
    : t(std::forward<Callable>(func), std::forward<Args>(args)...)
  {}
  explicit joining_thread(std::thread _t) noexcept : t(std::move(_t)) {}

  joining_thread(joining_thread &&other) noexcept : t(std::move(other.t)) {}
  joining_thread &operator=(joining_thread &&other) noexcept
  {
    if (joinable()) { join(); }
    t = std::move(other.t);
    return *this;
  }
  joining_thread &operator=(std::thread other) noexcept
  {
    if (joinable()) { join(); }
    t = std::move(other);
    return *this;
  }
  ~joining_thread() noexcept
  {
    if (joinable()) { join(); }
  }
  joining_thread(joining_thread const &) = delete;
  joining_thread operator=(joining_thread const &) = delete;

  void swap(joining_thread &other) noexcept { t.swap(other.t); }
  std::thread::id get_id() const noexcept { return t.get_id(); }
  bool joinable() const noexcept { return t.joinable(); }
  void join() { t.join(); }
  void detach() { t.detach(); }
  std::thread &as_thread() noexcept { return t; }
  const std::thread &as_thread() const noexcept { return t; }

private:
  std::thread t;
};
