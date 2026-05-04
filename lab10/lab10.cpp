#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
using namespace std;

// 1 
void task1() {
    cout << "\n--- TASK 1 ---\n";

    auto worker = [](int x) {
        cout << "Square of " << x << " = " << x * x << endl;
        };

    thread t1(worker, 2);
    thread t2(worker, 3);
    thread t3(worker, 4);

    t1.join();
    t2.join();
    t3.join();
}

// 2 
int counter = 0;

void task2() {
    cout << "\n--- TASK 2 (Data Race) ---\n";

    auto worker = [](int id) {
        for (int i = 0; i < 5; i++) {
            counter += id;
            cout << "Thread " << id << " counter = " << counter << endl;
        }
        };

    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();
}

// 3 
mutex mtx;

void task3() {
    cout << "\n--- TASK 3 (Mutex) ---\n";
    counter = 0;

    auto worker = [](int id) {
        for (int i = 0; i < 5; i++) {
            mtx.lock();
            counter += id;
            cout << "Thread " << id << " counter = " << counter << endl;
            mtx.unlock();
        }
        };

    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();
}

// 4 
mutex m1, m2;

void task4() {
    cout << "\n--- TASK 4 (Deadlock) ---\n";

    auto thread1 = []() {
        m1.lock();
        cout << "Thread 1 locked m1\n";
        this_thread::sleep_for(chrono::milliseconds(100));

        m2.lock();
        cout << "Thread 1 locked m2\n";

        m2.unlock();
        m1.unlock();
        };

    auto thread2 = []() {
        m2.lock();
        cout << "Thread 2 locked m2\n";
        this_thread::sleep_for(chrono::milliseconds(100));

        m1.lock();
        cout << "Thread 2 locked m1\n";

        m1.unlock();
        m2.unlock();
        };

    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();
}

// 5 
class SafeQueue {
private:
    queue<int> q;
    mutex mtx;
    condition_variable cv;
    int max_size = 5;

public:
    void enqueue(int value) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]() { return q.size() < max_size; });

        q.push(value);
        cout << "Produced: " << value << endl;

        cv.notify_all();
    }

    int dequeue() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]() { return !q.empty(); });

        int value = q.front();
        q.pop();

        cout << "Consumed: " << value << endl;

        cv.notify_all();
        return value;
    }
};

void task5() {
    cout << "\nTASK 5 (Producer-Consumer)\n";

    SafeQueue sq;

    auto producer = [&]() {
        for (int i = 1; i <= 10; i++) {
            sq.enqueue(i);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        };

    auto consumer = [&]() {
        for (int i = 1; i <= 10; i++) {
            sq.dequeue();
            this_thread::sleep_for(chrono::milliseconds(150));
        }
        };

    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();

    return 0;
}