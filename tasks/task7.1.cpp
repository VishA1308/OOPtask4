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
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
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
    friend class SimpleWatch; 
};

class SimpleWatch {
public:
    void ShowTime(const Time& time) const {
        std::cout << std::setfill('0') << std::setw(2) << time.hours << ":"
            << std::setfill('0') << std::setw(2) << time.minutes << ":"
            << std::setfill('0') << std::setw(2) << time.seconds << std::endl;
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

    void ShowTime(Time& time) const {
        if (is24HourFormat) {
            std::cout << std::setfill('0') << std::setw(2) << time.GetHours() << ":"
                << std::setfill('0') << std::setw(2) << time.GetMinutes() << ":"
                << std::setfill('0') << std::setw(2) << time.GetSeconds() << std::endl;
        }
        else {
            int h = time.GetHours() % 12;
            h = (h == 0) ? 12 : h; // Преобразование 0 в 12
            std::string period = (time.GetHours() >= 12) ? "PM" : "AM";
            std::cout << std::setfill('0') << std::setw(2) << h << ":"
                << std::setfill('0') << std::setw(2) << time.GetMinutes() << ":"
                << std::setfill('0') << std::setw(2) << time.GetSeconds() << " " << period << std::endl;
        }
    }

    void SetTime(Time& time, int h, int m, int s) {
        time.SetHours(h);
        time.SetMinutes(m);
        time.SetSeconds(s);
    }
};

int main() {
    Time t(10, 30, 45);
    SimpleWatch sw;

    sw.ShowTime(t); // Показывает текущее время

    sw.SetTime(t, 12, 45, 30); // Устанавливаем новое время через SimpleWatch
    sw.ShowTime(t); // Показывает обновленное время

    Watch w;
    w.SetFormat(false); // Устанавливаем 12-часовой формат
    w.ShowTime(t); // Показывает время в 12-часовом формате

    return 0;
}
