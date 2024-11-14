#include <iostream>
#include <vector>
#include <list>
#include <memory>

static int _objectCount;

class Time {
    int hours, minutes, seconds;

public:
    Time() : Time(0, 0, 0) {}

    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        _objectCount++;
        Normalize();
        std::cout << "Parameterized constructor called. Current object count: " << _objectCount << std::endl;
    }

    Time(const Time& other) : hours(other.hours), minutes(other.minutes), seconds(other.seconds) {
        _objectCount++;
        Normalize();
        std::cout << "Copy constructor called. Current object count: " << _objectCount << std::endl;
    }

    Time& operator=(const Time& other) {
        if (this != &other) {
            hours = other.hours;
            minutes = other.minutes;
            seconds = other.seconds;
            Normalize();
        }
        return *this;
    }

    ~Time() {
        _objectCount--;
        std::cout << "Destructor called. Current object count: " << _objectCount << std::endl;
    }

    void Normalize() noexcept {
        // Нормализация секунд
        if (seconds < 0) {
            int minutesToSubtract = (-seconds + 59) / 60; // Количество минут, которое нужно вычесть
            minutes -= minutesToSubtract; // Уменьшаем минуты на количество полных минут
            seconds += minutesToSubtract * 60; // Добавляем к секундам количество секунд, которые мы вычли из минут
            if (seconds < 0) { // Если после этого секунды все еще отрицательные
                minutes -= 1; // Уменьшаем минуты на 1
                seconds += 60; // И добавляем 60 секунд
            }
        }

        if (seconds >= 60) {
            minutes += seconds / 60; // Увеличиваем минуты
            seconds %= 60; // Приводим секунды к диапазону [0, 59]
        }

        // Нормализация минут
        if (minutes < 0) {
            int hoursToSubtract = (-minutes + 59) / 60; // Количество часов, которое нужно вычесть
            hours -= hoursToSubtract; // Уменьшаем часы на количество полных часов
            minutes += hoursToSubtract * 60; // Добавляем к минутам количество минут, которые мы вычли из часов
            if (minutes < 0) { // Если минуты все еще отрицательные
                hours -= 1; // Уменьшаем часы на 1
                minutes += 60; // И добавляем 60 минут
            }
        }

        if (minutes >= 60) {
            hours += minutes / 60; // Увеличиваем часы
            minutes %= 60; // Приводим минуты к диапазону [0, 59]
        }

        // Нормализация часов
        if (hours < 0) {
            hours = 0; // Часы не могут быть отрицательными
        }

        if (hours >= 24) {
            hours %= 24; // Приводим часы к диапазону [0, 23]
        }
    }




    int GetHours() const {
        return hours;
    }

    int GetMinutes() const {
        return minutes;
    }

    int GetSeconds() const {
        return seconds;
    }
    void SetHours(int h) {
        hours = h;
        Normalize();
    }

    void SetMinutes(int m) {
        minutes = m;
        Normalize();
    }

    void SetSeconds(int s) {
        seconds = s;
        Normalize();
    }

    void PrintTime() const {
        std::cout << "H:" << hours << " M:" << minutes << " S:" << seconds << std::endl;
    }
};