#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <memory> // Для std::allocator
#include <iterator> // Для std::iterator
#include <cstddef>
#include <limits>
class StandartExample
{
public:
    StandartExample(size_t n);

    int factotial(int n);
    void printmap();
private:
    size_t _size = 0;
    std::map<int, int> _map;
};
inline StandartExample::StandartExample(size_t n)
{
    _size = n;
    for (auto i = 0; i < _size; i ++)
    {
        _map[i] = factotial(i);
    }

}
inline int StandartExample::factotial(int n)
{
    int result = 1;
    for (auto i = 1; i <= n; i++)
    {
        result = result * i;
    }
    return result;
}

inline void StandartExample::printmap()
{
    for (auto i = 0; i < _size; i ++)
    {
        std::cout << i << " " << _map[i];
        if (i != (_size - 1))
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}


//##!!!!!!!!!!!
template <typename T>
struct MyAllocator 
{
    // Определяем типы, необходимые для совместимости с STL
    using value_type = T;  // Основной тип элементов

    // Типы указателей и ссылок
    using pointer = T*;             // Указатель на тип T
    using const_pointer = const T*; // Константный указатель
    using reference = T&;           // Ссылка на тип T
    using const_reference = const T&; // Константная ссылка

    // Структура для переопределения типа аллокатора
    template <typename U>
    struct rebind {
        using other = MyAllocator<U>;  // Новый тип аллокатора для типа U
    };


	MyAllocator() = default;
    ~MyAllocator() = default;

	template <typename U>
	MyAllocator(const MyAllocator<U>&) {};

	T* allocate (std::size_t n)
    {
        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();  // Если память не выделилась - исключение
        return reinterpret_cast<T*>(p); 
    }
	
	void deallocate (T* p, std::size_t n)
    {
        std::free(p); 
    }
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) 
    {
        new (p) U(std::forward<Args>(args)...);
    }
    template <typename U>
    void destroy(U* p) 
    {
        p->~U();
    }

};

class MyMapPool
{
public:
    MyMapPool() = default;
    MyMapPool(size_t n);

    void pushone(int a);
    int getone(int i);
    size_t getsize();

private:
    std::map<int, int, std::less<int>,MyAllocator<std::pair<const int, int>>> _mappool;
    size_t _size;
    size_t current_ = 0;
};

inline MyMapPool::MyMapPool(size_t n)
{
    _size = n;
    for (int i = 0; i < n; i++)
    {
        _mappool[i] = 0;
    }
}

inline void MyMapPool::pushone(int a)
{
    if (current_ < _size)
    {
        
        current_++;
        _mappool[static_cast<int>(current_ - 1)] = a;
    }

}

inline int MyMapPool::getone(int i)
{
    return _mappool[i];
}

inline size_t MyMapPool::getsize()
{
    return current_;
}

class MyExample
{
public:
    MyExample(size_t n);

    void printmap();

private:

    MyMapPool _mymappool;
    int factotial(int n)
    {
        int result = 1;
        for (auto i = 1; i <= n; i++)
        {
            result = result * i;
        }
        return result;
    }
};

inline MyExample::MyExample(size_t n)
{
    _mymappool = MyMapPool{n};
    for (int i = 0; i < n; i++)
    {
        _mymappool.pushone(factotial(i));
    }
}

inline void MyExample::printmap()
{
    int z = static_cast<int>(_mymappool.getsize());
    for (int i = 0; i < z; i ++)
    {
        std::cout << i << " " << _mymappool.getone(i);
        if (i != (z - 1))
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

}

//##########container
class MyContainer
{
public:
    MyContainer();
    ~MyContainer();

    void push_back(int value);
    void printall();

private:
    size_t m_size;
    struct Node
    {
        Node* next;
        Node* prev;
        int data;
    };
    Node* data;

    void freememory(){
        if (data){
            
            for(size_t i = m_size; i > 0; i--){
                Node* del_data = data;
                for (size_t j = 1; j < i; j++){
                    del_data = del_data->prev;
                }                
                delete del_data;
            }
            std::cout << "clear mem of list con" << std::endl;
        }
    }
};

inline MyContainer::MyContainer() : m_size{0}, data{nullptr}{}

inline MyContainer::~MyContainer()
{
    freememory();
}

inline void MyContainer::push_back(int value)
{
    Node* new_data = new Node{};
    new_data->prev = data;
    new_data->next = nullptr;
    new_data->data = value;
    if (m_size>0){
        data->next = new_data;
    }
    data = new_data;
    m_size++; 
}
inline void MyContainer::printall()
{
    Node* print_data = data;
    for (size_t i = m_size; i > 1; i--){
        print_data = print_data->prev;
    }
    for (size_t j = 0; j < m_size; j++){
        std::cout << print_data->data;
        print_data = print_data->next;
        if ((j) != m_size - 1){
            std::cout << ",";
        }
    }
    std::cout << std::endl;
    
}

struct Node
{
    Node* next;
    Node* prev;
    int data;
};
class MyContainerZ
{
    public:
        MyContainerZ(size_t n);
        ~MyContainerZ();

        //void push_back(int value);
        void push_back2(int value);
        void printall();
        Node* get_next();
        void clear();
    private:
        size_t m_size;
        size_t current;

    Node* data;

    Node *get_this(size_t i)
    {
        return &data[i];
    }

    void freememory(){
        if (data){
            Node* del_data;
            del_data = data;
            for(size_t i = m_size; i > 1; i--)
            {
                del_data = del_data->prev;
            }
            std::free(del_data->prev);
        }
        std::cout << "clear mem of list alloc con" << std::endl;
    }

};
inline MyContainerZ::MyContainerZ(size_t n):m_size{n}, data{nullptr}, current{0}
{
    data = static_cast<Node*>(std::malloc(m_size * sizeof(Node)));
}

inline MyContainerZ::~MyContainerZ()
{
    freememory();
}

// inline void MyContainerZ::push_back(int value)
// {
//     Node* new_data = new Node{};
//     new_data->prev = data;
//     new_data->next = nullptr;
//     new_data->data = value;
//     if (current>0){
//         data->next = new_data;
//     }
//     data = new_data;
//     current++;
    
// }
inline void MyContainerZ::push_back2(int value)
{
    Node* new_data = get_next();
    new(new_data) Node{};
    new_data->prev = data;
    new_data->next = nullptr;
    new_data->data = value;
    if (current>0){
        data->next = new_data;
    }
    data = new_data;
    current++;
}
inline void MyContainerZ::printall()
{
    Node* print_data = data;
    for (size_t i = m_size; i > 1; i--){
        print_data = print_data->prev;
    }
    for (size_t j = 0; j < m_size; j++){
        std::cout << print_data->data;
        print_data = print_data->next;
        if ((j) != m_size - 1){
            std::cout << ",";
        }
    }
    std::cout << std::endl;
    
}

inline Node *MyContainerZ::get_next()
{
    if (current >= m_size) return nullptr;  // Проверка на переполнение
    return &data[current+1];
}

inline void MyContainerZ::clear(){
    freememory();
}

///Attempt+
namespace newcont {

template<typename T>
class MyAllocator {
public:
    using value_type = T;

    MyAllocator() noexcept {}
    template<typename U>
    MyAllocator(const MyAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(malloc(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        free(p);
    }
};


template<typename T, typename Allocator = MyAllocator<T>>
class MyContainer {
public:
    class MyIterator {
    public:
        explicit MyIterator(T* ptr) : m_ptr(ptr) {}

        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }

        MyIterator& operator++() {
            ++m_ptr;
            return *this;
        }

        MyIterator operator++(int) {
            MyIterator tmp = *this;
            ++m_ptr;
            return tmp;
        }

        bool operator==(const MyIterator& other) const {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const MyIterator& other) const {
            return m_ptr != other.m_ptr;
        }

    private:
        T* m_ptr;
    };


    MyContainer(const Allocator& alloc = Allocator());        
    ~MyContainer();

    void push_back(const T& value);
    void printall();

    MyIterator begin() { return MyIterator(m_data); }
    MyIterator end() { return MyIterator(m_data + m_size); }

private:
    Allocator m_allocator;
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;

    void reserve(std::size_t new_cap) {
        if (new_cap <= m_capacity)
            return;

        T* new_data = m_allocator.allocate(new_cap);
        for (std::size_t i = 0; i < m_size; ++i) {
            new (new_data + i) T(std::move(m_data[i]));
            m_data[i].~T();
        }
        if (m_data)
            m_allocator.deallocate(m_data, m_capacity);
        
        m_data = new_data;
        m_capacity = new_cap;
    }

    void clear() {
        for (std::size_t i = 0; i < m_size; ++i)
            m_data[i].~T();
        m_size = 0;
    }
};


template <typename T, typename Allocator>
inline MyContainer<T, Allocator>::MyContainer(const Allocator &alloc): m_allocator(alloc), m_data(nullptr), m_size(0), m_capacity(0)
{
    T* new_data = m_allocator.allocate(10);
}
template <typename T, typename Allocator>
inline MyContainer<T, Allocator>::~MyContainer()
{
        clear();
        if (m_data)
            m_allocator.deallocate(m_data, m_capacity);
}

template <typename T, typename Allocator>
inline void MyContainer<T, Allocator>::push_back(const T &value)
{
    if (m_size == m_capacity)
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    new (m_data + m_size) T(value);
    ++m_size;
}

template <typename T, typename Allocator>
inline void MyContainer<T, Allocator>::printall()
{
    size_t n = 1;
    for (auto i = begin(); i != end(); i++)
    {
        std::cout << *i;
        if (n != m_size)
            std::cout << ",";
        n++;
    }
    std::cout << std::endl;
}

} // namespace newcont
