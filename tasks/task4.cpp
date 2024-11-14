#include <iostream>
#include <vector>
#include <list>
#include <memory>

class Time {
    int hours, minutes, seconds;
    static int objectCount;

public:
    Time() : Time(0, 0, 0) {}

    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        objectCount++;
        Normalize();
        std::cout << "Parameterized constructor called. Current object count: " << objectCount << std::endl;
    }

    Time(const Time& other) : hours(other.hours), minutes(other.minutes), seconds(other.seconds) {
        objectCount++;
        Normalize();
        std::cout << "Copy constructor called. Current object count: " << objectCount << std::endl;
    }

    Time& operator=(const Time& other) {
        if (this != &other) { // предотвращаем самоприсваивание
            hours = other.hours;
            minutes = other.minutes;
            seconds = other.seconds;
            Normalize();
        }
        return *this;
    }

    ~Time() {
        objectCount--;
        std::cout << "Destructor called. Current object count: " << objectCount << std::endl;
    }

    void Normalize() noexcept {
        // Нормализация времени
        if (seconds < 0) {
            minutes -= (-seconds + 59) / 60;
            seconds = (seconds + 60) % 60;
        }
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }

        if (minutes < 0) {
            hours -= (-minutes + 59) / 60;
            minutes = (minutes + 60) % 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }

        if (hours < 0) hours = 0;
        if (hours >= 24) hours %= 24;
    }

    void SetHours(int h) {
        hours = h;
        Normalize();
    }

    void PrintTime() const {
        std::cout << "H:" << hours << " M:" << minutes << " S:" << seconds << std::endl;
    }
};

int Time::objectCount = 0;

int main()
{
    Time t;
    t.SetHours(1);

    Time t2 = t; // вызов конструктора копирования
    t2.SetHours(2);
    t2.PrintTime();

    {
        t2.SetHours(12);
        t2.PrintTime();

        Time t3(22, 22, 22); // изменено имя переменной на t3
        t3.PrintTime();
    }

    t2.PrintTime();

    Time t4(3, 3, 3); // изменено имя переменной на t4
    t4 = t; // вызов оператора присваивания
    t4.SetHours(3);
    t4.PrintTime();
}