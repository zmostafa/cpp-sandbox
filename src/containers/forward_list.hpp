#include <cstddef>

namespace sandbox {
namespace containers {

  struct base_node
  {
    base_node *_next;
  };

  template<typename T> struct node : base_node
  {
    T _val;
  };

  template<typename T> class forward_list
  {
    base_node _node;
    size_t _size;
  };

  template<typename T> class forward_listItr
  {
    base_node *_node;
  };

}// namespace containers
}// namespace sandbox
