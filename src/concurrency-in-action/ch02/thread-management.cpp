#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <thread>

// Basic thread creation

void do_somthing();
void do_somthing_else();

// clang is not happy about creating thread with
// static storage duration, this may throw exception
std::thread my_thread(do_somthing);

class background_task
{
public:
  void operator()() const
  {
    do_somthing();
    do_somthing_else();
  }
};

background_task f;
std::thread background_task_thread(f);

// C++ most vexing parse will interpret the follwoing
// as function declaration rather than named variable
// declares a my_thread function that takes a single parameter (of type
// pointer-to-a-function-taking-no-parameters-and-returning-a-background_task-object) and returns a std::thread object,
// rather than launching a new thread
std::thread another_thread(background_task());

// Correct syntax
std::thread correct_thread_background((background_task()));
std::thread correct_thread_background_init{ background_task() };

// Creating thread using lambda
std::thread lambda_thread([] {
  do_somthing();
  do_somthing_else();
});

// A function that returns while a thread still has access to local variables
struct func
{
  int &i;
  func(int &_i) : i(_i) {}
  void operator()()
  {
    for (unsigned j = 0; j < 1000000; ++j) { do_somthing(); }
  }
};

void oops()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();
}

// waiting for thread to finish
struct func;
void func_with_throw()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try {
    do_somthing();
  } catch (const std::exception &) {
    t.join();
    throw;
  }
  t.join();
}

// using RAII to wait for a thread to complete
class thread_guard
{
  std::thread &t;

public:
  explicit thread_guard(std::thread &t_) : t(t_) {}
  ~thread_guard()
  {
    // join() can be called only once for a given thread of execution, so it would be a mistake to do so if the thread
    // had already been joined
    if (t.joinable()) { t.join(); }
  }
  // delete copy ctor and copy assignement
  thread_guard(thread_guard const &) = delete;
  thread_guard operator=(thread_guard const &) = delete;
};

// when the execution of the current thread reaches the end of f, the local objects are destroyed in reverse order of
// construction. Consequently, the thread_guard object, g, is destroyed first, and the thread is joined with, in the
// destructor. This even happens if the function exits because do_something an exception
struct func;
void func_with_raii()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);
  do_somthing();
}

// Running threads in background
int main()
{
  std::thread background_thread(do_somthing);
  background_thread.detach();
  assert(!background_thread.joinable());
}

// passing arguments to thread functions
// it’s important to bear in mind that by default, the arguments are copied into internal storage, where they can be
// accessed by the newly created thread of execution, and then passed to the callable object or function as rvalues as
// if they were temporaries.
void thread_fun(int i, std::string const &s);
std::thread t(f, 3, "hello");

void oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  // here’s a significant chance that the oops function will exit before the buffer has been converted to a std::string
  // on the new thread, thus leading to undefined behavior.
  std::thread t(f, 3, buffer);
  // solution, no implicit conversion
  std::thread t1(f, 3, std::string(buffer));
  t.detach();
}

void update_data_for_widget(widget_id w, widget_data &data);
void oops_again(widget_id w)
{
  widget_data data;
  // data is copied to thread, not passed by reference
  std::thread t(update_data_for_widget, w, data);
  // solution
  std::thread t1(update_data_for_widget, w, std::ref(data));
  display_status();
  t.join();
  process_widget_data(data);
}

// Arguments can't be copied, but moved
class big_object
{
  void prepare_data(int &i);
};
void process_big_object(std::unique_ptr<big_object>);
std::unique_ptr<big_object> p(new big_object);
p->prepare_data(42);
std::thread t_with_moved_pointer(process_big_object, std::move(p));

void some_function();
void some_other_function();
std::thread t1(some_function);// ok
std::thread t2 = std::move(t1);// ok, t1 is not attached to a thread
t1 = std::thread(some_other_function);// ok, t1 can be assigned to a thread
std::thread t3;
t3 = std::move(t2);// ok, t2 is not assigned to a thread
t1 = std::move(t3);// not ok, t1 is already associated with a thread, std::terminate will be called

// Returning a std::thread from a function
std::thread f_return_thread()
{
  void some_function();
  return std::thread(some_function);
}
std::thread g_return_thread()
{
  void some_other_function(int);
  std::thread t(some_other_function, 42);
  return t;
}

// move thread ownership to a function
void f(std::thread t);
void g()
{
  void some_other_function();
  f(std::thread(some_other_function));
  std::thread t(some_function);
  f(std::move(t));
}

// Scoped thread
class scoped_thread
{
  std::thread t;

public:
  explicit scoped_thread(std::thread t_) : t(std::move(t_))
  {
    if (!t.joinable()) { throw std::logic_error("No Thread"); }
  }
  ~scoped_thread() { t.join(); }

  scoped_thread(scoped_thread const &) = delete;
  scoped_thread operator=(scoped_thread const &) = delete;
};
struct func;
void f()
{
  int some_local_state = 0;
  scoped_thread t{ std::thread(func(some_local_state)) };
  do_somthing();
}
