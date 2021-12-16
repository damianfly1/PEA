#pragma once
#include "BBvertice.h"

//Komparator stworzony dla kolejki priorytetowej z wierzcho�kami w algorytmie branch&bound

struct CompareCost {
    bool operator()(BBvertice const v1, BBvertice const v2)  {
        //sortujemy malej�co po priority i rosn�co po cost
        if (v1.priority == v2.priority) return v1.cost > v2.cost;
        else return v1.priority < v2.priority;
    }
};