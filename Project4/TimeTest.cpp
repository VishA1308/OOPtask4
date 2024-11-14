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
    Time t(1, 61, 61); // 1 ���, 61 ������, 61 �������
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 2);
    EXPECT_EQ(t.GetMinutes(), 2);
    EXPECT_EQ(t.GetSeconds(), 1);
}
TEST(TimeTest, NormalizeOver24Hours) {
    Time t(25, 0, 0); // 25 �����, 0 �����, 0 ������
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 1); // ������ ���� 1 ���
    EXPECT_EQ(t.GetMinutes(), 0); // ������ ���� 0 �����
    EXPECT_EQ(t.GetSeconds(), 0); // ������ ���� 0 ������
}
TEST(TimeTest, NormalizeMultipleOverflows) {
    Time t(1, 120, 120); // 1 ���, 120 �����, 120 ������
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 3); // ������ ���� 3 ����
    EXPECT_EQ(t.GetMinutes(), 2); // ������ ���� 0 �����
    EXPECT_EQ(t.GetSeconds(), 0); // ������ ���� 0 ������
}
TEST(TimeTest, NormalizeNegativeMinutes) {
    Time t(0, -120, 0); // 0 �����, -120 �����, 0 ������
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 0); // ���� ������ ���� 0
    EXPECT_EQ(t.GetMinutes(), 0); // ������ ������ ���� 0
    EXPECT_EQ(t.GetSeconds(), 0); // ������� ������ ���� 0
}
TEST(TimeTest, NormalizeNegativeSeconds) {
    Time t(0, 0, -61); // 0 �����, 0 �����, -61 �������
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