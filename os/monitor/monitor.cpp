/*
  * Producer-Consumer problem using monitor
  *
  * Compile using: g++ -std=c++11 monitor.cpp -o monitor -pthread
  *
  * Author: Nischal Khanal
  *
pseudocode
-----------------
  Monitor Class:
  Initialize: buffer, count, mutex, not_full, not_empty

  insertItem(item):
    lock(mutex)
    wait(not_full, count != BUFFER_SIZE)
    buffer.push(item)
    count++
    unlock(mutex)
    signal(not_empty)

  removeItem():
    lock(mutex)
    wait(not_empty, count != 0)
    item = buffer.front()
    buffer.pop()
    count--
    unlock(mutex)
    signal(not_full)
    return item

Producer Function:
  for i in range(100):
    item = produceItem()
    monitor.insertItem(item)
    print("Producer produced item:", item)
    sleep(100)

Consumer Function:
  for i in range(100):
    item = monitor.removeItem()
    print("Consumer consumed item:", item)
    sleep(100)

Main Function:
  srand(current_time)
  monitor = Monitor()

  producer_thread = create_thread(producer, monitor)
  consumer_thread = create_thread(consumer, monitor)

  join_threads(producer_thread, consumer_thread)



1. Shared Resource Protection:
   - Mutex ensures that shared data, like the buffer, is accessed by only one thread at a time.

2. Mutual Exclusion:
   - Mutex acts like a lock, allowing only one thread to access critical sections of code at any given time.

3. Atomic Operations:
   - Mutex ensures that operations on shared data happen without interruption, avoiding inconsistencies.

4. Prevention of Race Conditions:
   - It prevents race conditions by making sure that shared data is accessed in a controlled, synchronized way.

5. Deadlock Prevention:
    - Mutexes can be unlocked by the same thread that locked them, preventing deadlocks.

Encapsulation bundles everything together, mutual exclusion ensures orderly access, and atomic operations keep things running smoothly without interruptions. 

How do monitors handle blocking?
  - Link:
     http://denninginstitute.com/modules/ipc/pink/swmon.html



*/

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

const int BUFFER_SIZE = 5;

// Monitor class to manage the shared buffer between producer and consumer
class Monitor
{
private:
  std::queue<int> buffer;
  int count;
  std::mutex mutex;
  std::condition_variable not_full;  // Condition variable to signal when buffer is not full
  std::condition_variable not_empty; // Condition variable to signal when buffer is not empty
public:
  Monitor() : count(0) {}

  // Insert an item into the buffer
  void insertItem(int item)
  {
    std::unique_lock<std::mutex> lock(mutex);

    // Wait until the buffer is not full
    not_full.wait(lock, [this]()
                  { return count != BUFFER_SIZE; });

    buffer.push(item);
    count++;

    lock.unlock();

    // Signal that buffer is not empty
    not_empty.notify_one();
  }

  // Remove an item from the buffer
  int removeItem()
  {
    std::unique_lock<std::mutex> lock(mutex);

    // Wait until the buffer is not empty
    not_empty.wait(lock, [this]()
                   { return count != 0; });

    int item = buffer.front();
    buffer.pop();
    count--;

    lock.unlock();

    // Signal that buffer is not full
    not_full.notify_one();

    return item;
  }
};

// Producer function
void producer(Monitor &monitor)
{
  for (int i = 0; i < 100; ++i)
  {
    monitor.insertItem(i);
    std::cout << "Producer produced item: " << i << std::endl;

    // Simulate some work being done
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

// Consumer function
void consumer(Monitor &monitor)
{
  int item;
  for (int i = 0; i < 100; ++i)
  {
    item = monitor.removeItem();
    std::cout << "Consumer consumed item: " << item << std::endl;

    // Simulate some work being done
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

int main()
{
  srand(time(NULL));

  Monitor monitor;

  // Create producer and consumer threads
  std::thread producer_thread(producer, std::ref(monitor));
  std::thread consumer_thread(consumer, std::ref(monitor));

  // Wait for both threads to finish
  producer_thread.join();
  consumer_thread.join();

  return 0;
}
