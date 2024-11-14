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
        // ������������ ������
        if (seconds < 0) {
            int minutesToSubtract = (-seconds + 59) / 60; // ���������� �����, ������� ����� �������
            minutes -= minutesToSubtract; // ��������� ������ �� ���������� ������ �����
            seconds += minutesToSubtract * 60; // ��������� � �������� ���������� ������, ������� �� ����� �� �����
            if (seconds < 0) { // ���� ����� ����� ������� ��� ��� �������������
                minutes -= 1; // ��������� ������ �� 1
                seconds += 60; // � ��������� 60 ������
            }
        }

        if (seconds >= 60) {
            minutes += seconds / 60; // ����������� ������
            seconds %= 60; // �������� ������� � ��������� [0, 59]
        }

        // ������������ �����
        if (minutes < 0) {
            int hoursToSubtract = (-minutes + 59) / 60; // ���������� �����, ������� ����� �������
            hours -= hoursToSubtract; // ��������� ���� �� ���������� ������ �����
            minutes += hoursToSubtract * 60; // ��������� � ������� ���������� �����, ������� �� ����� �� �����
            if (minutes < 0) { // ���� ������ ��� ��� �������������
                hours -= 1; // ��������� ���� �� 1
                minutes += 60; // � ��������� 60 �����
            }
        }

        if (minutes >= 60) {
            hours += minutes / 60; // ����������� ����
            minutes %= 60; // �������� ������ � ��������� [0, 59]
        }

        // ������������ �����
        if (hours < 0) {
            hours = 0; // ���� �� ����� ���� ��������������
        }

        if (hours >= 24) {
            hours %= 24; // �������� ���� � ��������� [0, 23]
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