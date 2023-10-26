#pragma once

BOOL GetMessageAHookInit()
{
    return true;
}

BOOL GetMessageAHookUninit()
{
    return true;
}

void InitPlayGetMessageATAS()
{

}

void UninitPlayGetMessageATAS()
{

}

void InitRecordGetMessageATAS()
{
}

void UninitRecordGetMessageATAS()
{
}

GameInput GetMessageAInput(BOOL TAS)
{

    return GameInput();
}

void SetMessageAInput(GameInput GetMessageAGameInput, BOOL TAS)
{
}


