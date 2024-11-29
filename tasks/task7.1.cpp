#include <iostream>
#include <iomanip>

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

        if (hours < 0) {
            hours = 0;
        }

        if (hours >= 24) {
            hours %= 24;
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
    // Дружественный класс SimpleWatch
    friend class SimpleWatch;

    // Дружественный класс Watch
    friend class Watch;

    void PrintTime() const {
        std::cout << "H:" << hours << " M:" << minutes << " S:" << seconds << std::endl;
    }
};

class SimpleWatch {
public:
    void ShowTime(const Time& time) const {
        time.PrintTime();
    }

    void SetTime(Time& time, int h, int m, int s) {
        time.hours = h;
        time.minutes = m;
        time.seconds = s;
        time.Normalize();
    }
};

class Watch {
private:
    bool is24HourFormat;

public:
    Watch(bool format = true) : is24HourFormat(format) {}

    void SetFormat(bool format) {
        is24HourFormat = format;
    }

    void ShowTime(const Time& time) const {
        if (is24HourFormat) {
            std::cout << std::setfill('0') << std::setw(2) << time.GetHours() << ":"
                << std::setfill('0') << std::setw(2) << time.GetMinutes() << ":"
                << std::setfill('0') << std::setw(2) << time.GetSeconds() << " (24-hour format)" << std::endl;
        }
        else {
            int hour = time.GetHours();
            std::string period = hour >= 12 ? "PM" : "AM";
            hour = hour % 12;
            hour = hour ? hour : 12; // час "0" становится "12"
            std::cout << hour << ":"
                << std::setfill('0') << std::setw(2) << time.GetMinutes() << ":"
                << std::setfill('0') << std::setw(2) << time.GetSeconds() << " (" << period << ")" << std::endl;
        }
    }

    void SetTime(Time& time, int h, int m, int s) {
        time.hours = h;
        time.minutes = m;
        time.seconds = s;
        time.Normalize();
    }
};

int main() {
    Time t(13, 30, 45); // Создаем объект времени
    SimpleWatch sw;     // Создаем объект SimpleWatch
    sw.ShowTime(t);     // Показываем текущее время

    // Устанавливаем новое время
    sw.SetTime(t, 9, 15, 30);
    sw.ShowTime(t);

    Watch watch; // Создаем объект Watch
    watch.SetFormat(false); // Устанавливаем формат 12 часов
    watch.ShowTime(t);      // Показываем время в формате 12 часов

    return 0;
}
