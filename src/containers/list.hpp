#include <cstddef>

namespace sandbox {
namespace containers {

  template<typename T> struct node
  {
    node *_next;
    T _val;
  };

  template<typename T> class list
  {
    node<T> *head;
    size_t size;
  };

  template<typename T> class iterator
  {
    node<T> *_node;
    node<T> **_head;
  };


}// namespace containers
}// namespace sandbox
