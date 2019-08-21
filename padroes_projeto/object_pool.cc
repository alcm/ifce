#include <iostream>
#include <mutex>
#include <vector>

struct Object {

};

template <class T>
class ObjectPool {
   public:
    explicit ObjectPool(const int n_objects)
    {
        objects_.reserve(n_objects);
        for (int i = 0; i < n_objects; i++)
            objects_.emplace_back(new T());
    }

    ~ObjectPool()
    {
        for (auto &entry : objects_)
            delete entry;
    }

    T *Pick() 
    {
        std::lock_guard<std::mutex> lk(mutex_);

        if (!objects_.empty()) {
            auto obj = objects_.back();

            objects_.pop_back();
            std::cout << "Object picked from pool" << std::endl;
            return obj;
        }

        return nullptr;
    }

    void Return(T *obj)
    {
        std::lock_guard<std::mutex> lk(mutex_);

        if (objects_.size() != objects_.max_size()) {
            objects_.emplace_back(obj);
            std::cout << "Object returned to pool" << std::endl;
        }
    }

   private:
    std::mutex mutex_;
    std::vector<T *> objects_;
};

int main()
{
    ObjectPool<Object> pool(5);

    auto item1 = pool.Pick();
    auto item2 = pool.Pick();
    auto item3 = pool.Pick();
    auto item4 = pool.Pick();
    auto item5 = pool.Pick();
}
