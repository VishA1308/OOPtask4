#include <gtest/gtest.h>
#include "Time.cpp"

TEST(TimeTest, DefaultConstructor) 
{
    Time t; 
    EXPECT_EQ(t.GetHours(), 0);
    EXPECT_EQ(t.GetMinutes(), 0);
    EXPECT_EQ(t.GetSeconds(), 0);
}

TEST(TimeTest, ParameterizedConstructor)
{
    Time t(12, 30, 45);
    EXPECT_EQ(t.GetHours(), 12);
    EXPECT_EQ(t.GetMinutes(), 30);
    EXPECT_EQ(t.GetSeconds(), 45);
}

TEST(TimeTest, CopyConstructor) 
{
    Time t1(10, 20, 30);
    Time t2(t1); 
    EXPECT_EQ(t2.GetHours(), 10);
    EXPECT_EQ(t2.GetMinutes(), 20);
    EXPECT_EQ(t2.GetSeconds(), 30);
}


TEST(TimeTest, AssignmentOperator) 
{
    Time t1(1, 2, 3);
    Time t2;
    t2 = t1; 
    EXPECT_EQ(t2.GetHours(), 1);
    EXPECT_EQ(t2.GetMinutes(), 2);
    EXPECT_EQ(t2.GetSeconds(), 3);
}
TEST(TimeTest, NormalizeBasic) {
    Time t(1, 61, 61); // 1 час, 61 минута, 61 секунда
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 2);
    EXPECT_EQ(t.GetMinutes(), 2);
    EXPECT_EQ(t.GetSeconds(), 1);
}
TEST(TimeTest, NormalizeOver24Hours) {
    Time t(25, 0, 0); // 25 часов, 0 минут, 0 секунд
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 1); // Должно быть 1 час
    EXPECT_EQ(t.GetMinutes(), 0); // Должно быть 0 минут
    EXPECT_EQ(t.GetSeconds(), 0); // Должно быть 0 секунд
}
TEST(TimeTest, NormalizeMultipleOverflows) {
    Time t(1, 120, 120); // 1 час, 120 минут, 120 секунд
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 3); // Должно быть 3 часа
    EXPECT_EQ(t.GetMinutes(), 2); // Должно быть 0 минут
    EXPECT_EQ(t.GetSeconds(), 0); // Должно быть 0 секунд
}
TEST(TimeTest, NormalizeNegativeMinutes) {
    Time t(0, -120, 0); // 0 часов, -120 минут, 0 секунд
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 0); // Часы должны быть 0
    EXPECT_EQ(t.GetMinutes(), 0); // Минуты должны быть 0
    EXPECT_EQ(t.GetSeconds(), 0); // Секунды должны быть 0
}
TEST(TimeTest, NormalizeNegativeSeconds) {
    Time t(0, 0, -61); // 0 часов, 0 минут, -61 секунда
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 0);
    EXPECT_EQ(t.GetMinutes(), 58);
    EXPECT_EQ(t.GetSeconds(), 59);
}
TEST(TimeTest, SetHoursp)
{
    Time t;
    t.SetHours(5);
    EXPECT_EQ(t.GetHours(), 5);
    t.SetMinutes(5);
    EXPECT_EQ(t.GetMinutes(), 5);
    t.SetSeconds(5);
    EXPECT_EQ(t.GetSeconds(), 5);
}