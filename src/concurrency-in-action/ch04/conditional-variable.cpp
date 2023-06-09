#include <condition_variable>
#include <mutex>
#include <queue>

struct data_chunk;

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

bool more_data_to_prepare();
data_chunk prepare_data();

void data_preparation_thread()
{
  while (more_data_to_prepare()) {
    data_chunk const data = prepare_data();
    // Put the code for adding the data in a small scope
    // then notify the condition_variable after unlocking
    {
      std::lock_guard<std::mutex> lk(mut);
      data_queue.push(data);
    }
    data_cond.notify_one();
  }
}

void data_processing_thread()
{
  while (true) {
    // unique_lock is used to enable the thread to release mutex
    // if the condition in wait() is not fulfilled, lock_guard won't
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [] { return !data_queue.empty(); });
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    process(data);
    if (is_last_chunk(data)) { break; }
  }
}
