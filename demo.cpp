#include <iostream>
#include <string>
#include "cloakwork.h"

// simple function to demonstrate function pointer obfuscation
int simple_add(int a, int b) {
    return a + b;
}

// alternate implementation for metamorphic demo
int simple_add_v2(int a, int b) {
    return (a + b);
}

// function to demonstrate flattening
int calculate_something(int value) {
    return value * 2 + 10;
}

// demonstrates scattered data storage
struct secret_data {
    int user_id;
    int access_level;
    int session_token;
};

int main() {
    std::cout << "=== CLOAKWORK COMPREHENSIVE DEMO ===" << std::endl;
    std::cout << "demonstrating obfuscation, encryption, and anti-debug features" << std::endl;
    std::cout << "NOTE: crash-on-debug features disabled for demo (shows detections without crashing)" << std::endl << std::endl;

    // ==================================================================
    // 1. BASIC STRING ENCRYPTION (compile-time + runtime)
    // ==================================================================
    std::cout << "[1] String Encryption Demo" << std::endl;

    // strings are encrypted at compile-time with unique per-execution keys
    const char* encrypted_msg = CW_STR("this string is encrypted at compile-time!");
    std::cout << "   encrypted: " << encrypted_msg << std::endl;

    const char* another_msg = CW_STR("each execution has different runtime keys");
    std::cout << "   runtime entropy: " << another_msg << std::endl << std::endl;

    // ==================================================================
    // 2. ENHANCED STRING ENCRYPTION (multi-layer + stack-based)
    // ==================================================================
    std::cout << "[2] Enhanced String Encryption Demo" << std::endl;

    // multi-layer encrypted string (3 encryption layers + polymorphic re-encryption)
    const char* layered_msg = CW_STR_LAYERED("triple-layer encrypted string with polymorphic decryption!");
    std::cout << "   layered encryption: " << layered_msg << std::endl;

    // stack-based encrypted string (auto-clears on scope exit)
    {
        auto stack_msg = CW_STR_STACK("this string auto-clears when leaving scope");
        std::cout << "   stack-based encryption: " << stack_msg.get() << std::endl;
        std::cout << "   (buffer will be overwritten with random data on scope exit)" << std::endl;
    }

    std::cout << std::endl;

    // ==================================================================
    // 3. ANTI-DEBUG PROTECTION
    // ==================================================================
    std::cout << "[3] Anti-Debug Protection Demo" << std::endl;
    std::cout << "   checking for debuggers and analysis tools..." << std::endl;

    // individual checks for demonstration (non-crashing)
    bool any_detected = false;

    if (cloakwork::anti_debug::is_debugger_present()) {
        std::cout << "   WARNING: basic debugger detected!" << std::endl;
        any_detected = true;
    } else {
        std::cout << "   basic debugger check: clean" << std::endl;
    }

    if (cloakwork::anti_debug::has_hardware_breakpoints()) {
        std::cout << "   WARNING: hardware breakpoints detected!" << std::endl;
        any_detected = true;
    } else {
        std::cout << "   hardware breakpoint check: clean" << std::endl;
    }

    if (cloakwork::anti_debug::advanced::detect_hiding_tools()) {
        std::cout << "   WARNING: anti-anti-debug tools detected!" << std::endl;
        any_detected = true;
    } else {
        std::cout << "   hiding tools check: clean" << std::endl;
    }

    if (cloakwork::anti_debug::advanced::suspicious_parent_process()) {
        std::cout << "   WARNING: suspicious parent process!" << std::endl;
        any_detected = true;
    } else {
        std::cout << "   parent process check: clean" << std::endl;
    }

    // note: comprehensive check would crash if debugger detected (commented out for demo)
    // CW_ANTI_DEBUG();

    if (any_detected) {
        std::cout << "   NOTE: in production, CW_ANTI_DEBUG() would crash here" << std::endl;
    }

    std::cout << std::endl;

    // ==================================================================
    // 4. VALUE OBFUSCATION
    // ==================================================================
    std::cout << "[4] Value Obfuscation Demo" << std::endl;

    // obfuscated integer - stored with xor/rotation/addition layers
    auto obfuscated_number = CW_INT(42);
    std::cout << "   obfuscated value (multi-layer): " << obfuscated_number.get() << std::endl;

    // MBA (mixed boolean arithmetic) obfuscation
    auto mba_number = CW_MBA(1337);
    std::cout << "   MBA obfuscated value: " << mba_number.get() << std::endl;

    // polymorphic value - mutates internal representation
    auto poly_value = CW_POLY(12345);
    std::cout << "   polymorphic value: " << static_cast<int>(poly_value) << std::endl;

    // scattered across memory - prevents memory dumping
    secret_data my_data = { 1001, 5, static_cast<int>(0xDEADBEEF) };
    auto scattered = CW_SCATTER(my_data);
    secret_data retrieved = scattered.get();
    std::cout << "   scattered data recovered - user_id: " << retrieved.user_id << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 5. MIXED BOOLEAN ARITHMETIC (MBA) DEMO
    // ==================================================================
    std::cout << "[5] Mixed Boolean Arithmetic Demo" << std::endl;

    // demonstrate MBA transformations (normally hidden inside obfuscation)
    using namespace cloakwork::mba;

    int val1 = 100;
    int val2 = 50;

    // MBA addition: (x ^ y) + 2 * (x & y)
    int mba_add_result = add_mba(val1, val2);
    std::cout << "   MBA add(100, 50) = " << mba_add_result << " (expected: 150)" << std::endl;

    // MBA subtraction: (x ^ y) - 2 * (~x & y)
    int mba_sub_result = sub_mba(val1, val2);
    std::cout << "   MBA sub(100, 50) = " << mba_sub_result << " (expected: 50)" << std::endl;

    // MBA negation: ~x + 1
    int mba_neg_result = neg_mba(42);
    std::cout << "   MBA neg(42) = " << mba_neg_result << " (expected: -42)" << std::endl;

    std::cout << "   (these transformations hide arithmetic from static analysis)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 6. CONTROL FLOW OBFUSCATION
    // ==================================================================
    std::cout << "[6] Control Flow Obfuscation Demo" << std::endl;

    auto test_value_obf = CW_INT(100);
    int test_value = test_value_obf.get();

    // obfuscated if/else with opaque predicates
    CW_IF(test_value > 50) {
        std::cout << "   obfuscated if: value is greater than 50" << std::endl;
    } CW_ELSE {
        std::cout << "   obfuscated else: this shouldn't execute" << std::endl;
    }

    // obfuscated branching
    CW_BRANCH(test_value == 100) {
        std::cout << "   obfuscated branch: value equals 100" << std::endl;
    }

    std::cout << std::endl;

    // ==================================================================
    // 7. CONTROL FLOW FLATTENING
    // ==================================================================
    std::cout << "[7] Control Flow Flattening Demo" << std::endl;

    // flatten the control flow via state machine
    auto flattened_result = CW_FLATTEN(calculate_something, 15);
    std::cout << "   flattened function result: " << flattened_result << std::endl;
    std::cout << "   (in IDA: this will show complex state machine)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 8. FUNCTION POINTER OBFUSCATION
    // ==================================================================
    std::cout << "[8] Function Pointer Obfuscation Demo" << std::endl;

    // obfuscate function pointer with anti-debug checks
    auto obfuscated_func = CW_CALL(simple_add);
    int func_result = obfuscated_func(15, 27);
    std::cout << "   obfuscated function call result: " << func_result << std::endl;
    std::cout << "   (function pointer is encrypted and includes anti-debug)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 9. METAMORPHIC FUNCTION DEMO
    // ==================================================================
    std::cout << "[9] Metamorphic Function Demo" << std::endl;

    // create metamorphic function that switches between implementations
    cloakwork::metamorphic::metamorphic_function<int(int, int)> meta_add({simple_add, simple_add_v2});

    std::cout << "   calling metamorphic function 5 times:" << std::endl;
    for (int i = 0; i < 5; i++) {
        int result = meta_add(10, 20);
        std::cout << "     call " << (i+1) << ": result = " << result << std::endl;
    }
    std::cout << "   (implementation switches between calls, confuses analysis)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 10. COMPREHENSIVE PROTECTION DEMO
    // ==================================================================
    std::cout << "[10] Comprehensive Protection Demo" << std::endl;
    std::cout << "    combining multiple protection layers..." << std::endl;

    // protected "secret" calculation with all layers
    auto secret_key_obf = CW_MBA(0x1337);  // MBA obfuscated value
    int secret_key = secret_key_obf.get();

    CW_IF(secret_key != 0) {
        // note: CW_CHECK_ANALYSIS() would crash if debugger detected (commented for demo)
        // CW_CHECK_ANALYSIS();

        // transform the key using obfuscated operations
        auto xor_part = CW_INT(secret_key ^ 0xDEAD);
        auto add_part = CW_MBA(0xBEEF);
        int transformed_key = xor_part.get() + add_part.get();

        std::cout << "    " << CW_STR_LAYERED("protected computation result: ") << transformed_key << std::endl;
        std::cout << "    " << CW_STR_LAYERED("(CW_CHECK_ANALYSIS would protect this in production)") << std::endl;
    } CW_ELSE {
        std::cout << "    " << CW_STR("unexpected code path") << std::endl;
    }

    std::cout << std::endl;

    // ==================================================================
    // 11. ADVANCED ANTI-DEBUG SHOWCASE
    // ==================================================================
    std::cout << "[11] Advanced Anti-Debug Techniques" << std::endl;
    std::cout << "    running comprehensive analysis detection..." << std::endl;

    // check for advanced debugging techniques
    if (cloakwork::anti_debug::advanced::kernel_debugger_present()) {
        std::cout << "    ALERT: kernel debugger detected!" << std::endl;
    } else {
        std::cout << "    kernel debugger: not detected" << std::endl;
    }

    // timing check can have false positives, so it's disabled in comprehensive_check
    if (cloakwork::anti_debug::advanced::advanced_timing_check()) {
        std::cout << "    INFO: timing discrepancy detected (may be false positive)" << std::endl;
    } else {
        std::cout << "    timing analysis: clean" << std::endl;
    }

    if (cloakwork::anti_debug::advanced::detect_debugger_artifacts()) {
        std::cout << "    INFO: debugger artifacts found in registry" << std::endl;
    } else {
        std::cout << "    registry artifacts: clean" << std::endl;
    }

    // show comprehensive check result without crashing
    if (cloakwork::anti_debug::comprehensive_check()) {
        std::cout << "    COMPREHENSIVE: debugger detected (CW_ANTI_DEBUG would crash)" << std::endl;
    } else {
        std::cout << "    COMPREHENSIVE: all checks passed" << std::endl;
    }

    std::cout << std::endl;

    // ==================================================================
    // 12. ENCRYPTED MESSAGE OUTPUT
    // ==================================================================
    std::cout << "[12] Final Encrypted Output" << std::endl;

    // all these strings are encrypted and have unique runtime keys
    std::cout << "    " << CW_STR("this demo showcases:") << std::endl;
    std::cout << "    - " << CW_STR_LAYERED("multi-layer compile-time string encryption") << std::endl;
    std::cout << "    - " << CW_STR_LAYERED("stack-based auto-clearing encrypted strings") << std::endl;
    std::cout << "    - " << CW_STR("mixed boolean arithmetic (MBA) obfuscation") << std::endl;
    std::cout << "    - " << CW_STR("enhanced value obfuscation with MBA") << std::endl;
    std::cout << "    - " << CW_STR("control flow obfuscation and flattening") << std::endl;
    std::cout << "    - " << CW_STR("function pointer encryption") << std::endl;
    std::cout << "    - " << CW_STR("metamorphic function implementations") << std::endl;
    std::cout << "    - " << CW_STR("comprehensive anti-debug protection") << std::endl;
    std::cout << "    - " << CW_STR("detection of modern analysis tools") << std::endl;

    std::cout << std::endl;
    std::cout << "=== DEMO COMPLETE ===" << std::endl;
    std::cout << std::endl;

    // ==================================================================
    // INTERACTIVE EXIT
    // ==================================================================
    std::cout << CW_STR("press enter to exit (protected)...") << std::endl;
    std::cin.get();

    // obfuscated return value
    return CW_MBA(0);
}
