#include "pch.h"
#include "InputLayout.h"



// --- Functions ---
void MergeGameInputs(GameInput* DST, GameInput* MOUSE, GameInput* KEYBOARD, GameInput* JOYSTICK)
{
    DST->ESC = KEYBOARD->ESC;
    DST->TAB = KEYBOARD->TAB;
    DST->LSHIFT = KEYBOARD->LSHIFT;
    DST->RSHIFT = KEYBOARD->RSHIFT;
    DST->CTRL = KEYBOARD->CTRL;
    DST->ALT = KEYBOARD->ALT;
    DST->BACK = KEYBOARD->BACK;
    DST->RETURN = KEYBOARD->RETURN;
    DST->SPACE = KEYBOARD->SPACE;
    DST->AUP = KEYBOARD->SPACE;
    DST->ARIGHT = KEYBOARD->ARIGHT;
    DST->ADOWN = KEYBOARD->ADOWN;
    DST->ALEFT = KEYBOARD->ALEFT;
    DST->D0 = KEYBOARD->D0;
    DST->D1 = KEYBOARD->D1;
    DST->D2 = KEYBOARD->D2;
    DST->D3 = KEYBOARD->D3;
    DST->D4 = KEYBOARD->D4;
    DST->D5 = KEYBOARD->D5;
    DST->D6 = KEYBOARD->D6;
    DST->D7 = KEYBOARD->D7;
    DST->D8 = KEYBOARD->D8;
    DST->D9 = KEYBOARD->D9;
    DST->A = KEYBOARD->A;
    DST->B = KEYBOARD->B;
    DST->C = KEYBOARD->C;
    DST->D = KEYBOARD->D;
    DST->E = KEYBOARD->E;
    DST->F = KEYBOARD->F;
    DST->G = KEYBOARD->G;
    DST->H = KEYBOARD->H;
    DST->I = KEYBOARD->I;
    DST->J = KEYBOARD->J;
    DST->K = KEYBOARD->K;
    DST->L = KEYBOARD->L;
    DST->M = KEYBOARD->M;
    DST->N = KEYBOARD->N;
    DST->O = KEYBOARD->O;
    DST->P = KEYBOARD->P;
    DST->Q = KEYBOARD->Q;
    DST->R = KEYBOARD->R;
    DST->S = KEYBOARD->S;
    DST->T = KEYBOARD->T;
    DST->U = KEYBOARD->U;
    DST->V = KEYBOARD->V;
    DST->W = KEYBOARD->W;
    DST->X = KEYBOARD->X;
    DST->Y = KEYBOARD->Y;
    DST->Z = KEYBOARD->Z;
    DST->NUM0 = KEYBOARD->NUM0;
    DST->NUM1 = KEYBOARD->NUM1;
    DST->NUM2 = KEYBOARD->NUM2;
    DST->NUM3 = KEYBOARD->NUM3;
    DST->NUM4 = KEYBOARD->NUM4;
    DST->NUM5 = KEYBOARD->NUM5;
    DST->NUM6 = KEYBOARD->NUM6;
    DST->NUM7 = KEYBOARD->NUM7;
    DST->NUM8 = KEYBOARD->NUM8;
    DST->NUM9 = KEYBOARD->NUM9;
    DST->NUMDIV = KEYBOARD->NUMDIV;
    DST->NUMMUL = KEYBOARD->NUMMUL;
    DST->NUMMIN = KEYBOARD->NUMMIN;
    DST->NUMPLU = KEYBOARD->NUMPLU;
    DST->NUMRET = KEYBOARD->NUMRET;
    DST->NUMDEL = KEYBOARD->NUMDEL;
    DST->F1 = KEYBOARD->F1;
    DST->F2 = KEYBOARD->F2;
    DST->F3 = KEYBOARD->F3;
    DST->F4 = KEYBOARD->F4;
    DST->F5 = KEYBOARD->F5;
    DST->F6 = KEYBOARD->F6;
    DST->F7 = KEYBOARD->F7;
    DST->F8 = KEYBOARD->F8;
    DST->F9 = KEYBOARD->F9;
    DST->F10 = KEYBOARD->F10;
    DST->F11 = KEYBOARD->F11;
    DST->F12 = KEYBOARD->F12;
    DST->COMMA = KEYBOARD->COMMA;
    DST->DOT = KEYBOARD->DOT;
    DST->PLUS = KEYBOARD->PLUS;
    DST->MINUS = KEYBOARD->MINUS;
    DST->LMB = MOUSE->LMB;
    DST->RMB = MOUSE->RMB;
    DST->MB = MOUSE->MB;
    DST->ME1 = MOUSE->ME1;
    DST->ME2 = MOUSE->ME2;
    DST->WHEEL = MOUSE->WHEEL;
    DST->MOUSEX = MOUSE->MOUSEX;
    DST->MOUSEY = MOUSE->MOUSEY;
    DST->JOYA = JOYSTICK->JOYA;
    DST->JOYB = JOYSTICK->JOYB;
    DST->JOYX = JOYSTICK->JOYX;
    DST->JOYY = JOYSTICK->JOYY;
    DST->JOYSTART = JOYSTICK->JOYSTART;
    DST->JOYSELECT = JOYSTICK->JOYSELECT;
    DST->JOYRB = JOYSTICK->JOYRB;
    DST->JOYLB = JOYSTICK->JOYLB;
    DST->JOYUP = JOYSTICK->JOYUP;
    DST->JOYDOWN = JOYSTICK->JOYDOWN;
    DST->JOYRIGHT = JOYSTICK->JOYRIGHT;
    DST->JOYLEFT = JOYSTICK->JOYLEFT;
    DST->JOYRT = JOYSTICK->JOYRT;
    DST->JOYLT = JOYSTICK->JOYLT;
    DST->JOYRAXISX = JOYSTICK->JOYRAXISX;
    DST->JOYRAXISY = JOYSTICK->JOYRAXISY;
    DST->JOYLAXISX = JOYSTICK->JOYLAXISX;
    DST->JOYLAXISY = JOYSTICK->JOYLAXISY;
    DST->JOYRS = JOYSTICK->JOYRS;
    DST->JOYLS = JOYSTICK->JOYLS;
}

void LoadGameInputLayout(GameInputLayout* DST, std::string fileName)
{
    std::ifstream file(fileName);

    while (!file.eof()) {
        std::string line = "";
        std::getline(file, line);

        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });
        while (line.find(" ") != std::string::npos) line.replace(line.find(" "), 1, "");
        while (line.find(";") != std::string::npos) line.replace(line.find(";"), 1, "");

        if (line.length() > 0) {
            if (line.find("=") != std::string::npos) {
                size_t delimiter = line.find("=");
                std::string id = line.substr(0, delimiter);
                std::string map = line.substr(delimiter + 1, line.length() - delimiter - 1);

                if (id == "esc") DST->ESC = map;
                if (id == "tab") DST->TAB = map;
                if (id == "lshift") DST->LSHIFT = map;
                if (id == "rshift") DST->RSHIFT = map;
                if (id == "ctrl") DST->CTRL = map;
                if (id == "alt") DST->ALT = map;
                if (id == "back") DST->BACK = map;
                if (id == "return") DST->RETURN = map;
                if (id == "space") DST->SPACE = map;
                if (id == "aup") DST->AUP = map;
                if (id == "aright") DST->ARIGHT = map;
                if (id == "adown") DST->ADOWN = map;
                if (id == "aleft") DST->ALEFT = map;
                if (id == "d0") DST->D0 = map;
                if (id == "d1") DST->D1 = map;
                if (id == "d2") DST->D2 = map;
                if (id == "d3") DST->D3 = map;
                if (id == "d4") DST->D4 = map;
                if (id == "d5") DST->D5 = map;
                if (id == "d6") DST->D6 = map;
                if (id == "d7") DST->D7 = map;
                if (id == "d8") DST->D8 = map;
                if (id == "d9") DST->D9 = map;
                if (id == "a") DST->A = map;
                if (id == "b") DST->B = map;
                if (id == "c") DST->C = map;
                if (id == "d") DST->D = map;
                if (id == "e") DST->E = map;
                if (id == "f") DST->F = map;
                if (id == "g") DST->G = map;
                if (id == "h") DST->H = map;
                if (id == "i") DST->I = map;
                if (id == "j") DST->J = map;
                if (id == "k") DST->K = map;
                if (id == "l") DST->L = map;
                if (id == "m") DST->M = map;
                if (id == "n") DST->N = map;
                if (id == "o") DST->O = map;
                if (id == "p") DST->P = map;
                if (id == "q") DST->Q = map;
                if (id == "r") DST->R = map;
                if (id == "s") DST->S = map;
                if (id == "t") DST->T = map;
                if (id == "u") DST->U = map;
                if (id == "v") DST->V = map;
                if (id == "w") DST->W = map;
                if (id == "x") DST->X = map;
                if (id == "y") DST->Y = map;
                if (id == "z") DST->Z = map;
                if (id == "num0") DST->NUM0 = map;
                if (id == "num1") DST->NUM1 = map;
                if (id == "num2") DST->NUM2 = map;
                if (id == "num3") DST->NUM3 = map;
                if (id == "num4") DST->NUM4 = map;
                if (id == "num5") DST->NUM5 = map;
                if (id == "num6") DST->NUM6 = map;
                if (id == "num7") DST->NUM7 = map;
                if (id == "num8") DST->NUM8 = map;
                if (id == "num9") DST->NUM9 = map;
                if (id == "numdiv") DST->NUMDIV = map;
                if (id == "nummul") DST->NUMMUL = map;
                if (id == "nummin") DST->NUMMIN = map;
                if (id == "numplu") DST->NUMPLU = map;
                if (id == "numret") DST->NUMRET = map;
                if (id == "numdel") DST->NUMDEL = map;
                if (id == "f1") DST->F1 = map;
                if (id == "f2") DST->F2 = map;
                if (id == "f3") DST->F3 = map;
                if (id == "f4") DST->F4 = map;
                if (id == "f5") DST->F5 = map;
                if (id == "f6") DST->F6 = map;
                if (id == "f7") DST->F7 = map;
                if (id == "f8") DST->F8 = map;
                if (id == "f9") DST->F9 = map;
                if (id == "f10") DST->F10 = map;
                if (id == "f11") DST->F11 = map;
                if (id == "f12") DST->F12 = map;
                if (id == "comma") DST->COMMA = map;
                if (id == "dot") DST->DOT = map;
                if (id == "plus") DST->PLUS = map;
                if (id == "minus") DST->MINUS = map;
                if (id == "lmb") DST->LMB = map;
                if (id == "rmb") DST->RMB = map;
                if (id == "mb") DST->MB = map;
                if (id == "me1") DST->ME1 = map;
                if (id == "me2") DST->ME2 = map;
                if (id == "wheel") DST->WHEEL = map;
                if (id == "mousex") DST->MOUSEX = map;
                if (id == "mousey") DST->MOUSEY = map;
                if (id == "joya") DST->JOYA = map;
                if (id == "joyb") DST->JOYB = map;
                if (id == "joyx") DST->JOYX = map;
                if (id == "joyy") DST->JOYY = map;
                if (id == "joystart") DST->JOYSTART = map;
                if (id == "joyselect") DST->JOYSELECT = map;
                if (id == "joyrb") DST->JOYRB = map;
                if (id == "joylb") DST->JOYLB = map;
                if (id == "joyup") DST->JOYUP = map;
                if (id == "joydown") DST->JOYDOWN = map;
                if (id == "joyright") DST->JOYRIGHT = map;
                if (id == "joyleft") DST->JOYLEFT = map;
                if (id == "joyrt") DST->JOYRT = map;
                if (id == "joylt") DST->JOYLT = map;
                if (id == "joyraxisx") DST->JOYRAXISX = map;
                if (id == "joyraxisy") DST->JOYRAXISY = map;
                if (id == "joylaxisx") DST->JOYLAXISX = map;
                if (id == "joylaxisy") DST->JOYLAXISY = map;
                if (id == "joyrs") DST->JOYRS = map;
                if (id == "joyls") DST->JOYLS = map;
            }
        }
    }
}


