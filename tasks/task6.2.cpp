#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <stdexcept>

static int _objectCount;

class Time {
    int hours, minutes, seconds;

public:
    Time() : Time(0, 0, 0) {}

    Time(int h, int m, int s) {
        if (h < 0 || m < 0 || s < 0) {
            throw std::invalid_argument("Negative values are not allowed.");
        }
        hours = h;
        minutes = m;
        seconds = s;
        _objectCount++;
        Normalize();
        std::cout << "Parameterized constructor called. Current object count: " << _objectCount << std::endl;
    }

    Time(const Time& other) noexcept : hours(other.hours), minutes(other.minutes), seconds(other.seconds) {
        _objectCount++;
        Normalize();
        std::cout << "Copy constructor called. Current object count: " << _objectCount << std::endl;
    }

    Time& operator=(const Time& other) noexcept {
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
            int minutesToSubtract = (-seconds + 59) / 60; 
            minutes -= minutesToSubtract; 
            seconds += minutesToSubtract * 60; 
            if (seconds < 0) { 
                minutes -= 1; 
                seconds += 60; 
            }
        }

        if (seconds >= 60) {
            minutes += seconds / 60; 
            seconds %= 60;
        }

        // Нормализация минут
        if (minutes < 0) {
            int hoursToSubtract = (-minutes + 59) / 60; 
            hours -= hoursToSubtract;
            minutes += hoursToSubtract * 60; 
            if (minutes < 0) { 
                hours -= 1;
                minutes += 60; 
            }
        }

        if (minutes >= 60) {
            hours += minutes / 60; 
            minutes %= 60; 
        }

        // Нормализация часов
        if (hours < 0) {
            hours = 0; 
        }

        if (hours >= 24) {
            hours %= 24; 
        }
    }

    int GetHours() const noexcept {
        return hours;
    }

    int GetMinutes() const noexcept {
        return minutes;
    }

    int GetSeconds() const noexcept {
        return seconds;
    }
    void SetHours(int h) {
        if (h < 0) throw std::invalid_argument("Negative hour value is not allowed.");
        hours = h;
        Normalize();
    }

    void SetMinutes(int m) {
        if (m < 0) throw std::invalid_argument("Negative minute value is not allowed.");
        minutes = m;
        Normalize();
    }

    void SetSeconds(int s) {
        if (s < 0) throw std::invalid_argument("Negative second value is not allowed.");
        seconds = s;
        Normalize();
    }

    void PrintTime() const noexcept {
        std::cout << "H:" << hours << " M:" << minutes << " S:" << seconds << std::endl;
    }
};
int main() {
    try {
        Time t1(-1, 30, 45); // Это вызовет исключение
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        Time t2(10, 30, 45);
        t2.PrintTime();

        t2.SetHours(-5); // Это вызовет исключение
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
