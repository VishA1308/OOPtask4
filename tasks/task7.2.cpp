#include <iostream>
#include <string>

static int _objectCount;

class Time {
    int hours, minutes, seconds;

public:
    Time() : Time(0, 0, 0) {}

    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        _objectCount++;
        Normalize();
        std::cout << "Time: Parameterized constructor called. Current object count: " << _objectCount << std::endl;
    }

    Time(const Time& other) : hours(other.hours), minutes(other.minutes), seconds(other.seconds) {
        _objectCount++;
        Normalize();
        std::cout << "Time: Copy constructor called. Current object count: " << _objectCount << std::endl;
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
        std::cout << "Time: Destructor called. Current object count: " << _objectCount << std::endl;
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
    int GetHours() const { return hours; }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }

    void PrintTime() const {
        std::cout << "Current Time: " << hours << ":" << minutes << ":" << seconds << std::endl;
    }
};

class Clock {
protected:
    Time time;

public:
    Clock(int h, int m, int s) : time(h, m, s) {
        std::cout << "Clock: Parameterized constructor called." << std::endl;
    }

    virtual ~Clock() {
        std::cout << "Clock: Destructor called." << std::endl;
    }

    void SetTime(int h, int m, int s) {
        time.SetHours(h);
        time.SetMinutes(m);
        time.SetSeconds(s);
    }

    void ShowTime() const {
        time.PrintTime();
    }
};

class CuckooClock : public Clock {
public:
    CuckooClock(int h, int m, int s) : Clock(h, m, s) {
        std::cout << "CuckooClock: Parameterized constructor called." << std::endl;
    }

    ~CuckooClock() {
        std::cout << "CuckooClock: Destructor called." << std::endl;
    }
};

class WallClock : public Clock {
public:
    WallClock(int h, int m, int s) : Clock(h, m, s) {
        std::cout << "WallClock: Parameterized constructor called." << std::endl;
    }

    ~WallClock() {
        std::cout << "WallClock: Destructor called." << std::endl;
    }
};

class Watch : public Clock {
public:
    Watch(int h, int m, int s) : Clock(h, m, s) {
        std::cout << "Watch: Parameterized constructor called." << std::endl;
    }

    ~Watch() {
        std::cout << "Watch: Destructor called." << std::endl;
    }
};
class SmartWatch : public Watch {
public:    SmartWatch(int h, int m, int s) : Watch(h, m, s) {
    std::cout << "SmartWatch: Parameterized constructor called." << std::endl;
}

      ~SmartWatch() {
          std::cout << "SmartWatch: Destructor called." << std::endl;
      }
};

int main() {
    CuckooClock cuckoo(12, 30, 45);
    cuckoo.ShowTime();

    WallClock wall(15, 45, 30);
    wall.ShowTime();

    Watch wristwatch(9, 15, 5);
    wristwatch.ShowTime();

    SmartWatch smart(23, 59, 59);
    smart.ShowTime();

    return 0;
}
