#pragma once
#include "Participant.h"
class Dealer :
    public Participant
{
public:
    Dealer(const char* pname) : Participant(pname) {};
    virtual ~Dealer();
};

