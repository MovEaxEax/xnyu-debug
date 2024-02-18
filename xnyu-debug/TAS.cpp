#include "pch.h"
#include "TAS.h"
#include "Conversions.h"
#include "InputLayout.h"
#include "DebugFunctions.h"
#include "DebugAddresses.h"
#include "Variable.h"
#include "xNyuTASLanguageDatatypes.h"
#include "Logging.h"



// --- Variables ---
std::string TASTargetScript = "";

bool TASPlayingActive = false;
bool TASPlayingInit = false;

bool TASRecordingActive = false;
bool TASRecordingInit = false;

GameInputLayout TASInputLayout = GameInputLayout();
GameInput TASInputStateCurrent = GameInput();
GameInput TASInputStateLast = GameInput();

long long TASFramesPassed = 0;



// --- Functions ---
std::string GameInputToFrame(GameInput* SRC)
{
    std::string frame = "\tframe { ";

    if (SRC->ESC) frame = frame + TASInputLayout.ESC + "(); ";
    if (SRC->TAB) frame = frame + TASInputLayout.TAB + "(); ";
    if (SRC->LSHIFT) frame = frame + TASInputLayout.LSHIFT + "(); ";
    if (SRC->RSHIFT) frame = frame + TASInputLayout.RSHIFT + "(); ";
    if (SRC->CTRL) frame = frame + TASInputLayout.CTRL + "(); ";
    if (SRC->ALT) frame = frame + TASInputLayout.ALT + "(); ";
    if (SRC->BACK) frame = frame + TASInputLayout.BACK + "(); ";
    if (SRC->RETURN) frame = frame + TASInputLayout.RETURN + "(); ";
    if (SRC->SPACE) frame = frame + TASInputLayout.SPACE + "(); ";
    if (SRC->AUP) frame = frame + TASInputLayout.AUP + "(); ";
    if (SRC->ARIGHT) frame = frame + TASInputLayout.ARIGHT + "(); ";
    if (SRC->ADOWN) frame = frame + TASInputLayout.ADOWN + "(); ";
    if (SRC->ALEFT) frame = frame + TASInputLayout.ALEFT + "(); ";
    if (SRC->D0) frame = frame + TASInputLayout.D0 + "(); ";
    if (SRC->D1) frame = frame + TASInputLayout.D1 + "(); ";
    if (SRC->D2) frame = frame + TASInputLayout.D2 + "(); ";
    if (SRC->D3) frame = frame + TASInputLayout.D3 + "(); ";
    if (SRC->D4) frame = frame + TASInputLayout.D4 + "(); ";
    if (SRC->D5) frame = frame + TASInputLayout.D5 + "(); ";
    if (SRC->D6) frame = frame + TASInputLayout.D6 + "(); ";
    if (SRC->D7) frame = frame + TASInputLayout.D7 + "(); ";
    if (SRC->D8) frame = frame + TASInputLayout.D8 + "(); ";
    if (SRC->D9) frame = frame + TASInputLayout.D9 + "(); ";
    if (SRC->A) frame = frame + TASInputLayout.A + "(); ";
    if (SRC->B) frame = frame + TASInputLayout.B + "(); ";
    if (SRC->C) frame = frame + TASInputLayout.C + "(); ";
    if (SRC->D) frame = frame + TASInputLayout.D + "(); ";
    if (SRC->E) frame = frame + TASInputLayout.E + "(); ";
    if (SRC->F) frame = frame + TASInputLayout.F + "(); ";
    if (SRC->G) frame = frame + TASInputLayout.G + "(); ";
    if (SRC->H) frame = frame + TASInputLayout.H + "(); ";
    if (SRC->I) frame = frame + TASInputLayout.I + "(); ";
    if (SRC->J) frame = frame + TASInputLayout.J + "(); ";
    if (SRC->K) frame = frame + TASInputLayout.K + "(); ";
    if (SRC->L) frame = frame + TASInputLayout.L + "(); ";
    if (SRC->M) frame = frame + TASInputLayout.M + "(); ";
    if (SRC->N) frame = frame + TASInputLayout.N + "(); ";
    if (SRC->O) frame = frame + TASInputLayout.O + "(); ";
    if (SRC->P) frame = frame + TASInputLayout.P + "(); ";
    if (SRC->Q) frame = frame + TASInputLayout.Q + "(); ";
    if (SRC->R) frame = frame + TASInputLayout.R + "(); ";
    if (SRC->S) frame = frame + TASInputLayout.S + "(); ";
    if (SRC->T) frame = frame + TASInputLayout.T + "(); ";
    if (SRC->U) frame = frame + TASInputLayout.U + "(); ";
    if (SRC->V) frame = frame + TASInputLayout.V + "(); ";
    if (SRC->W) frame = frame + TASInputLayout.W + "(); ";
    if (SRC->X) frame = frame + TASInputLayout.X + "(); ";
    if (SRC->Y) frame = frame + TASInputLayout.Y + "(); ";
    if (SRC->Z) frame = frame + TASInputLayout.Z + "(); ";
    if (SRC->NUM0) frame = frame + TASInputLayout.NUM0 + "(); ";
    if (SRC->NUM1) frame = frame + TASInputLayout.NUM1 + "(); ";
    if (SRC->NUM2) frame = frame + TASInputLayout.NUM2 + "(); ";
    if (SRC->NUM3) frame = frame + TASInputLayout.NUM3 + "(); ";
    if (SRC->NUM4) frame = frame + TASInputLayout.NUM4 + "(); ";
    if (SRC->NUM5) frame = frame + TASInputLayout.NUM5 + "(); ";
    if (SRC->NUM6) frame = frame + TASInputLayout.NUM6 + "(); ";
    if (SRC->NUM7) frame = frame + TASInputLayout.NUM7 + "(); ";
    if (SRC->NUM8) frame = frame + TASInputLayout.NUM8 + "(); ";
    if (SRC->NUM9) frame = frame + TASInputLayout.NUM9 + "(); ";
    if (SRC->NUMDIV) frame = frame + TASInputLayout.NUMDIV + "(); ";
    if (SRC->NUMMUL) frame = frame + TASInputLayout.NUMMUL + "(); ";
    if (SRC->NUMMIN) frame = frame + TASInputLayout.NUMMIN + "(); ";
    if (SRC->NUMPLU) frame = frame + TASInputLayout.NUMPLU + "(); ";
    if (SRC->NUMRET) frame = frame + TASInputLayout.NUMRET + "(); ";
    if (SRC->NUMDEL) frame = frame + TASInputLayout.NUMDEL + "(); ";
    if (SRC->F1) frame = frame + TASInputLayout.F1 + "(); ";
    if (SRC->F2) frame = frame + TASInputLayout.F2 + "(); ";
    if (SRC->F3) frame = frame + TASInputLayout.F3 + "(); ";
    if (SRC->F4) frame = frame + TASInputLayout.F4 + "(); ";
    if (SRC->F5) frame = frame + TASInputLayout.F5 + "(); ";
    if (SRC->F6) frame = frame + TASInputLayout.F6 + "(); ";
    if (SRC->F7) frame = frame + TASInputLayout.F7 + "(); ";
    if (SRC->F8) frame = frame + TASInputLayout.F8 + "(); ";
    if (SRC->F9) frame = frame + TASInputLayout.F9 + "(); ";
    if (SRC->F10) frame = frame + TASInputLayout.F10 + "(); ";
    if (SRC->F11) frame = frame + TASInputLayout.F11 + "(); ";
    if (SRC->F12) frame = frame + TASInputLayout.F12 + "(); ";
    if (SRC->COMMA) frame = frame + TASInputLayout.COMMA + "(); ";
    if (SRC->DOT) frame = frame + TASInputLayout.DOT + "(); ";
    if (SRC->PLUS) frame = frame + TASInputLayout.PLUS + "(); ";
    if (SRC->MINUS) frame = frame + TASInputLayout.MINUS + "(); ";
    if (SRC->LMB) frame = frame + TASInputLayout.LMB + "(); ";
    if (SRC->RMB) frame = frame + TASInputLayout.RMB + "(); ";
    if (SRC->MB) frame = frame + TASInputLayout.MB + "(); ";
    if (SRC->ME1) frame = frame + TASInputLayout.ME1 + "(); ";
    if (SRC->ME2) frame = frame + TASInputLayout.ME2 + "(); ";
    if (SRC->WHEEL != 0) frame = frame + TASInputLayout.WHEEL + "(" + std::to_string(SRC->WHEEL) + "); ";
    if (SRC->MOUSEX != 0) frame = frame + TASInputLayout.MOUSEX + "(" + std::to_string(SRC->MOUSEX) + "); ";
    if (SRC->MOUSEY != 0) frame = frame + TASInputLayout.MOUSEY + "(" + std::to_string(SRC->MOUSEY) + "); ";
    if (SRC->JOYA) frame = frame + TASInputLayout.JOYA + "(); ";
    if (SRC->JOYB) frame = frame + TASInputLayout.JOYB + "(); ";
    if (SRC->JOYX) frame = frame + TASInputLayout.JOYX + "(); ";
    if (SRC->JOYY) frame = frame + TASInputLayout.JOYY + "(); ";
    if (SRC->JOYSTART) frame = frame + TASInputLayout.JOYSTART + "(); ";
    if (SRC->JOYSELECT) frame = frame + TASInputLayout.JOYSELECT + "(); ";
    if (SRC->JOYRB) frame = frame + TASInputLayout.JOYRB + "(); ";
    if (SRC->JOYLB) frame = frame + TASInputLayout.JOYLB + "(); ";
    if (SRC->JOYUP) frame = frame + TASInputLayout.JOYUP + "(); ";
    if (SRC->JOYDOWN) frame = frame + TASInputLayout.JOYDOWN + "(); ";
    if (SRC->JOYRIGHT) frame = frame + TASInputLayout.JOYRIGHT + "(); ";
    if (SRC->JOYLEFT) frame = frame + TASInputLayout.JOYLEFT + "(); ";
    if (SRC->JOYRT) frame = frame + TASInputLayout.JOYRT + "(" + std::to_string(SRC->JOYRT) + "); ";
    if (SRC->JOYLT) frame = frame + TASInputLayout.JOYLT + "(" + std::to_string(SRC->JOYLT) + "); ";
    if (SRC->JOYRAXISX != 0) frame = frame + TASInputLayout.JOYRAXISX + "(" + std::to_string(SRC->JOYRAXISX) + "); ";
    if (SRC->JOYRAXISY != 0) frame = frame + TASInputLayout.JOYRAXISY + "(" + std::to_string(SRC->JOYRAXISY) + "); ";
    if (SRC->JOYLAXISX != 0) frame = frame + TASInputLayout.JOYLAXISX + "(" + std::to_string(SRC->JOYLAXISX) + "); ";
    if (SRC->JOYLAXISY != 0) frame = frame + TASInputLayout.JOYLAXISY + "(" + std::to_string(SRC->JOYLAXISY) + "); ";
    if (SRC->JOYRS != 0) frame = frame + TASInputLayout.JOYRS + "(); ";
    if (SRC->JOYLS != 0) frame = frame + TASInputLayout.JOYLS + "(); ";

    frame = frame + "}";
    return frame;
}

void GameInputSetFrame(GameInput* SRC, std::vector<std::string> parameter)
{
    for (int i = 0; i < parameter.size(); i++)
    {
        std::vector<std::string> parameterSplitted;
        splitStringVector(parameterSplitted, parameter[i], ",");

        if (parameterSplitted[0] == TASInputLayout.ESC) SRC->ESC = true;
        if (parameterSplitted[0] == TASInputLayout.TAB) SRC->TAB = true;
        if (parameterSplitted[0] == TASInputLayout.LSHIFT) SRC->LSHIFT = true;
        if (parameterSplitted[0] == TASInputLayout.RSHIFT) SRC->RSHIFT = true;
        if (parameterSplitted[0] == TASInputLayout.CTRL) SRC->CTRL = true;
        if (parameterSplitted[0] == TASInputLayout.ALT) SRC->ALT = true;
        if (parameterSplitted[0] == TASInputLayout.BACK) SRC->BACK = true;
        if (parameterSplitted[0] == TASInputLayout.RETURN) SRC->RETURN = true;
        if (parameterSplitted[0] == TASInputLayout.SPACE) SRC->SPACE = true;
        if (parameterSplitted[0] == TASInputLayout.AUP) SRC->AUP = true;
        if (parameterSplitted[0] == TASInputLayout.ARIGHT) SRC->ARIGHT = true;
        if (parameterSplitted[0] == TASInputLayout.ADOWN) SRC->ADOWN = true;
        if (parameterSplitted[0] == TASInputLayout.ALEFT) SRC->ALEFT = true;
        if (parameterSplitted[0] == TASInputLayout.D0) SRC->D0 = true;
        if (parameterSplitted[0] == TASInputLayout.D1) SRC->D1 = true;
        if (parameterSplitted[0] == TASInputLayout.D2) SRC->D2 = true;
        if (parameterSplitted[0] == TASInputLayout.D3) SRC->D3 = true;
        if (parameterSplitted[0] == TASInputLayout.D4) SRC->D4 = true;
        if (parameterSplitted[0] == TASInputLayout.D5) SRC->D5 = true;
        if (parameterSplitted[0] == TASInputLayout.D6) SRC->D6 = true;
        if (parameterSplitted[0] == TASInputLayout.D7) SRC->D7 = true;
        if (parameterSplitted[0] == TASInputLayout.D8) SRC->D8 = true;
        if (parameterSplitted[0] == TASInputLayout.D9) SRC->D9 = true;
        if (parameterSplitted[0] == TASInputLayout.A) SRC->A = true;
        if (parameterSplitted[0] == TASInputLayout.B) SRC->B = true;
        if (parameterSplitted[0] == TASInputLayout.C) SRC->C = true;
        if (parameterSplitted[0] == TASInputLayout.D) SRC->D = true;
        if (parameterSplitted[0] == TASInputLayout.E) SRC->E = true;
        if (parameterSplitted[0] == TASInputLayout.F) SRC->F = true;
        if (parameterSplitted[0] == TASInputLayout.G) SRC->G = true;
        if (parameterSplitted[0] == TASInputLayout.H) SRC->H = true;
        if (parameterSplitted[0] == TASInputLayout.I) SRC->I = true;
        if (parameterSplitted[0] == TASInputLayout.J) SRC->J = true;
        if (parameterSplitted[0] == TASInputLayout.K) SRC->K = true;
        if (parameterSplitted[0] == TASInputLayout.L) SRC->L = true;
        if (parameterSplitted[0] == TASInputLayout.M) SRC->M = true;
        if (parameterSplitted[0] == TASInputLayout.N) SRC->N = true;
        if (parameterSplitted[0] == TASInputLayout.O) SRC->O = true;
        if (parameterSplitted[0] == TASInputLayout.P) SRC->P = true;
        if (parameterSplitted[0] == TASInputLayout.Q) SRC->Q = true;
        if (parameterSplitted[0] == TASInputLayout.R) SRC->R = true;
        if (parameterSplitted[0] == TASInputLayout.S) SRC->S = true;
        if (parameterSplitted[0] == TASInputLayout.T) SRC->T = true;
        if (parameterSplitted[0] == TASInputLayout.U) SRC->U = true;
        if (parameterSplitted[0] == TASInputLayout.V) SRC->V = true;
        if (parameterSplitted[0] == TASInputLayout.W) SRC->W = true;
        if (parameterSplitted[0] == TASInputLayout.X) SRC->X = true;
        if (parameterSplitted[0] == TASInputLayout.Y) SRC->Y = true;
        if (parameterSplitted[0] == TASInputLayout.Z) SRC->Z = true;
        if (parameterSplitted[0] == TASInputLayout.NUM0) SRC->NUM0 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM1) SRC->NUM1 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM2) SRC->NUM2 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM3) SRC->NUM3 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM4) SRC->NUM4 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM5) SRC->NUM5 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM6) SRC->NUM6 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM7) SRC->NUM7 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM8) SRC->NUM8 = true;
        if (parameterSplitted[0] == TASInputLayout.NUM9) SRC->NUM9 = true;
        if (parameterSplitted[0] == TASInputLayout.NUMDIV) SRC->NUMDIV = true;
        if (parameterSplitted[0] == TASInputLayout.NUMMUL) SRC->NUMMUL = true;
        if (parameterSplitted[0] == TASInputLayout.NUMMIN) SRC->NUMMIN = true;
        if (parameterSplitted[0] == TASInputLayout.NUMPLU) SRC->NUMPLU = true;
        if (parameterSplitted[0] == TASInputLayout.NUMRET) SRC->NUMRET = true;
        if (parameterSplitted[0] == TASInputLayout.NUMDEL) SRC->NUMDEL = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.F1) SRC->F1 = true;
        if (parameterSplitted[0] == TASInputLayout.COMMA) SRC->COMMA = true;
        if (parameterSplitted[0] == TASInputLayout.DOT) SRC->DOT = true;
        if (parameterSplitted[0] == TASInputLayout.PLUS) SRC->PLUS = true;
        if (parameterSplitted[0] == TASInputLayout.MINUS) SRC->MINUS = true;
        if (parameterSplitted[0] == TASInputLayout.LMB) SRC->LMB = true;
        if (parameterSplitted[0] == TASInputLayout.RMB) SRC->RMB = true;
        if (parameterSplitted[0] == TASInputLayout.MB) SRC->MB = true;
        if (parameterSplitted[0] == TASInputLayout.ME1) SRC->ME1 = true;
        if (parameterSplitted[0] == TASInputLayout.ME2) SRC->ME2 = true;
        if (parameterSplitted[0] == TASInputLayout.WHEEL && parameterSplitted[1] != "0") SRC->WHEEL = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.MOUSEX && parameterSplitted[1] != "0") SRC->MOUSEX = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.MOUSEY && parameterSplitted[1] != "0") SRC->MOUSEY = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.JOYA) SRC->JOYA = true;
        if (parameterSplitted[0] == TASInputLayout.JOYB) SRC->JOYB = true;
        if (parameterSplitted[0] == TASInputLayout.JOYX) SRC->JOYX = true;
        if (parameterSplitted[0] == TASInputLayout.JOYY) SRC->JOYY = true;
        if (parameterSplitted[0] == TASInputLayout.JOYSTART) SRC->JOYSTART = true;
        if (parameterSplitted[0] == TASInputLayout.JOYSELECT) SRC->JOYSELECT = true;
        if (parameterSplitted[0] == TASInputLayout.JOYRB) SRC->JOYRB = true;
        if (parameterSplitted[0] == TASInputLayout.JOYLB) SRC->JOYLB = true;
        if (parameterSplitted[0] == TASInputLayout.JOYUP) SRC->JOYUP = true;
        if (parameterSplitted[0] == TASInputLayout.JOYDOWN) SRC->JOYDOWN = true;
        if (parameterSplitted[0] == TASInputLayout.JOYRIGHT) SRC->JOYRIGHT = true;
        if (parameterSplitted[0] == TASInputLayout.JOYLEFT) SRC->JOYLEFT = true;
        if (parameterSplitted[0] == TASInputLayout.JOYRT && parameterSplitted[1] != "0") SRC->JOYRT = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.JOYLT && parameterSplitted[1] != "0") SRC->JOYLT = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.JOYRAXISX && parameterSplitted[1] != "0") SRC->JOYRAXISX = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.JOYRAXISY && parameterSplitted[1] != "0") SRC->JOYRAXISY = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.JOYLAXISX && parameterSplitted[1] != "0") SRC->JOYLAXISX = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.JOYLAXISY && parameterSplitted[1] != "0") SRC->JOYLAXISY = std::stoi(parameterSplitted[1]);
        if (parameterSplitted[0] == TASInputLayout.JOYRS) SRC->JOYRS = true;
        if (parameterSplitted[0] == TASInputLayout.JOYLS) SRC->JOYLS = true;
        if (parameter.size() > 2) if (parameter[2] == "set") SRC->SETMOUSE = true;
    }
}

bool FindDebugFunction(std::string parentName, std::string childName, DebugFunction* debugFunction)
{
    bool found = false;
    for (int i = 0; i < DebugFunctions.size(); i++)
    {
        std::string nameParentTarget = DebugFunctions[i].nameParent;
        std::transform(nameParentTarget.begin(), nameParentTarget.end(), nameParentTarget.begin(), [](unsigned char c) { return std::tolower(c); });
        if (nameParentTarget == parentName)
        {
            for (int k = 0; k < DebugFunctions[i].functions.size(); k++)
            {
                std::string nameChildTarget = DebugFunctions[i].functions[k].nameChild;
                std::transform(nameChildTarget.begin(), nameChildTarget.end(), nameChildTarget.begin(), [](unsigned char c) { return std::tolower(c); });
                if (nameChildTarget == childName)
                {
                    *debugFunction = DebugFunctions[i].functions[k];
                    found = true;
                    break;
                }
            }
            break;
        }
    }

    return found;
}

bool FindDebugAddress(std::string parentName, std::string childName, DebugAddress* debugAddress)
{
    bool found = false;
    for (int i = 0; i < DebugAddresses.size(); i++)
    {
        std::string nameParentTarget = DebugAddresses[i].nameParent;
        std::transform(nameParentTarget.begin(), nameParentTarget.end(), nameParentTarget.begin(), [](unsigned char c) { return std::tolower(c); });
        if (nameParentTarget == parentName)
        {
            for (int k = 0; k < DebugAddresses[i].addresses.size(); k++)
            {
                std::string nameChildTarget = DebugAddresses[i].addresses[k].nameChild;
                std::transform(nameChildTarget.begin(), nameChildTarget.end(), nameChildTarget.begin(), [](unsigned char c) { return std::tolower(c); });
                if (nameChildTarget == childName)
                {
                    *debugAddress = DebugAddresses[i].addresses[k];
                    found = true;
                    break;
                }
            }
            break;
        }
    }

    return found;
}

bool FindTASVariable(std::string name, Variable* variableTarget, std::vector<Variable>* variables)
{
    bool found = false;
    for (int i = 0; i < variables->size(); i++)
    {
        if (variables->data()[i].name == name)
        {
            variableTarget = &variables->data()[i];
            found = true;
            break;
        }
    }

    return found;
}

int ParseScript(NTLScript* script)
{
    if (!script->init)
    {
        script->instructionpointer = script->entrypoint;
        script->init = true;
    }

    Instruction instruction = script->instructions[script->instructionpointer];
    bool disableStackIncrease = false;

    switch (instruction.opcode)
    {
    case OpCode::JMP:
        script->instructionpointer = instruction.address;
        disableStackIncrease = true;
        break;
    case OpCode::JMPOFF:
        script->instructionpointer += instruction.address;
        disableStackIncrease = true;
        break;
    case OpCode::IF:
        bool checkCondition = false;
        if (!checkCondition)
        {
            script->instructionpointer = instruction.address;
            disableStackIncrease = true;
        }
        break;
    case OpCode::RET:
        script->instructionpointer = script->stackpointer[script->stackpointer.size() - 1];
        script->stackpointer.pop_back();
        break;
    case OpCode::RETSET:
        script->stackpointer.push_back(instruction.address);
        break;
    case OpCode::CALLDBG:

        break;
    case OpCode::LOG:

        break;
    case OpCode::FRAME:

        break;
    case OpCode::CREATE_VAR:

        break;
    case OpCode::REMOVE_VAR:

        break;
    case OpCode::SET_VAR_PLAIN:

        break;
    case OpCode::PLUS_VAR_PLAIN:

        break;
    case OpCode::MINUS_VAR_PLAIN:

        break;
    case OpCode::MULTI_VAR_PLAIN:

        break;
    case OpCode::DIVIDE_VAR_PLAIN:

        break;
    case OpCode::SET_VAR_FROM_VAR:

        break;
    case OpCode::PLUS_VAR_FROM_VAR:

        break;
    case OpCode::MINUS_VAR_FROM_VAR:

        break;
    case OpCode::MULTI_VAR_FROM_VAR:

        break;
    case OpCode::DIVIDE_VAR_FROM_VAR:

        break;
    case OpCode::SET_VAR_FROM_VAR_DBG:

        break;
    case OpCode::PLUS_VAR_FROM_VAR_DBG:

        break;
    case OpCode::MINUS_VAR_FROM_VAR_DBG:

        break;
    case OpCode::MULTI_VAR_FROM_VAR_DBG:

        break;
    case OpCode::DIVIDE_VAR_FROM_VAR_DBG:

        break;
    case OpCode::SET_VAR_DBG_PLAIN:

        break;
    case OpCode::PLUS_VAR_DBG_PLAIN:

        break;
    case OpCode::MINUS_VAR_DBG_PLAIN:

        break;
    case OpCode::MULTI_VAR_DBG_PLAIN:

        break;
    case OpCode::DIVIDE_VAR_DBG_PLAIN:

        break;
    case OpCode::SET_VAR_DBG_FROM_VAR:

        break;
    case OpCode::PLUS_VAR_DBG_FROM_VAR:

        break;
    case OpCode::MINUS_VAR_DBG_FROM_VAR:

        break;
    case OpCode::MULTI_VAR_DBG_FROM_VAR:

        break;
    case OpCode::DIVIDE_VAR_DBG_FROM_VAR:

        break;
    case OpCode::SET_VAR_DBG_FROM_VAR_DBG:

        break;
    case OpCode::PLUS_VAR_DBG_FROM_VAR_DBG:

        break;
    case OpCode::MINUS_VAR_DBG_FROM_VAR_DBG:

        break;
    case OpCode::MULTI_VAR_DBG_FROM_VAR_DBG:

        break;
    case OpCode::DIVIDE_VAR_DBG_FROM_VAR_DBG:

        break;
    case OpCode::CREATEFILE:

        break;
    case OpCode::WRITEFILE:

        break;
    }










    return 0;
}

EXTERN_DLL_EXPORT bool PlayScriptRoutine() {
    try
    {

    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: PlayScriptRoutine()", false, "red");



    }
    return true;
}

EXTERN_DLL_EXPORT bool RecordScriptRoutine() {
    try
    {

    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: RecordScriptRoutine()", false, "red");



    }
    return true;
}

EXTERN_DLL_EXPORT void TASRoutine()
{
    if (TASPlayingActive) PlayScriptRoutine();
    if (TASRecordingActive) RecordScriptRoutine();
}


