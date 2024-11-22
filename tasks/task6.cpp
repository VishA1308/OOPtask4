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

    void PrintTime() const {
        std::cout << "H:" << hours << " M:" << minutes << " S:" << seconds << std::endl;
    }
};
int main()
{
    // Создание одного экземпляра Time в динамической памяти
    Time* singleTime = new Time(10, 30, 45);
    singleTime->PrintTime();

    // Создание массива объектов Time в динамической памяти
    Time* timeArray = new Time[3]{ {1, 20, 30}, {2, 15, 45}, {3, 10, 55} };
    for (int i = 0; i < 3; ++i) {
        timeArray[i].PrintTime();
    }

   
    delete singleTime;       
    delete[] timeArray;     

    return 0;
}
//int main() {
//    std::vector<Time> timeVector;
//    timeVector.emplace_back(1, 0, 0);
//    timeVector.emplace_back(2, 30, 15);
//    timeVector.emplace_back(3, 45, 30);
//
//    std::cout << "Vector contents:" << std::endl;
//    for (const auto& t : timeVector) {
//        t.PrintTime();
//    }
//
//    std::list<Time> timeList;
//    timeList.push_back(Time(4, 15, 45));
//    timeList.push_back(Time(5, 50, 20));
//
//    std::cout << "List contents:" << std::endl;
//    for (const auto& t : timeList) {
//        t.PrintTime();
//    }
//
//    return 0;
//}
//int main() {
//    // Умный указатель unique_ptr
//    std::unique_ptr<Time> uniqueTime = std::make_unique<Time>(12, 34, 56);
//    uniqueTime->PrintTime();
//
//    // Умный указатель shared_ptr
//    std::shared_ptr<Time> sharedTime1 = std::make_shared<Time>(7, 8, 9);
//    std::shared_ptr<Time> sharedTime2 = sharedTime1; // shared_ptr делит владение
//    sharedTime1->PrintTime();
//
//    std::cout << "Shared Time use count: " << sharedTime1.use_count() << std::endl;
//
//    return 0;
//}
