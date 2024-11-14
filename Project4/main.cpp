#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include "Time.cpp"


int main()
{
    Time t;
    t.SetHours(1);

    Time t2 = t; 
    t2.SetHours(2);
    t2.PrintTime();

    {
        t2.SetHours(12);
        t2.PrintTime();

        Time t3(22, 22, 22); 
        t3.PrintTime();
    }

    t2.PrintTime();

    Time t4(3, 3, 3); 
    t4 = t; 
    t4.SetHours(3);
    t4.PrintTime();
}