#include <iostream>
#include "cloakwork.h"

int main() {
    // encrypt the hello world string at compile-time
    std::cout << CW_STR("Hello World") << std::endl;

    std::cout.flush();

    // virtualize the return value (0) in a clear scope
    int return_value = 0;
    {
        CW_VM_START();
        CW_VM_PUSH(42);
        CW_VM_PUSH(42);
        CW_VM_XOR();  // 42 ^ 42 = 0

        // execute and store result immediately
        return_value = static_cast<int>(CW_VM_EXECUTE());
    }

    std::cout << std::endl << CW_STR("Press Enter to exit...");
    std::cin.get();

    return return_value;
}