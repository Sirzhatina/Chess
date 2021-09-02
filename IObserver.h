#pragma once

/*
        Classes Gameplay, IObserver (interface) and Game_basics 
        are combined into Observer design pattern
*/

class Gameplay;
class IObserver
{
public:
    virtual void handleEvent(const Gameplay* observed) = 0;
    virtual ~IObserver() = default;
};