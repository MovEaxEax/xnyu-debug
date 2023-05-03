#pragma once
#pragma once

//
// Variable struct
//

struct Variable {
    std::string name;
    std::string type;
    std::string value;
    bool forceHex;
};



//
// Variable types check
//

bool CheckVariableType(std::string type, std::string value)
{
    if (value == "true" || value == "false") return type == "bool";

    if (value[0] == '\"' || value[0] == '\'')
    {
        if (value[value.length() - 1] == '\"' || value[value.length() - 1] == '\'') return type == "string";
        else return false;
    }

    size_t pos = 0;
    if (value[0] == '-') pos = 1;

    if (value.find(".") == std::string::npos)
    {
        if (value.find_first_not_of("0123456789abcdefABCDEF", pos) == std::string::npos || (value[pos] == '0' && (value[pos + 1] == 'x' || value[pos + 1] == 'X')))
        {
            try
            {
                long long number = std::stoll(value, &pos, 16);
                if (number < 256 && pos == 0 && type == "byte") return true;
                if (number < INT_MAX && (type == "int32" || type == "int64")) return true;
                if (number < MAXLONGLONG && (type == "int64")) return true;
            }
            catch (std::exception a)
            {
                return false;
            }
            return false;
        }
        else
        {
            try
            {
                long long number = std::stoll(value, &pos);
                if (number < 256 && pos == 0 && type == "byte") return true;
                if (number < INT_MAX && (type == "int32" || type == "int64")) return true;
                if (number < MAXLONGLONG && (type == "int64")) return true;
            }
            catch (std::exception a)
            {
                return false;
            }
            return false;
        }
    }
    else
    {
        try
        {
            float number = std::stof(value, &pos);
            if (type == "float" || type == "double") return true;
        }
        catch (std::exception a)
        {
        }
        try
        {
            double number = std::stod(value, &pos);
            if (type == "double") return true;
        }
        catch (std::exception a)
        {
            return false;
        }
        return false;
    }
    return false;
}

std::string GetValueType(std::string value)
{
    if (value == "true" || value == "false") return "bool";

    if (value[0] == '\"' || value[0] == '\'')
    {
        if (value[value.length() - 1] == '\"' || value[value.length() - 1] == '\'') return "string";
        else return "";
    }

    size_t pos = 0;
    if (value[0] == '-') pos = 1;

    if (value.find(".") == std::string::npos)
    {
        if (value.find_first_not_of("0123456789abcdefABCDEF", pos) == std::string::npos || (value[pos] == '0' && (value[pos + 1] == 'x' || value[pos + 1] == 'X')))
        {
            try
            {
                long long number = std::stoll(value, &pos, 16);
                if (number < 256 && pos == 0) return "byte";
                if (number < INT_MAX) return "int32";
                if (number < MAXLONGLONG) return "int64";
            }
            catch (std::exception a)
            {
                return "";
            }
            return "";
        }
        else
        {
            try
            {
                long long number = std::stoll(value, &pos);
                if (number < 256 && pos == 0) return "byte";
                if (number < INT_MAX) return "int32";
                if (number < MAXLONGLONG) return "int64";
            }
            catch (std::exception a)
            {
                return "";
            }
            return "";
        }
    }
    else
    {
        try
        {
            float number = std::stof(value, &pos);
            return "float";
        }
        catch (std::exception a)
        {
        }
        try
        {
            double number = std::stod(value, &pos);
            return "double";
        }
        catch (std::exception a)
        {
            return "";
        }
        return "";
    }
    return "";
}



//
// Variable getters and setters
//

void SetVariable(Variable* variable, std::string value)
{
    if (CheckVariableType(variable->type, value)) variable->value = value;
    else variable->value = "none";
}

std::string GetVariableString(Variable* variable)
{
    std::string result = variable->value;
    return result.substr(1, result.length() - 2);
}

bool GetVariableBool(Variable* variable)
{
    return variable->value == "true" ? true : false;
}

BYTE GetVariableByte(Variable* variable)
{
    BYTE val;
    if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val = (BYTE)std::stoi(variable->value, 0, 16);
    else val = (BYTE)std::stoi(variable->value);
    return val;
}

int GetVariableInt32(Variable* variable)
{
    int val;
    if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val = std::stoi(variable->value, 0, 16);
    else val = std::stoi(variable->value);
    return val;
    return std::stoi(variable->value);
}

long long GetVariableInt64(Variable* variable)
{
    long long val;
    if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val = std::stoi(variable->value, 0, 16);
    else val = std::stoi(variable->value);
    return val;
    return std::stoll(variable->value);
}

float GetVariableFloat(Variable* variable)
{
    return std::stof(variable->value);
}

double GetVariableDouble(Variable* variable)
{
    return std::stod(variable->value);
}

std::string GetVariableString(std::string value)
{
    std::string result = value;
    return result.substr(1, result.length() - 2);
}

bool GetVariableBool(std::string value)
{
    return value == "true" ? true : false;
}

BYTE GetVariableByte(std::string value)
{
    BYTE val;
    if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val = (BYTE)std::stoi(value, 0, 16);
    else val = (BYTE)std::stoi(value);
    return val;
}

int GetVariableInt32(std::string value)
{
    int val;
    if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val = std::stoi(value, 0, 16);
    else val = std::stoi(value);
    return val;
    return std::stoi(value);
}

long long GetVariableInt64(std::string value)
{
    long long val;
    if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val = std::stoi(value, 0, 16);
    else val = std::stoi(value);
    return val;
    return std::stoll(value);
}

float GetVariableFloat(std::string value)
{
    return std::stof(value);
}

double GetVariableDouble(std::string value)
{
    return std::stod(value);
}



//
// Variable to maths conversion
//

void VariableAdd(Variable* variable, std::string value)
{
    if (variable->value == "none" || value == "none") return;
    if (!CheckVariableType(variable->type, value) || variable->type == "string" || variable->type == "bool")
    {
        variable->value = "none";
        return;
    }

    try
    {
        if (variable->type == "byte")
        {
            BYTE val1;
            BYTE val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = (BYTE)std::stoi(variable->value, 0, 16);
            else val1 = (BYTE)std::stoi(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = (BYTE)std::stoi(value, 0, 16);
            else val2 = (BYTE)std::stoi(value);
            variable->value = std::to_string(val1 + val2);
            return;
        }
        if (variable->type == "int32")
        {
            int val1;
            int val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = std::stoi(variable->value, 0, 16);
            else val1 = std::stoi(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = std::stoi(value, 0, 16);
            else val2 = std::stoi(value);
            variable->value = std::to_string(val1 + val2);
            return;
        }
        if (variable->type == "int64")
        {
            long long val1;
            long long val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = std::stoll(variable->value, 0, 16);
            else val1 = std::stoll(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = std::stoll(value, 0, 16);
            else val2 = std::stoll(value);
            variable->value = std::to_string(val1 + val2);
            return;
        }
        if (variable->type == "float")
        {
            float val1 = std::stof(variable->value);
            float val2 = std::stof(value);
            variable->value = std::to_string(val1 + val2);
            return;
        }
        if (variable->type == "double")
        {
            double val1 = std::stod(variable->value);
            double val2 = std::stod(value);
            variable->value = std::to_string(val1 + val2);
            return;
        }
        variable->value = "none";
    }
    catch (std::exception e)
    {
        variable->value = "none";
    }
}

void VariableAdd(Variable* variableDST, Variable* variableSRC)
{
    if (variableDST->value == "none" || variableSRC->value == "none") return;
    if (!CheckVariableType(variableDST->type, variableSRC->value) || variableDST->type == "string" || variableSRC->type == "string" || variableDST->type == "bool" || variableSRC->type == "bool")
    {
        variableDST->value = "none";
        return;
    }

    try
    {
        if (variableDST->type == "byte")
        {
            BYTE val1;
            BYTE val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = (BYTE)std::stoi(variableDST->value, 0, 16);
            else val1 = (BYTE)std::stoi(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = (BYTE)std::stoi(variableSRC->value, 0, 16);
            else val2 = (BYTE)std::stoi(variableSRC->value);
            variableDST->value = std::to_string(val1 + val2);
            return;
        }
        if (variableDST->type == "int32")
        {
            int val1;
            int val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = std::stoi(variableDST->value, 0, 16);
            else val1 = std::stoi(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = std::stoi(variableSRC->value, 0, 16);
            else val2 = std::stoi(variableSRC->value);
            variableDST->value = std::to_string(val1 + val2);
            return;
        }
        if (variableDST->type == "int64")
        {
            long long val1;
            long long val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = (BYTE)std::stoll(variableDST->value, 0, 16);
            else val1 = std::stoll(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = (BYTE)std::stoll(variableSRC->value, 0, 16);
            else val2 = std::stoll(variableSRC->value);
            variableDST->value = std::to_string(val1 + val2);
            return;
        }
        if (variableDST->type == "float")
        {
            float val1 = std::stof(variableDST->value);
            float val2 = std::stof(variableSRC->value);
            variableDST->value = std::to_string(val1 + val2);
            return;
        }
        if (variableDST->type == "double")
        {
            double val1 = std::stod(variableDST->value);
            double val2 = std::stod(variableSRC->value);
            variableDST->value = std::to_string(val1 + val2);
            return;
        }
        variableDST->value = "none";
    }
    catch (std::exception e)
    {
        variableDST->value = "none";
    }
}

void VariableSubtract(Variable* variable, std::string value)
{
    if (variable->value == "none" || value == "none") return;
    if (!CheckVariableType(variable->type, value) || variable->type == "string" || variable->type == "bool")
    {
        variable->value = "none";
        return;
    }

    try
    {
        if (variable->type == "byte")
        {
            BYTE val1;
            BYTE val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = (BYTE)std::stoi(variable->value, 0, 16);
            else val1 = (BYTE)std::stoi(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = (BYTE)std::stoi(value, 0, 16);
            else val2 = (BYTE)std::stoi(value);
            variable->value = std::to_string(val1 - val2);
            return;
        }
        if (variable->type == "int32")
        {
            int val1;
            int val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = std::stoi(variable->value, 0, 16);
            else val1 = std::stoi(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = std::stoi(value, 0, 16);
            else val2 = std::stoi(value);
            variable->value = std::to_string(val1 - val2);
            return;
        }
        if (variable->type == "int64")
        {
            long long val1;
            long long val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = std::stoll(variable->value, 0, 16);
            else val1 = std::stoll(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = std::stoll(value, 0, 16);
            else val2 = std::stoll(value);
            variable->value = std::to_string(val1 - val2);
            return;
        }
        if (variable->type == "float")
        {
            float val1 = std::stof(variable->value);
            float val2 = std::stof(value);
            variable->value = std::to_string(val1 - val2);
            return;
        }
        if (variable->type == "double")
        {
            double val1 = std::stod(variable->value);
            double val2 = std::stod(value);
            variable->value = std::to_string(val1 - val2);
            return;
        }
        variable->value = "none";
    }
    catch (std::exception e)
    {
        variable->value = "none";
    }
}

void VariableSubtract(Variable* variableDST, Variable* variableSRC)
{
    if (variableDST->value == "none" || variableSRC->value == "none") return;
    if (!CheckVariableType(variableDST->type, variableSRC->value) || variableDST->type == "string" || variableSRC->type == "string" || variableDST->type == "bool" || variableSRC->type == "bool")
    {
        variableDST->value = "none";
        return;
    }

    try
    {
        if (variableDST->type == "byte")
        {
            BYTE val1;
            BYTE val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = (BYTE)std::stoi(variableDST->value, 0, 16);
            else val1 = (BYTE)std::stoi(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = (BYTE)std::stoi(variableSRC->value, 0, 16);
            else val2 = (BYTE)std::stoi(variableSRC->value);
            variableDST->value = std::to_string(val1 - val2);
            return;
        }
        if (variableDST->type == "int32")
        {
            int val1;
            int val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = std::stoi(variableDST->value, 0, 16);
            else val1 = std::stoi(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = std::stoi(variableSRC->value, 0, 16);
            else val2 = std::stoi(variableSRC->value);
            variableDST->value = std::to_string(val1 - val2);
            return;
        }
        if (variableDST->type == "int64")
        {
            long long val1;
            long long val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = (BYTE)std::stoll(variableDST->value, 0, 16);
            else val1 = std::stoll(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = (BYTE)std::stoll(variableSRC->value, 0, 16);
            else val2 = std::stoll(variableSRC->value);
            variableDST->value = std::to_string(val1 - val2);
            return;
        }
        if (variableDST->type == "float")
        {
            float val1 = std::stof(variableDST->value);
            float val2 = std::stof(variableSRC->value);
            variableDST->value = std::to_string(val1 - val2);
            return;
        }
        if (variableDST->type == "double")
        {
            double val1 = std::stod(variableDST->value);
            double val2 = std::stod(variableSRC->value);
            variableDST->value = std::to_string(val1 - val2);
            return;
        }
        variableDST->value = "none";
    }
    catch (std::exception e)
    {
        variableDST->value = "none";
    }
}

void VariableMultiply(Variable* variable, std::string value)
{
    if (variable->value == "none" || value == "none") return;
    if (!CheckVariableType(variable->type, value) || variable->type == "string" || variable->type == "bool")
    {
        variable->value = "none";
        return;
    }

    try
    {
        if (variable->type == "byte")
        {
            BYTE val1;
            BYTE val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = (BYTE)std::stoi(variable->value, 0, 16);
            else val1 = (BYTE)std::stoi(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = (BYTE)std::stoi(value, 0, 16);
            else val2 = (BYTE)std::stoi(value);
            variable->value = std::to_string(val1 * val2);
            return;
        }
        if (variable->type == "int32")
        {
            int val1;
            int val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = std::stoi(variable->value, 0, 16);
            else val1 = std::stoi(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = std::stoi(value, 0, 16);
            else val2 = std::stoi(value);
            variable->value = std::to_string(val1 * val2);
            return;
        }
        if (variable->type == "int64")
        {
            long long val1;
            long long val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = std::stoll(variable->value, 0, 16);
            else val1 = std::stoll(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = std::stoll(value, 0, 16);
            else val2 = std::stoll(value);
            variable->value = std::to_string(val1 * val2);
            return;
        }
        if (variable->type == "float")
        {
            float val1 = std::stof(variable->value);
            float val2 = std::stof(value);
            variable->value = std::to_string(val1 * val2);
            return;
        }
        if (variable->type == "double")
        {
            double val1 = std::stod(variable->value);
            double val2 = std::stod(value);
            variable->value = std::to_string(val1 * val2);
            return;
        }
        variable->value = "none";
    }
    catch (std::exception e)
    {
        variable->value = "none";
    }
}

void VariableMultiply(Variable* variableDST, Variable* variableSRC)
{
    if (variableDST->value == "none" || variableSRC->value == "none") return;
    if (!CheckVariableType(variableDST->type, variableSRC->value) || variableDST->type == "string" || variableSRC->type == "string" || variableDST->type == "bool" || variableSRC->type == "bool")
    {
        variableDST->value = "none";
        return;
    }

    try
    {
        if (variableDST->type == "byte")
        {
            BYTE val1;
            BYTE val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = (BYTE)std::stoi(variableDST->value, 0, 16);
            else val1 = (BYTE)std::stoi(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = (BYTE)std::stoi(variableSRC->value, 0, 16);
            else val2 = (BYTE)std::stoi(variableSRC->value);
            variableDST->value = std::to_string(val1 * val2);
            return;
        }
        if (variableDST->type == "int32")
        {
            int val1;
            int val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = std::stoi(variableDST->value, 0, 16);
            else val1 = std::stoi(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = std::stoi(variableSRC->value, 0, 16);
            else val2 = std::stoi(variableSRC->value);
            variableDST->value = std::to_string(val1 * val2);
            return;
        }
        if (variableDST->type == "int64")
        {
            long long val1;
            long long val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = (BYTE)std::stoll(variableDST->value, 0, 16);
            else val1 = std::stoll(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = (BYTE)std::stoll(variableSRC->value, 0, 16);
            else val2 = std::stoll(variableSRC->value);
            variableDST->value = std::to_string(val1 * val2);
            return;
        }
        if (variableDST->type == "float")
        {
            float val1 = std::stof(variableDST->value);
            float val2 = std::stof(variableSRC->value);
            variableDST->value = std::to_string(val1 * val2);
            return;
        }
        if (variableDST->type == "double")
        {
            double val1 = std::stod(variableDST->value);
            double val2 = std::stod(variableSRC->value);
            variableDST->value = std::to_string(val1 * val2);
            return;
        }
        variableDST->value = "none";
    }
    catch (std::exception e)
    {
        variableDST->value = "none";
    }
}

void VariableDivide(Variable* variable, std::string value)
{
    if (variable->value == "none" || value == "none") return;
    if (!CheckVariableType(variable->type, value) || variable->type == "string" || variable->type == "bool")
    {
        variable->value = "none";
        return;
    }

    if (value.find_first_not_of("xX.-0", 0) == std::string::npos)
    {
        variable->value = "none";
        return;
    }

    try
    {
        if (variable->type == "byte")
        {
            BYTE val1;
            BYTE val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = (BYTE)std::stoi(variable->value, 0, 16);
            else val1 = (BYTE)std::stoi(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = (BYTE)std::stoi(value, 0, 16);
            else val2 = (BYTE)std::stoi(value);
            variable->value = std::to_string(val1 / val2);
            return;
        }
        if (variable->type == "int32")
        {
            int val1;
            int val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = std::stoi(variable->value, 0, 16);
            else val1 = std::stoi(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = std::stoi(value, 0, 16);
            else val2 = std::stoi(value);
            variable->value = std::to_string(val1 / val2);
            return;
        }
        if (variable->type == "int64")
        {
            long long val1;
            long long val2;
            if (variable->value[0] == '0' && (variable->value[1] == 'x' || variable->value[1] == 'X')) val1 = std::stoll(variable->value, 0, 16);
            else val1 = std::stoll(variable->value);
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) val2 = std::stoll(value, 0, 16);
            else val2 = std::stoll(value);
            variable->value = std::to_string(val1 / val2);
            return;
        }
        if (variable->type == "float")
        {
            float val1 = std::stof(variable->value);
            float val2 = std::stof(value);
            variable->value = std::to_string(val1 / val2);
            return;
        }
        if (variable->type == "double")
        {
            double val1 = std::stod(variable->value);
            double val2 = std::stod(value);
            variable->value = std::to_string(val1 / val2);
            return;
        }
        variable->value = "none";
    }
    catch (std::exception e)
    {
        variable->value = "none";
    }
}

void VariableDivide(Variable* variableDST, Variable* variableSRC)
{
    if (variableDST->value == "none" || variableSRC->value == "none") return;
    if (!CheckVariableType(variableDST->type, variableSRC->value) || variableDST->type == "string" || variableSRC->type == "string" || variableDST->type == "bool" || variableSRC->type == "bool")
    {
        variableDST->value = "none";
        return;
    }

    if (variableSRC->value.find_first_not_of("xX.-0", 0) == std::string::npos)
    {
        variableDST->value = "none";
        return;
    }

    try
    {
        if (variableDST->type == "byte")
        {
            BYTE val1;
            BYTE val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = (BYTE)std::stoi(variableDST->value, 0, 16);
            else val1 = (BYTE)std::stoi(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = (BYTE)std::stoi(variableSRC->value, 0, 16);
            else val2 = (BYTE)std::stoi(variableSRC->value);
            variableDST->value = std::to_string(val1 / val2);
            return;
        }
        if (variableDST->type == "int32")
        {
            int val1;
            int val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = std::stoi(variableDST->value, 0, 16);
            else val1 = std::stoi(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = std::stoi(variableSRC->value, 0, 16);
            else val2 = std::stoi(variableSRC->value);
            variableDST->value = std::to_string(val1 / val2);
            return;
        }
        if (variableDST->type == "int64")
        {
            long long val1;
            long long val2;
            if (variableDST->value[0] == '0' && (variableDST->value[1] == 'x' || variableDST->value[1] == 'X')) val1 = (BYTE)std::stoll(variableDST->value, 0, 16);
            else val1 = std::stoll(variableDST->value);
            if (variableSRC->value[0] == '0' && (variableSRC->value[1] == 'x' || variableSRC->value[1] == 'X')) val2 = (BYTE)std::stoll(variableSRC->value, 0, 16);
            else val2 = std::stoll(variableSRC->value);
            variableDST->value = std::to_string(val1 / val2);
            return;
        }
        if (variableDST->type == "float")
        {
            float val1 = std::stof(variableDST->value);
            float val2 = std::stof(variableSRC->value);
            variableDST->value = std::to_string(val1 / val2);
            return;
        }
        if (variableDST->type == "double")
        {
            double val1 = std::stod(variableDST->value);
            double val2 = std::stod(variableSRC->value);
            variableDST->value = std::to_string(val1 / val2);
            return;
        }
        variableDST->value = "none";
    }
    catch (std::exception e)
    {
        variableDST->value = "none";
    }
}


