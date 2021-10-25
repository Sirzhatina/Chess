#pragma once

/*
        Classes Gameplay, IObserver (interface) and Game_basics 
        are combined into Observer design pattern
*/

class Chess::Gameplay;
class IObserver
{
public:
    virtual void handleEvent(const Chess::Gameplay* observed) = 0;
    virtual ~IObserver() = default;
};