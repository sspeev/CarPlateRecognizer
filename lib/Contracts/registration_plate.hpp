#pragma once

class registration_plate {
private:
    char* prefix = nullptr;
    int number = 0;
    char* suffix = nullptr;

public:
    // Constructor/destructor for memory management
    registration_plate(const char* plate = nullptr); // Added default constructor
    ~registration_plate();

    // Prefix getters and setters
    void SetPrefix(const char*);
    const char* GetPrefix() const;

    // Number getters and setters
    void SetNumber(int);
    int GetNumber() const;

    // Suffix getters and setters
    void SetSuffix(const char*);
    const char* GetSuffix() const;

    //Friend declarations
    friend std::ostream& operator<<(std::ostream& os, const registration_plate& plate);
    friend std::istream& operator>>(std::istream& is, registration_plate& plate);
};