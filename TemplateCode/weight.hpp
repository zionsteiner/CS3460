#include <cstdint>
#include <ratio>

namespace usu
{
    template <typename R, typename T = std::uint64_t>
    class weight
    {
      public:
        using ratio = R;
        using countType = T;

        weight()
        {
            m_count = 0;
        }
        weight(T count)
        {
            m_count = count ? count : 0;
        }

        T count() const
        {
            return m_count;
        }

        weight operator+(const weight& rhs)
        {
            return weight<R, T>(static_cast<T>(count() + rhs.count()));
        }

        weight operator-(const weight& rhs)
        {
            T diff = count() - rhs.count();
            if (diff < 0)
            {
                diff = 0;
            }

            return weight<R, T>(diff);
        }

      private:
        T m_count;
    };

    using microgram = weight<std::ratio<1, 1000000>>;

    using gram = weight<std::ratio<1, 1>>;

    using kilogram = weight<std::ratio<1000, 1>>;

    using ounce = weight<std::ratio<28349523125, 1000000000>, double>;

    using pound = weight<std::ratio<45359237, 100000>, double>;

    using ton = weight<std::ratio<90718474, 100>, double>;

    template <typename R, typename T, typename S>
    weight<R, T> operator*(const weight<R, T>& lhs, S rhs)
    {
        return weight<R, T>(static_cast<T>(lhs.count() * rhs));
    }

    template <typename R, typename T, typename S>
    weight<R, T> operator*(S lhs, const weight<R, T>& rhs)
    {
        return weight<R, T>(static_cast<T>(lhs * rhs.count()));
    }

    template <typename To, typename From>
    To weight_cast(From& from)
    {
        double ratio = static_cast<double>(To::ratio::den * From::ratio::num) / (To::ratio::num * From::ratio::den);

        return To(static_cast<typename To::countType>(ratio * from.count()));
    }
} // namespace usu