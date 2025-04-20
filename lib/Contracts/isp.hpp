#pragma once

class isp{
    private:
        int year = 0;
        int month = 0;
        int day = 0;

    isp(const char*);
    ~isp();

    public:
        int GetYear() const;
        int GetMonth() const;
        int GetDay() const;

        void SetYear(int year);
        void SetMonth(int month);
        void SetDay(int day);
};