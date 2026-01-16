#include "IReport.hpp"

void IReport::generateReport(ISystem* s) {
    std::cout << "\nGenerating System Report..." << std::endl;
    std::cout << "System Armed: " << (s->getArmed() ? "YES" : "NO") << std::endl;
}