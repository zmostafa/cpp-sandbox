/*
A thread safe singleton implementation, C++ requires the initializer 
for a local static variable is only run once.
*/

class FileSystem
{
public:
  static FileSystem instance()
  {
    static FileSystem *instance = new FileSystem();
    return *instance;
  }

private:
  FileSystem() = default;
};
