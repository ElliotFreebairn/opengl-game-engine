class Side
{
public:
    enum Value : uint8_t
    {
        Front,
        Back,
        Left,
        Right,
        Top,
        Bottom
    };

    Side() = default; // use compiler generated version of that function
    constexpr Side(Value aSide) : value(aSide) { }; // constexpr specifies the value of an object
                                                    // or a function can be evaled at run time
    std::string asString()
    {
        switch (value)
        {
            case Front:
                break;
            case Back:
                break;
            case Left:
                return "Left";
            case Right:
                return "Right";
            case Top:
                break;
            case Bottom:
                break;
        }
        return "None";
    }

private:
    Value value;
};
