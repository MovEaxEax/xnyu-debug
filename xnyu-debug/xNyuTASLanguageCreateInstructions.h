#pragma once

// --- Functions ---


#include "pch.h"
#include "Conversions.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "Variable.h"
#include "xNyuTASLanguageDatatypes.h"



// --- Functions ---

// ---------- Jumps ----------
Instruction Create_NTLI_JMP(int address, std::string replacer = "");
Instruction Create_NTLI_JMPOFF(int address, std::string replacer = "");

// ---------- TAS Variable Management ----------
Instruction Create_NTLI_CREATE_VAR(std::string name, std::string type);
Instruction Create_NTLI_REMOVE_VAR(std::string name);

// ---------- Returning ----------
Instruction Create_NTLI_RET();
Instruction Create_NTLI_RETSET(int address);
Instruction Create_NTLI_CALLDBG(std::string name);

// ---------- TAS Variable Delegation ----------
Instruction Create_NTLI_SET_VAR_PLAIN(std::string name, std::string value);
Instruction Create_NTLI_PLUS_VAR_PLAIN(std::string name, std::string factor);
Instruction Create_NTLI_MINUS_VAR_PLAIN(std::string name, std::string factor);
Instruction Create_NTLI_MULTI_VAR_PLAIN(std::string name, std::string factor);
Instruction Create_NTLI_DIVIDE_VAR_PLAIN(std::string name, std::string factor);
Instruction Create_NTLI_SET_VAR_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_PLUS_VAR_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_MINUS_VAR_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_MULTI_VAR_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_DIVIDE_VAR_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_SET_VAR_FROM_VAR_DBG(std::string name, std::string var);
Instruction Create_NTLI_PLUS_VAR_FROM_VAR_DBG(std::string name, std::string var);
Instruction Create_NTLI_MINUS_VAR_FROM_VAR_DBG(std::string name, std::string var);
Instruction Create_NTLI_MULTI_VAR_FROM_VAR_DBG(std::string name, std::string var);
Instruction Create_NTLI_DIVIDE_VAR_FROM_VAR_DBG(std::string name, std::string var);

// ---------- DBG Variable Delegation ----------
Instruction Create_NTLI_SET_VAR_DBG_PLAIN(std::string name, std::string value);
Instruction Create_NTLI_PLUS_VAR_DBG_PLAIN(std::string name, std::string factor);
Instruction Create_NTLI_MINUS_VAR_DBG_PLAIN(std::string name, std::string factor);
Instruction Create_NTLI_MULTI_VAR_DBG_PLAIN(std::string name, std::string factor);
Instruction Create_NTLI_DIVIDE_VAR_DBG_PLAIN(std::string name, std::string factor);
Instruction Create_NTLI_SET_VAR_DBG_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_PLUS_VAR_DBG_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_MINUS_VAR_DBG_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_MULTI_VAR_DBG_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_DIVIDE_VAR_DBG_FROM_VAR(std::string name, std::string var);
Instruction Create_NTLI_SET_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var);
Instruction Create_NTLI_PLUS_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var);
Instruction Create_NTLI_MINUS_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var);
Instruction Create_NTLI_MULTI_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var);
Instruction Create_NTLI_DIVIDE_VAR_DBG_FROM_VAR_DBG(std::string name, std::string var);

// ---------- TAS Inputs ----------
Instruction Create_NTLI_FRAME(std::vector<std::string> inputs);




