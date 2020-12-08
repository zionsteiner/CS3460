#pragma once

#include <cstdint>
#include <utility>

namespace usu
{
    template <typename T>
    class shared_ptr
    {
      public:
        shared_ptr(T* rawPtr) :
            m_rawPtr(nullptr),
            m_refCount(nullptr)
        {
            m_rawPtr = rawPtr;
            m_refCount = new std::size_t(1);
        }

        shared_ptr(const shared_ptr& other) :
            m_rawPtr(nullptr),
            m_refCount(nullptr)
        {
            *this = other;
        }

        shared_ptr(shared_ptr&& other) :
            m_rawPtr(nullptr),
            m_refCount(nullptr)
        {
            *this = other;
        }

        ~shared_ptr()
        {
            cleanup();
        }

        void cleanup()
        {
            if (m_refCount != nullptr)
            {
                (*m_refCount)--;

                if (*m_refCount == 0)
                {
                    delete m_rawPtr;
                    delete m_refCount;
                }
            }
        }

        T* get() const { return m_rawPtr; }
        std::size_t use_count() const { return *m_refCount; }

        // Operators
        shared_ptr& operator=(const shared_ptr& rhs)
        {
            if (this != &rhs)
            {
                cleanup();

                m_rawPtr = rhs.m_rawPtr;
                m_refCount = rhs.m_refCount;
                (*m_refCount)++;
            }

            return *this;
        }

        shared_ptr& operator=(shared_ptr&& rhs)
        {
            std::swap(m_rawPtr, rhs.m_rawPtr);
            std::swap(m_refCount, rhs.m_refCount);

            return *this;
        }

        T* operator->() const
        {
            return get();
        }

        T& operator*() const
        {
            return *m_rawPtr;
        }

      private:
        T* m_rawPtr;
        std::size_t* m_refCount;
    };

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T>
    class shared_ptr<T[]>
    {
      public:
        shared_ptr(T* rawPtr, std::size_t arrSize) :
            m_rawPtr(nullptr),
            m_arrSize(0),
            m_refCount(nullptr)
        {
            m_rawPtr = rawPtr;
            m_arrSize = arrSize;
            m_refCount = new std::size_t(1);
        }

        shared_ptr(const shared_ptr& other) :
            m_rawPtr(nullptr),
            m_arrSize(0),
            m_refCount(nullptr)
        {
            *this = other;
        }

        shared_ptr(shared_ptr&& other) :
            m_rawPtr(nullptr),
            m_arrSize(0),
            m_refCount(nullptr)
        {
            *this = other;
        }

        ~shared_ptr()
        {
            cleanup();
        }

        void cleanup()
        {
            if (m_refCount != nullptr)
            {
                (*m_refCount)--;
                if (*m_refCount == 0)
                {
                    delete[] m_rawPtr;
                    delete m_refCount;
                }
            }
        }

        std::size_t size() const { return m_arrSize; }

        // Operators
        shared_ptr& operator=(const shared_ptr& rhs)
        {
            if (this != &rhs)
            {
                cleanup();

                m_rawPtr = rhs.m_rawPtr;
                m_arrSize = rhs.m_arrSize;
                m_refCount = rhs.m_refCount;
                (*m_refCount)++;
            }

            return *this;
        }

        shared_ptr& operator=(shared_ptr&& rhs)
        {
            std::swap(m_rawPtr, rhs.m_rawPtr);
            std::swap(m_arrSize, rhs.m_arrSize);
            std::swap(m_refCount, rhs.m_refCount);

            return *this;
        }

        T& operator[](std::size_t index) const
        {
            return m_rawPtr[index];
        }

      private:
        T* m_rawPtr;
        std::size_t m_arrSize;
        std::size_t* m_refCount;
    };

    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }
} // namespace usu