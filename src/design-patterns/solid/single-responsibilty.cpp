// A class should have a single reason to change, i.e.
// a class should have a primary responsibility

#include <boost/lexical_cast.hpp>
#include <cstdio>
#include <fstream>
#include <string>
#include <utility>

using namespace std;
using namespace boost;

struct Journal
{
  string title;
  vector<string> entries;

  explicit Journal(string title) : title(std::move(title)) {}

  void add_entry(const string &entry)
  {
    static int count = 1;
    entries.push_back(std::to_string(count++) + ": " + entry);
  }

  // This breaks single responsibility for this class, it should be separated
  // void save(const string &filename)
  // {
  //   ofstream ofs(filename);
  //   for (auto &e : entries) { ofs << e << endl; }
  // }
};

struct PersistenceManager
{

  static void save(const Journal &journal, const string &filename)
  {
    ofstream ofs(filename);
    for (const auto &entry : journal.entries) { ofs << entry << "\n"; }
  }
};
int main(int  /*argc*/, char * /*argv*/[])
{

  Journal journal{ "Dear Diary" };
  journal.add_entry("I found a bug");
  journal.add_entry("The bug ate me");

  // Breaks the sepration of concenre rule
  // journal.save("Diary.txt");

  PersistenceManager persistencemanager;
  persistencemanager.save(journal, "Diary.txt");

  (void)getchar();
  return 0;
}
