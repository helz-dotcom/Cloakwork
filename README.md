# Cloakwork

**Cloakwork** is an advanced header-only C++20 obfuscation library providing comprehensive protections against static and dynamic analysis. It is highly configurable, extremely modular, and can be embedded directly with no separate compilation step needed. No dependencies required. This was a college project that spiraled into what it is now, so enjoy.

> Inspired by [obfusheader.h](https://github.com/ac3ss0r/obfusheader.h) and Zapcrash's nimrodhide.h

**Author:** helz.dev on Discord
**License:** MIT

***

## ✨ Features

- **Compile-time string encryption**
  - Encrypts string literals and decrypts on-the-fly at runtime.
  - Multi-layer encryption with polymorphic re-encryption.
  - Stack-based encrypted strings with automatic cleanup.
- **Integer/value obfuscation**
  - Protects sensitive values with random key-based encoding and mutation.
  - Mixed Boolean Arithmetic (MBA) obfuscation for arithmetic operations.
- **Data hiding & scattering**
  - Splits and scrambles user data across memory or in polymorphic wrappers.
  - True heap-based data scattering for structure obfuscation.
- **Control flow obfuscation**
  - Opaque predicates using runtime values.
  - Control flow flattening via state machines.
  - Branch indirection and dead code insertion.
- **Function pointer obfuscation**
  - Multi-layer pointer encryption with rotation and XOR.
  - Decoy pointer arrays to hide real function addresses.
- **Anti-debugging**
  - Multiple techniques including timing checks, PEB inspection, hardware breakpoint detection.
  - Parent process analysis and debugger window detection.
  - Anti-anti-debug plugin detection (ScyllaHide, TitanHide, etc.).
  - Kernel debugger detection and memory breakpoint detection.
- **Metamorphic code generation**
  - Self-mutating code and cross-variant function dispatching.
- **Compile-time randomization**
  - All transformations use compile-time random generation—no two builds are alike.
  - Runtime entropy combining multiple sources (RDTSC, ASLR, hardware RNG).
- **Full modular configuration**
  - Every feature is a toggle—disable heavy modules for performance or size.

***

## ⚡ Quick Usage

Add to your project (no build step needed):

```cpp
#include "cloakwork.h"
```

**String Encryption:**
```cpp
const char* msg = CW_STR("secret message");
// automatically decrypted at runtime only

// multi-layer encryption with polymorphic re-encryption
const char* secure = CW_STR_LAYERED("ultra secret");

// stack-based with auto-cleanup on scope exit
auto stack_str = CW_STR_STACK("temporary secret");
```

**Obfuscated Values:**
```cpp
// basic obfuscation
int key = CW_INT(0xDEADBEEF);

// MBA (mixed boolean arithmetic) obfuscation
auto mba_val = CW_MBA(42);

// obfuscated arithmetic operations
int sum = CW_ADD(x, y);
int diff = CW_SUB(x, y);
int and_result = CW_AND(a, b);
int or_result = CW_OR(a, b);
```

**Data Hiding:**
```cpp
// scatter data across heap allocations
auto hidden = CW_SCATTER(myStructInstance);

// polymorphic value that mutates internally
auto poly = CW_POLY(100);
```

**Control Flow Obfuscation:**
```cpp
// obfuscated if/else with opaque predicates
CW_IF(is_authenticated)
    process_secure_data();
CW_CHECK_ANALYSIS() // crashes if being debugged
CW_ELSE
    handle_error();

// flatten control flow via state machine
auto safe_val = CW_FLATTEN([](int v) { return v * 2; }, user_val);

// indirect branching
CW_BRANCH(isValid)
    do_something();
```

**Function Call Protection:**
```cpp
auto obf_func = CW_CALL(&myFunction);
obf_func(arg1, arg2); // calls through obfuscated pointer
```

**Anti-Debug:**
```cpp
// comprehensive check (crashes if debugger detected)
CW_ANTI_DEBUG();

// analysis check with advanced techniques
CW_CHECK_ANALYSIS();

// inline check (scatter these throughout your code)
CW_INLINE_CHECK();

// manual checking
if (cloakwork::anti_debug::is_debugger_present()) {
    // handle debugger
}

if (cloakwork::anti_debug::comprehensive_check()) {
    // advanced checks detected something
}
```

**Random Number Generation:**
```cpp
// compile-time random (unique per build)
constexpr auto ct_rand = CW_RANDOM_CT();
constexpr int ct_range = CW_RAND_CT(1, 100);

// runtime random (unique per execution)
uint64_t rt_rand = CW_RANDOM_RT();
int rt_range = CW_RAND_RT(1, 100);
```

***

## 🛠️ Configuration

Tweak features by defining feature macros **before** including the header:

```cpp
#define CW_ENABLE_METAMORPHIC 0
#define CW_ENABLE_STRING_ENCRYPTION 1
#include "cloakwork.h"
```

### Configuration Options

- `CW_ENABLE_ALL` – Master on/off switch (default: 1)
- `CW_ENABLE_STRING_ENCRYPTION` – String encryption (default: 1)
- `CW_ENABLE_VALUE_OBFUSCATION` – Integer/value obfuscation (default: 1)
- `CW_ENABLE_CONTROL_FLOW` – Control flow obfuscation (default: 1)
- `CW_ENABLE_ANTI_DEBUG` – Anti-debugging features (default: 1)
- `CW_ENABLE_FUNCTION_OBFUSCATION` – Function pointer obfuscation (default: 1)
- `CW_ENABLE_DATA_HIDING` – Data scattering/polymorphic values (default: 1)
- `CW_ENABLE_METAMORPHIC` – Metamorphic code generation (default: 1)
- `CW_ENABLE_COMPILE_TIME_RANDOM` – Compile-time randomization (default: 1)
- `CW_ANTI_DEBUG_RESPONSE` – Response to debugger detection: 0=ignore, 1=crash, 2=fake data (default: 1)

All features are **enabled by default**. For minimal configuration:

```cpp
#define CW_ENABLE_ALL 0                      // disable everything first
#define CW_ENABLE_STRING_ENCRYPTION 1        // enable only what you need
#define CW_ENABLE_VALUE_OBFUSCATION 1
#include "cloakwork.h"
```

Performance-focused configuration:

```cpp
#define CW_ENABLE_METAMORPHIC 0              // disable heavy features
#define CW_ENABLE_CONTROL_FLOW 0
#include "cloakwork.h"
```

***

## 📚 API Reference

### String Encryption

- `CW_STR(s)` – Compile-time encrypted string, decrypts at runtime
- `CW_STR_LAYERED(s)` – Multi-layer encrypted string with polymorphic re-encryption
- `CW_STR_STACK(s)` – Stack-based encrypted string with auto-cleanup on scope exit

### Value Obfuscation

- `CW_INT(x)` – Obfuscated integer/numeric value
- `CW_MBA(x)` – MBA (Mixed Boolean Arithmetic) obfuscated value
- `CW_ADD(a, b)` – Obfuscated addition using MBA
- `CW_SUB(a, b)` – Obfuscated subtraction using MBA
- `CW_AND(a, b)` – Obfuscated bitwise AND using MBA
- `CW_OR(a, b)` – Obfuscated bitwise OR using MBA

### Data Hiding

- `CW_SCATTER(x)` – Scatters data across heap allocations
- `CW_POLY(x)` – Polymorphic value that mutates representation internally

### Control Flow

- `CW_IF(expr)` – Obfuscated if with opaque predicates
- `CW_ELSE` – Obfuscated else clause
- `CW_BRANCH(cond)` – Indirect branching with obfuscation
- `CW_FLATTEN(func, ...)` – Flattens control flow via state machine

### Function Protection

- `CW_CALL(func)` – Obfuscates function pointer with multi-layer encryption

### Anti-Debugging

- `CW_ANTI_DEBUG()` – Crashes if debugger detected (comprehensive checks)
- `CW_CHECK_ANALYSIS()` – Advanced anti-analysis check
- `CW_INLINE_CHECK()` – Inline anti-debug check (scatter throughout code)
- `cloakwork::anti_debug::is_debugger_present()` – Returns true if debugger detected
- `cloakwork::anti_debug::comprehensive_check()` – Advanced multi-layer detection
- `cloakwork::anti_debug::timing_check(func)` – Timing-based debugger detection

### Random Number Generation

- `CW_RANDOM_CT()` – Compile-time random value (unique per build)
- `CW_RAND_CT(min, max)` – Compile-time random in range
- `CW_RANDOM_RT()` – Runtime random value (unique per execution)
- `CW_RAND_RT(min, max)` – Runtime random in range

### Template Classes

- `cloakwork::obfuscated_value<T>` – Generic value obfuscation
- `cloakwork::mba_obfuscated<T>` – MBA-based obfuscation
- `cloakwork::data_hiding::scattered_value<T, Chunks>` – Data scattering
- `cloakwork::data_hiding::polymorphic_value<T>` – Polymorphic value
- `cloakwork::obfuscated_call<Func>` – Function pointer obfuscation
- `cloakwork::metamorphic::metamorphic_function<Func>` – Metamorphic function wrapper

***

## 💡 Advanced Integration

All features are **header-only** and are **Windows-focused** (with advanced anti-debug using Win32 APIs). C++20 or above required.

- Deep integration possible with scatter/polymorphic wrappers for sensitive data structures.
- Metamorphic function patterns confuse code flow analysis.
- Anti-debug techniques include:
  - PEB inspection (BeingDebugged flag)
  - Hardware breakpoint detection via debug registers
  - Timing analysis (RDTSC vs QueryPerformanceCounter)
  - Parent process analysis
  - Debugger window class detection
  - Anti-anti-debug plugin detection (ScyllaHide, TitanHide, HyperHide)
  - Kernel debugger detection
  - Memory breakpoint (PAGE_GUARD) detection
- Control flow flattening uses runtime-keyed state machines to frustrate static analysis.
- String encryption uses multi-layer XOR with position-dependent keys and optional polymorphic re-encryption.

***

## 🪪 Credits

- Inspired by legendary tools: obfusheader.h, nimrodhide.h, and the anti-re tools of unknowncheats.
- Created by helz.dev/Helzky / Discord: `helz.dev`
- Open for contributions and issues!

***

## ⚖️ License

MIT License – do what you want, no warranty.

***

**Cloakwork: Ultra-obfuscated, ultra-useful… Happy hiding!**

---
