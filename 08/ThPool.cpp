using namespace std;
#include <iostream>
#include <assert.h>
#include <future>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
class ThreadPool
{
private:
    size_t threads;
    std::mutex mx;
    std::condition_variable condition;
    std::deque < std::packaged_task<void()>> todo;
    std::vector < std::future<void>> done;
    void thread_task();
public:


    // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func &&func, Args... args); //->std::future<decltype(func(args...))>;
    void finish() {
        {
            std::unique_lock<std::mutex> l(mx);
            for (auto&&unused : done) {
                todo.push_back({});
            }
        }
        condition.notify_all();
        done.clear();
    }
    explicit ThreadPool(size_t poolSize) {
        threads = poolSize;
        for (std::size_t i = 0; i < poolSize; i++)
        {
            // each thread is a std::async running this->thread_task():
            done.push_back(

                std::async(
                    std::launch::async,
                    [this] { thread_task(); }
                )
            );
        }
    }
    ~ThreadPool() {
        finish();
    }
};

template<class Func, class ...Args>// or Func ?
auto ThreadPool::exec(Func&& func, Args ...args)
{
    using restype = decltype(func(args...));
    static packaged_task<restype(Args...)> pk(std::forward<Func>(func)); //args... std::result_of_t<Func&()>
    auto r = pk.get_future();
    {
        std::unique_lock<std::mutex> l(mx);
        todo.emplace_back([=]() mutable { return pk(args...); }); //
    }
    condition.notify_one(); // wake a thread to work on the task

    return r; // return the future result of the task
}
void ThreadPool::thread_task() {
    while (true) {
        std::packaged_task<void()> f;
        {
            std::unique_lock<std::mutex> l(mx);
            if (todo.empty()) {
                condition.wait(l, [this] {return !todo.empty(); });
            }
            f = std::move(todo.front());
            todo.pop_front();
        }
        if (!f.valid()) return;
        f(); 
    }
}


int f(int x) {
    return x;
}
int g(int x, int y) {

    return x + y;
}


int main() {
    ThreadPool th(5);
    auto t = th.exec(f,5);
    auto t_ = th.exec(g, 5,100);
    assert (t.get()==5);
    assert(t_.get() == 105);
    cout << "All test passed";
    return 0;
}