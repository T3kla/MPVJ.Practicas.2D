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

    Size(Value value);

    operator Value() const;

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

    static Size OneSmaller(Size Value);
    static Size OneBigger(Size Value);
    Size OneSmaller();
    Size OneBigger();

  private:
    Value value;
};
