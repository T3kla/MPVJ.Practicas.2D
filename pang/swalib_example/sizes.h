#pragma once

class Size
{
  public:
    enum Value : unsigned char
    {
        None,
        Default,
        S,
        M,
        B,
        L,
    };

    Size() = default;

    Size(Value value) : value(value)
    {
    }

    operator Value() const
    {
        return value;
    }

    explicit operator bool() = delete;

    bool operator==(Size a) const
    {
        return value == a.value;
    }

    bool operator!=(Size a) const
    {
        return value != a.value;
    }

    bool operator==(Size::Value a) const
    {
        return value == a;
    }

    bool operator!=(Size::Value a) const
    {
        return value != a;
    }

    static Size OneSmaller(Size Value)
    {
        switch (Value)
        {
        case Size::L:
            return Size::B;
        case Size::B:
            return Size::M;
        case Size::M:
            return Size::S;
        default:
            return Size::None;
        }
    }

    static Size OneBigger(Size Value)
    {
        switch (Value)
        {
        case Size::S:
            return Size::M;
        case Size::M:
            return Size::B;
        case Size::B:
            return Size::L;
        default:
            return Size::None;
        }
    }

    Size OneSmaller()
    {
        switch (value)
        {
        case Size::L:
            return Size::B;
        case Size::B:
            return Size::M;
        case Size::M:
            return Size::S;
        default:
            return Size::None;
        }
    }

    Size OneBigger(Size value)
    {
        switch (value)
        {
        case Size::S:
            return Size::M;
        case Size::M:
            return Size::B;
        case Size::B:
            return Size::L;
        default:
            return Size::None;
        }
    }

  private:
    Value value;
};
