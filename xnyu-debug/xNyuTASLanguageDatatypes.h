#pragma once

// --- Enums ---
enum OpCode : BYTE
{
    JMP = 1,
    JMPOFF = 2,
    IF = 3,
    RET = 4,
    RETSET = 5,
    CALLDBG = 6,
    LOG = 7,
    FRAME = 8,

    CREATE_VAR = 9,
    REMOVE_VAR = 10,

    SET_VAR_PLAIN = 11,
    PLUS_VAR_PLAIN = 12,
    MINUS_VAR_PLAIN = 13,
    MULTI_VAR_PLAIN = 14,
    DIVIDE_VAR_PLAIN = 15,
    SET_VAR_FROM_VAR = 16,
    PLUS_VAR_FROM_VAR = 17,
    MINUS_VAR_FROM_VAR = 18,
    MULTI_VAR_FROM_VAR = 19,
    DIVIDE_VAR_FROM_VAR = 20,
    SET_VAR_FROM_VAR_DBG = 21,
    PLUS_VAR_FROM_VAR_DBG = 22,
    MINUS_VAR_FROM_VAR_DBG = 23,
    MULTI_VAR_FROM_VAR_DBG = 24,
    DIVIDE_VAR_FROM_VAR_DBG = 25,

    SET_VAR_DBG_PLAIN = 26,
    PLUS_VAR_DBG_PLAIN = 27,
    MINUS_VAR_DBG_PLAIN = 28,
    MULTI_VAR_DBG_PLAIN = 29,
    DIVIDE_VAR_DBG_PLAIN = 30,
    SET_VAR_DBG_FROM_VAR = 31,
    PLUS_VAR_DBG_FROM_VAR = 32,
    MINUS_VAR_DBG_FROM_VAR = 33,
    MULTI_VAR_DBG_FROM_VAR = 34,
    DIVIDE_VAR_DBG_FROM_VAR = 35,
    SET_VAR_DBG_FROM_VAR_DBG = 36,
    PLUS_VAR_DBG_FROM_VAR_DBG = 37,
    MINUS_VAR_DBG_FROM_VAR_DBG = 38,
    MULTI_VAR_DBG_FROM_VAR_DBG = 39,
    DIVIDE_VAR_DBG_FROM_VAR_DBG = 40,

    CREATEFILE = 41,
    WRITEFILE = 42,
};



// --- Structs ---
struct Instruction
{
    OpCode opcode;
    std::vector<std::string> params;
    int address;
};

struct Registers
{
    int rInt32;
    long long rInt64;
    float rFloat;
    double rDouble;
    BYTE rByte;
    std::string rString;
};

struct Stack
{
    std::vector<int> returns;
};

struct NTLScript
{
    std::vector<Instruction> instructions;
    std::vector<std::vector<Variable>> variables;
    int instructionpointer;
    int depthpointer;
    std::vector<int> stackpointer;
    int entrypoint;
    Registers registers;
    Stack stack;
    bool init;
};

struct CodeBlock
{
    std::string name;
    std::string content;
};

struct CodeBlockFunctional
{
    std::string name;
    std::vector<std::string> parameter;
    std::string content;
};

struct FunctionSignature
{
    std::string name;
    std::string returntype;
    std::vector<std::string> parameter;
    std::string content;
    std::vector<Instruction> instructions;
    std::string uuid;
    int address;
};



