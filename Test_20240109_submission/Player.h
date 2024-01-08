#pragma once
#include "Participant.h"
class Player :
    public Participant
{
public:
    Player(const char* pname) : Participant(pname) {};
    virtual ~Player();


};

