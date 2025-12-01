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
    // 5. BOOLEAN OBFUSCATION DEMO
    // ==================================================================
    std::cout << "[5] Boolean Obfuscation Demo" << std::endl;

    // CW_TRUE and CW_FALSE - obfuscated constants using opaque predicates
    std::cout << "   testing CW_TRUE: ";
    if (CW_TRUE) {
        std::cout << "always executes (correct)" << std::endl;
    } else {
        std::cout << "ERROR - should not happen" << std::endl;
    }

    std::cout << "   testing CW_FALSE: ";
    if (CW_FALSE) {
        std::cout << "ERROR - should not happen" << std::endl;
    } else {
        std::cout << "never executes true branch (correct)" << std::endl;
    }

    // CW_BOOL - obfuscate boolean expressions
    int test_x = 50;
    int test_y = 100;
    bool obf_result = CW_BOOL(test_x < test_y);
    std::cout << "   CW_BOOL(50 < 100) = " << (obf_result ? "true" : "false") << " (expected: true)" << std::endl;

    bool obf_result2 = CW_BOOL(test_x > test_y);
    std::cout << "   CW_BOOL(50 > 100) = " << (obf_result2 ? "true" : "false") << " (expected: false)" << std::endl;

    // obfuscated_bool class for persistent storage
    cloakwork::bool_obfuscation::obfuscated_bool license_flag(true);
    std::cout << "   obfuscated_bool(true).get() = " << (license_flag.get() ? "true" : "false") << std::endl;

    license_flag = false;
    std::cout << "   after setting to false: " << (license_flag.get() ? "true" : "false") << std::endl;

    // demonstrate logical operators
    cloakwork::bool_obfuscation::obfuscated_bool flag_a(true);
    cloakwork::bool_obfuscation::obfuscated_bool flag_b(false);
    std::cout << "   !obfuscated_bool(true) = " << ((!flag_a).get() ? "true" : "false") << " (expected: false)" << std::endl;
    std::cout << "   obfuscated_bool(true) && false = " << ((flag_a && false).get() ? "true" : "false") << " (expected: false)" << std::endl;
    std::cout << "   obfuscated_bool(false) || true = " << ((flag_b || true).get() ? "true" : "false") << " (expected: true)" << std::endl;

    std::cout << "   (booleans stored as multi-byte patterns, not simple 0/1)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 6. MIXED BOOLEAN ARITHMETIC (MBA) DEMO
    // ==================================================================
    std::cout << "[6] Mixed Boolean Arithmetic Demo" << std::endl;

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
    // 7. CONTROL FLOW OBFUSCATION
    // ==================================================================
    std::cout << "[7] Control Flow Obfuscation Demo" << std::endl;

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
    // 8. CONTROL FLOW FLATTENING
    // ==================================================================
    std::cout << "[8] Control Flow Flattening Demo" << std::endl;

    // flatten the control flow via state machine
    auto flattened_result = CW_FLATTEN(calculate_something, 15);
    std::cout << "   flattened function result: " << flattened_result << std::endl;
    std::cout << "   (in IDA: this will show complex state machine)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 9. FUNCTION POINTER OBFUSCATION
    // ==================================================================
    std::cout << "[9] Function Pointer Obfuscation Demo" << std::endl;

    // obfuscate function pointer with anti-debug checks
    auto obfuscated_func = CW_CALL(simple_add);
    int func_result = obfuscated_func(15, 27);
    std::cout << "   obfuscated function call result: " << func_result << std::endl;
    std::cout << "   (function pointer is encrypted and includes anti-debug)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 10. METAMORPHIC FUNCTION DEMO
    // ==================================================================
    std::cout << "[10] Metamorphic Function Demo" << std::endl;

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
    // 11. COMPREHENSIVE PROTECTION DEMO
    // ==================================================================
    std::cout << "[11] Comprehensive Protection Demo" << std::endl;
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
    // 12. ADVANCED ANTI-DEBUG SHOWCASE
    // ==================================================================
    std::cout << "[12] Advanced Anti-Debug Techniques" << std::endl;
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
    // 13. WIDE STRING ENCRYPTION
    // ==================================================================
    std::cout << "[13] Wide String Encryption Demo" << std::endl;

    const wchar_t* wide_msg = CW_WSTR(L"this is an encrypted wide string!");
    std::wcout << L"   encrypted wide string: " << wide_msg << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 14. COMPILE-TIME STRING HASHING
    // ==================================================================
    std::cout << "[14] Compile-Time String Hashing Demo" << std::endl;

    // compile-time hash - computed at build time
    constexpr uint32_t kernel32_hash = CW_HASH("kernel32.dll");
    constexpr uint32_t ntdll_hash = CW_HASH("ntdll.dll");

    std::cout << "   hash of 'kernel32.dll': 0x" << std::hex << kernel32_hash << std::dec << std::endl;
    std::cout << "   hash of 'ntdll.dll': 0x" << std::hex << ntdll_hash << std::dec << std::endl;

    // runtime hash comparison
    const char* test_str = "kernel32.dll";
    uint32_t runtime_hash = cloakwork::hash::fnv1a_runtime(test_str);
    std::cout << "   runtime hash matches compile-time: " << (runtime_hash == kernel32_hash ? "yes" : "no") << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 15. IMPORT HIDING / DYNAMIC API RESOLUTION
    // ==================================================================
    std::cout << "[15] Import Hiding Demo" << std::endl;
    std::cout << "   resolving APIs without import table..." << std::endl;

    // get ntdll base address by hash (use case-insensitive hash for module names)
    void* ntdll_base = cloakwork::imports::getModuleBase(CW_HASH_CI("ntdll.dll"));
    std::cout << "   ntdll.dll base: 0x" << std::hex << reinterpret_cast<uintptr_t>(ntdll_base) << std::dec << std::endl;

    // get kernel32 base
    void* k32_base = cloakwork::imports::getModuleBase(CW_HASH_CI("kernel32.dll"));
    std::cout << "   kernel32.dll base: 0x" << std::hex << reinterpret_cast<uintptr_t>(k32_base) << std::dec << std::endl;

    // resolve function by hash
    if (ntdll_base) {
        void* nt_close = cloakwork::imports::getProcAddress(ntdll_base, CW_HASH("NtClose"));
        std::cout << "   NtClose address: 0x" << std::hex << reinterpret_cast<uintptr_t>(nt_close) << std::dec << std::endl;
    }

    std::cout << "   (these functions are not in the import table!)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 16. DIRECT SYSCALL NUMBERS
    // ==================================================================
    std::cout << "[16] Direct Syscall Demo" << std::endl;

    uint32_t syscall_NtClose = CW_SYSCALL_NUMBER(NtClose);
    uint32_t syscall_NtQueryInformationProcess = CW_SYSCALL_NUMBER(NtQueryInformationProcess);

    std::cout << "   NtClose syscall number: 0x" << std::hex << syscall_NtClose << std::dec << std::endl;
    std::cout << "   NtQueryInformationProcess syscall number: 0x" << std::hex << syscall_NtQueryInformationProcess << std::dec << std::endl;
    std::cout << "   (syscall numbers are OS version dependent)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 17. ANTI-VM/SANDBOX DETECTION
    // ==================================================================
    std::cout << "[17] Anti-VM/Sandbox Detection Demo" << std::endl;
    std::cout << "   running VM/sandbox detection checks..." << std::endl;

    if (cloakwork::anti_debug::anti_vm::is_hypervisor_present()) {
        std::cout << "   INFO: hypervisor detected" << std::endl;
    } else {
        std::cout << "   hypervisor check: clean" << std::endl;
    }

    if (cloakwork::anti_debug::anti_vm::detect_vm_vendor()) {
        std::cout << "   INFO: VM vendor signature detected" << std::endl;
    } else {
        std::cout << "   VM vendor check: clean" << std::endl;
    }

    if (cloakwork::anti_debug::anti_vm::detect_low_resources()) {
        std::cout << "   INFO: low resources detected (possible sandbox)" << std::endl;
    } else {
        std::cout << "   resource check: clean" << std::endl;
    }

    if (cloakwork::anti_debug::anti_vm::detect_sandbox_dlls()) {
        std::cout << "   INFO: sandbox DLLs detected" << std::endl;
    } else {
        std::cout << "   sandbox DLL check: clean" << std::endl;
    }

    if (CW_CHECK_VM()) {
        std::cout << "   COMPREHENSIVE: VM/sandbox detected (CW_ANTI_VM would crash)" << std::endl;
    } else {
        std::cout << "   COMPREHENSIVE: all VM/sandbox checks passed" << std::endl;
    }

    std::cout << std::endl;

    // ==================================================================
    // 18. OBFUSCATED COMPARISONS
    // ==================================================================
    std::cout << "[18] Obfuscated Comparisons Demo" << std::endl;

    int cmp_a = 42;
    int cmp_b = 42;
    int cmp_c = 100;

    std::cout << "   CW_EQ(42, 42) = " << (CW_EQ(cmp_a, cmp_b) ? "true" : "false") << " (expected: true)" << std::endl;
    std::cout << "   CW_NE(42, 100) = " << (CW_NE(cmp_a, cmp_c) ? "true" : "false") << " (expected: true)" << std::endl;
    std::cout << "   CW_LT(42, 100) = " << (CW_LT(cmp_a, cmp_c) ? "true" : "false") << " (expected: true)" << std::endl;
    std::cout << "   CW_GT(100, 42) = " << (CW_GT(cmp_c, cmp_a) ? "true" : "false") << " (expected: true)" << std::endl;
    std::cout << "   CW_LE(42, 42) = " << (CW_LE(cmp_a, cmp_b) ? "true" : "false") << " (expected: true)" << std::endl;
    std::cout << "   CW_GE(100, 42) = " << (CW_GE(cmp_c, cmp_a) ? "true" : "false") << " (expected: true)" << std::endl;
    std::cout << "   (comparisons use MBA and XOR to hide the actual operation)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 19. ENCRYPTED CONSTANTS
    // ==================================================================
    std::cout << "[19] Encrypted Constants Demo" << std::endl;

    // compile-time encrypted constant
    int encrypted_magic = CW_CONST(0xDEADBEEF);
    std::cout << "   CW_CONST(0xDEADBEEF) = 0x" << std::hex << encrypted_magic << std::dec << std::endl;

    int encrypted_value = CW_CONST(12345);
    std::cout << "   CW_CONST(12345) = " << encrypted_value << std::endl;

    // runtime constant (different key each execution)
    cloakwork::constants::runtime_constant<int> rt_const(9999);
    std::cout << "   runtime_constant(9999) = " << rt_const.get() << std::endl;
    std::cout << "   (constants are XOR-encrypted and decrypted at runtime)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 20. JUNK CODE INSERTION
    // ==================================================================
    std::cout << "[20] Junk Code Insertion Demo" << std::endl;

    std::cout << "   inserting junk computation..." << std::endl;
    CW_JUNK();
    std::cout << "   junk computation complete" << std::endl;

    std::cout << "   inserting junk control flow..." << std::endl;
    CW_JUNK_FLOW();
    std::cout << "   junk control flow complete" << std::endl;

    std::cout << "   (junk code confuses decompilers and increases entropy)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 21. RETURN ADDRESS SPOOFING
    // ==================================================================
    std::cout << "[21] Return Address Spoofing Demo" << std::endl;

    void* ret_gadget = cloakwork::spoof::getRetGadget();
    std::cout << "   found ret gadget at: 0x" << std::hex << reinterpret_cast<uintptr_t>(ret_gadget) << std::dec << std::endl;
    std::cout << "   (can be used to spoof return addresses in call stacks)" << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 22. INTEGRITY VERIFICATION
    // ==================================================================
    std::cout << "[22] Integrity Verification Demo" << std::endl;

    // check if our own functions are hooked
    bool simple_add_hooked = CW_DETECT_HOOK(simple_add);
    std::cout << "   simple_add hook check: " << (simple_add_hooked ? "HOOKED!" : "clean") << std::endl;

    // compute hash of function
    uint32_t func_hash = cloakwork::integrity::computeHash(
        reinterpret_cast<const void*>(&simple_add), 32);
    std::cout << "   simple_add code hash: 0x" << std::hex << func_hash << std::dec << std::endl;

    // verify multiple functions at once
    bool all_clean = cloakwork::integrity::verifyFunctions(&simple_add, &simple_add_v2);
    std::cout << "   all functions clean: " << (all_clean ? "yes" : "NO - hooks detected!") << std::endl;

    std::cout << std::endl;

    // ==================================================================
    // 23. ENCRYPTED MESSAGE OUTPUT
    // ==================================================================
    std::cout << "[23] Final Encrypted Output" << std::endl;

    // all these strings are encrypted and have unique runtime keys
    std::cout << "    " << CW_STR("this demo showcases:") << std::endl;
    std::cout << "    - " << CW_STR_LAYERED("multi-layer compile-time string encryption") << std::endl;
    std::cout << "    - " << CW_STR_LAYERED("wide string encryption (wchar_t)") << std::endl;
    std::cout << "    - " << CW_STR("compile-time string hashing (FNV-1a)") << std::endl;
    std::cout << "    - " << CW_STR("mixed boolean arithmetic (MBA) obfuscation") << std::endl;
    std::cout << "    - " << CW_STR("boolean obfuscation with opaque predicates") << std::endl;
    std::cout << "    - " << CW_STR("obfuscated comparison operators") << std::endl;
    std::cout << "    - " << CW_STR("encrypted compile-time constants") << std::endl;
    std::cout << "    - " << CW_STR("control flow obfuscation and flattening") << std::endl;
    std::cout << "    - " << CW_STR("junk code insertion") << std::endl;
    std::cout << "    - " << CW_STR("function pointer encryption") << std::endl;
    std::cout << "    - " << CW_STR("metamorphic function implementations") << std::endl;
    std::cout << "    - " << CW_STR("import hiding / dynamic API resolution") << std::endl;
    std::cout << "    - " << CW_STR("direct syscall number extraction") << std::endl;
    std::cout << "    - " << CW_STR("return address spoofing infrastructure") << std::endl;
    std::cout << "    - " << CW_STR("comprehensive anti-debug protection") << std::endl;
    std::cout << "    - " << CW_STR("anti-VM/sandbox detection") << std::endl;
    std::cout << "    - " << CW_STR("code integrity verification / hook detection") << std::endl;

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
