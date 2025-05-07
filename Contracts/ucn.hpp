#pragma once
#include <string>
#include <stdexcept>
#include <cctype>
#include <array>

class ucn {
private:
    std::string value;
    int year;
    int month;
    int day;
    std::string region;

    bool isValidDate(int year, int month, int day) {
        if (month < 1 || month > 12) {
            return false;
        }

        if (day < 1) {
            return false;
        }

        // Check days in month
        const std::array<int, 12> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Adjust February for leap years
        int maxDay = daysInMonth[month - 1];
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
            maxDay = 29;
        }
        
        return day <= maxDay;
    }

    bool validateChecksum(const std::string& ucnStr) {
        // Weights for each position in UCN
        const std::array<int, 9> weights = {2, 4, 8, 5, 10, 9, 7, 3, 6};
        
        int sum = 0;
        for (int i = 0; i < 9; ++i) {
            sum += (ucnStr[i] - '0') * weights[i];
        }
        
        int remainder = sum % 11;
        int checkDigit = remainder < 10 ? remainder : 0;
        
        return checkDigit == (ucnStr[9] - '0');
    }

    void validateAndParse(const char* ucnValue) {
        // Check for null input
        if (ucnValue == nullptr) {
            throw std::invalid_argument("UCN cannot be null");
        }

        // Check for empty input
        std::string ucnStr(ucnValue);
        if (ucnStr.empty()) {
            throw std::invalid_argument("UCN cannot be empty");
        }

        // Check length
        if (ucnStr.length() != 10) {
            throw std::invalid_argument("UCN must be exactly 10 digits");
        }

        // Check if all characters are digits
        for (char c : ucnStr) {
            if (!std::isdigit(c)) {
                throw std::invalid_argument("UCN must contain only digits");
            }
        }

        // Extract date components
        int yearPrefix = std::stoi(ucnStr.substr(0, 2));
        int monthCode = std::stoi(ucnStr.substr(2, 2));
        int dayValue = std::stoi(ucnStr.substr(4, 2));

        // Determine century and adjust month
        int actualMonth = monthCode;
        int actualYear = 0;

        if (monthCode > 40) {
            // Born after 2000
            actualMonth = monthCode - 40;
            actualYear = 2000 + yearPrefix;
        } else if (monthCode > 20) {
            // Born between 1800-1899
            actualMonth = monthCode - 20;
            actualYear = 1800 + yearPrefix;
        } else {
            // Born between 1900-1999
            actualYear = 1900 + yearPrefix;
        }

        // Validate date
        if (!isValidDate(actualYear, actualMonth, dayValue)) {
            throw std::invalid_argument("UCN contains invalid date");
        }

        // Validate checksum
        if (!validateChecksum(ucnStr)) {
            throw std::invalid_argument("UCN has invalid checksum");
        }

        // If we got here, the UCN is valid, so set the class members
        value = ucnStr;
        year = actualYear;
        month = actualMonth;
        day = dayValue;

        // Set region based on region code
        int regionCode = std::stoi(ucnStr.substr(6, 3));
        setRegion(regionCode);
    }

    void setRegion(int regionCode) {
        // Implementation based on real Bulgarian region codes
        if (regionCode >= 43 && regionCode <= 93) {
            region = "Burgas";
        } else if (regionCode >= 280 && regionCode <= 301) {
            region = "Kustendil";
        } else if (regionCode >= 100 && regionCode <= 139) {
            region = "Varna";
        } else if (regionCode >= 500 && regionCode <= 799) {
            region = "Sofia-grad";
        } else {
            region = "Unknown";
        }
    }

public:
    ucn(const char* ucnValue) {
        validateAndParse(ucnValue);
    }

    ucn(const ucn& other) : value(other.value), year(other.year), month(other.month), day(other.day), region(other.region) {}

    ucn(ucn&& other) noexcept : value(std::move(other.value)), year(other.year), month(other.month), day(other.day), region(std::move(other.region)) {}

    ucn& operator=(const ucn& other) {
        if (this != &other) {
            value = other.value;
            year = other.year;
            month = other.month;
            day = other.day;
            region = other.region;
        }
        return *this;
    }

    ucn& operator=(ucn&& other) noexcept {
        if (this != &other) {
            value = std::move(other.value);
            year = other.year;
            month = other.month;
            day = other.day;
            region = std::move(other.region);
        }
        return *this;
    }

    bool operator<(const ucn& other) const {
        if (year != other.year) {
            return year < other.year;
        }
        if (month != other.month) {
            return month < other.month;
        }
        return day < other.day;
    }

    bool operator==(const ucn& other) const {
        return value == other.value;
    }

    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }
    std::string GetRegion() const { return region; }
};