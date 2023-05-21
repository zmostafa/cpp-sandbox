

// Thread safety lazy-initialization
#include <memory>
#include <mutex>
#include <string>
struct some_resource
{
  void do_something();
};
std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;
void foo()
{
  std::unique_lock<std::mutex> lk(resource_mutex);
  if (!resource_ptr) { resource_ptr.reset(new some_resource); }
  lk.unlock();
  resource_ptr->do_something();
}

// double-checked-locking pattern
// can also lead to race condition not only for the pointer
// but for the object instance of some_resource
void undefined_behavior_with_double_checked_locking()
{
  if (!resource_ptr) {
    std::lock_guard<std::mutex> lk(some_resource);
    if (!resource_ptr) { resource_ptr.reset(new some_resource); }
  }
  resource_ptr->do_something();
}


// using std::call_once(), and std::once_flag for one time init
std::once_flag resource_flag;
void init_resource() { resource_ptr.reset(new some_resource); }

void foo_call_once()
{
  std::call_once(resource_flag, init_resource);
  resource_ptr->do_something();
}

// Thread-safe lazy initialization of a class member using std::call_once
class connection_info;
class connection_handle;
class connection_manager;
struct data_packet;
class X
{
  connection_info connection_details;
  connection_handle connection;
  std::once_flag connection_init_flag;
  void open_connection() { connection = connection_manager.open(connection_details); }

public:
  X(connection_info const &connection_details_) : connection_details(connection_details_) {}
  void send_data(data_packet const &data)
  {
    std::call_once(connection_init_flag, &X::open_connection, this);
    connection.send_data(data);
  }

  data_packet recieve_data()
  {
    std::call_once(connection_init_flag, &X::open_connection, this);
    return connection.recieve_data();
  }
};

// Protecting a data structure with std::shared_mutex
#include <map>
#include <shared_mutex>

class dns_entry;
class dns_cache
{
  std::map<std::string, dns_entry> entries;
  mutable std::shared_mutex entry_mutex;

public:
  dns_entry find_entry(std::string const &domain) const
  {
    std::shared_lock<std::shared_mutex> lk(entry_mutex);
    std::map<std::string, dns_entry>::const_iterator const it = entries.find(domain);
    return it == entries.end() ? dns_entry() : it->second;
  }

  void update_or_add_entry(std::string const &domain, dns_entry const &dns_details)
  {
    std::lock_guard<std::shared_mutex> lk(entry_mutex);
    // std::unique_lock<std::shared_mutex> un_lk(entry_mutex);
    entries[domain] = dns_details;
  }
};
