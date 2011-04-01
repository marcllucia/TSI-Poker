#include "card.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;
Card::Card()
{
    covered=true;
}

Card::~Card()
{
}

Card::Card(int id)
{
    idCard=id;
    covered=true;
}

