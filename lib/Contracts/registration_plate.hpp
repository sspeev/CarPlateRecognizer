#pragma once
#include <string>

class registration_plate {
private:
    std::string prefix = "";
    int number = 0;
    std::string suffix = "";

public:
    // Prefix getters and setters
    void SetPrefix(const std::string& input);
    std::string GetPrefix() const;
    
    // Number getters and setters
    void SetNumber(int input);
    int GetNumber() const;
    
    // Suffix getters and setters
    void SetSuffix(const std::string& input);
    std::string GetSuffix() const;
};