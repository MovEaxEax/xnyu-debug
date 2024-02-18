#include "pch.h"
#include "Conversions.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "Variable.h"
#include "xNyuTASLanguageDatatypes.h"



// --- Functions ---

// ---------- Jumps ----------

Instruction Create_NTLI_JMP(int address, std::string replacer)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::JMP;
    if (replacer != "") instruction.params.push_back(replacer);
    instruction.address = address;
    return instruction;
}

Instruction Create_NTLI_JMPOFF(int address, std::string replacer)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::JMPOFF;
    if (replacer != "") instruction.params.push_back(replacer);
    instruction.address = address;
    return instruction;
}

Instruction Create_NTLI_CALLDBG(std::string name)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::CALLDBG;
    instruction.params.push_back(name);
    return instruction;
}





// ---------- Returning ----------

Instruction Create_NTLI_RET()
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::RET;
    return instruction;
}

Instruction Create_NTLI_RETSET(int address)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::RETSET;
    instruction.address = address;
    return instruction;
}





// ---------- TAS Variable Management ----------

Instruction Create_NTLI_CREATE_VAR(std::string name, std::string type)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::CREATE_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(type);
    return instruction;
}

Instruction Create_NTLI_REMOVE_VAR(std::string name)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::REMOVE_VAR;
    instruction.params.push_back(name);
    return instruction;
}





// ---------- TAS Variable Delegation ----------

Instruction Create_NTLI_SET_VAR_PLAIN(std::string name, std::string value)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::SET_VAR_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(value);
    return instruction;
}

Instruction Create_NTLI_PLUS_VAR_PLAIN(std::string name, std::string factor)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::PLUS_VAR_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(factor);
    return instruction;
}

Instruction Create_NTLI_MINUS_VAR_PLAIN(std::string name, std::string factor)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MINUS_VAR_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(factor);
    return instruction;
}

Instruction Create_NTLI_MULTI_VAR_PLAIN(std::string name, std::string factor)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MULTI_VAR_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(factor);
    return instruction;
}

Instruction Create_NTLI_DIVIDE_VAR_PLAIN(std::string name, std::string factor)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::DIVIDE_VAR_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(factor);
    return instruction;
}



Instruction Create_NTLI_SET_VAR_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::SET_VAR_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_PLUS_VAR_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::PLUS_VAR_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_MINUS_VAR_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MINUS_VAR_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_MULTI_VAR_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MULTI_VAR_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_DIVIDE_VAR_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::DIVIDE_VAR_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}



Instruction Create_NTLI_SET_VAR_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::SET_VAR_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_PLUS_VAR_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::PLUS_VAR_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_MINUS_VAR_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MINUS_VAR_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_MULTI_VAR_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MULTI_VAR_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_DIVIDE_VAR_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::DIVIDE_VAR_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}







// ---------- Debug Variable Delegation ----------

Instruction Create_NTLI_SET_VAR_DBG_PLAIN(std::string name, std::string value)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::SET_VAR_DBG_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(value);
    return instruction;
}

Instruction Create_NTLI_PLUS_VAR_DBG_PLAIN(std::string name, std::string factor)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::PLUS_VAR_DBG_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(factor);
    return instruction;
}

Instruction Create_NTLI_MINUS_VAR_DBG_PLAIN(std::string name, std::string factor)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MINUS_VAR_DBG_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(factor);
    return instruction;
}

Instruction Create_NTLI_MULTI_VAR_DBG_PLAIN(std::string name, std::string factor)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MULTI_VAR_DBG_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(factor);
    return instruction;
}

Instruction Create_NTLI_DIVIDE_VAR_DBG_PLAIN(std::string name, std::string factor)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::DIVIDE_VAR_DBG_PLAIN;
    instruction.params.push_back(name);
    instruction.params.push_back(factor);
    return instruction;
}



Instruction Create_NTLI_SET_VAR_DBG_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::SET_VAR_DBG_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_PLUS_VAR_DBG_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::PLUS_VAR_DBG_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_MINUS_VAR_DBG_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MINUS_VAR_DBG_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_MULTI_VAR_DBG_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MULTI_VAR_DBG_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_DIVIDE_VAR_DBG_FROM_VAR(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::DIVIDE_VAR_DBG_FROM_VAR;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}



Instruction Create_NTLI_SET_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::SET_VAR_DBG_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_PLUS_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::PLUS_VAR_DBG_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_MINUS_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MINUS_VAR_DBG_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_MULTI_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::MULTI_VAR_DBG_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}

Instruction Create_NTLI_DIVIDE_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::DIVIDE_VAR_DBG_FROM_VAR_DBG;
    instruction.params.push_back(name);
    instruction.params.push_back(var);
    return instruction;
}





// ---------- TAS Inputs ----------

Instruction Create_NTLI_FRAME(std::vector<std::string> inputs)
{
    Instruction instruction = Instruction();
    instruction.opcode = OpCode::FRAME;
    for (int i = 0; i < inputs.size(); i++) instruction.params.push_back(inputs[i]);
    return instruction;
}

