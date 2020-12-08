#pragma once

#include <exception>
#include <vector>

/* Generic max-heap implementation*/
namespace usu
{
    template <typename V, typename P = unsigned int>
    class priority_queue
    {
      public:
        using value_type = V;
        using priority_type = P;
        using size_type = std::size_t;
        using pointer_type = V*;
        using reference_type = V&;

        // (value, priority) container
        struct entry
        {
            value_type value;
            priority_type priority;

            bool operator<(const entry& other) const { return priority < other.priority ? true : false; }
            bool operator<=(const entry& other) const { return priority <= other.priority ? true : false; }
            bool operator>(const entry& other) const { return priority > other.priority ? true : false; }
            bool operator>=(const entry& other) const { return priority >= other.priority ? true : false; }
            bool operator==(const entry& other) const { return priority == other.priority ? true : false; }
        };

        class iterator : public std::iterator<std::forward_iterator_tag, priority_queue*>
        {
          public:
            iterator() :
                iterator(nullptr)
            {
            }

            iterator(std::vector<entry>* ptr) :
                m_pos(0), m_data(ptr)
            {
            }

            iterator(size_type pos, std::vector<entry>* ptr) :
                m_pos(pos), m_data(ptr)
            {
            }

            iterator(const iterator& other);
            iterator(iterator&& other);

            iterator& operator=(const iterator& other);
            iterator& operator=(iterator&& other);

            size_type operator-(const iterator& other) const { return m_pos - other.m_pos; }

            iterator operator++();
            iterator operator++(int);
            entry* operator->() const { return &(*m_data)[m_pos]; }
            entry& operator*() const { return (*m_data)[m_pos]; }

            bool operator==(const iterator& other) const { return (m_data == other.m_data) && (m_pos == other.m_pos); }
            bool operator!=(const iterator& other) const { return !((*this) == other); }

          private:
            size_type m_pos;
            std::vector<entry>* m_data;
        };

        priority_queue() :
            m_size(0), m_heap(0)
        {
        }

        priority_queue(std::initializer_list<entry> inputs) :
            m_size(inputs.size()), m_heap(inputs)
        {
            buildHeap();
        }

        void enqueue(value_type value, priority_type priority);
        auto dequeue();
        iterator find(value_type value);
        void update(iterator i, priority_type priority);
        bool empty() const { return m_size == 0 ? true : false; }
        size_type size() const { return m_size; }
        iterator begin() { return iterator(&m_heap); }
        iterator end() { return iterator(m_size, &m_heap); }

      private:
        size_type m_size;
        std::vector<entry> m_heap;

        void buildHeap();
        void siftDown(size_type pos);
        void siftUp(size_type pos);
        bool isLeaf(size_type pos) const { return (pos >= m_size / 2) && (pos < m_size); }
        size_type getLeftChildPos(size_type pos) const;
        size_type getRightChildPos(size_type pos) const;
        size_type getParentPos(size_type pos) const;
        void swap(size_type first, size_type second);
        void increaseSize();
    };

    template <typename V, typename P>
    void priority_queue<V, P>::enqueue(typename priority_queue<V, P>::value_type value, typename priority_queue<V, P>::priority_type priority)
    {
        if (m_size == m_heap.size())
        {
            increaseSize();
        }

        entry newEntry{ value, priority };

        size_type pos = m_size++;
        m_heap[pos] = newEntry;

        siftUp(pos);

        return;
    }

    template <typename V, typename P>
    auto priority_queue<V, P>::dequeue()
    {
        if (empty())
        {
            throw new std::exception();
        }

        swap(0, --m_size);
        siftDown(0);

        auto item = m_heap[m_size];

        m_heap.erase(--m_heap.end());

        return item;
    }

    template <typename V, typename P>
    typename priority_queue<V, P>::iterator priority_queue<V, P>::find(V value)
    {
        iterator iter = this->end();

        for (size_type i = 0; i < m_size; ++i)
        {
            if (m_heap[i].value == value)
            {
                iter = iterator(i, &m_heap);
                break;
            }
        }

        return iter;
    }

    template <typename V, typename P>
    void priority_queue<V, P>::update(typename priority_queue<V, P>::iterator i, P priority)
    {
        i->priority = priority;

        size_type pos = i - begin();
        siftUp(pos);
        siftDown(pos);

        return;
    }

    template <typename V, typename P>
    void priority_queue<V, P>::increaseSize()
    {
        auto newCapacity = static_cast<size_type>(static_cast<double>(m_heap.size()) * 1.25 + 1);
        m_heap.resize(newCapacity);

        return;
    }

    template <typename V, typename P>
    void priority_queue<V, P>::buildHeap()
    {
        for (size_type pos = m_size / 2; pos--;)
        {
            siftDown(pos);
        }

        return;
    }

    template <typename V, typename P>
    void priority_queue<V, P>::siftDown(size_type pos)
    {
        // Invalid positions
        if ((pos < 0) || (pos >= m_size))
        {
            return;
        }

        while (!isLeaf(pos))
        {
            // Set j to pos of higher priority item
            size_type j = getLeftChildPos(pos);
            if ((j < (m_size - 1)) && (m_heap[j] < m_heap[j + 1]))
            {
                ++j;
            }

            if (m_heap[pos] >= m_heap[j])
            {
                return;
            }

            swap(pos, j);
            pos = j;
        }

        return;
    }

    template <typename V, typename P>
    void priority_queue<V, P>::siftUp(size_type pos)
    {
        size_type parentPos = getParentPos(pos);
        while ((pos != 0) && (m_heap[pos] > m_heap[parentPos]))
        {
            swap(pos, parentPos);
            pos = parentPos;
            parentPos = getParentPos(pos);
        }

        return;
    }

    template <typename V, typename P>
    void priority_queue<V, P>::swap(size_type first, size_type second)
    {
        if (first == second)
        {
            return;
        }

        auto temp = m_heap[first];
        m_heap[first] = m_heap[second];
        m_heap[second] = temp;

        return;
    }

    template <typename V, typename P>
    typename priority_queue<V, P>::size_type priority_queue<V, P>::getLeftChildPos(size_type pos) const
    {
        // No children
        if ((pos >= m_size / 2) || (pos < 0))
        {
            return static_cast<size_type>(-1);
        }

        return 2 * pos + 1;
    }

    template <typename V, typename P>
    typename priority_queue<V, P>::size_type priority_queue<V, P>::getRightChildPos(size_type pos) const
    {
        // No children
        if ((pos >= m_size / 2) || (pos < 0))
        {
            return -1;
        }

        return 2 * pos + 2;
    }

    template <typename V, typename P>
    typename priority_queue<V, P>::size_type priority_queue<V, P>::getParentPos(size_type pos) const
    {
        // No parent
        if ((pos <= 0) || (pos > m_size))
        {
            return static_cast<size_type>(-1);
        }

        return (pos - 1) / 2;
    }

    template <typename V, typename P>
    priority_queue<V, P>::iterator::iterator(const iterator& other)
    {
        m_pos = other.m_pos;
        m_data = other.m_data;
    }

    template <typename V, typename P>
    priority_queue<V, P>::iterator::iterator(iterator&& other)
    {
        m_pos = other.m_pos;
        m_data = other.m_data;

        other.m_pos = 0;
        other.m_data = nullptr;
    }

    template <typename V, typename P>
    typename priority_queue<V, P>::iterator::iterator& priority_queue<V, P>::iterator::operator=(const iterator& other)
    {
        m_pos = other.m_pos;
        m_data = other.m_data;

        return *this;
    }

    template <typename V, typename P>
    typename priority_queue<V, P>::iterator::iterator& priority_queue<V, P>::iterator::operator=(iterator&& other)
    {
        if (this != &other)
        {
            std::swap(m_pos, other.m_pos);
            std::swap(m_data, other.m_data);
        }

        return *this;
    }

    template <typename V, typename P>
    typename priority_queue<V, P>::iterator::iterator priority_queue<V, P>::iterator::operator++()
    {
        m_pos++;
        return *this;
    }

    template <typename V, typename P>
    typename priority_queue<V, P>::iterator::iterator priority_queue<V, P>::iterator::operator++(int)
    {
        auto temp = *this;
        m_pos++;
        return temp;
    }
} // namespace usu
