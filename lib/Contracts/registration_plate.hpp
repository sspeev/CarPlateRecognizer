#pragma once

class registration_plate {
private:
    char* prefix = nullptr;
    int number = 0;
    char* suffix = nullptr;

public:
    registration_plate(const char* plate = nullptr);
    ~registration_plate();

    void SetPrefix(const char*);
    const char* GetPrefix() const;

    void SetNumber(int);
    int GetNumber() const;

    void SetSuffix(const char*);
    const char* GetSuffix() const;

    friend std::ostream& operator<<(std::ostream& os, const registration_plate& plate);
    friend std::istream& operator>>(std::istream& is, registration_plate& plate);
    friend bool operator==(const registration_plate& plate1, const registration_plate& plate2);
    friend bool operator<(const registration_plate& plate1, const registration_plate& plate2);
    const std::string to_string() const;
};