#include "size.h"

Size::Size(Value value) : value(value)
{
}

Size::operator Value() const
{
    return value;
}

Size Bigger(Size size)
{
    switch (size)
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

Size Smaller(Size size)
{
    switch (size)
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

Size Size::OneSmaller(Size size)
{
    return Smaller(size);
}

Size Size::OneBigger(Size size)
{
    return Bigger(size);
}

Size Size::OneSmaller()
{
    return Smaller(value);
}

Size Size::OneBigger()
{
    return Bigger(value);
}
