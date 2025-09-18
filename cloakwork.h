#ifndef CLOAKWORK_H
#define CLOAKWORK_H

// Cloakwork advanced obfuscation library - header-only c++20 implementation
// Comprehensive protection against static and dynamic analysis

// ██████╗██╗      ██████╗  █████╗ ██╗  ██╗██╗    ██╗ ██████╗ ██████╗ ██╗  ██╗
//██╔════╝██║     ██╔═══██╗██╔══██╗██║ ██╔╝██║    ██║██╔═══██╗██╔══██╗██║ ██╔╝
//██║     ██║     ██║   ██║███████║█████╔╝ ██║ █╗ ██║██║   ██║██████╔╝█████╔╝
//██║     ██║     ██║   ██║██╔══██║██╔═██╗ ██║███╗██║██║   ██║██╔══██╗██╔═██╗
//╚██████╗███████╗╚██████╔╝██║  ██║██║  ██╗╚███╔███╔╝╚██████╔╝██║  ██║██║  ██╗
// ╚═════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝

// Created by @helz.dev on Discord.
// Inspiration from obfusheader.h and Zapcrash's nimrodhide.h

// =================================================================
// COMPILE-TIME CONFIGURATION
// =================================================================
//
// Cloakwork can be configured at compile-time to include only the features you need.
// This reduces binary size and compilation time significantly.
//
// To disable a feature, define the corresponding macro as 0 before including this header:
//   #define CW_ENABLE_STRING_ENCRYPTION 0
//   #include "cloakwork.h"
//
// Alternatively, you can define them as compiler flags:
//   -DCW_ENABLE_VIRTUALIZATION=0
//
// By default, all features are enabled for backwards compatibility.
//
// Configuration options:
// ----------------------
// CW_ENABLE_ALL                    - master switch to enable/disable everything (default: 1)
// CW_ENABLE_STRING_ENCRYPTION      - compile-time string encryption (default: 1)
// CW_ENABLE_VALUE_OBFUSCATION      - integer/value obfuscation (default: 1)
// CW_ENABLE_CONTROL_FLOW           - control flow obfuscation (default: 1)
// CW_ENABLE_ANTI_DEBUG             - anti-debugging features (default: 1)
// CW_ENABLE_FUNCTION_OBFUSCATION   - function pointer obfuscation (default: 1)
// CW_ENABLE_DATA_HIDING            - scattered/polymorphic values (default: 1)
// CW_ENABLE_METAMORPHIC            - metamorphic code generation (default: 1)
// CW_ENABLE_FAKE_SIGNATURES        - fake packer signatures (default: 1)
// CW_ENABLE_VIRTUALIZATION         - virtualization engine (default: 1)
// CW_ENABLE_COMPILE_TIME_RANDOM    - compile-time random generation (default: 1)
//
// Minimal configuration example:
// ------------------------------
// #define CW_ENABLE_ALL 0                      // disable everything first
// #define CW_ENABLE_STRING_ENCRYPTION 1        // enable only what you need
// #define CW_ENABLE_VALUE_OBFUSCATION 1
// #include "cloakwork.h"
//
// Performance-focused configuration:
// -----------------------------------
// #define CW_ENABLE_VIRTUALIZATION 0           // disable heavy features
// #define CW_ENABLE_METAMORPHIC 0
// #define CW_ENABLE_FAKE_SIGNATURES 0
// #include "cloakwork.h"
//
// =================================================================

// default configuration - all features enabled
#ifndef CW_ENABLE_ALL
    #define CW_ENABLE_ALL 1
#endif

// individual feature flags with defaults based on master switch
#ifndef CW_ENABLE_COMPILE_TIME_RANDOM
    #define CW_ENABLE_COMPILE_TIME_RANDOM CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_STRING_ENCRYPTION
    #define CW_ENABLE_STRING_ENCRYPTION CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_VALUE_OBFUSCATION
    #define CW_ENABLE_VALUE_OBFUSCATION CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_CONTROL_FLOW
    #define CW_ENABLE_CONTROL_FLOW CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_ANTI_DEBUG
    #define CW_ENABLE_ANTI_DEBUG CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_FUNCTION_OBFUSCATION
    #define CW_ENABLE_FUNCTION_OBFUSCATION CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_DATA_HIDING
    #define CW_ENABLE_DATA_HIDING CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_METAMORPHIC
    #define CW_ENABLE_METAMORPHIC CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_FAKE_SIGNATURES
    #define CW_ENABLE_FAKE_SIGNATURES CW_ENABLE_ALL
#endif

#ifndef CW_ENABLE_VIRTUALIZATION
    #define CW_ENABLE_VIRTUALIZATION CW_ENABLE_ALL
#endif

// validate configuration dependencies
#if CW_ENABLE_VIRTUALIZATION && !CW_ENABLE_VALUE_OBFUSCATION
    #error "CW_ENABLE_VIRTUALIZATION requires CW_ENABLE_VALUE_OBFUSCATION to be enabled"
#endif

#if CW_ENABLE_DATA_HIDING && !CW_ENABLE_COMPILE_TIME_RANDOM
    #error "CW_ENABLE_DATA_HIDING requires CW_ENABLE_COMPILE_TIME_RANDOM to be enabled"
#endif

#if CW_ENABLE_CONTROL_FLOW && !CW_ENABLE_COMPILE_TIME_RANDOM
    #error "CW_ENABLE_CONTROL_FLOW requires CW_ENABLE_COMPILE_TIME_RANDOM to be enabled"
#endif

// =================================================================
// includes
// =================================================================

#include <cstdint>
#include <array>
#include <bit>
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
    #include <intrin.h>
    #include <winternl.h>
#endif

// compiler detection and configuration
#ifdef _MSC_VER
    #define CW_FORCEINLINE __forceinline
    #define CW_NOINLINE __declspec(noinline)
    #define CW_SECTION(x) __declspec(allocate(x))
    #pragma warning(push)
    #pragma warning(disable: 4996 4244 4267)
#else
    #define CW_FORCEINLINE __attribute__((always_inline)) inline
    #define CW_NOINLINE __attribute__((noinline))
    #define CW_SECTION(x) __attribute__((section(x)))
#endif

// =================================================================
// CLOAKWORK QUICK REFERENCE WIKI
// =================================================================
//
// STRING ENCRYPTION
// -----------------
// CW_STR("text")                   - encrypts string at compile-time, decrypts at runtime
//                                    usage: const char* msg = CW_STR("secret message");
//
// INTEGER/VALUE OBFUSCATION
// -------------------------
// CW_INT(value)                    - obfuscates integer/numeric values
//                                    usage: int x = CW_INT(42);
//
// CW_SCATTER(value)                - scatters data across memory chunks
//                                    usage: auto scattered = CW_SCATTER(myStruct);
//
// CW_POLY(value)                   - creates polymorphic value that mutates internally
//                                    usage: auto poly = CW_POLY(100);
//
// obfuscated_value<T>              - template class for obfuscating any value type
//                                    usage: obfuscated_value<int> val(42);
//
// CONTROL FLOW OBFUSCATION
// ------------------------
// CW_IF(condition)                 - obfuscated if statement with opaque predicates
//                                    usage: CW_IF(x > 0) { /* code */ }
//
// CW_ELSE                          - obfuscated else clause
//                                    usage: CW_IF(cond) { } CW_ELSE { }
//
// CW_BRANCH(condition)             - indirect branching with obfuscation
//                                    usage: CW_BRANCH(isValid) { /* code */ }
//
// CW_FLATTEN(func, args...)        - flattens control flow via state machine
//                                    usage: auto result = CW_FLATTEN(myFunc, arg1, arg2);
//
// FUNCTION CALL PROTECTION
// ------------------------
// CW_CALL(function)                - obfuscates function pointer and adds anti-debug
//                                    usage: auto obf_func = CW_CALL(originalFunc);
//                                           obf_func(args);
//
// obfuscated_call<Func>            - template class for function pointer obfuscation
//                                    usage: obfuscated_call<decltype(func)> obf{func};
//
// ANTI-DEBUGGING/ANALYSIS
// -----------------------
// CW_ANTI_DEBUG()                  - crashes if debugger detected (multiple techniques)
//                                    usage: CW_ANTI_DEBUG();
//
// CW_CHECK_ANALYSIS()              - comprehensive check for debuggers/hardware breakpoints
//                                    usage: CW_CHECK_ANALYSIS();
//
// anti_debug::is_debugger_present() - returns true if debugger detected
//                                     usage: if(anti_debug::is_debugger_present()) { }
//
// anti_debug::timing_check(func)   - detects debuggers via timing analysis
//                                    usage: if(timing_check([](){}, 1000)) { }
//
// anti_debug::has_breakpoints()    - scans memory for int3 breakpoints
//                                    usage: if(has_breakpoints(addr, size)) { }
//
// anti_debug::has_hardware_breakpoints() - checks debug registers
//                                          usage: if(has_hardware_breakpoints()) { }
//
// COMPILE-TIME RANDOMIZATION
// --------------------------
// CW_RANDOM()                      - generates compile-time random value
//                                    usage: constexpr auto rand = CW_RANDOM();
//
// CW_RAND(min, max)                - compile-time random in range [min, max]
//                                    usage: constexpr int x = CW_RAND(1, 100);
//
// VIRTUALIZATION ENGINE
// ---------------------
// CW_VM_START()                    - begin virtualized code section
//                                    usage: CW_VM_START();
//
// CW_VM_PUSH(value)                - push value to VM stack
//                                    usage: CW_VM_PUSH(42);
//
// CW_VM_ADD()                      - add top two stack values
//                                    usage: CW_VM_ADD();
//
// CW_VM_SUB()                      - subtract top two stack values
//                                    usage: CW_VM_SUB();
//
// CW_VM_MUL()                      - multiply top two stack values
//                                    usage: CW_VM_MUL();
//
// CW_VM_XOR()                      - xor top two stack values
//                                    usage: CW_VM_XOR();
//
// CW_VM_EXECUTE()                  - execute virtualized code and get result
//                                    usage: auto result = CW_VM_EXECUTE();
//
// CW_VIRTUALIZE(expr)              - quick virtualization of expressions
//                                    usage: auto val = CW_VIRTUALIZE(compute_mul(10, 20));
//
// virtualization::bytecode_builder - manual bytecode construction
//                                    usage: bytecode_builder b;
//                                           b.push_imm(10).push_imm(20).add();
//
// virtualization::vm_interpreter   - VM interpreter for executing bytecode
//                                    usage: vm_interpreter vm(bytecode);
//                                           auto result = vm.execute();
//
// virtualization::virtualized_code - high-level builder for complex expressions
//                                    usage: virtualized_code vc;
//                                           auto result = vc.compute_add(5, 10).execute();
//
// ADVANCED FEATURES
// -----------------
// encrypted_string<N>              - template class for string encryption
//                                    usage: encrypted_string str{"secret"};
//
// scattered_value<T>               - template for scattering data across memory
//                                    usage: scattered_value<MyStruct> data{myStruct};
//
// polymorphic_value<T>             - value that changes internal representation
//                                    usage: polymorphic_value<int> val{42};
//
// flattened_flow<Func>             - control flow flattening via state machine
//                                    usage: flattened_flow<decltype(func)>().execute(func, args);
//
// metamorphic_function<Func>       - self-modifying function selector
//                                    usage: metamorphic_function<Func> meta{{func1, func2}};
//
// control_flow::opaque_true<>()    - always returns true (hard to analyze)
//                                    usage: if(opaque_true<>()) { }
//
// control_flow::opaque_false<>()   - always returns false (hard to analyze)
//                                    usage: if(!opaque_false<>()) { }
//
// control_flow::indirect_branch()  - adds indirect jumps to confuse analysis
//                                    usage: auto val = indirect_branch(myValue);
//
// USAGE EXAMPLES
// --------------
// // protect sensitive strings
// MessageBoxA(0, CW_STR("this string is encrypted"), CW_STR("title"), 0);
//
// // obfuscate important values
// int key = CW_INT(0xDEADBEEF);
// float pi = CW_POLY(3.14159f);
//
// // protect function calls
// auto encrypted_func = CW_CALL(ImportantFunction);
// auto result = encrypted_func(param1, param2);
//
// // obfuscate control flow
// CW_IF(user_authenticated) {
//     CW_CHECK_ANALYSIS();  // crash if being analyzed
//     process_sensitive_data();
// } CW_ELSE {
//     handle_error();
// }
//
// // flatten complex logic
// auto value = CW_FLATTEN([](int x) { return x * 2; }, input);
//
// // virtualize critical calculations
// CW_VM_START();
// CW_VM_PUSH(secret_key);
// CW_VM_PUSH(0xDEADBEEF);
// CW_VM_XOR();
// CW_VM_PUSH(magic_value);
// CW_VM_ADD();
// uint64_t result = CW_VM_EXECUTE();
//
// // use high-level virtualization api
// cloakwork::virtualization::virtualized_code vc;
// auto encrypted_result = vc.complex_expr(10, 20, 30, 40).execute();
//
// // create custom virtualized function
// cloakwork::virtualization::bytecode_builder builder;
// builder.push_imm(password_hash)
//        .push_imm(salt)
//        .xor_op()
//        .push_imm(iterations)
//        .mul()
//        .halt();
// cloakwork::virtualization::vm_interpreter vm(builder.finalize());
// auto secure_hash = vm.execute();
//
// =================================================================

namespace cloakwork {

    // =================================================================
    // compile-time random number generation
    // =================================================================

#if CW_ENABLE_COMPILE_TIME_RANDOM
    namespace detail {
        template<size_t N>
        constexpr uint32_t fnv1a_hash(const char (&str)[N], uint32_t basis = 0x811c9dc5) {
            uint32_t hash = basis;
            for(size_t i = 0; i < N-1; ++i) {
                hash ^= static_cast<uint32_t>(str[i]);
                hash *= 0x01000193;
            }
            return hash;
        }

        constexpr uint32_t compile_seed() {
            // combine multiple compile-time values for entropy
            constexpr uint32_t time_hash = fnv1a_hash(__TIME__);
            constexpr uint32_t date_hash = fnv1a_hash(__DATE__);
            constexpr uint32_t file_hash = fnv1a_hash(__FILE__);
            return time_hash ^ (date_hash << 1) ^ (file_hash >> 1) ^ __LINE__;
        }

        template<uint32_t Seed>
        struct random_generator {
            static constexpr uint32_t value = ((Seed * 1664525u + 1013904223u) ^ __COUNTER__);
            static constexpr uint32_t next() {
                return random_generator<value>::value;
            }
        };
    }

    // macro for compile-time random values
    #define CW_RANDOM() (cloakwork::detail::random_generator<cloakwork::detail::compile_seed() ^ __COUNTER__>::value)
    #define CW_RAND(min, max) ((min) + (CW_RANDOM() % ((max) - (min) + 1)))
#else
    // fallback to simple runtime random when compile-time random is disabled
    #define CW_RANDOM() (rand())
    #define CW_RAND(min, max) ((min) + (rand() % ((max) - (min) + 1)))
#endif

    // =================================================================
    // anti-debugging and anti-analysis
    // =================================================================

#if CW_ENABLE_ANTI_DEBUG
    namespace anti_debug {

        // check for debugger presence using multiple techniques
        CW_FORCEINLINE bool is_debugger_present() {
#ifdef _WIN32
            // technique 1: isdebuggerpresent api
            if (::IsDebuggerPresent()) return true;

            // technique 2: peb flag check (x64 compatible) - wrapped in try-catch for safety - this wasnt working before but now is due to some magic that i dont really fully understand if im being honest
            __try {
#ifdef _WIN64
                PPEB peb = (PPEB)__readgsqword(0x60);
                if (peb && peb->BeingDebugged) return true;

                // technique 3: ntglobalflag check
                if (peb) {
                    DWORD nt_global_flag = *(DWORD*)((uint8_t*)peb + 0xBC);
                    if (nt_global_flag & 0x70) return true;
                }
#else
                PPEB peb = (PPEB)__readfsdword(0x30);
                if (peb && peb->BeingDebugged) return true;

                // technique 3: ntglobalflag check
                if (peb) {
                    DWORD nt_global_flag = *(DWORD*)((uint8_t*)peb + 0x68);
                    if (nt_global_flag & 0x70) return true;
                }
#endif
            }
            __except(EXCEPTION_EXECUTE_HANDLER) {
                // silently handle access violations
            }

            // technique 4: heap flag checks, careful cause this is a heavier check
            HANDLE heap = GetProcessHeap();
            if (heap) {
                DWORD heap_flags = 0;
                DWORD heap_force_flags = 0;

                if (sizeof(void*) == 8) {
                    // 64-bit offsets
                    heap_flags = *(DWORD*)((uint8_t*)heap + 0x70);
                    heap_force_flags = *(DWORD*)((uint8_t*)heap + 0x74);
                } else {
                    // 32-bit offsets
                    heap_flags = *(DWORD*)((uint8_t*)heap + 0x40);
                    heap_force_flags = *(DWORD*)((uint8_t*)heap + 0x44);
                }

                if ((heap_flags & 0x02) || heap_force_flags != 0) return true;
            }
#endif
            return false;
        }

        // timing-based debugger detection
        template<typename Func>
        CW_FORCEINLINE bool timing_check(Func func, uint64_t threshold = 1000) {
#ifdef _WIN32
            LARGE_INTEGER start, end, freq;
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);

            func();

            QueryPerformanceCounter(&end);
            uint64_t elapsed = ((end.QuadPart - start.QuadPart) * 1000000) / freq.QuadPart;

            return elapsed > threshold;
#else
            return false;
#endif
        }

        // breakpoint detection via int3 scan
        CW_FORCEINLINE bool has_breakpoints(void* addr, size_t size) {
            uint8_t* bytes = reinterpret_cast<uint8_t*>(addr);
            for(size_t i = 0; i < size; ++i) {
                if(bytes[i] == 0xCC) return true; // int3 instruction
            }
            return false;
        }

        // hardware breakpoint detection
        CW_FORCEINLINE bool has_hardware_breakpoints() {
#ifdef _WIN32
            CONTEXT ctx = {};
            ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

            if(GetThreadContext(GetCurrentThread(), &ctx)) {
                return (ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3);
            }
#endif
            return false;
        }
    }

    // macro to crash if debugger detected
    #define CW_ANTI_DEBUG() \
        do { \
            if(cloakwork::anti_debug::is_debugger_present()) { \
                __debugbreak(); \
                *(volatile int*)0 = 0; \
            } \
        } while(0)
#else
    // no-op when anti-debug is disabled
    namespace anti_debug {
        inline bool is_debugger_present() { return false; }
        template<typename Func> inline bool timing_check(Func, uint64_t = 1000) { return false; }
        inline bool has_breakpoints(void*, size_t) { return false; }
        inline bool has_hardware_breakpoints() { return false; }
    }
    #define CW_ANTI_DEBUG() ((void)0)
#endif

    // =================================================================
    // compile-time string encryption
    // =================================================================

#if CW_ENABLE_STRING_ENCRYPTION
    namespace string_encrypt {

        template<size_t N, char Key1 = CW_RAND(1, 127), char Key2 = CW_RAND(1, 127)>
        class encrypted_string {
        private:
            std::array<char, N> data;
            mutable bool decrypted = false;

            // multi-layer xor encryption
            static constexpr char encrypt_char(char c, size_t i) {
                char k1 = Key1 + static_cast<char>(i);
                char k2 = Key2 - static_cast<char>(i * 3);
                char k3 = static_cast<char>((i * i) ^ 0x5A);
                return c ^ k1 ^ k2 ^ k3;
            }

            CW_FORCEINLINE void decrypt_impl() const {
                if(!decrypted) {
                    auto& mutable_data = const_cast<std::array<char, N>&>(data);
                    for(size_t i = 0; i < N; ++i) {
                        char k1 = Key1 + static_cast<char>(i);
                        char k2 = Key2 - static_cast<char>(i * 3);
                        char k3 = static_cast<char>((i * i) ^ 0x5A);
                        mutable_data[i] ^= k1 ^ k2 ^ k3;
                    }
                    const_cast<bool&>(decrypted) = true;
                }
            }

        public:
            template<size_t... I>
            constexpr encrypted_string(const char (&str)[N], std::index_sequence<I...>)
                : data{encrypt_char(str[I], I)...}, decrypted(false) {}

            constexpr encrypted_string(const char (&str)[N])
                : encrypted_string(str, std::make_index_sequence<N>{}) {}

            CW_FORCEINLINE const char* get() const {
                decrypt_impl();
                return data.data();
            }

            CW_FORCEINLINE operator const char*() const {
                return get();
            }
        };

        template<size_t N>
        encrypted_string(const char (&)[N]) -> encrypted_string<N>;
    }

    // macro for easy string encryption
#define CW_STR(s) \
    ([]() -> const char* { \
        static cloakwork::string_encrypt::encrypted_string<sizeof(s)> enc(s); \
        volatile int dummy = rand(); \
        return dummy ? enc.get() : nullptr; \
    }())
#else
    // no-op when string encryption is disabled
    #define CW_STR(s) (s)
#endif

    // =================================================================
    // integer and data obfuscation
    // =================================================================

#if CW_ENABLE_VALUE_OBFUSCATION
    template<typename T>
    class obfuscated_value {
    private:
        mutable T value{};
        T xor_key{};
        T add_key{};

        // rotate bits for additional obfuscation
        template<typename U = T>
        static constexpr std::enable_if_t<std::is_integral_v<U>, U>
        rotate_left(U val, int shift) {
            constexpr int bits = sizeof(U) * 8;
            shift %= bits;
            return (val << shift) | (val >> (bits - shift));
        }

        template<typename U = T>
        static constexpr std::enable_if_t<std::is_integral_v<U>, U>
        rotate_right(U val, int shift) {
            constexpr int bits = sizeof(U) * 8;
            shift %= bits;
            return (val >> shift) | (val << (bits - shift));
        }

    public:
        // default constructor
        obfuscated_value() {
            // initialize with random keys
            xor_key = static_cast<T>(CW_RANDOM());
            add_key = static_cast<T>(CW_RANDOM());
            set(static_cast<T>(0));
        }

        obfuscated_value(T val) {
            // initialize with random keys
            xor_key = static_cast<T>(CW_RANDOM());
            add_key = static_cast<T>(CW_RANDOM());
            set(val);
        }

        CW_FORCEINLINE void set(T val) {
            if constexpr(std::is_integral_v<T>) {
                // multi-step obfuscation for integers
                T temp = val + add_key;
                temp = rotate_left(temp, 5);
                temp ^= xor_key;
                temp = rotate_right(temp, 3);
                value = temp;
            } else if constexpr(sizeof(T) == sizeof(uint64_t)) {
                // for 64-bit non-integral types
                uint64_t bits = std::bit_cast<uint64_t>(val);
                uint64_t key_bits = std::bit_cast<uint64_t>(xor_key);
                bits ^= key_bits;
                value = std::bit_cast<T>(bits);
            } else if constexpr(sizeof(T) == sizeof(uint32_t)) {
                // for 32-bit non-integral types
                uint32_t bits = std::bit_cast<uint32_t>(val);
                uint32_t key_bits = std::bit_cast<uint32_t>(xor_key);
                bits ^= key_bits;
                value = std::bit_cast<T>(bits);
            } else {
                // fallback for other types
                value = val;
            }
        }

        CW_FORCEINLINE T get() const {
            if constexpr(std::is_integral_v<T>) {
                // reverse the obfuscation
                T temp = value;
                temp = rotate_left(temp, 3);
                temp ^= xor_key;
                temp = rotate_right(temp, 5);
                return temp - add_key;
            } else if constexpr(sizeof(T) == sizeof(uint64_t)) {
                uint64_t bits = std::bit_cast<uint64_t>(value);
                uint64_t key_bits = std::bit_cast<uint64_t>(xor_key);
                bits ^= key_bits;
                return std::bit_cast<T>(bits);
            } else if constexpr(sizeof(T) == sizeof(uint32_t)) {
                uint32_t bits = std::bit_cast<uint32_t>(value);
                uint32_t key_bits = std::bit_cast<uint32_t>(xor_key);
                bits ^= key_bits;
                return std::bit_cast<T>(bits);
            } else {
                return value;
            }
        }

        CW_FORCEINLINE operator T() const { return get(); }
        CW_FORCEINLINE obfuscated_value& operator=(T val) { set(val); return *this; }
    };
#else
    // pass-through when value obfuscation is disabled
    template<typename T>
    class obfuscated_value {
    private:
        T value{};
    public:
        obfuscated_value() = default;
        obfuscated_value(T val) : value(val) {}
        CW_FORCEINLINE void set(T val) { value = val; }
        CW_FORCEINLINE T get() const { return value; }
        CW_FORCEINLINE operator T() const { return value; }
        CW_FORCEINLINE obfuscated_value& operator=(T val) { value = val; return *this; }
    };
#endif

    // =================================================================
    // control flow obfuscation
    // =================================================================

#if CW_ENABLE_CONTROL_FLOW
    namespace control_flow {

        // opaque predicates - always true but hard to analyze
        template<int N = CW_RAND(1, 100)>
        CW_FORCEINLINE bool opaque_true() {
            volatile int x = N;
            volatile int y = N * 2;

            // expression that always evaluates to true
            bool result = ((x * x) + (y * y)) > 0;
            result = result && ((x ^ y) != (x & y) || (x | y) == (x | y));
            result = result && ((x << 1) == (y) || (x >> 1) != y);

            return result;
        }

        template<int N = CW_RAND(1, 100)>
        CW_FORCEINLINE bool opaque_false() {
            volatile int x = N;
            volatile int y = N;

            // expression that always evaluates to false
            bool result = (x * x) < 0;
            result = result || ((x ^ x) != 0);
            result = result || ((x & (~x)) != 0);

            return result;
        }

        // control flow flattening via state machine
        template<typename Func>
        class flattened_flow {
        private:
            enum State {
                START = CW_RAND(100, 200),
                EXEC = CW_RAND(201, 300),
                END = CW_RAND(301, 400),
                FAKE1 = CW_RAND(401, 500),
                FAKE2 = CW_RAND(501, 600)
            };

        public:
            template<typename... Args>
            CW_FORCEINLINE auto execute(Func func, Args&&... args) -> decltype(func(std::forward<Args>(args)...)) {
                volatile int state = START;
                volatile int next_state = 0;

                // add random jumps to confuse analysis
                volatile int jumps = CW_RAND(3, 7);

                using ResultType = decltype(func(std::forward<Args>(args)...));
                ResultType result{};

                while(state != END) {
                    switch(state ^ 0xDEADBEEF) {
                        case START ^ 0xDEADBEEF:
                            next_state = opaque_true<>() ? EXEC : FAKE1;
                            if(--jumps > 0 && opaque_false<>()) next_state = FAKE2;
                            break;

                        case EXEC ^ 0xDEADBEEF:
                            result = func(std::forward<Args>(args)...);
                            next_state = END;
                            if(opaque_false<>()) next_state = FAKE1;
                            break;

                        case FAKE1 ^ 0xDEADBEEF:
                            {
                                // dead code to confuse analysis
                                volatile int dummy = 42;
                                dummy = dummy * 2 + 1;
                                next_state = EXEC;
                            }
                            break;

                        case FAKE2 ^ 0xDEADBEEF:
                            {
                                // more dead code
                                volatile float dummy2 = 3.14f;
                                dummy2 = dummy2 * 2.0f;
                                next_state = START;
                            }
                            break;

                        default:
                            next_state = START;
                            break;
                    }

                    state = next_state;

                    // random delay to prevent pattern analysis
                    for(volatile int i = 0; i < CW_RAND(1, 5); ++i) {
                        // compiler barrier
                        _ReadWriteBarrier();
                    }
                }

                return result;
            }
        };

        // indirect branching via computed goto
        template<typename T>
        CW_FORCEINLINE T indirect_branch(T value) {
            volatile T result = value;
            volatile int selector = CW_RAND(0, 4);

            // create multiple paths that all lead to same result
            switch(selector) {
                case 0:
                    result = result ^ 0 ^ 0;
                    break;
                case 1:
                    result = (result * 1) / 1;
                    break;
                case 2:
                    result = result + 0 - 0;
                    break;
                case 3:
                    result = result | 0 & ~0;
                    break;
                case 4:
                    result = result << 0 >> 0;
                    break;
            }

            return result;
        }
    }

    // macros for control flow obfuscation
    #define CW_IF(cond) \
        if(cloakwork::control_flow::opaque_true<>() && (cond))

    #define CW_ELSE \
        else if(cloakwork::control_flow::opaque_true<>())

    #define CW_FLATTEN(func, ...) \
        cloakwork::control_flow::flattened_flow<decltype(func)>().execute(func, __VA_ARGS__)
#else
    // pass-through when control flow obfuscation is disabled
    namespace control_flow {
        template<int N = 0> inline bool opaque_true() { return true; }
        template<int N = 0> inline bool opaque_false() { return false; }
        template<typename T> inline T indirect_branch(T value) { return value; }
    }
    #define CW_IF(cond) if(cond)
    #define CW_ELSE else
    #define CW_FLATTEN(func, ...) func(__VA_ARGS__)
#endif

    // =================================================================
    // function pointer obfuscation and indirection
    // =================================================================

#if CW_ENABLE_FUNCTION_OBFUSCATION
    template<typename Func>
    class obfuscated_call {
    private:
        // store function pointer in obfuscated form
        uintptr_t obfuscated_ptr;
        uintptr_t xor_key;

        // array of decoy function pointers
        static constexpr size_t DECOY_COUNT = 10;
        uintptr_t decoys[DECOY_COUNT];

        CW_FORCEINLINE uintptr_t obfuscate_ptr(Func* ptr) {
            uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);

            // multi-stage obfuscation
            addr = std::rotl(addr, 13);
            addr ^= xor_key;
            addr = std::rotr(addr, 7);
            addr += 0xDEADBEEF;

            return addr;
        }

        CW_FORCEINLINE Func* deobfuscate_ptr(uintptr_t obf) {
            // reverse the obfuscation
            uintptr_t addr = obf;
            addr -= 0xDEADBEEF;
            addr = std::rotl(addr, 7);
            addr ^= xor_key;
            addr = std::rotr(addr, 13);

            return reinterpret_cast<Func*>(addr);
        }

    public:
        obfuscated_call(Func* func)
            : xor_key(CW_RANDOM() | 0xCAFEBABE) {

            // store real function pointer obfuscated
            obfuscated_ptr = obfuscate_ptr(func);

            // fill decoy array with garbage
            for(size_t i = 0; i < DECOY_COUNT; ++i) {
                decoys[i] = CW_RANDOM() ^ xor_key;
            }

            // randomly place real pointer in decoy array
            decoys[CW_RAND(0, DECOY_COUNT-1)] = obfuscated_ptr;
        }

        template<typename... Args>
        CW_FORCEINLINE auto operator()(Args&&... args) {
            if(anti_debug::has_hardware_breakpoints()) {
                *(volatile int*)0 = 0;
            }

            // indirect call through deobfuscation
            Func* real_func = deobfuscate_ptr(obfuscated_ptr);

            // add timing check with higher threshold for compatibility
            auto call_wrapper = [&]() {
                return real_func(std::forward<Args>(args)...);
            };

            // increased threshold to avoid false positives
            if(anti_debug::timing_check([](){}, 10000)) {
                // debugger detected
                __debugbreak();
            }

            return call_wrapper();
        }
    };
#else
    // pass-through when function obfuscation is disabled
    template<typename Func>
    class obfuscated_call {
    private:
        Func* func_ptr;
    public:
        obfuscated_call(Func* func) : func_ptr(func) {}
        template<typename... Args>
        CW_FORCEINLINE auto operator()(Args&&... args) {
            return func_ptr(std::forward<Args>(args)...);
        }
    };
#endif

    // =================================================================
    // advanced data hiding techniques
    // =================================================================

#if CW_ENABLE_DATA_HIDING
    namespace data_hiding {

        // scatter data across memory to prevent dumping
        template<typename T, size_t Chunks = 8>
        class scattered_value {
        private:
            struct chunk {
                uint8_t data[sizeof(T) / Chunks + (sizeof(T) % Chunks ? 1 : 0)];
                uint8_t xor_key;
            };

            chunk chunks[Chunks];

        public:
            scattered_value() {
                // default constructor - scatter zero value
                T default_value{};
                const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&default_value);
                size_t byte_idx = 0;

                for(size_t i = 0; i < Chunks; ++i) {
                    chunks[i].xor_key = static_cast<uint8_t>(CW_RANDOM());

                    size_t chunk_size = sizeof(chunks[i].data);
                    for(size_t j = 0; j < chunk_size && byte_idx < sizeof(T); ++j, ++byte_idx) {
                        chunks[i].data[j] = bytes[byte_idx] ^ chunks[i].xor_key;
                    }
                }
            }

            scattered_value(const T& value) {
                const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);
                size_t byte_idx = 0;

                for(size_t i = 0; i < Chunks; ++i) {
                    chunks[i].xor_key = static_cast<uint8_t>(CW_RANDOM());

                    size_t chunk_size = sizeof(chunks[i].data);
                    for(size_t j = 0; j < chunk_size && byte_idx < sizeof(T); ++j, ++byte_idx) {
                        chunks[i].data[j] = bytes[byte_idx] ^ chunks[i].xor_key;
                    }
                }
            }

            CW_FORCEINLINE T get() const {
                T result;
                uint8_t* result_bytes = reinterpret_cast<uint8_t*>(&result);
                size_t byte_idx = 0;

                for(size_t i = 0; i < Chunks; ++i) {
                    size_t chunk_size = sizeof(chunks[i].data);
                    for(size_t j = 0; j < chunk_size && byte_idx < sizeof(T); ++j, ++byte_idx) {
                        result_bytes[byte_idx] = chunks[i].data[j] ^ chunks[i].xor_key;
                    }
                }

                return result;
            }

            CW_FORCEINLINE operator T() const { return get(); }
        };

        // polymorphic value that changes representation
        template<typename T>
        class polymorphic_value {
        private:
            mutable T value;
            mutable uint32_t mutation_count = 0;

            CW_FORCEINLINE void mutate() const {
                // change internal representation periodically
                if(++mutation_count % 100 == 0) {
                    T temp = value;

                    // apply random transformation
                    uint32_t transform = CW_RANDOM() % 4;
                    switch(transform) {
                        case 0: // xor swap for integral types only
                            if constexpr(std::is_integral_v<T> && sizeof(T) <= sizeof(uint64_t)) {
                                if constexpr(sizeof(T) == 8) {
                                    uint64_t bits = std::bit_cast<uint64_t>(temp);
                                    bits = ~bits;
                                    value = std::bit_cast<T>(bits);
                                    bits = std::bit_cast<uint64_t>(value);
                                    bits = ~bits;
                                    value = std::bit_cast<T>(bits);
                                } else if constexpr(sizeof(T) == 4) {
                                    uint32_t bits = std::bit_cast<uint32_t>(temp);
                                    bits = ~bits;
                                    value = std::bit_cast<T>(bits);
                                    bits = std::bit_cast<uint32_t>(value);
                                    bits = ~bits;
                                    value = std::bit_cast<T>(bits);
                                } else if constexpr(sizeof(T) == 2) {
                                    uint16_t bits = std::bit_cast<uint16_t>(temp);
                                    bits = ~bits;
                                    value = std::bit_cast<T>(bits);
                                } else {
                                    value = temp; // fallback
                                }
                            }
                            break;
                        case 1: // rotate for unsigned integral types
                            if constexpr(std::is_unsigned_v<T> && std::is_integral_v<T>) {
                                value = std::rotl(value, 1);
                                value = std::rotr(value, 1);
                            }
                            break;
                        case 2: // add-subtract
                            if constexpr(std::is_arithmetic_v<T>) {
                                T key = static_cast<T>(mutation_count);
                                value = temp + key;
                                value = value - key;
                            }
                            break;
                        case 3: // no-op
                            break;
                    }
                }
            }

        public:
            polymorphic_value() : value{}, mutation_count(0) {} // default constructor
            polymorphic_value(T val) : value(val) {}

            CW_FORCEINLINE T get() const {
                mutate();
                return value;
            }

            CW_FORCEINLINE void set(T val) {
                value = val;
                mutate();
            }

            CW_FORCEINLINE operator T() const { return get(); }
        };
    }
#else
    // pass-through when data hiding is disabled
    namespace data_hiding {
        template<typename T, size_t Chunks = 8>
        class scattered_value {
        private:
            T value;
        public:
            scattered_value() : value{} {}  // default constructor
            scattered_value(const T& val) : value(val) {}
            CW_FORCEINLINE T get() const { return value; }
            CW_FORCEINLINE operator T() const { return value; }
        };

        template<typename T>
        class polymorphic_value {
        private:
            T value;
        public:
            polymorphic_value() : value{} {}  // default constructor
            polymorphic_value(T val) : value(val) {}
            CW_FORCEINLINE T get() const { return value; }
            CW_FORCEINLINE void set(T val) { value = val; }
            CW_FORCEINLINE operator T() const { return value; }
        };
    }
#endif

    // =================================================================
    // metamorphic code generation
    // =================================================================

#if CW_ENABLE_METAMORPHIC
    namespace metamorphic {

        // self-modifying code pattern
        template<typename Func>
        class metamorphic_function {
        private:
            static constexpr size_t MAX_MUTATIONS = 5;

            struct mutation {
                Func* func;
                uint32_t key;
            };

            mutation mutations[MAX_MUTATIONS];
            mutable size_t current_mutation = 0;

        public:
            metamorphic_function(std::initializer_list<Func*> funcs) {
                size_t i = 0;
                for(auto* func : funcs) {
                    if(i < MAX_MUTATIONS) {
                        mutations[i].func = func;
                        mutations[i].key = CW_RANDOM();
                        ++i;
                    }
                }

                // fill remaining slots with first function
                while(i < MAX_MUTATIONS) {
                    mutations[i] = mutations[0];
                    ++i;
                }
            }

            template<typename... Args>
            CW_FORCEINLINE auto operator()(Args&&... args) const {
                // select mutation based on runtime conditions
                current_mutation = (current_mutation + 1) % MAX_MUTATIONS;

                // add randomness to selection
                if(CW_RANDOM() % 100 < 20) {
                    current_mutation = CW_RANDOM() % MAX_MUTATIONS;
                }

                return mutations[current_mutation].func(std::forward<Args>(args)...);
            }
        };
    }
#else
    // pass-through when metamorphic is disabled
    namespace metamorphic {
        template<typename Func>
        class metamorphic_function {
        private:
            Func* func_ptr;
        public:
            metamorphic_function(std::initializer_list<Func*> funcs) {
                if(funcs.size() > 0) func_ptr = *funcs.begin();
            }
            template<typename... Args>
            CW_FORCEINLINE auto operator()(Args&&... args) const {
                return func_ptr(std::forward<Args>(args)...);
            }
        };
    }
#endif

    // ===========================================================================
    // fake signatures and watermarks (need to improve, sigs are outdated i think)
    // ===========================================================================

#if CW_ENABLE_FAKE_SIGNATURES
    namespace signatures {

        // embed fake packer signatures
        #ifdef _MSC_VER
            #pragma section(".themida", read)
            #pragma section(".vmp0", read)
            #pragma section(".enigma1", read)
            #pragma section(".aspack", read)
            #pragma section(".upx0", read)
        #endif

        CW_SECTION(".themida") volatile const char themida_sig[] = "Themida";
        CW_SECTION(".vmp0") volatile const char vmp_sig[] = "VMProtect";
        CW_SECTION(".enigma1") volatile const char enigma_sig[] = "\x45\x6E\x69\x67\x6D\x61";
        CW_SECTION(".aspack") volatile const char aspack_sig[] = "ASPack";
        CW_SECTION(".upx0") volatile const char upx_sig[] = "UPX!";

        // add fake import signatures
        CW_NOINLINE void fake_imports() {
            volatile const char* fake_dlls[] = {
                "vmp_api.dll",
                "themida_sdk.dll",
                "obsidium.dll",
                "aspr_api.dll"
            };

            for(auto dll : fake_dlls) {
                volatile size_t len = 0;
                while(dll[len]) len++;
            }
        }
    }
#else
    // no-op when fake signatures are disabled
    namespace signatures {
        inline void fake_imports() {}
    }
#endif

    // ====================================================================================================================
    // virtualization engine - converts code to custom bytecode (THIS IS VERY HEAVY SO BE CAREFUL WHEN IMPLEMENTING THIS)
    // ====================================================================================================================

#if CW_ENABLE_VIRTUALIZATION
    namespace virtualization {

        // polymorphic instruction encoding system
        namespace poly_opcodes {
            // compile-time rotate left for uint8_t
            constexpr uint8_t rotl8(uint8_t val, int shift) {
                shift &= 7;
                return (val << shift) | (val >> (8 - shift));
            }

            // generate compile-time random transform
            template<uint32_t Seed>
            struct instruction_encoder {
                static constexpr uint8_t key = static_cast<uint8_t>(Seed ^ 0xA5);
                static constexpr uint8_t transform(uint8_t base) {
                    return rotl8(base ^ key, (Seed % 7) + 1);
                }
            };
        }

        // heavily obfuscated opcode definitions with polymorphic encoding
        enum class opcode : uint8_t {
            // each opcode has multiple valid encodings
            NOP = CW_RAND(0x00, 0x0F),
            NOP_ALT1 = CW_RAND(0x10, 0x1F),
            NOP_ALT2 = CW_RAND(0xE0, 0xE7),

            PUSH_IMM = CW_RAND(0x20, 0x27),
            PUSH_IMM_ALT = CW_RAND(0x28, 0x2F),
            PUSH_REG = CW_RAND(0x30, 0x37),
            POP_REG = CW_RAND(0x38, 0x3F),

            // arithmetic with multiple encodings
            ADD = CW_RAND(0x40, 0x43),
            ADD_ALT = CW_RAND(0x44, 0x47),
            SUB = CW_RAND(0x48, 0x4B),
            SUB_ALT = CW_RAND(0x4C, 0x4F),
            MUL = CW_RAND(0x50, 0x53),
            MUL_ALT = CW_RAND(0x54, 0x57),
            DIV = CW_RAND(0x58, 0x5B),
            MOD = CW_RAND(0x5C, 0x5F),
            NEG = CW_RAND(0x60, 0x63),

            // bitwise with morphing
            AND = CW_RAND(0x64, 0x67),
            OR = CW_RAND(0x68, 0x6B),
            XOR = CW_RAND(0x6C, 0x6F),
            XOR_ALT = CW_RAND(0x70, 0x73),
            NOT = CW_RAND(0x74, 0x77),
            SHL = CW_RAND(0x78, 0x7B),
            SHR = CW_RAND(0x7C, 0x7F),
            ROL = CW_RAND(0x80, 0x83),
            ROR = CW_RAND(0x84, 0x87),

            // control flow obfuscation
            JMP = CW_RAND(0x88, 0x8B),
            JZ = CW_RAND(0x8C, 0x8F),
            JNZ = CW_RAND(0x90, 0x93),
            JG = CW_RAND(0x94, 0x97),
            JL = CW_RAND(0x98, 0x9B),
            JGE = CW_RAND(0x9C, 0x9F),
            JLE = CW_RAND(0xA0, 0xA3),

            // comparison
            CMP = CW_RAND(0xA4, 0xA7),
            TEST = CW_RAND(0xA8, 0xAB),

            // memory operations
            LOAD = CW_RAND(0xAC, 0xAF),
            STORE = CW_RAND(0xB0, 0xB3),

            // special operations
            CALL = CW_RAND(0xB4, 0xB7),
            RET = CW_RAND(0xB8, 0xBB),
            HALT = CW_RAND(0xBC, 0xBF),
            HALT_ALT = CW_RAND(0xC0, 0xC3),

            // heavy obfuscation opcodes
            JUNK = CW_RAND(0xC4, 0xC7),
            SHUFFLE = CW_RAND(0xC8, 0xCB),
            ENCRYPT = CW_RAND(0xCC, 0xCF),
            MORPH = CW_RAND(0xD0, 0xD3),
            FAKE_OP1 = CW_RAND(0xD4, 0xD7),
            FAKE_OP2 = CW_RAND(0xD8, 0xDB),
            FAKE_OP3 = CW_RAND(0xDC, 0xDF),
        };

        // scattered vm state to prevent easy analysis
        namespace vm_state {
            // split context into multiple obfuscated structures
            struct scattered_registers {
                obfuscated_value<uint64_t> r[8]; // simplified for compatibility
                obfuscated_value<uint64_t> shadow[8];

                scattered_registers() {
                    // arrays of obfuscated_value will be default constructed
                }
            };

            struct polymorphic_stack {
                static constexpr size_t REAL_SIZE = 1024;
                static constexpr size_t FAKE_SIZE = 256;

                obfuscated_value<uint64_t> real_stack[REAL_SIZE]; // simplified
                volatile uint64_t decoy_stack[FAKE_SIZE]; // fake stack for confusion
                obfuscated_value<size_t> sp{0};
                obfuscated_value<size_t> fake_sp{0};

                CW_FORCEINLINE void morph_push(uint64_t val) {
                    // randomly use real or update both
                    if(CW_RANDOM() % 100 < 80) {
                        if(sp.get() < REAL_SIZE) {
                            real_stack[sp.get()] = val;
                            sp = sp.get() + 1;
                        }
                    }
                    // always update decoy
                    if(fake_sp.get() < FAKE_SIZE) {
                        decoy_stack[fake_sp.get()] = val ^ CW_RANDOM();
                        fake_sp = fake_sp.get() + 1;
                    }
                }

                CW_FORCEINLINE uint64_t morph_pop() {
                    // decoy operation
                    if(fake_sp.get() > 0) {
                        size_t temp_sp = fake_sp.get() - 1;
                        fake_sp = temp_sp;
                        volatile uint64_t fake = decoy_stack[temp_sp];
                        fake = fake * 2 + 1;
                    }

                    if(sp.get() > 0) {
                        sp = sp.get() - 1;
                        return real_stack[sp.get()].get();
                    }
                    return 0;
                }
            };

            struct obfuscated_control {
                obfuscated_value<size_t> real_ip{0};
                obfuscated_value<size_t> shadow_ip{0}; // fake ip
                obfuscated_value<uint32_t> flags{0};
                obfuscated_value<uint32_t> fake_flags{0};
            };
        }

        // heavily obfuscated vm context
        struct vm_context {
            vm_state::scattered_registers regs;
            vm_state::polymorphic_stack stack;
            vm_state::obfuscated_control control;

            // scattered memory with fake regions
            std::array<uint8_t, 2048> real_memory{};
            std::array<uint8_t, 1024> fake_memory1{};
            std::array<uint8_t, 1024> fake_memory2{};

            vm_context() : regs{}, stack{}, control{}, real_memory{}, fake_memory1{}, fake_memory2{} {}

            // obfuscated stack operations
            CW_FORCEINLINE void push(uint64_t value) {
                stack.morph_push(value);
                // fake operations
                volatile uint64_t dummy = value;
                dummy = std::rotl(dummy ^ 0xCAFEBABE, CW_RAND(1,31));
                fake_memory1[CW_RAND(0,1023)] = static_cast<uint8_t>(dummy);
            }

            CW_FORCEINLINE uint64_t pop() {
                // decoy operations
                volatile uint8_t fake = fake_memory2[CW_RAND(0,1023)];
                fake = fake ^ 0x42;

                return stack.morph_pop();
            }

            // indirect register access
            CW_FORCEINLINE uint64_t get_reg(uint8_t reg) {
                uint8_t real_reg = reg & 0x07;
                // update shadow register to confuse analysis
                regs.shadow[real_reg] = CW_RANDOM();
                return regs.r[real_reg].get();
            }

            CW_FORCEINLINE void set_reg(uint8_t reg, uint64_t value) {
                uint8_t real_reg = reg & 0x07;
                regs.r[real_reg] = value;
                // update shadow with junk
                regs.shadow[real_reg] = value ^ CW_RANDOM();
            }

            // property accessors for compatibility
            size_t sp() const { return stack.sp.get(); }
            void set_sp(size_t val) { stack.sp = val; }
            size_t ip() const { return control.real_ip.get(); }
            void set_ip(size_t val) {
                control.real_ip = val;
                control.shadow_ip = val ^ CW_RANDOM(); // confuse analysis
            }
            uint32_t flags() const { return control.flags.get(); }
            void set_flags(uint32_t val) {
                control.flags = val;
                control.fake_flags = ~val; // inverse for confusion
            }
        };

        // polymorphic bytecode builder with instruction morphing
        class bytecode_builder {
        private:
            std::vector<uint8_t> code;
            std::vector<uint8_t> shadow_code; // fake bytecode stream
            bool has_halt = false;

            // polymorphic encryption with multiple layers
            void multi_layer_encrypt() {
                // layer 1: xor with rotating key
                uint8_t key1 = static_cast<uint8_t>(CW_RANDOM());
                for(size_t i = 0; i < code.size(); ++i) {
                    code[i] ^= key1;
                    key1 = std::rotl(key1, 1) + static_cast<uint8_t>(i);
                }

                // layer 2: substitution cipher
                for(size_t i = 0; i < code.size(); ++i) {
                    code[i] = std::rotl(code[i], (i % 7) + 1);
                }

                // layer 3: position-dependent transform
                for(size_t i = 1; i < code.size(); ++i) {
                    code[i] ^= code[i-1];
                }
            }

            // instruction morphing - replace single instruction with equivalent sequence
            void morph_instruction(opcode op) {
                switch(CW_RANDOM() % 4) {
                    case 0:
                        // direct emission
                        code.push_back(static_cast<uint8_t>(op));
                        break;
                    case 1:
                        // emit with junk prefix
                        code.push_back(static_cast<uint8_t>(opcode::NOP_ALT1));
                        code.push_back(static_cast<uint8_t>(op));
                        break;
                    case 2:
                        // emit with fake operation
                        code.push_back(static_cast<uint8_t>(opcode::FAKE_OP1));
                        code.push_back(static_cast<uint8_t>(op));
                        code.push_back(static_cast<uint8_t>(opcode::NOP_ALT2));
                        break;
                    case 3:
                        // emit alternate encoding if available
                        if(op == opcode::ADD && CW_RANDOM() % 2) {
                            code.push_back(static_cast<uint8_t>(opcode::ADD_ALT));
                        } else if(op == opcode::XOR && CW_RANDOM() % 2) {
                            code.push_back(static_cast<uint8_t>(opcode::XOR_ALT));
                        } else {
                            code.push_back(static_cast<uint8_t>(op));
                        }
                        break;
                }
            }

        public:
            // polymorphic opcode emission
            bytecode_builder& emit(opcode op) {
                // track halt
                if(op == opcode::HALT || op == opcode::HALT_ALT) {
                    has_halt = true;
                    // randomly choose halt variant
                    op = CW_RANDOM() % 2 ? opcode::HALT : opcode::HALT_ALT;
                }

                // apply instruction morphing
                morph_instruction(op);

                // add to shadow code
                shadow_code.push_back(static_cast<uint8_t>(CW_RANDOM()));

                // randomly insert obfuscation
                if(!has_halt && CW_RANDOM() % 100 < 30) {
                    switch(CW_RANDOM() % 5) {
                        case 0:
                            code.push_back(static_cast<uint8_t>(opcode::JUNK));
                            break;
                        case 1:
                            code.push_back(static_cast<uint8_t>(opcode::SHUFFLE));
                            break;
                        case 2:
                            code.push_back(static_cast<uint8_t>(opcode::NOP));
                            break;
                        case 3:
                            code.push_back(static_cast<uint8_t>(opcode::FAKE_OP2));
                            break;
                        case 4:
                            code.push_back(static_cast<uint8_t>(opcode::MORPH));
                            break;
                    }
                }

                return *this;
            }

            bytecode_builder& emit_byte(uint8_t byte) {
                code.push_back(byte);
                shadow_code.push_back(byte ^ 0xFF);
                return *this;
            }

            bytecode_builder& emit_imm(uint64_t value) {
                // obfuscate immediate values
                uint64_t obf_value = value ^ CW_RANDOM();

                // store with random endianness
                if(CW_RANDOM() % 2) {
                    // little-endian
                    for(int i = 0; i < 8; ++i) {
                        code.push_back(static_cast<uint8_t>(obf_value >> (i * 8)));
                    }
                    code.push_back(0x00); // endianness marker
                } else {
                    // big-endian
                    for(int i = 7; i >= 0; --i) {
                        code.push_back(static_cast<uint8_t>(obf_value >> (i * 8)));
                    }
                    code.push_back(0xFF); // endianness marker
                }

                return *this;
            }

            // polymorphic instruction builders
            bytecode_builder& push_imm(uint64_t value) {
                // randomly choose push variant
                if(CW_RANDOM() % 2) {
                    emit(opcode::PUSH_IMM);
                } else {
                    emit(opcode::PUSH_IMM_ALT);
                }
                emit_imm(value);
                return *this;
            }

            // arithmetic with morphing
            bytecode_builder& add() {
                if(CW_RANDOM() % 3 == 0) {
                    // morph ADD into SUB with negation
                    emit(opcode::NEG);
                    emit(opcode::SUB);
                } else {
                    emit(CW_RANDOM() % 2 ? opcode::ADD : opcode::ADD_ALT);
                }
                return *this;
            }

            bytecode_builder& sub() {
                if(CW_RANDOM() % 3 == 0) {
                    // morph SUB into ADD with negation
                    emit(opcode::NEG);
                    emit(opcode::ADD);
                } else {
                    emit(CW_RANDOM() % 2 ? opcode::SUB : opcode::SUB_ALT);
                }
                return *this;
            }

            bytecode_builder& mul() {
                emit(CW_RANDOM() % 2 ? opcode::MUL : opcode::MUL_ALT);
                return *this;
            }

            bytecode_builder& div() { return emit(opcode::DIV); }

            // bitwise with morphing
            bytecode_builder& xor_op() {
                if(CW_RANDOM() % 3 == 0) {
                    // morph XOR into (A OR B) AND NOT(A AND B)
                    // this is complex so just emit XOR for now
                    emit(CW_RANDOM() % 2 ? opcode::XOR : opcode::XOR_ALT);
                } else {
                    emit(CW_RANDOM() % 2 ? opcode::XOR : opcode::XOR_ALT);
                }
                return *this;
            }

            bytecode_builder& and_op() { return emit(opcode::AND); }
            bytecode_builder& or_op() { return emit(opcode::OR); }
            bytecode_builder& not_op() { return emit(opcode::NOT); }

            bytecode_builder& jmp(size_t offset) {
                emit(opcode::JMP);
                emit_imm(offset);
                return *this;
            }

            bytecode_builder& halt() {
                has_halt = true;
                return emit(CW_RANDOM() % 2 ? opcode::HALT : opcode::HALT_ALT);
            }

            // finalize with heavy obfuscation
            std::vector<uint8_t> finalize() {
                if(!has_halt) {
                    halt();
                }

                // add polymorphic padding
                size_t padding = CW_RAND(8, 32);
                for(size_t i = 0; i < padding; ++i) {
                    code.push_back(static_cast<uint8_t>(CW_RANDOM()));
                    shadow_code.push_back(static_cast<uint8_t>(CW_RANDOM()));
                }

                // randomly interleave shadow code
                if(CW_RANDOM() % 100 < 20) {
                    for(size_t i = 0; i < shadow_code.size() && i < code.size(); i += CW_RAND(3,7)) {
                        code.insert(code.begin() + i, shadow_code[i]);
                    }
                }

                // apply multi-layer encryption
                multi_layer_encrypt();

                return code;
            }
        };

        // heavily obfuscated vm interpreter that hides vm patterns
        class vm_interpreter {
        private:
            vm_context ctx;
            std::vector<uint8_t> bytecode;
            std::vector<uint8_t> fake_bytecode; // decoy

            // multi-layer decryption state
            struct decrypt_state {
                uint8_t key1;
                uint8_t key2;
                uint8_t key3;
                size_t position;
            } decrypt;

            // indirect execution table with function pointers
            using handler_func = void(vm_interpreter::*)(uint64_t&, uint64_t&);
            handler_func handlers[256];

            // polymorphic decryption
            CW_FORCEINLINE uint8_t multi_decrypt_byte() {
                if(ctx.ip() >= bytecode.size()) return 0;

                uint8_t byte = bytecode[ctx.ip()];

                // reverse multi-layer encryption
                // layer 3 reverse: position-dependent
                if(ctx.ip() > 0) {
                    byte ^= bytecode[ctx.ip() - 1];
                }

                // layer 2 reverse: substitution
                byte = std::rotr(byte, (ctx.ip() % 7) + 1);

                // layer 1 reverse: xor with rotating key
                byte ^= decrypt.key1;
                decrypt.key1 = std::rotl(decrypt.key1, 1) + static_cast<uint8_t>(ctx.ip());

                // decoy operations
                volatile uint8_t fake = fake_bytecode[ctx.ip() % fake_bytecode.size()];
                fake = fake ^ decrypt.key2;
                decrypt.key2 = std::rotl(decrypt.key2, 3);

                ctx.set_ip(ctx.ip() + 1);
                return byte;
            }

            // fetch with endianness handling
            CW_FORCEINLINE uint64_t multi_fetch_imm() {
                uint64_t value = 0;

                // read 8 bytes
                uint8_t bytes[8];
                for(int i = 0; i < 8; ++i) {
                    bytes[i] = multi_decrypt_byte();
                }

                // check endianness marker
                uint8_t marker = multi_decrypt_byte();

                if(marker == 0x00) {
                    // little-endian
                    for(int i = 0; i < 8; ++i) {
                        value |= static_cast<uint64_t>(bytes[i]) << (i * 8);
                    }
                } else {
                    // big-endian
                    for(int i = 0; i < 8; ++i) {
                        value |= static_cast<uint64_t>(bytes[i]) << ((7-i) * 8);
                    }
                }

                // de-obfuscate value
                value ^= CW_RANDOM();

                return value;
            }

            // heavily obfuscated instruction dispatcher
            CW_FORCEINLINE bool dispatch_morphed() {
                uint8_t op = multi_decrypt_byte();

                // anti-analysis checks
                static size_t chaos_counter = 0;
                if(++chaos_counter % 50 == 0) {
                    if(anti_debug::is_debugger_present() ||
                       anti_debug::has_hardware_breakpoints()) {
                        // corrupt execution subtly
                        op = poly_opcodes::rotl8(op, chaos_counter % 8);
                        ctx.push(CW_RANDOM()); // inject garbage
                    }
                }

                // polymorphic opcode recognition
                uint64_t dummy1 = 0, dummy2 = 0;
                return handle_polymorphic_op(op, dummy1, dummy2);
            }

            // unified polymorphic handler
            CW_FORCEINLINE bool handle_polymorphic_op(uint8_t op, uint64_t& v1, uint64_t& v2) {
                // check all possible encodings
                if(op == static_cast<uint8_t>(opcode::NOP) ||
                   op == static_cast<uint8_t>(opcode::NOP_ALT1) ||
                   op == static_cast<uint8_t>(opcode::NOP_ALT2)) {
                    // nop with decoy operations
                    volatile uint32_t decoy = CW_RANDOM();
                    decoy = std::rotl(decoy, 5);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::PUSH_IMM) ||
                          op == static_cast<uint8_t>(opcode::PUSH_IMM_ALT)) {
                    uint64_t value = multi_fetch_imm();
                    ctx.push(value);
                    // fake operations
                    fake_bytecode.push_back(static_cast<uint8_t>(value));
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::PUSH_REG)) {
                    uint8_t reg = multi_decrypt_byte();
                    ctx.push(ctx.get_reg(reg));
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::POP_REG)) {
                    uint8_t reg = multi_decrypt_byte();
                    ctx.set_reg(reg, ctx.pop());
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::ADD) ||
                          op == static_cast<uint8_t>(opcode::ADD_ALT)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    // obfuscated addition
                    uint64_t result = (v1 ^ v2) + ((v1 & v2) << 1);
                    ctx.push(result);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::SUB) ||
                          op == static_cast<uint8_t>(opcode::SUB_ALT)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v1 - v2);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::MUL) ||
                          op == static_cast<uint8_t>(opcode::MUL_ALT)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v1 * v2);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::DIV)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v2 != 0 ? v1 / v2 : 0);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::MOD)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v2 != 0 ? v1 % v2 : 0);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::NEG)) {
                    v1 = ctx.pop();
                    int64_t signed_val = static_cast<int64_t>(v1);
                    ctx.push(static_cast<uint64_t>(-signed_val));
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::XOR) ||
                          op == static_cast<uint8_t>(opcode::XOR_ALT)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v1 ^ v2);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::AND)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v1 & v2);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::OR)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v1 | v2);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::NOT)) {
                    v1 = ctx.pop();
                    ctx.push(~v1);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::SHL)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v1 << v2);
                    return true;
                } else if(op == static_cast<uint8_t>(opcode::SHR)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(v1 >> v2);
                    return true;
                } else if(op == static_cast<uint8_t>(opcode::ROL)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(std::rotl(v1, static_cast<int>(v2)));
                    return true;
                } else if(op == static_cast<uint8_t>(opcode::ROR)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.push(std::rotr(v1, static_cast<int>(v2)));
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::JMP)) {
                    size_t target = static_cast<size_t>(multi_fetch_imm());
                    ctx.set_ip(target);
                    return true;
                } else if(op == static_cast<uint8_t>(opcode::JZ)) {
                    size_t target = static_cast<size_t>(multi_fetch_imm());
                    if((ctx.flags() & 1) != 0) {
                        ctx.set_ip(target);
                    }
                    return true;
                } else if(op == static_cast<uint8_t>(opcode::JNZ)) {
                    size_t target = static_cast<size_t>(multi_fetch_imm());
                    if((ctx.flags() & 1) == 0) {
                        ctx.set_ip(target);
                    }
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::CMP)) {
                    v2 = ctx.pop();
                    v1 = ctx.pop();
                    ctx.set_flags((v1 == v2) ? 1 : 0);
                    return true;

                } else if(op == static_cast<uint8_t>(opcode::HALT) ||
                          op == static_cast<uint8_t>(opcode::HALT_ALT)) {
                    return false;

                } else if(op == static_cast<uint8_t>(opcode::JUNK) ||
                          op == static_cast<uint8_t>(opcode::FAKE_OP1) ||
                          op == static_cast<uint8_t>(opcode::FAKE_OP2) ||
                          op == static_cast<uint8_t>(opcode::FAKE_OP3)) {
                    // elaborate dead code
                    volatile uint64_t junk = CW_RANDOM();
                    junk = (junk * junk) ^ 0xDEADBEEF;
                    junk = std::rotl(junk, CW_RAND(1,63));
                    fake_bytecode.push_back(static_cast<uint8_t>(junk));
                    return true;
                } else if(op == static_cast<uint8_t>(opcode::SHUFFLE)) {
                    // complex stack manipulation
                    if(ctx.sp() >= 2) {
                        uint64_t temp1 = ctx.pop();
                        uint64_t temp2 = ctx.pop();
                        ctx.push(temp1);
                        ctx.push(temp2);
                    }
                    return true;
                } else if(op == static_cast<uint8_t>(opcode::MORPH)) {
                    // metamorphic operation
                    decrypt.key1 = std::rotl(decrypt.key1, 3);
                    decrypt.key2 ^= CW_RANDOM();
                    return true;
                } else {
                    // unrecognized opcode - add confusion
                    ctx.push(CW_RANDOM() ^ op);
                    return true;
                }
            }

        public:
            vm_interpreter(std::vector<uint8_t>&& code)
                : bytecode(std::move(code)),
                  fake_bytecode(CW_RAND(100,200)),
                  decrypt{static_cast<uint8_t>(CW_RANDOM()),
                          static_cast<uint8_t>(CW_RANDOM()),
                          static_cast<uint8_t>(CW_RANDOM()), 0} {
                // initialize fake bytecode with random data
                for(auto& b : fake_bytecode) {
                    b = static_cast<uint8_t>(CW_RANDOM());
                }
            }

            // heavily obfuscated execution
            CW_FORCEINLINE uint64_t execute() {
                // reset context with obfuscation
                ctx = vm_context();
                ctx.set_ip(0);
                ctx.set_sp(0);

                // clear real stack
                for(size_t i = 0; i < vm_state::polymorphic_stack::REAL_SIZE; ++i) {
                    ctx.stack.real_stack[i] = 0;
                }

                // fill fake stack with garbage
                for(size_t i = 0; i < vm_state::polymorphic_stack::FAKE_SIZE; ++i) {
                    ctx.stack.decoy_stack[i] = CW_RANDOM();
                }

                // safety limits with obfuscation
                size_t max_instructions = 100000 + CW_RAND(0, 10000);
                size_t instruction_count = 0;

                // main execution loop with heavy obfuscation
                while(instruction_count < max_instructions) {
                    // inject random delays and checks
                    if(CW_RANDOM() % 500 < 3) {
                        if(anti_debug::timing_check([](){}, 5000)) {
                            // detected timing analysis
                            ctx.push(CW_RANDOM());
                        }

                        for(volatile int i = 0; i < CW_RAND(1, 3); ++i) {
                            _ReadWriteBarrier();
                        }
                    }

                    if(!dispatch_morphed()) {
                        break;
                    }

                    instruction_count++;

                    // periodic stack obfuscation
                    if(instruction_count % 100 == 0) {
                        ctx.stack.fake_sp = CW_RAND(0, vm_state::polymorphic_stack::FAKE_SIZE-1);
                    }
                }

                // return top of stack with obfuscation
                if(ctx.sp() > 0) {
                    return ctx.stack.real_stack[ctx.sp() - 1].get();
                }
                return 0;
            }

            // execute with inputs (obfuscated)
            CW_FORCEINLINE uint64_t execute(std::initializer_list<uint64_t> inputs) {
                // reset with obfuscation
                ctx = vm_context();
                ctx.set_ip(0);
                ctx.set_sp(0);

                // push inputs with obfuscation
                for(auto val : inputs) {
                    if(ctx.sp() < vm_state::polymorphic_stack::REAL_SIZE) {
                        ctx.push(val);
                        // add decoy value
                        ctx.stack.decoy_stack[CW_RAND(0, vm_state::polymorphic_stack::FAKE_SIZE-1)] = val ^ CW_RANDOM();
                    }
                }

                // randomized safety limit
                size_t max_instructions = 100000 + CW_RAND(0, 10000);
                size_t instruction_count = 0;

                // obfuscated execution loop
                while(instruction_count < max_instructions) {
                    if(!dispatch_morphed()) {
                        break;
                    }
                    instruction_count++;

                    // anti-analysis measures
                    if(instruction_count % 250 == 0) {
                        ctx.control.shadow_ip = ctx.control.real_ip.get() ^ CW_RANDOM();
                        ctx.control.fake_flags = ~ctx.control.flags.get();
                    }
                }

                // return result with obfuscation
                if(ctx.sp() > 0) {
                    volatile uint64_t decoy = ctx.stack.decoy_stack[0];
                    decoy = decoy * 2 + 1; // decoy operation
                    return ctx.stack.real_stack[ctx.sp() - 1].get();
                }
                return 0;
            }
        };

        // helper to create virtualized lambda functions
        template<typename Func>
        class virtualized_function {
        private:
            std::vector<uint8_t> bytecode;

        public:
            virtualized_function(std::vector<uint8_t>&& code)
                : bytecode(std::move(code)) {}

            template<typename... Args>
            CW_FORCEINLINE auto operator()(Args... args) {
                vm_interpreter vm(std::vector<uint8_t>(bytecode));
                return vm.execute({static_cast<uint64_t>(args)...});
            }
        };

        // builder pattern for creating virtualized code
        class virtualized_code {
        private:
            bytecode_builder builder;

        public:
            // arithmetic expression builders
            virtualized_code& compute_add(uint64_t a, uint64_t b) {
                builder.push_imm(a).push_imm(b).add();
                return *this;
            }

            virtualized_code& compute_mul(uint64_t a, uint64_t b) {
                builder.push_imm(a).push_imm(b).mul();
                return *this;
            }

            virtualized_code& compute_xor(uint64_t a, uint64_t b) {
                builder.push_imm(a).push_imm(b).xor_op();
                return *this;
            }

            // expression (a * b) + (c ^ d)
            virtualized_code& complex_expr(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
                builder.push_imm(a).push_imm(b).mul()
                       .push_imm(c).push_imm(d).xor_op()
                       .add();
                return *this;
            }

            // finalize and get executable
            virtualized_function<void> build() {
                return virtualized_function<void>(builder.finalize());
            }

            // execute immediately
            uint64_t execute() {
                vm_interpreter vm(builder.finalize());
                return vm.execute();
            }
        };
    }
#else
    // minimal stub when virtualization is disabled
    namespace virtualization {
        // provide empty stubs to prevent compilation errors
        struct bytecode_builder {
            bool has_halt = false;
            bytecode_builder& push_imm(uint64_t) { return *this; }
            bytecode_builder& add() { return *this; }
            bytecode_builder& sub() { return *this; }
            bytecode_builder& mul() { return *this; }
            bytecode_builder& xor_op() { return *this; }
            bytecode_builder& halt() { has_halt = true; return *this; }
            std::vector<uint8_t> finalize() { return {}; }
        };

        struct vm_interpreter {
            vm_interpreter(std::vector<uint8_t>&&) {}
            uint64_t execute() { return 0; }
        };

        struct virtualized_code {
            virtualized_code& compute_add(uint64_t, uint64_t) { return *this; }
            virtualized_code& compute_mul(uint64_t, uint64_t) { return *this; }
            uint64_t execute() { return 0; }
        };
    }
#endif

    // =================================================================
    // convenience macros
    // =================================================================

    // protect integer values
    #if CW_ENABLE_VALUE_OBFUSCATION
        #define CW_INT(x) (cloakwork::obfuscated_value<decltype(x)>{x})
    #else
        #define CW_INT(x) (x)
    #endif

    // protect function calls
    #if CW_ENABLE_FUNCTION_OBFUSCATION
        #define CW_CALL(func) cloakwork::obfuscated_call<decltype(func)>{func}
    #else
        #define CW_CALL(func) (func)
    #endif

    // scatter data in memory
    #if CW_ENABLE_DATA_HIDING
        #define CW_SCATTER(x) (cloakwork::data_hiding::scattered_value<decltype(x)>{x})
        #define CW_POLY(x) (cloakwork::data_hiding::polymorphic_value<decltype(x)>{x})
    #else
        #define CW_SCATTER(x) (x)
        #define CW_POLY(x) (x)
    #endif

    // check for analysis
    #if CW_ENABLE_ANTI_DEBUG
        #define CW_CHECK_ANALYSIS() \
            do { \
                if(cloakwork::anti_debug::is_debugger_present() || \
                   cloakwork::anti_debug::has_hardware_breakpoints()) { \
                    volatile int crash = *(int*)0; \
                } \
            } while(0)
    #else
        #define CW_CHECK_ANALYSIS() ((void)0)
    #endif

    // obfuscated branch
    #if CW_ENABLE_CONTROL_FLOW
        #define CW_BRANCH(cond) \
            if(cloakwork::control_flow::indirect_branch(cloakwork::control_flow::opaque_true<>() && (cond)))
    #else
        #define CW_BRANCH(cond) if(cond)
    #endif

    // virtualization macros
    #if CW_ENABLE_VIRTUALIZATION
        #define CW_VM_START() \
            cloakwork::virtualization::bytecode_builder _cw_vm_builder;

        #define CW_VM_PUSH(val) \
            _cw_vm_builder.push_imm(val);

        #define CW_VM_ADD() \
            _cw_vm_builder.add();

        #define CW_VM_SUB() \
            _cw_vm_builder.sub();

        #define CW_VM_MUL() \
            _cw_vm_builder.mul();

        #define CW_VM_XOR() \
            _cw_vm_builder.xor_op();

        #define CW_VM_EXECUTE() \
            ([&]() -> uint64_t { \
                /* finalize() will ensure HALT is added if not present */ \
                auto bytecode = _cw_vm_builder.finalize(); \
                cloakwork::virtualization::vm_interpreter vm(std::move(bytecode)); \
                uint64_t result = vm.execute(); \
                return result; \
            }())

        #define CW_VIRTUALIZE(expr) \
            ([&]() { \
                cloakwork::virtualization::virtualized_code vc; \
                return vc.expr.execute(); \
            }())

        #define CW_VM_FUNC(name, ...) \
            auto name = [&](__VA_ARGS__) { \
                cloakwork::virtualization::bytecode_builder builder; \
                /* user adds bytecode here - finalize() ensures HALT is added */ \
                return cloakwork::virtualization::virtualized_function<void>(builder.finalize()); \
            }
    #else
        // pass-through when virtualization is disabled
        #define CW_VM_START() ((void)0)
        #define CW_VM_PUSH(val) ((void)(val))
        #define CW_VM_ADD() ((void)0)
        #define CW_VM_SUB() ((void)0)
        #define CW_VM_MUL() ((void)0)
        #define CW_VM_XOR() ((void)0)
        #define CW_VM_EXECUTE() (0)
        #define CW_VIRTUALIZE(expr) (expr)
        #define CW_VM_FUNC(name, ...) ((void)0)
    #endif

} // namespace cloakwork

#ifdef _MSC_VER
    #pragma warning(pop)
#endif

#endif // CLOAKWORK_H