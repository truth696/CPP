#include "TitanSecurity.hpp"

void TitanSystem::SetMode(std::string mode) {
    if (mode == "Day" || mode == "Night" || mode == "Away") {
        currentMode = mode;
        std::cout << "[System] Mode set to: " << mode << std::endl;
        if (mode == "Away") systemArmed = true;
    } else std::cout << "[Error] Unknown mode." << std::endl;
}
