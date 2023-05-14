#include <thread>
#include <utility>

class joining_thread
{
public:
  joining_thread() noexcept = default;
  template<typename Callable, typename... Args>
  explicit joining_thread(Callable &&func, Args &&...args)
    : t(std::forward<Callable>(func), std::forward<Args>(args)...)
  {}
                                                       explicit joining_thread(std::thread _t) noexcept : t(std::move(_t)) {}

                                                      joining_thread(joining_thread&& other) noexcept : t(std::move(other.t)) {}
    joining_thread& operator=(joining_thread&& other) noexcept {
      if(joinable()){
        join();
      }
  t = std::move(other.t);
      return *this;
    }

private:
  std::thread t;
};
