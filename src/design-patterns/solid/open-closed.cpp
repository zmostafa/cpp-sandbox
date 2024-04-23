// Open-Close princable; open to extention but closed for modification

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color { RED, GREEN, BLUE };
enum class Size { SMALL, MEDIUM, LARGE };

struct Product
{
  string name;
  Color color;
  Size size;
};

struct ProductFilter
{
  vector<Product *> by_color(vector<Product *> items, Color color)
  {
    vector<Product *> result;
    for (auto &item : items) {
      if (item->color == color) { result.push_back(item); }
    }
    return result;
  }
};

template<typename T> struct Specification
{
  virtual bool is_satisfied(T *item) = 0;
};

template<typename T> struct Filter
{
  virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product>
{
  vector<Product *> filter(vector<Product *> items, Specification<Product> &spec) override
  {
    vector<Product *> result;
    for (auto &item : items) {
      if (spec.is_satisfied(item)) result.push_back(item);
    }
    return result;
  }
};

struct ColorSpecification : Specification<Product>
{
  Color color;
  ColorSpecification(Color color) : color(color) {}
  bool is_satisfied(Product *item) override { return item->color == color; }
};

struct SizeSpecification : Specification<Product>
{
  Size size;
  SizeSpecification(Size size) : size(size) {}

  bool is_satisfied(Product *item) override { return item->size == size; }
};

int main(int argc, char *argv[])
{
  Product apple{ "Apple", Color::GREEN, Size::SMALL };
  Product tree{ "Tree", Color::GREEN, Size::LARGE };
  Product house{ "House", Color::BLUE, Size::LARGE };

  vector<Product *> items{ &apple, &tree, &house };

  BetterFilter bf;
  ColorSpecification green(Color::GREEN);
  for (auto &item : bf.filter(items, green)) { cout << item->name << " is Green\n"; }
  return 0;
}
