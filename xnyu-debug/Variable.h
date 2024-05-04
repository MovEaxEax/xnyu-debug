#pragma once

#undef VOID
enum class VariableType : int
{
    UNKNOWN = 0,
    BYTE = 1,
    BOOL = 2,
    INT32 = 3,
    INT64 = 4,
    FLOAT = 5,
    DOUBLE = 6,
    STRING = 7,
    VOID = 8
};

using VariableData = std::variant<byte, bool, int, long long, float, double, std::string>;
class Variable {
public:
    template<typename T>
    Variable(T value) : data(value)
    {
        null = false;
        setType<T>();
    }

    Variable(VariableType _type)
    {
        null = true;
        type = _type;
    }

    Variable(const std::string& value, VariableType type)
    {
        null = false;
        std::istringstream iss(value);
        switch (type) {
        case VariableType::BYTE:
        {
            int temp;
            iss >> std::hex >> temp;
            data = static_cast<byte>(temp);
        }
        break;
        case VariableType::BOOL:
            data = (value == "true" || value == "1" || value == "0x1");
            break;
        case VariableType::INT32:
            iss >> std::hex >> std::get<int>(data);
            break;
        case VariableType::INT64:
            iss >> std::hex >> std::get<long long>(data);
            break;
        case VariableType::FLOAT:
            iss >> std::get<float>(data);
            break;
        case VariableType::DOUBLE:
            iss >> std::get<double>(data);
            break;
        case VariableType::STRING:
            data = value;
            break;
        default: throw std::invalid_argument("Unknown type");
        }
    }

    template<typename T>
    void setValue(T value) {
        null = false;
        data = value;
    }

    VariableData getValue() const
    {
        return data;
    }

    template<typename T>
    T getValueAs() const {
        return std::get<T>(data);
    }

    VariableType getType() const {
        return type;
    }

    byte getByte() const
    {
        return std::get<byte>(data);
    }

    bool getBool() const
    {
        return std::get<byte>(data);
    }

    int getInt32() const
    {
        return std::get<byte>(data);
    }

    long long getInt64() const
    {
        return std::get<long long>(data);
    }

    float getFloat() const
    {
        return std::get<float>(data);
    }

    double getDouble() const
    {
        return std::get<double>(data);
    }

    std::string getString() const
    {
        return std::get<std::string>(data);
    }

    void setNull(bool value)
    {
        null = value;
    }

    bool isNull()
    {
        return null;
    }

private:
    VariableData data;
    VariableType type;
    bool null = false;

    template<typename T>
    void setType() {
        if constexpr (std::is_same_v<T, byte>) type = VariableType::BYTE;
        else if constexpr (std::is_same_v<T, bool>) type = VariableType::BOOL;
        else if constexpr (std::is_same_v<T, int>) type = VariableType::INT32;
        else if constexpr (std::is_same_v<T, long long>) type = VariableType::INT64;
        else if constexpr (std::is_same_v<T, float>) type = VariableType::FLOAT;
        else if constexpr (std::is_same_v<T, double>) type = VariableType::DOUBLE;
        else if constexpr (std::is_same_v<T, std::string>) type = VariableType::STRING;
        else type = VariableType::UNKNOWN;
    }
};


