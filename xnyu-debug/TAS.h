#pragma once
std::string TASScript = "";

bool TASPlayScript = false;
bool TASPlayScriptDone = false;
bool TASPlayScriptInit = false;
bool TASPlayScriptUninit = false;
bool TASPlayScriptThenRecord = false;
bool TASPlayStartedSignal = false;
bool TASPlaySkipFirstSync = false;
std::ifstream TASPlayScriptStream;

bool TASRecordScript = false;
bool TASRecordScriptDone = false;
bool TASRecordScriptInit = false;
bool TASRecordScriptUninit = false;
bool TASRecordFrameByFrame = false;
bool TASRecordStartedSignal = false;
bool TASRecordSkipFirstSync = false;
std::string TASRecordFrameReceived;
std::ofstream TASRecordScriptStream;

GameInput TASInputCurrent;
GameInput TASInputLast;

std::string TASLastError = "";

struct Instruction {
    std::string type;
    std::vector<std::string> parameter;
};

struct Function {
    std::string name;
    std::vector<Instruction> instructions;
    int id;
};

struct Stack {
    int id;
    int line;
};

GameInputLayout TASInputLayout;
std::vector<Function> TASScriptFunctions;
std::vector<Variable> TASScriptVariables;
std::vector<Stack> TASStack;
Stack TASCurrentStack;
int TASFunctionId = 0;
int TASRepeatNamer = 0;
long long TASFramesPassed = 0;

std::string ReadScript(std::string file_path) {
    // Load Script
    std::ifstream file(file_path);

    std::string script = "";

    while (!file.eof()) {

        // Read line
        std::string line = "";
        std::getline(file, line);

        //Declare Substrings
        std::string substring_instruction = "";
        std::string substring_iterations = "";

        // Check if line contains content
        if (line.length() > 0) {

            // Make line lowercase
            std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });

            // Delete comments
            if (line.find("//") != std::string::npos) {
                line.replace(line.find("//"), line.length() - line.find("//"), "");
            }

            // Delete hashtags
            if (line.find("#") != std::string::npos) {
                while (line.find("#") != std::string::npos) {
                    line.replace(line.find("#"), 1, "");
                }
            }

            // Delete tabulators
            if (line.find("\t") != std::string::npos) {
                while (line.find("\t") != std::string::npos) {
                    line.replace(line.find("\t"), 1, "");
                }
            }

            // Delete line breaks
            if (line.find("\n") != std::string::npos) {
                while (line.find("\n") != std::string::npos) {
                    line.replace(line.find("\n"), 1, "");
                }
            }

            // Delete line breaks
            if (line.find("\r") != std::string::npos) {
                while (line.find("\r") != std::string::npos) {
                    line.replace(line.find("\r"), 1, "");
                }
            }

            // Delete whitespaces
            if (line.find(" ") != std::string::npos) {
                bool inside_quotes = false;
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == '\"') {
                        inside_quotes = !inside_quotes;
                    }
                    else if (line[i] == ' ' && !inside_quotes) {
                        line.erase(i, 1);
                        i--;
                    }
                }
            }

            if (line.length() > 0) {
                script = script + line;
            }

        }
    }

    file.close();

    return script;
}

int ParseInstructions(std::vector<Instruction> &functions, std::string content)
{
    while (content.length() > 0)
    {
        Instruction instruction;
        int entries[10];
        entries[0] = content.find("(") == std::string::npos ? INT32_MAX : content.find("(");
        entries[1] = content.find("{") == std::string::npos ? INT32_MAX : content.find("{");
        entries[2] = content.find("+") == std::string::npos ? INT32_MAX : content.find("+");
        entries[3] = content.find("-") == std::string::npos ? INT32_MAX : content.find("-");
        entries[4] = content.find("*") == std::string::npos ? INT32_MAX : content.find("*");
        entries[5] = content.find("/") == std::string::npos ? INT32_MAX : content.find("/");
        entries[6] = content.find("=") == std::string::npos ? INT32_MAX : content.find("=");
        entries[7] = content.find(";") == std::string::npos ? INT32_MAX : content.find(";");
        entries[8] = entries[1] + 1;
        entries[9] = entries[0] + 1;
        int smallest = entries[0];
        int index = 0;
        for (int i = 1; i < 7; i++) {
            if (entries[i] < smallest) {
                smallest = entries[i];
                index = i;
            }
        }
        // Syntax error
        if (entries[index] == INT32_MAX) return -1;

        if (index == 0)
        {
            instruction.type = content.substr(0, entries[index]);
            entries[9] = content.find(")", entries[0]);
            if (content.substr(entries[9] + 1, 1) == ";")
            {
                // Function
                std::string parameter = content.substr(entries[index] + 1, entries[9] - (entries[index] + 1));
                if (parameter.length() > 0)
                {
                    if (parameter.find(",") != std::string::npos)
                    {
                        std::vector<std::string> params;
                        splitStringVector(params, parameter, ",");
                        for (int i = 0; i < params.size(); i++)
                        {
                            instruction.parameter.push_back(params[i]);
                        }
                    }
                    else
                    {
                        instruction.parameter.push_back(parameter);
                    }
                }
                functions.push_back(instruction);
                content.replace(0, entries[7] + 1, "");
            }
            else
            {
                // while, if, repeat
                entries[8] = entries[1];
                int openbraces = 1;
                while (openbraces > 0)
                {
                    int nextOpen = content.find("{", entries[8] + 1);
                    int nextClose = content.find("}", entries[8] + 1);
                    if (nextOpen == std::string::npos) nextOpen = INT32_MAX;
                    if (nextClose == std::string::npos) nextClose = INT32_MAX;

                    if (nextClose < nextOpen)
                    {
                        entries[8] = nextClose;
                        openbraces--;
                    }
                    else if (nextOpen < nextClose)
                    {
                        entries[8] = nextOpen;
                        openbraces++;
                    }
                    else {
                        // Error in brackets
                        return -1;
                    }
                }

                std::string parameter = content.substr(entries[index] + 1, entries[9] - (entries[index] + 1));
                std::string subPayload = content.substr(entries[1] + 1, entries[8] - (entries[1] + 1));

                std::vector<Instruction> subInstructions;
                ParseInstructions(subInstructions, subPayload);

                if (instruction.type == "while")
                {
                    Instruction startInstruction;
                    startInstruction.type = "ifnotjmp";
                    startInstruction.parameter.push_back(std::to_string(subInstructions.size() + 2));
                    Instruction endInstruction;
                    endInstruction.type = "jmp";
                    endInstruction.parameter.push_back("-" + std::to_string(subInstructions.size() + 1));
                    if (parameter.find("&&") != std::string::npos)
                    {
                        //endInstruction.parameter.push_back("&&");
                        startInstruction.parameter.push_back("&&");
                        std::vector<std::string> params;
                        splitStringVector(params, parameter, "&&");
                        for (int i = 0; i < params.size(); i++)
                        {
                            //endInstruction.parameter.push_back(params[i]);
                            startInstruction.parameter.push_back(params[i]);
                        }
                    }
                    else if (parameter.find("||") != std::string::npos)
                    {
                        //endInstruction.parameter.push_back("||");
                        startInstruction.parameter.push_back("||");
                        std::vector<std::string> params;
                        splitStringVector(params, parameter, "||");
                        for (int i = 0; i < params.size(); i++)
                        {
                            //endInstruction.parameter.push_back(params[i]);
                            startInstruction.parameter.push_back(params[i]);
                        }
                    }
                    else
                    {
                        //endInstruction.parameter.push_back(parameter);
                        startInstruction.parameter.push_back(parameter);
                    }

                    functions.push_back(startInstruction);
                    for(int i = 0; i < subInstructions.size(); i++) functions.push_back(subInstructions[i]);
                    functions.push_back(endInstruction);
                }
                if (instruction.type == "if")
                {
                    Instruction endInstruction;
                    endInstruction.type = "ifjmp";
                    endInstruction.parameter.push_back(std::to_string(subInstructions.size() + 1));
                    if (parameter.find("&&") != std::string::npos)
                    {
                        endInstruction.parameter.push_back("&&");
                        std::vector<std::string> params;
                        splitStringVector(params, parameter, "&&");
                        for (int i = 0; i < params.size(); i++) endInstruction.parameter.push_back(params[i]);
                    }
                    else if (parameter.find("||") != std::string::npos)
                    {
                        endInstruction.parameter.push_back("||");
                        std::vector<std::string> params;
                        splitStringVector(params, parameter, "||");
                        for (int i = 0; i < params.size(); i++) endInstruction.parameter.push_back(params[i]);
                    }
                    else
                    {
                        endInstruction.parameter.push_back(parameter);
                    }

                    functions.push_back(endInstruction);
                    for (int i = 0; i < subInstructions.size(); i++) functions.push_back(subInstructions[i]);
                }
                if (instruction.type == "repeat")
                {
                    Instruction createInstruction;
                    createInstruction.type = "int";
                    createInstruction.parameter.push_back("repeater" + std::to_string(TASRepeatNamer));
                    createInstruction.parameter.push_back("0");
                    Instruction incrementInstruction;
                    incrementInstruction.type = "plus";
                    incrementInstruction.parameter.push_back("repeater" + std::to_string(TASRepeatNamer));
                    incrementInstruction.parameter.push_back("1");
                    Instruction removeInstruction;
                    removeInstruction.type = "remove";
                    removeInstruction.parameter.push_back("repeater" + std::to_string(TASRepeatNamer));
                    Instruction endInstruction;
                    endInstruction.type = "ifjmp";
                    endInstruction.parameter.push_back("-" + std::to_string(subInstructions.size() + 1));
                    endInstruction.parameter.push_back("repeater" + std::to_string(TASRepeatNamer) + ">=" + parameter);

                    functions.push_back(createInstruction);
                    for (int i = 0; i < subInstructions.size(); i++) functions.push_back(subInstructions[i]);
                    functions.push_back(incrementInstruction);
                    functions.push_back(endInstruction);
                    functions.push_back(removeInstruction);

                    TASRepeatNamer++;
                }

                content.replace(0, entries[8] + 1, "");
            }
        }
        if (index == 1)
        {
            // Block (frame)
            instruction.type = content.substr(0, entries[index]);
            entries[8] = entries[1];

            int openbraces = 1;
            while (openbraces > 0)
            {
                int nextOpen = content.find("{", entries[8] + 1);
                int nextClose = content.find("}", entries[8] + 1);
                if (nextOpen == std::string::npos) nextOpen = INT32_MAX;
                if (nextClose == std::string::npos) nextClose = INT32_MAX;

                if (nextClose < nextOpen)
                {
                    entries[8] = nextClose;
                    openbraces--;
                }
                else if (nextOpen < nextClose)
                {
                    entries[8] = nextOpen;
                    openbraces++;
                }
                else {
                    // Error in brackets
                    return -1;
                }
            }

            std::string payload = content.substr(entries[index] + 1, entries[8] - (entries[index] + 1));

            if (payload.length() > 0)
            {
                if (payload.substr(payload.length() - 1, 1) == ";") payload = payload.substr(0, payload.length() - 1);
                std::vector<std::string> payloadEntries;
                splitStringVector(payloadEntries, payload, ";");
                for (int i = 0; i < payloadEntries.size(); i++)
                {
                    std::string instructionFinal = payloadEntries[i].substr(0, payloadEntries[i].find("("));
                    std::string parameterFinal = payloadEntries[i].substr(payloadEntries[i].find("(") + 1, payloadEntries[i].find(")") - (payloadEntries[i].find("(") + 1));
                    if (parameterFinal.length() > 0) instructionFinal = instructionFinal + "," + parameterFinal;
                    instruction.parameter.push_back(instructionFinal);
                }
            }

            functions.push_back(instruction);
            content.replace(0, entries[8] + 1, "");
        }
        if (index == 2)
        {
            // Plus
            if (entries[7] == INT32_MAX) return -1;
            instruction.type = "plus";
            instruction.parameter.push_back(content.substr(0, entries[index]));
            instruction.parameter.push_back(content.substr(entries[index] + 2, entries[7] - (entries[index] + 2)));
            functions.push_back(instruction);
            content.replace(0, entries[7] + 1, "");
        }
        if (index == 3)
        {
            // Minus
            if (entries[7] == INT32_MAX) return -1;
            instruction.type = "minus";
            instruction.parameter.push_back(content.substr(0, entries[index]));
            instruction.parameter.push_back(content.substr(entries[index] + 2, entries[7] - (entries[index] + 2)));
            functions.push_back(instruction);
            content.replace(0, entries[7] + 1, "");
        }
        if (index == 4)
        {
            // Multi
            if (entries[7] == INT32_MAX) return -1;
            instruction.type = "multi";
            instruction.parameter.push_back(content.substr(0, entries[index]));
            instruction.parameter.push_back(content.substr(entries[index] + 2, entries[7] - (entries[index] + 2)));
            functions.push_back(instruction);
            content.replace(0, entries[7] + 1, "");
        }
        if (index == 5)
        {
            // Divide
            if (entries[7] == INT32_MAX) return -1;
            instruction.type = "divide";
            instruction.parameter.push_back(content.substr(0, entries[index]));
            instruction.parameter.push_back(content.substr(entries[index] + 2, entries[7] - (entries[index] + 2)));
            functions.push_back(instruction);
            content.replace(0, entries[7] + 1, "");
        }
        if (index == 6)
        {
            // Equal
            if (entries[7] == INT32_MAX) return -1;

            if (content.substr(0, 4) == "byte")
            {
                instruction.type = "byte";
                instruction.parameter.push_back(content.substr(4, content.find("=") - 4));
            }
            else if (content.substr(0, 4) == "bool")
            {
                instruction.type = "bool";
                instruction.parameter.push_back(content.substr(4, content.find("=") - 4));
            }
            if (content.substr(0, 5) == "int32")
            {
                instruction.type = "int32";
                instruction.parameter.push_back(content.substr(5, content.find("=") - 5));
            }
            else if (content.substr(0, 5) == "int64")
            {
                instruction.type = "int64";
                instruction.parameter.push_back(content.substr(5, content.find("=") - 5));
            }
            else if (content.substr(0, 5) == "float")
            {
                instruction.type = "float";
                instruction.parameter.push_back(content.substr(5, content.find("=") - 5));
            }
            else if (content.substr(0, 6) == "double")
            {
                instruction.type = "double";
                instruction.parameter.push_back(content.substr(6, content.find("=") - 6));
            }
            else if (content.substr(0, 6) == "string")
            {
                instruction.type = "string";
                instruction.parameter.push_back(content.substr(6, content.find("=") - 6));
            }
            else
            {
                instruction.type = "equal";
                instruction.parameter.push_back(content.substr(5, content.find("=") - 5));
            }

            instruction.parameter.push_back(content.substr(entries[index] + 1, entries[7] - (entries[index] + 1)));
            functions.push_back(instruction);
            content.replace(0, entries[7] + 1, "");
        }

    }

    return 0;
}

int ParseFunction(std::vector<Function> &functions, std::string script)
{
    while (script.length() > 0)
    {
        Function function;
        int functionEntry = script.find("{");
        int functionEnd = functionEntry;
        std::string functionName = script.substr(0, functionEntry);
        if (functionEntry == std::string::npos) break;
        int openbraces = 1;

        while (openbraces > 0)
        {
            int nextOpen = script.find("{", functionEnd + 1);
            int nextClose = script.find("}", functionEnd + 1);
            if (nextOpen == std::string::npos) nextOpen = INT32_MAX;
            if (nextClose == std::string::npos) nextClose = INT32_MAX;

            if (nextClose < nextOpen)
            {
                functionEnd = nextClose;
                openbraces--;
            }
            else if (nextOpen < nextClose)
            {
                functionEnd = nextOpen;
                openbraces++;
            }
            else {
                // Error in brackets
                return -1;
            }
        }
        std::string functionContent = script.substr(functionEntry + 1, functionEnd - (functionEntry + 1));

        if (functionName == "imports")
        {
            if (functionContent.find("/") != std::string::npos) {
                while (functionContent.find("/") != std::string::npos) {
                    functionContent.replace(functionContent.find("/"), 1, "\\");
                }
            }
            while (functionContent.length() > 0)
            {
                std::string imports = functionContent.substr(1, functionContent.find("\"", 1) - 1);
                script = script + ReadScript(GlobalSettings.config_script_directory + imports);
                functionContent.replace(0, functionContent.find(";") + 1, "");
            }
        }
        else
        {
            ParseInstructions(function.instructions, functionContent);
            function.name = functionName;
            function.id = TASFunctionId;
            int mergeIndex = -1;
            if (functions.size() > 0)
            {
                for (int i = 0; i < functions.size(); i++)
                {
                    if (functions[i].name == function.name)
                    {
                        mergeIndex = i;
                        break;
                    }
                }
            }
            if (mergeIndex > -1)
            {
                if (function.instructions.size() > 0)
                {
                    for (int i = 0; i < function.instructions.size(); i++)
                    {
                        functions[mergeIndex].instructions.push_back(function.instructions[i]);
                    }
                }
            }
            else
            {
                functions.push_back(function);
                TASFunctionId++;
            }
        }
        script.replace(0, functionEnd + 1, "");
    }

    return 0;
}

void AddFunctionLifecycles(std::vector<Function> &functions, std::vector<Stack> &stack, Stack* currentStack)
{
    Function init;
    init.name = "init";
    init.id = TASFunctionId;
    TASFunctionId++;
    Function exit;
    exit.name = "exit";
    exit.id = TASFunctionId;
    TASFunctionId++;
    Function main;
    main.name = "main";
    main.id = TASFunctionId;
    TASFunctionId++;
    functions.push_back(init);
    functions.push_back(exit);
    functions.push_back(main);
    Stack mainStack;
    mainStack.id = main.id;
    mainStack.line = 0;
    Stack exitStack;
    exitStack.id = exit.id;
    exitStack.line = 0;
    stack.push_back(exitStack);
    stack.push_back(mainStack);
    currentStack->id = init.id;
    currentStack->line = 0;
}

void AddFunctionReturn(std::vector<Function> &functions)
{
    Instruction ret;
    ret.type = "return";
    if (functions.size() > 0) for (int i = 0; i < functions.size(); i++) functions[i].instructions.push_back(ret);
}

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

void GameInputSetFrame(GameInput* SRC, std::string key, std::vector<std::string> parameter)
{
    if (key == TASInputLayout.ESC) SRC->ESC = true;
    if (key == TASInputLayout.TAB) SRC->TAB = true;
    if (key == TASInputLayout.LSHIFT) SRC->LSHIFT = true;
    if (key == TASInputLayout.RSHIFT) SRC->RSHIFT = true;
    if (key == TASInputLayout.CTRL) SRC->CTRL = true;
    if (key == TASInputLayout.ALT) SRC->ALT = true;
    if (key == TASInputLayout.BACK) SRC->BACK = true;
    if (key == TASInputLayout.RETURN) SRC->RETURN = true;
    if (key == TASInputLayout.SPACE) SRC->SPACE = true;
    if (key == TASInputLayout.AUP) SRC->AUP = true;
    if (key == TASInputLayout.ARIGHT) SRC->ARIGHT = true;
    if (key == TASInputLayout.ADOWN) SRC->ADOWN = true;
    if (key == TASInputLayout.ALEFT) SRC->ALEFT = true;
    if (key == TASInputLayout.D0) SRC->D0 = true;
    if (key == TASInputLayout.D1) SRC->D1 = true;
    if (key == TASInputLayout.D2) SRC->D2 = true;
    if (key == TASInputLayout.D3) SRC->D3 = true;
    if (key == TASInputLayout.D4) SRC->D4 = true;
    if (key == TASInputLayout.D5) SRC->D5 = true;
    if (key == TASInputLayout.D6) SRC->D6 = true;
    if (key == TASInputLayout.D7) SRC->D7 = true;
    if (key == TASInputLayout.D8) SRC->D8 = true;
    if (key == TASInputLayout.D9) SRC->D9 = true;
    if (key == TASInputLayout.A) SRC->A = true;
    if (key == TASInputLayout.B) SRC->B = true;
    if (key == TASInputLayout.C) SRC->C = true;
    if (key == TASInputLayout.D) SRC->D = true;
    if (key == TASInputLayout.E) SRC->E = true;
    if (key == TASInputLayout.F) SRC->F = true;
    if (key == TASInputLayout.G) SRC->G = true;
    if (key == TASInputLayout.H) SRC->H = true;
    if (key == TASInputLayout.I) SRC->I = true;
    if (key == TASInputLayout.J) SRC->J = true;
    if (key == TASInputLayout.K) SRC->K = true;
    if (key == TASInputLayout.L) SRC->L = true;
    if (key == TASInputLayout.M) SRC->M = true;
    if (key == TASInputLayout.N) SRC->N = true;
    if (key == TASInputLayout.O) SRC->O = true;
    if (key == TASInputLayout.P) SRC->P = true;
    if (key == TASInputLayout.Q) SRC->Q = true;
    if (key == TASInputLayout.R) SRC->R = true;
    if (key == TASInputLayout.S) SRC->S = true;
    if (key == TASInputLayout.T) SRC->T = true;
    if (key == TASInputLayout.U) SRC->U = true;
    if (key == TASInputLayout.V) SRC->V = true;
    if (key == TASInputLayout.W) SRC->W = true;
    if (key == TASInputLayout.X) SRC->X = true;
    if (key == TASInputLayout.Y) SRC->Y = true;
    if (key == TASInputLayout.Z) SRC->Z = true;
    if (key == TASInputLayout.NUM0) SRC->NUM0 = true;
    if (key == TASInputLayout.NUM1) SRC->NUM1 = true;
    if (key == TASInputLayout.NUM2) SRC->NUM2 = true;
    if (key == TASInputLayout.NUM3) SRC->NUM3 = true;
    if (key == TASInputLayout.NUM4) SRC->NUM4 = true;
    if (key == TASInputLayout.NUM5) SRC->NUM5 = true;
    if (key == TASInputLayout.NUM6) SRC->NUM6 = true;
    if (key == TASInputLayout.NUM7) SRC->NUM7 = true;
    if (key == TASInputLayout.NUM8) SRC->NUM8 = true;
    if (key == TASInputLayout.NUM9) SRC->NUM9 = true;
    if (key == TASInputLayout.NUMDIV) SRC->NUMDIV = true;
    if (key == TASInputLayout.NUMMUL) SRC->NUMMUL = true;
    if (key == TASInputLayout.NUMMIN) SRC->NUMMIN = true;
    if (key == TASInputLayout.NUMPLU) SRC->NUMPLU = true;
    if (key == TASInputLayout.NUMRET) SRC->NUMRET = true;
    if (key == TASInputLayout.NUMDEL) SRC->NUMDEL = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.F1) SRC->F1 = true;
    if (key == TASInputLayout.COMMA) SRC->COMMA = true;
    if (key == TASInputLayout.DOT) SRC->DOT = true;
    if (key == TASInputLayout.PLUS) SRC->PLUS = true;
    if (key == TASInputLayout.MINUS) SRC->MINUS = true;
    if (key == TASInputLayout.LMB) SRC->LMB = true;
    if (key == TASInputLayout.RMB) SRC->RMB = true;
    if (key == TASInputLayout.MB) SRC->MB = true;
    if (key == TASInputLayout.ME1) SRC->ME1 = true;
    if (key == TASInputLayout.ME2) SRC->ME2 = true;
    if (key == TASInputLayout.WHEEL && parameter[0] != "0") SRC->WHEEL = std::stoi(parameter[0]);
    if (key == TASInputLayout.MOUSEX && parameter[0] != "0") SRC->MOUSEX = std::stoi(parameter[0]);
    if (key == TASInputLayout.MOUSEY && parameter[0] != "0") SRC->MOUSEY = std::stoi(parameter[0]);
    if (key == TASInputLayout.JOYA) SRC->JOYA = true;
    if (key == TASInputLayout.JOYB) SRC->JOYB = true;
    if (key == TASInputLayout.JOYX) SRC->JOYX = true;
    if (key == TASInputLayout.JOYY) SRC->JOYY = true;
    if (key == TASInputLayout.JOYSTART) SRC->JOYSTART = true;
    if (key == TASInputLayout.JOYSELECT) SRC->JOYSELECT = true;
    if (key == TASInputLayout.JOYRB) SRC->JOYRB = true;
    if (key == TASInputLayout.JOYLB) SRC->JOYLB = true;
    if (key == TASInputLayout.JOYUP) SRC->JOYUP = true;
    if (key == TASInputLayout.JOYDOWN) SRC->JOYDOWN = true;
    if (key == TASInputLayout.JOYRIGHT) SRC->JOYRIGHT = true;
    if (key == TASInputLayout.JOYLEFT) SRC->JOYLEFT = true;
    if (key == TASInputLayout.JOYRT && parameter[0] != "0") SRC->JOYRT = std::stoi(parameter[0]);
    if (key == TASInputLayout.JOYLT && parameter[0] != "0") SRC->JOYLT = std::stoi(parameter[0]);
    if (key == TASInputLayout.JOYRAXISX && parameter[0] != "0") SRC->JOYRAXISX = std::stoi(parameter[0]);
    if (key == TASInputLayout.JOYRAXISY && parameter[0] != "0") SRC->JOYRAXISY = std::stoi(parameter[0]);
    if (key == TASInputLayout.JOYLAXISX && parameter[0] != "0") SRC->JOYLAXISX = std::stoi(parameter[0]);
    if (key == TASInputLayout.JOYLAXISY && parameter[0] != "0") SRC->JOYLAXISY = std::stoi(parameter[0]);
    if (key == TASInputLayout.JOYRS) SRC->JOYRS = true;
    if (key == TASInputLayout.JOYLS) SRC->JOYLS = true;
    if (parameter.size() > 1)
    {
        if (parameter[1] == "set")
        {
            SRC->SETMOUSE = true;
        }
    }
}

bool VariableCondition(std::string condition)
{
    std::string paramA = "";
    std::string paramB = "";
    std::string paramC = "";

    if (condition.find("==") != std::string::npos)
    {
        paramA = condition.substr(0, condition.find("=="));
        paramB = "==";
        paramC = condition.substr(condition.find("==") + 2, condition.length() - (condition.find("==") + 2));
    }
    else if (condition.find("!=") != std::string::npos)
    {
        paramA = condition.substr(0, condition.find("!="));
        paramB = "!=";
        paramC = condition.substr(condition.find("!=") + 2, condition.length() - (condition.find("!=") + 2));
    }
    else if (condition.find("<=") != std::string::npos)
    {
        paramA = condition.substr(0, condition.find("<="));
        paramB = "<=";
        paramC = condition.substr(condition.find("<=") + 2, condition.length() - (condition.find("<=") + 2));
    }
    else if (condition.find(">=") != std::string::npos)
    {
        paramA = condition.substr(0, condition.find(">="));
        paramB = ">=";
        paramC = condition.substr(condition.find(">=") + 2, condition.length() - (condition.find(">=") + 2));
    }
    else if (condition.find("<") != std::string::npos)
    {
        paramA = condition.substr(0, condition.find("<"));
        paramB = "<";
        paramC = condition.substr(condition.find("<") + 1, condition.length() - (condition.find("<") + 1));
    }
    else if (condition.find(">") != std::string::npos)
    {
        paramA = condition.substr(0, condition.find(">"));
        paramB = ">";
        paramC = condition.substr(condition.find(">") + 1, condition.length() - (condition.find(">") + 1));
    }
    else
    {
        paramA = condition;
    }

    std::string valueA = paramA;
    std::string typeA = GetValueType(paramA);
    if (paramA.find(".") != std::string::npos && !is_digits(paramA, "."))
    {
        // Debug address
        std::string parentName = paramA.substr(0, paramA.find("."));
        std::string childName = paramA.substr(paramA.find(".") + 1, paramA.length() - (paramA.find(".") + 1));
        DebugAddress debugAddress;
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
                        debugAddress = DebugAddresses[i].addresses[k];
                        found = true;
                        break;
                    }
                }
                break;
            }
        }

        if (found)
        {
            // Debug address
            pGetDebugAddressValue(&debugAddress);
            valueA = debugAddress.value.value;
            typeA = debugAddress.value.type;
        }
        else
        {
            return false;
        }
    }
    else if (typeA == "")
    {
        // TAS variable
        for (int i = 0; i < TASScriptVariables.size(); i++)
        {
            if (TASScriptVariables[i].name == paramA)
            {
                valueA = TASScriptVariables[i].value;
                typeA = TASScriptVariables[i].type;
                break;
            }
        }
    }

    if (paramB == "" && paramC == "")
    {
        if (valueA == "none") return false;
        if (typeA == "bool") return (valueA == "true" ? true : false);
        if (typeA == "byte") return (valueA != "0" ? true : false);
        if (typeA == "int32") return (valueA != "0" ? true : false);
        if (typeA == "int64") return (valueA != "0" ? true : false);
        if (typeA == "float") return (valueA != "0" ? true : false);
        if (typeA == "double") return (valueA != "0" ? true : false);
        if (typeA == "string") return (valueA != "" ? true : false);
    }
    else
    {
        std::string valueC = paramC;
        std::string typeC = GetValueType(paramC);
        if (paramC.find(".") != std::string::npos && !is_digits(paramC, "."))
        {
            // Debug address
            std::string parentName = paramC.substr(0, paramC.find("."));
            std::string childName = paramC.substr(paramC.find(".") + 1, paramC.length() - (paramC.find(".") + 1));
            DebugAddress debugAddress;
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
                            debugAddress = DebugAddresses[i].addresses[k];
                            found = true;
                            break;
                        }
                    }
                    break;
                }
            }

            if (found)
            {
                // Debug address
                pGetDebugAddressValue(&debugAddress);
                valueC = debugAddress.value.value;
                typeC = debugAddress.value.type;
            }
            else
            {
                return false;
            }
        }
        else if(typeC == "")
        {
            // TAS variable
            for (int i = 0; i < TASScriptVariables.size(); i++)
            {
                if (TASScriptVariables[i].name == paramC)
                {
                    valueC = TASScriptVariables[i].value;
                    typeC = TASScriptVariables[i].type;
                    break;
                }
            }
        }

        long long vallA;
        long long vallC;
        double valdA;
        double valdC;
        std::string valsA;
        std::string valsC;
        bool valbA;
        bool valbC;

        if (typeA == "int32" || typeA == "int64" || typeA == "byte") vallA = GetVariableInt64(valueA);
        if (typeC == "int32" || typeC == "int64" || typeC == "byte") vallC = GetVariableInt64(valueC);
        if (typeA == "float" || typeA == "double") valdA = GetVariableDouble(valueA);
        if (typeC == "float" || typeC == "double") valdC = GetVariableDouble(valueC);
        if (typeA == "string") valsA = GetVariableString(valueA);
        if (typeC == "int32") valsC = GetVariableString(valueC);
        if (typeA == "bool") valbA = GetVariableBool(valueA);
        if (typeC == "bool") valbC = GetVariableBool(valueC);

        if (paramB == "==")
        {
            if ((typeA == "int32" || typeA == "int64" || typeA == "byte") && (typeC == "int32" || typeC == "int64" || typeC == "byte")) return vallA == vallC;
            if ((typeA == "float" || typeA == "double") && (typeC == "float" || typeC == "double")) return valdA == valdC;
            if (typeA == "string" && typeC == "string") return valsA == valsC;
            if (typeA == "bool" && typeC == "bool") return valbA == valbC;
        }
        else if (paramB == "!=")
        {
            if ((typeA == "int32" || typeA == "int64" || typeA == "byte") && (typeC == "int32" || typeC == "int64" || typeC == "byte")) return vallA != vallC;
            if ((typeA == "float" || typeA == "double") && (typeC == "float" || typeC == "double")) return valdA != valdC;
            if (typeA == "string" && typeC == "string") return valsA != valsC;
            if (typeA == "bool" && typeC == "bool") return valbA != valbC;
        }
        else if (paramB == "<=")
        {
            if ((typeA == "int32" || typeA == "int64" || typeA == "byte") && (typeC == "int32" || typeC == "int64" || typeC == "byte")) return vallA <= vallC;
            if ((typeA == "float" || typeA == "double") && (typeC == "float" || typeC == "double")) return valdA <= valdC;
        }
        else if (paramB == ">=")
        {
            if ((typeA == "int32" || typeA == "int64" || typeA == "byte") && (typeC == "int32" || typeC == "int64" || typeC == "byte")) return vallA >= vallC;
            if ((typeA == "float" || typeA == "double") && (typeC == "float" || typeC == "double")) return valdA >= valdC;
        }
        else if (paramB == "<")
        {
            if ((typeA == "int32" || typeA == "int64" || typeA == "byte") && (typeC == "int32" || typeC == "int64" || typeC == "byte")) return vallA < vallC;
            if ((typeA == "float" || typeA == "double") && (typeC == "float" || typeC == "double")) return valdA < valdC;
        }
        else if (paramB == ">")
        {
            if ((typeA == "int32" || typeA == "int64" || typeA == "byte") && (typeC == "int32" || typeC == "int64" || typeC == "byte")) return vallA > vallC;
            if ((typeA == "float" || typeA == "double") && (typeC == "float" || typeC == "double")) return valdA > valdC;
        }
    }

    return false;
}

int PlayInstruction(Instruction instruction)
{
    if (instruction.type == "ifjmp" || instruction.type == "ifnotjmp")
    {
        bool condition = false;

        if (instruction.parameter[1] == "&&")
        {
            // AND conditions
            for (int i = 2; i < instruction.parameter.size(); i++)
            {
                if (!VariableCondition(instruction.parameter[i]))
                {
                    condition = false;
                    break;
                }
                condition = true;
            }
        }
        else if (instruction.parameter[1] == "||")
        {
            // OR conditions
            for (int i = 2; i < instruction.parameter.size(); i++)
            {
                if (VariableCondition(instruction.parameter[i]))
                {
                    condition = true;
                    break;
                }
            }
        }
        else
        {
            // Single condition
            condition = VariableCondition(instruction.parameter[1]);
        }

        if (instruction.type == "ifjmp") if (condition) TASCurrentStack.line += std::stoi(instruction.parameter[0]); else TASCurrentStack.line++;
        if (instruction.type == "ifnotjmp") if (!condition) TASCurrentStack.line += std::stoi(instruction.parameter[0]); else TASCurrentStack.line++;
    }
    else if (instruction.type == "jmp")
    {
        TASCurrentStack.line += std::stoi(instruction.parameter[0]);
    }
    else if (instruction.type == "return")
    {
        if(TASStack.size() == 0) return 2;
        TASCurrentStack = TASStack[TASStack.size() - 1];
        TASStack.pop_back();
    }
    else if (instruction.type == "exit")
    {
        TASCurrentStack = TASStack[0];
        TASStack.clear();
    }
    else if (instruction.type == "log")
    {
        std::string finalText = "";
        for (int i = 0; i < instruction.parameter.size(); i++)
        {
            if (instruction.parameter[i].substr(0, 1) == "\"")
            {
                finalText = finalText + instruction.parameter[i].substr(1, instruction.parameter[i].length() - 2);
            }
            else
            {
                if (instruction.parameter[i].find(".") != std::string::npos && !is_digits(instruction.parameter[i], "."))
                {
                    // Debug address
                    std::string parentName = instruction.parameter[1].substr(0, instruction.parameter[1].find("."));
                    std::string childName = instruction.parameter[1].substr(instruction.parameter[1].find(".") + 1, instruction.parameter[1].length() - (instruction.parameter[1].find(".") + 1));
                    DebugAddress debugAddress;
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
                                    debugAddress = DebugAddresses[i].addresses[k];
                                    found = true;
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    if (found)
                    {
                        // Debug address
                        finalText = finalText + debugAddress.value.value;
                    }
                }
                else if(GetValueType(instruction.parameter[i]) == "")
                {
                    // TAS variable
                    for (int i = 0; i < TASScriptVariables.size(); i++)
                    {
                        if (TASScriptVariables[i].name == instruction.parameter[i])
                        {
                            finalText = finalText + TASScriptVariables[i].value;
                            break;
                        }
                    }
                }
            }
        }
        TASCurrentStack.line++;
    }
    else if (instruction.type == "byte" || instruction.type == "int32" || instruction.type == "int64" || instruction.type == "float" || instruction.type == "double" || instruction.type == "string" || instruction.type == "bool")
    {
        Variable variable;
        variable.type = instruction.type;
        variable.name = instruction.parameter[0];
        SetVariable(&variable, instruction.parameter[1]);
        TASScriptVariables.push_back(variable);
        TASCurrentStack.line++;
    }
    else if (instruction.type == "remove")
    {
        for (int i = 0; i < TASScriptVariables.size(); i++)
        {
            if (TASScriptVariables[i].name == instruction.parameter[0])
            {
                TASScriptVariables.erase(TASScriptVariables.begin() + i);
                break;
            }
        }
        TASCurrentStack.line++;
    }
    else if (instruction.type == "frame")
    {
        for (int i = 0; i < instruction.parameter.size(); i++)
        {
            std::string key = instruction.parameter[i];
            std::vector<std::string> params;
            if (instruction.parameter[i].find(",") != std::string::npos)
            {
                key = instruction.parameter[i].substr(0, instruction.parameter[i].find(","));
                std::string allParams = instruction.parameter[i].substr(instruction.parameter[i].find(",") + 1, instruction.parameter[i].length() - (instruction.parameter[i].find(",") + 1));
                splitStringVector(params, allParams, ",");
            }
            GameInputSetFrame(&TASInputCurrent, key, params);
        }
        TASCurrentStack.line++;
        return 1;
    }
    else if (instruction.type == "plus" || instruction.type == "minus" || instruction.type == "multi" || instruction.type == "divide" || instruction.type == "equal")
    {
        std::string value = instruction.parameter[1];
        std::string type = GetValueType(instruction.parameter[1]);
        if (instruction.parameter[1].find(".") != std::string::npos && !is_digits(instruction.parameter[1], "."))
        {
            // Debug address
            std::string parentName = instruction.parameter[1].substr(0, instruction.parameter[1].find("."));
            std::string childName = instruction.parameter[1].substr(instruction.parameter[1].find(".") + 1, instruction.parameter[1].length() - (instruction.parameter[1].find(".") + 1));
            DebugAddress debugAddress;
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
                            debugAddress = DebugAddresses[i].addresses[k];
                            found = true;
                            break;
                        }
                    }
                    break;
                }
            }

            if (found)
            {
                // Debug address
                pGetDebugAddressValue(&debugAddress);
                value = debugAddress.value.value;
                type = debugAddress.value.type;
            }
            else
            {
                return false;
            }
        }
        else if(type == "")
        {
            // TAS variable
            for (int i = 0; i < TASScriptVariables.size(); i++)
            {
                if (TASScriptVariables[i].name == instruction.parameter[1])
                {
                    value = TASScriptVariables[i].value;
                    type = TASScriptVariables[i].type;
                    break;
                }
            }
        }

        if (instruction.parameter[0].find(".") != std::string::npos && !is_digits(instruction.parameter[0], "."))
        {
            if (DebugAddresses.size() > 0)
            {
                std::string parentName = instruction.parameter[0].substr(0, instruction.parameter[0].find("."));
                std::string childName = instruction.parameter[0].substr(instruction.parameter[0].find(".") + 1, instruction.parameter[0].length() - (instruction.parameter[0].find(".") + 1));
                DebugAddress debugAddress;
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
                                debugAddress = DebugAddresses[i].addresses[k];
                                found = true;
                                break;
                            }
                        }
                        break;
                    }
                }

                if (found)
                {
                    // Debug address
                    if (instruction.type == "plus")
                    {
                        pGetDebugAddressValue(&debugAddress);
                        if (debugAddress.value.value != "none")
                        {
                            VariableAdd(&debugAddress.value, value);
                            if (debugAddress.value.value != "none")
                            {
                                pSetDebugAddressValue(&debugAddress);
                            }
                        }
                    }
                    else if (instruction.type == "minus")
                    {
                        pGetDebugAddressValue(&debugAddress);
                        if (debugAddress.value.value != "none")
                        {
                            VariableSubtract(&debugAddress.value, value);
                            if (debugAddress.value.value != "none")
                            {
                                pSetDebugAddressValue(&debugAddress);
                            }
                        }
                    }
                    else if (instruction.type == "multi")
                    {
                        pGetDebugAddressValue(&debugAddress);
                        if (debugAddress.value.value != "none")
                        {
                            VariableMultiply(&debugAddress.value, value);
                            if (debugAddress.value.value != "none")
                            {
                                pSetDebugAddressValue(&debugAddress);
                            }
                        }
                    }
                    else if (instruction.type == "divide")
                    {
                        pGetDebugAddressValue(&debugAddress);
                        if (debugAddress.value.value != "none")
                        {
                            VariableDivide(&debugAddress.value, value);
                            if (debugAddress.value.value != "none")
                            {
                                pSetDebugAddressValue(&debugAddress);
                            }
                        }
                    }
                    else if (instruction.type == "equal")
                    {
                        pGetDebugAddressValue(&debugAddress);
                        if (debugAddress.value.value != "none")
                        {
                            SetVariable(&debugAddress.value, value);
                            if (debugAddress.value.value != "none")
                            {
                                pSetDebugAddressValue(&debugAddress);
                            }
                        }
                    }
                }
            }
        }
        else if(GetValueType(instruction.parameter[0]) == "")
        {
            // TAS variable
            for (int i = 0; i < TASScriptVariables.size(); i++)
            {
                if (TASScriptVariables[i].name == instruction.parameter[0])
                {
                    if (instruction.type == "plus")
                    {
                        VariableAdd(&TASScriptVariables[i], value);
                    }
                    else if (instruction.type == "minus")
                    {
                        VariableSubtract(&TASScriptVariables[i], value);
                    }
                    else if (instruction.type == "multi")
                    {
                        VariableMultiply(&TASScriptVariables[i], value);
                    }
                    else if (instruction.type == "divide")
                    {
                        VariableDivide(&TASScriptVariables[i], value);
                    }
                    else if (instruction.type == "equal")
                    {
                        SetVariable(&TASScriptVariables[i], value);
                    }
                    break;
                }
            }
        }
        TASCurrentStack.line++;
    }
    else
    {
        // Function
        if (instruction.type.find(".") != std::string::npos && !is_digits(instruction.type, "."))
        {
            // Debug function
            std::string parentName = instruction.type.substr(0, instruction.type.find("."));
            std::string childName = instruction.type.substr(instruction.type.find(".") + 1, instruction.type.length() - (instruction.type.find(".") + 1));
            DebugFunction debugFunction;
            bool found = false;
            for (int i = 0; i < DebugAddresses.size(); i++)
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
                            debugFunction = DebugFunctions[i].functions[k];
                            found = true;
                            break;
                        }
                    }
                    break;
                }
            }

            if (found)
            {
                for (int i = 0; i < instruction.parameter.size(); i++)
                {
                    std::string value = instruction.parameter[i];
                    std::string type = GetValueType(instruction.parameter[i]);
                    if (value.find(".") != std::string::npos && !is_digits(value, "."))
                    {
                        // Debug address
                        std::string parentName = value.substr(0, value.find("."));
                        std::string childName = value.substr(value.find(".") + 1, value.length() - (value.find(".") + 1));
                        DebugAddress debugAddress;
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
                                        debugAddress = DebugAddresses[i].addresses[k];
                                        found = true;
                                        break;
                                    }
                                }
                                break;
                            }
                        }

                        if (found)
                        {
                            // Debug address
                            pGetDebugAddressValue(&debugAddress);
                            value = debugAddress.value.value;
                            type = debugAddress.value.type;
                        }
                        else
                        {
                            value = "none";
                        }
                    }
                    else if (type == "")
                    {
                        // TAS variable
                        for (int i = 0; i < TASScriptVariables.size(); i++)
                        {
                            if (TASScriptVariables[i].name == value)
                            {
                                value = TASScriptVariables[i].value;
                                type = TASScriptVariables[i].type;
                                break;
                            }
                        }
                    }
                    SetVariable(&debugFunction.parameter[i], value);
                }
                std::cout << "Execute!" << std::endl;
                std::cout << debugFunction.nameFull << std::endl;
                pExecuteDebugFunction(&debugFunction);
            }
            TASCurrentStack.line++;
        }
        else
        {
            // TAS function
            for (int i = 0; i < TASScriptFunctions.size(); i++)
            {
                if (TASScriptFunctions[i].name == instruction.type)
                {
                    TASCurrentStack.line++;
                    TASStack.push_back(TASCurrentStack);
                    TASCurrentStack.id = TASScriptFunctions[i].id;
                    TASCurrentStack.line = 0;
                    break;
                }
            }
        }
    }

    return 0;
}

bool __stdcall PlayScriptRoutine() {
    try
    {
        // Play the script
        if (TASPlayScriptInit) {
            TASFunctionId = 0;
            TASRepeatNamer = 0;
            TASFramesPassed = 0;

            // Clear vector if not empty
            if (TASScriptFunctions.size() > 0) TASScriptFunctions.clear();
            if (TASScriptVariables.size() > 0) TASScriptVariables.clear();
            if (TASStack.size() > 0) TASStack.clear();

            // Read Script
            AddFunctionLifecycles(TASScriptFunctions, TASStack, &TASCurrentStack);
            ParseFunction(TASScriptFunctions, ReadScript(TASScript));
            AddFunctionReturn(TASScriptFunctions);

            if (DevMode)
            {
                DebugConsoleOutput("Functions vector size: " + std::to_string(TASScriptFunctions.size()), true, "blue");
                for (int f = 0; f < TASScriptFunctions.size(); f++)
                {
                    DebugConsoleOutput("Name: " + TASScriptFunctions[f].name, true, "blue");
                    DebugConsoleOutput("ID: " + std::to_string(TASScriptFunctions[f].id), true, "blue");
                    DebugConsoleOutput("Size: " + std::to_string(TASScriptFunctions[f].instructions.size()), true, "blue");
                }
            }

            std::memset(&TASInputCurrent, 0x00, sizeof(GameInput));
            std::memset(&TASInputLast, 0x00, sizeof(GameInput));
            std::memset(&TASInputMouse, 0x00, sizeof(GameInput));
            std::memset(&TASInputKeyboard, 0x00, sizeof(GameInput));
            std::memset(&TASInputJoystick, 0x00, sizeof(GameInput));

            InitTASPlayers();

            // Disable Init Trigger
            TASPlayScriptInit = false;
            TASPlaySkipFirstSync = true;
        }

        if (TASPlayScript && !TASPlayScriptUninit) {
            bool TASPlayCanExecute = true;

            if (InputDriverMouseSet != InputDriverz::N0NE)
            {
                if (InputDriverMouseSet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputMouseSend || GetRawInputSendInformation)) TASPlayCanExecute = false;
                if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8MouseSend || DirectInput8SendInformation)) TASPlayCanExecute = false;
                if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA && TASSynchronizer.GetMessageAMouseSend) TASPlayCanExecute = false;
                if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW && TASSynchronizer.GetMessageWMouseSend) TASPlayCanExecute = false;
                if (InputDriverMouseSet == InputDriverz::S3ND1NPUT && TASSynchronizer.SendInputMouseSend) TASPlayCanExecute = false;
            }
            if (InputDriverKeyboardSet != InputDriverz::N0NE)
            {
                if (InputDriverKeyboardSet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputKeyboardSend || GetRawInputSendInformation)) TASPlayCanExecute = false;
                if (InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8KeyboardSend || DirectInput8SendInformation)) TASPlayCanExecute = false;
                if (InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA && TASSynchronizer.GetMessageAKeyboardSend) TASPlayCanExecute = false;
                if (InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW && TASSynchronizer.GetMessageWKeyboardSend) TASPlayCanExecute = false;
                if (InputDriverKeyboardSet == InputDriverz::S3ND1NPUT && TASSynchronizer.SendInputKeyboardSend) TASPlayCanExecute = false;
            }
            if (InputDriverJoystickSet != InputDriverz::N0NE)
            {
                if (InputDriverJoystickSet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputJoystickSend || GetRawInputSendInformation)) TASPlayCanExecute = false;
                if (InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8JoystickSend || DirectInput8SendInformation)) TASPlayCanExecute = false;
                if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4 && (TASSynchronizer.XInput1_4JoystickSend || GetXInput1_4SendInformation)) TASPlayCanExecute = false;
            }

            if (TASPlaySkipFirstSync)
            {
                TASPlayCanExecute = true;
                TASPlaySkipFirstSync = false;
            }

            if (TASPlayCanExecute)
            {
                //std::cout << "FRAME INDEX: " << std::dec << TASFramesPassed << std::endl;
                std::memcpy(&TASInputLast, &TASInputCurrent, sizeof(GameInput));
                std::memset(&TASInputCurrent, 0x00, sizeof(GameInput));
                std::memset(&TASInputMouse, 0x00, sizeof(GameInput));
                std::memset(&TASInputKeyboard, 0x00, sizeof(GameInput));
                std::memset(&TASInputJoystick, 0x00, sizeof(GameInput));

                while (TASPlayScript && !TASPlayScriptUninit)
                {
                    DebugConsoleOutput("Stack ID: " + std::to_string(TASCurrentStack.id), true, "blue");
                    DebugConsoleOutput("Stack Line: " + std::to_string(TASCurrentStack.line), true, "blue");

                    Instruction instruction = TASScriptFunctions[TASCurrentStack.id].instructions[TASCurrentStack.line];

                    int result = PlayInstruction(instruction);
                    if (result == 0)
                    {
                        // Next instruction
                    }
                    if (result == 1)
                    {
                        // Frame found
                        TASSynchronizer.RawInputKeyboardSend = true;
                        TASSynchronizer.RawInputMouseSend = true;
                        TASSynchronizer.RawInputJoystickSend = true;
                        TASSynchronizer.DirectInput8KeyboardSend = true;
                        TASSynchronizer.DirectInput8MouseSend = true;
                        TASSynchronizer.DirectInput8JoystickSend = true;
                        TASSynchronizer.XInput1_4JoystickSend = true;
                        TASSynchronizer.GetMessageAKeyboardSend = true;
                        TASSynchronizer.GetMessageAMouseSend = true;
                        TASSynchronizer.GetMessageWKeyboardSend = true;
                        TASSynchronizer.GetMessageWMouseSend = true;
                        TASSynchronizer.SendInputKeyboardSend = true;
                        TASSynchronizer.SendInputMouseSend = true;

                        SetTASInput(TASInputCurrent);
                        Sleep(5);

                        break;
                    }
                    if (result == 2)
                    {
                        // Exit script
                        TASPlayScriptUninit = true;
                        break;
                    }
                    if (result == -1)
                    {
                        // Error in script
                        DebugConsoleOutput("Error: TASPlayScript()", false, "red");
                        DebugConsoleOutput(TASLastError, false, "red");
                        TASPlayScriptUninit = true;
                        break;
                    }

                }

                TASFramesPassed++;
            }
            if (!TASPlayScriptUninit) return true;
        }

        if (TASPlayScriptUninit) {
            DebugConsoleOutput("TAS Play: Exit playing", false, "green");
            DebugConsoleOutput("TAS Play: Played " + std::to_string(TASFramesPassed) + " frames", false, "green");

            // Disable Uninit Trigger
            TASPlayScriptUninit = false;
            TASPlayScript = false;
            TASPlayScriptDone = true;
            TASPlaySkipFirstSync = false;

            if (TASPlayScriptThenRecord)
            {
                TASRecordScriptInit = true;
                TASRecordScript = true;
                TASRecordScriptUninit = false;
                TASRecordScriptDone = false;
                TASRecordStartedSignal = true;
            }

            UninitTASPlayers();
            return true;
        }
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: TASPlayScript()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");

        TASPlayScriptInit = false;
        TASPlayScriptUninit = false;
        TASPlayScript = false;
        TASPlayScriptDone = true;
        TASPlaySkipFirstSync = false;

        if (TASScriptFunctions.size() > 0) TASScriptFunctions.clear();
        if (TASScriptVariables.size() > 0) TASScriptVariables.clear();
        if (TASStack.size() > 0) TASStack.clear();

        UninitTASPlayers();
    }
    return false;
}



bool __stdcall RecordScriptRoutine() {
    try
    {
        // Record the script
        if (TASRecordScriptInit && !TASRecordScriptUninit) {
            // Create output file
            TASRecordScriptStream = std::ofstream(TASScript, std::ios_base::app | std::ios_base::out);
            TASFramesPassed = 0;

            auto r_t = std::time(nullptr);
            auto r_tm = *std::localtime(&r_t);
            TASRecordScriptStream << std::endl;
            TASRecordScriptStream << "//###################################" << std::endl;
            TASRecordScriptStream << "//# Recording Script time: " << std::put_time(&r_tm, "%H-%M-%S") << " #" << std::endl;
            TASRecordScriptStream << "//###################################" << std::endl;
            TASRecordScriptStream << std::endl;
            TASRecordScriptStream << "main" << std::endl;
            TASRecordScriptStream << "{" << std::endl;

            if (!TASPlayScriptThenRecord)
            {
                std::memset(&TASInputCurrent, 0x00, sizeof(GameInput));
                std::memset(&TASInputLast, 0x00, sizeof(GameInput));
                std::memset(&TASInputMouse, 0x00, sizeof(GameInput));
                std::memset(&TASInputKeyboard, 0x00, sizeof(GameInput));
                std::memset(&TASInputJoystick, 0x00, sizeof(GameInput));
            }

            InitTASRecorders();

            // Disable Init Trigger
            TASRecordScriptInit = false;
            TASRecordSkipFirstSync = true;
        }

        if (TASRecordScript && !TASRecordScriptUninit) {

            if (TASRecordFrameByFrame)
            {
                bool TASRecordCanExecute = true;

                Sleep(1);

                if (InputDriverMouseSet != InputDriverz::N0NE)
                {
                    if (InputDriverMouseSet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputMouseSend || GetRawInputSendInformation)) TASRecordCanExecute = false;
                    if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8MouseSend || DirectInput8SendInformation)) TASRecordCanExecute = false;
                    if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA && TASSynchronizer.GetMessageAMouseSend) TASRecordCanExecute = false;
                    if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW && TASSynchronizer.GetMessageWMouseSend) TASRecordCanExecute = false;
                    if (InputDriverMouseSet == InputDriverz::S3ND1NPUT && TASSynchronizer.SendInputMouseSend) TASRecordCanExecute = false;
                }
                if (InputDriverKeyboardSet != InputDriverz::N0NE)
                {
                    if (InputDriverKeyboardSet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputKeyboardSend || GetRawInputSendInformation)) TASRecordCanExecute = false;
                    if (InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8KeyboardSend || DirectInput8SendInformation)) TASRecordCanExecute = false;
                    if (InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA && TASSynchronizer.GetMessageAKeyboardSend) TASRecordCanExecute = false;
                    if (InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW && TASSynchronizer.GetMessageWKeyboardSend) TASRecordCanExecute = false;
                    if (InputDriverKeyboardSet == InputDriverz::S3ND1NPUT && TASSynchronizer.SendInputKeyboardSend) TASRecordCanExecute = false;
                }
                if (InputDriverJoystickSet != InputDriverz::N0NE)
                {
                    if (InputDriverJoystickSet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputJoystickSend || GetRawInputSendInformation)) TASRecordCanExecute = false;
                    if (InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8JoystickSend || DirectInput8SendInformation)) TASRecordCanExecute = false;
                    if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4 && (TASSynchronizer.XInput1_4JoystickSend || GetXInput1_4SendInformation)) TASRecordCanExecute = false;
                }

                if (TASPlaySkipFirstSync)
                {
                    TASRecordCanExecute = true;
                    TASPlaySkipFirstSync = false;
                }

                if (TASRecordCanExecute)
                {
                    std::cout << "111" << std::endl;
                    while (TASRecordFrameReceived == "" && !TASRecordScriptUninit)
                    {
                        Sleep(3);
                    }
                    std::cout << "222" << std::endl;
                    if (!TASRecordScriptUninit)
                    {
                        TASRecordScriptStream << TASRecordFrameReceived << std::endl;

                        DebugConsoleOutput(TASRecordFrameReceived, true, "green");

                        std::transform(TASRecordFrameReceived.begin(), TASRecordFrameReceived.end(), TASRecordFrameReceived.begin(), [](unsigned char c) { return std::tolower(c); });

                        TASRecordFrameReceived.replace(TASRecordFrameReceived.find("}"), 1, "");
                        TASRecordFrameReceived = TASRecordFrameReceived.substr(TASRecordFrameReceived.find("{") + 1, TASRecordFrameReceived.length() - (TASRecordFrameReceived.find("{") + 1));
                        if (TASRecordFrameReceived.find(" ") != std::string::npos) {
                            bool inside_quotes = false;
                            for (int i = 0; i < TASRecordFrameReceived.size(); i++) {
                                if (TASRecordFrameReceived[i] == '\"' || TASRecordFrameReceived[i] == '\'') {
                                    inside_quotes = !inside_quotes;
                                }
                                else if (TASRecordFrameReceived[i] == ' ' && !inside_quotes) {
                                    TASRecordFrameReceived.erase(i, 1);
                                    i--;
                                }
                            }
                        }

                        std::memcpy(&TASInputLast, &TASInputCurrent, sizeof(GameInput));
                        std::memset(&TASInputCurrent, 0x00, sizeof(GameInput));

                        if (TASRecordFrameReceived.find(";") != std::string::npos)
                        {
                            std::vector<std::string> instructions;
                            std::vector<std::vector<std::string>> parameter;
                            splitStringVector(instructions, TASRecordFrameReceived, ";");
                            int index = 0;
                            while (index < instructions.size())
                            {
                                if (instructions[index].find("("))
                                {
                                    std::vector<std::string> subParameter;
                                    splitStringVector(subParameter, instructions[index].substr(instructions[index].find("(") + 1, instructions[index].find(")") - (instructions[index].find("(") + 1)), ",");
                                    parameter.push_back(subParameter);
                                    instructions[index] = instructions[index].substr(0, instructions[index].find("("));
                                    index++;
                                }
                                else
                                {
                                    instructions.erase(instructions.begin() + index);
                                }
                            }
                            for (int i = 0; i < instructions.size(); i++)
                            {
                                GameInputSetFrame(&TASInputCurrent, instructions[i], parameter[i]);
                            }
                        }

                        if (TASRecordSkipFirstSync)
                        {
                            TASRecordSkipFirstSync = false;
                        }
                        else
                        {
                            while (TASSynchronizerFinishedCurrent < TASSynchronizerFinishedMax) Sleep(1);
                        }

                        TASSynchronizer.RawInputKeyboardSend = true;
                        TASSynchronizer.RawInputMouseSend = true;
                        TASSynchronizer.RawInputJoystickSend = true;
                        TASSynchronizer.DirectInput8KeyboardSend = true;
                        TASSynchronizer.DirectInput8MouseSend = true;
                        TASSynchronizer.DirectInput8JoystickSend = true;
                        TASSynchronizer.XInput1_4JoystickSend = true;
                        TASSynchronizer.GetMessageAKeyboardSend = true;
                        TASSynchronizer.GetMessageAMouseSend = true;
                        TASSynchronizer.GetMessageWKeyboardSend = true;
                        TASSynchronizer.GetMessageWMouseSend = true;
                        TASSynchronizer.SendInputKeyboardSend = true;
                        TASSynchronizer.SendInputMouseSend = true;

                        SetTASInput(TASInputCurrent);
                        Sleep(5);

                        // Synchronize with the drivers
                        TASSynchronizerFinishedCurrent = 0;

                        TASRecordFrameReceived = "";
                        TASFramesPassed++;
                    }
                }
            }
            else
            {
                bool TASRecordCanExecute = true;

                if (InputDriverMouseGet != InputDriverz::N0NE)
                {
                    if (InputDriverMouseGet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputMouseGet || GetRawInputGetInformation)) TASRecordCanExecute = false;
                    if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8MouseGet || DirectInput8GetInformation)) TASRecordCanExecute = false;
                    if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEA && TASSynchronizer.GetMessageAMouseGet) TASRecordCanExecute = false;
                    if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEW && TASSynchronizer.GetMessageWMouseGet) TASRecordCanExecute = false;
                    if (InputDriverMouseGet == InputDriverz::S3ND1NPUT && TASSynchronizer.SendInputMouseGet) TASRecordCanExecute = false;
                }
                if (InputDriverKeyboardGet != InputDriverz::N0NE)
                {
                    if (InputDriverKeyboardGet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputKeyboardGet || GetRawInputGetInformation)) TASRecordCanExecute = false;
                    if (InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8KeyboardGet || DirectInput8GetInformation)) TASRecordCanExecute = false;
                    if (InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEA && TASSynchronizer.GetMessageAKeyboardGet) TASRecordCanExecute = false;
                    if (InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEW && TASSynchronizer.GetMessageWKeyboardGet) TASRecordCanExecute = false;
                    if (InputDriverKeyboardGet == InputDriverz::S3ND1NPUT && TASSynchronizer.SendInputKeyboardGet) TASRecordCanExecute = false;
                }
                if (InputDriverJoystickGet != InputDriverz::N0NE)
                {
                    if (InputDriverJoystickGet == InputDriverz::RAW1NPUT && (TASSynchronizer.RawInputJoystickGet || GetRawInputGetInformation)) TASRecordCanExecute = false;
                    if (InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8 && (TASSynchronizer.DirectInput8JoystickGet || DirectInput8GetInformation)) TASRecordCanExecute = false;
                    if (InputDriverJoystickGet == InputDriverz::X1NPUT1_4 && (TASSynchronizer.XInput1_4JoystickSend || XInput1_4GetInformation)) TASRecordCanExecute = false;
                }

                if (TASPlaySkipFirstSync)
                {
                    TASRecordCanExecute = true;
                    TASPlaySkipFirstSync = false;
                }
                else
                {
                    if (TASRecordCanExecute)
                    {
                        std::memcpy(&TASInputLast, &TASInputCurrent, sizeof(GameInput));
                        std::memset(&TASInputCurrent, 0x00, sizeof(GameInput));
                        MergeGameInputs(&TASInputCurrent, &TASInputMouse, &TASInputKeyboard, &TASInputJoystick);
                        std::string RecordFrame = GameInputToFrame(&TASInputCurrent);
                        TASRecordScriptStream << RecordFrame << std::endl;
                        TASFramesPassed++;
                    }
                }

                if (TASRecordCanExecute)
                {
                    TASSynchronizer.RawInputKeyboardGet = true;
                    TASSynchronizer.RawInputMouseGet = true;
                    TASSynchronizer.RawInputJoystickGet = true;
                    TASSynchronizer.DirectInput8KeyboardGet = true;
                    TASSynchronizer.DirectInput8MouseGet = true;
                    TASSynchronizer.DirectInput8JoystickGet = true;
                    TASSynchronizer.XInput1_4JoystickGet = true;
                    TASSynchronizer.GetMessageAKeyboardGet = true;
                    TASSynchronizer.GetMessageAMouseGet = true;
                    TASSynchronizer.GetMessageWKeyboardGet = true;
                    TASSynchronizer.GetMessageWMouseGet = true;
                    TASSynchronizer.SendInputKeyboardGet = true;
                    TASSynchronizer.SendInputMouseGet = true;

                    GetTASInput();
                    Sleep(5);
                }
            }

            if (!TASRecordScriptUninit) return true;
        }

        if (TASRecordScriptUninit) {
            DebugConsoleOutput("TAS Record: Exit recording", false, "green");
            DebugConsoleOutput("TAS Record: Recorded " + std::to_string(TASFramesPassed) + " frames", false, "green");

            TASRecordScriptStream << "}" << std::endl;
            TASRecordScriptStream << std::endl;

            // Close output file stream
            TASRecordScriptStream.close();

            // Disable Uninit Trigger
            TASRecordScriptUninit = false;
            TASRecordSkipFirstSync = false;
            TASRecordScriptDone = true;

            UninitTASRecorders();
            return true;
        }
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: TASRecordScript()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");

        // Close output file stream
        if(TASRecordScriptStream.is_open()) TASRecordScriptStream.close();

        TASRecordScriptInit = false;
        TASRecordScriptUninit = false;
        TASRecordScript = false;
        TASRecordScriptDone = true;
        TASRecordSkipFirstSync = false;

        UninitTASRecorders();
    }
    return false;
}

void __stdcall TASRoutine()
{
    // Check frameskip
    GlobalFrameSkipCurrent++;
    if (GlobalFrameSkipCurrent >= GlobalSettings.config_frame_skip)
    {
        // TAS
        PlayScriptRoutine();
        RecordScriptRoutine();
        GlobalFrameSkipCurrent = 0;
    }
}