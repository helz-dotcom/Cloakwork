# Cloakwork

**Cloakwork** is an advanced header-only C++20 obfuscation library providing comprehensive protections against static and dynamic analysis. It is highly configurable, extremely modular, and can be embedded directly with no separate compilation step needed. No dependencies required. This was a college project that spiraled into what it is now, so enjoy.

> Inspired by [obfusheader.h](https://github.com/ac3ss0r/obfusheader.h) and Zapcrash's nimrodhide.h

**Author:** helz.dev on Discord
**License:** MIT

***

## Features

- **Compile-time string encryption**
  - Encrypts string literals and decrypts on-the-fly at runtime.
  - Multi-layer encryption with polymorphic re-encryption.
  - Stack-based encrypted strings with automatic cleanup.
  - Wide string (wchar_t) encryption support.
- **Compile-time string hashing**
  - FNV-1a hash computed at compile-time for API name hiding.
  - Runtime hash functions for dynamic string comparison.
  - Case-insensitive hashing variants.
- **Integer/value obfuscation**
  - Protects sensitive values with random key-based encoding and mutation.
  - Mixed Boolean Arithmetic (MBA) obfuscation for arithmetic operations.
  - Obfuscated comparison operators (==, !=, <, >, <=, >=).
  - Encrypted compile-time constants.
- **Data hiding & scattering**
  - Splits and scrambles user data across memory or in polymorphic wrappers.
  - True heap-based data scattering for structure obfuscation.
- **Control flow obfuscation**
  - Opaque predicates using runtime values.
  - Control flow flattening via state machines.
  - Branch indirection and dead code insertion.
  - Junk code insertion macros.
- **Function pointer obfuscation**
  - Multi-layer pointer encryption with rotation and XOR.
  - Decoy pointer arrays to hide real function addresses.
  - Return address spoofing infrastructure.
- **Import hiding**
  - Dynamic API resolution without import table entries.
  - Module enumeration via PEB walking.
  - Export table parsing with hash-based lookup.
- **Direct syscalls**
  - Syscall number extraction from ntdll.
  - Bypass usermode hooks entirely.
- **Anti-debugging**
  - Multiple techniques including timing checks, PEB inspection, hardware breakpoint detection.
  - Parent process analysis and debugger window detection.
  - Anti-anti-debug plugin detection (ScyllaHide, TitanHide, etc.).
  - Kernel debugger detection and memory breakpoint detection.
- **Anti-VM/Sandbox detection**
  - Hypervisor detection via CPUID.
  - VM vendor string detection (VMware, VirtualBox, Hyper-V, etc.).
  - Low resource detection (sandbox environments).
  - Sandbox DLL and artifact detection.
  - VM-specific registry key and MAC address detection.
- **Code integrity verification**
  - Function hash computation for tamper detection.
  - Hook detection at function entry points.
  - Integrity-checked function wrappers.
- **Metamorphic code generation**
  - Self-mutating code and cross-variant function dispatching.
- **Compile-time randomization**
  - All transformations use compile-time random generation—no two builds are alike.
  - Runtime entropy combining multiple sources (RDTSC, ASLR, hardware RNG).
- **Full modular configuration**
  - Every feature is a toggle—disable heavy modules for performance or size.

***

## Quick Usage

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

// wide string encryption
const wchar_t* wide = CW_WSTR(L"wide string secret");
```

**String Hashing:**
```cpp
// compile-time hash (computed at build time)
constexpr uint32_t hash = CW_HASH("kernel32.dll");

// use for API hiding
void* k32 = cloakwork::imports::getModuleBase(CW_HASH("kernel32.dll"));
```

**Obfuscated Values:**
```cpp
// basic obfuscation
int key = CW_INT(0xDEADBEEF);

// MBA (mixed boolean arithmetic) obfuscation
auto mba_val = CW_MBA(42);

// encrypted compile-time constants
int magic = CW_CONST(0xCAFEBABE);

// obfuscated arithmetic operations
int sum = CW_ADD(x, y);
int diff = CW_SUB(x, y);
```

**Obfuscated Comparisons:**
```cpp
// hide what you're comparing
if (CW_EQ(password_hash, expected_hash)) {
    // authenticated
}

if (CW_LT(health, 0)) {
    // game over
}

// all comparison operators: CW_EQ, CW_NE, CW_LT, CW_GT, CW_LE, CW_GE
```

**Boolean Obfuscation:**
```cpp
// obfuscated true/false using opaque predicates
if (CW_TRUE) {
    // always executes, but looks complex in disassembly
}

// obfuscate any boolean expression
bool result = CW_BOOL(x > 0 && y < 100);
```

**Import Hiding:**
```cpp
// resolve APIs without import table
void* ntdll = cloakwork::imports::getModuleBase(CW_HASH("ntdll.dll"));
void* func = cloakwork::imports::getProcAddress(ntdll, CW_HASH("NtClose"));

// or use the macro
auto pVirtualAlloc = CW_IMPORT("kernel32.dll", VirtualAlloc);
```

**Direct Syscalls:**
```cpp
// get syscall number for direct invocation
uint32_t syscall_num = CW_SYSCALL_NUMBER(NtClose);
```

**Control Flow Obfuscation:**
```cpp
// obfuscated if/else with opaque predicates
CW_IF(is_authenticated)
    process_secure_data();
CW_ELSE
    handle_error();

// flatten control flow via state machine
auto safe_val = CW_FLATTEN([](int v) { return v * 2; }, user_val);

// insert junk code
CW_JUNK();
CW_JUNK_FLOW();
```

**Anti-Debug:**
```cpp
// comprehensive check (crashes if debugger detected)
CW_ANTI_DEBUG();

// analysis check with advanced techniques
CW_CHECK_ANALYSIS();

// inline check (scatter these throughout your code)
CW_INLINE_CHECK();
```

**Anti-VM/Sandbox:**
```cpp
// comprehensive check (crashes if VM/sandbox detected)
CW_ANTI_VM();

// or just check
if (CW_CHECK_VM()) {
    // running in VM/sandbox
}
```

**Integrity Verification:**
```cpp
// check if function is hooked
if (CW_DETECT_HOOK(VirtualAlloc)) {
    // function has been hooked!
}

// verify multiple functions
bool clean = cloakwork::integrity::verifyFunctions(&func1, &func2);
```

***

## Configuration

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
- `CW_ENABLE_IMPORT_HIDING` – Dynamic API resolution (default: 1)
- `CW_ENABLE_SYSCALLS` – Direct syscall support (default: 1)
- `CW_ENABLE_ANTI_VM` – Anti-VM/sandbox detection (default: 1)
- `CW_ENABLE_INTEGRITY_CHECKS` – Code integrity verification (default: 1)
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

## API Reference

### String Encryption

- `CW_STR(s)` – Compile-time encrypted string, decrypts at runtime
- `CW_STR_LAYERED(s)` – Multi-layer encrypted string with polymorphic re-encryption
- `CW_STR_STACK(s)` – Stack-based encrypted string with auto-cleanup on scope exit
- `CW_WSTR(s)` – Wide string (wchar_t) encryption

### String Hashing

- `CW_HASH(s)` – Compile-time FNV-1a hash of string (case-sensitive, for function names)
- `CW_HASH_CI(s)` – Compile-time case-insensitive hash (for module names)
- `CW_HASH_WIDE(s)` – Compile-time hash of wide string
- `cloakwork::hash::fnv1a_runtime(str)` – Runtime hash of string
- `cloakwork::hash::fnv1a_runtime_ci(str)` – Case-insensitive runtime hash

### Value Obfuscation

- `CW_INT(x)` – Obfuscated integer/numeric value
- `CW_MBA(x)` – MBA (Mixed Boolean Arithmetic) obfuscated value
- `CW_CONST(x)` – Encrypted compile-time constant
- `CW_ADD(a, b)` – Obfuscated addition using MBA
- `CW_SUB(a, b)` – Obfuscated subtraction using MBA
- `CW_AND(a, b)` – Obfuscated bitwise AND using MBA
- `CW_OR(a, b)` – Obfuscated bitwise OR using MBA

### Obfuscated Comparisons

- `CW_EQ(a, b)` – Obfuscated equality (a == b)
- `CW_NE(a, b)` – Obfuscated not-equals (a != b)
- `CW_LT(a, b)` – Obfuscated less-than (a < b)
- `CW_GT(a, b)` – Obfuscated greater-than (a > b)
- `CW_LE(a, b)` – Obfuscated less-or-equal (a <= b)
- `CW_GE(a, b)` – Obfuscated greater-or-equal (a >= b)

### Boolean Obfuscation

- `CW_TRUE` – Obfuscated true using opaque predicates
- `CW_FALSE` – Obfuscated false using opaque predicates
- `CW_BOOL(expr)` – Obfuscates any boolean expression

### Data Hiding

- `CW_SCATTER(x)` – Scatters data across heap allocations
- `CW_POLY(x)` – Polymorphic value that mutates internally

### Control Flow

- `CW_IF(expr)` – Obfuscated if with opaque predicates
- `CW_ELSE` – Obfuscated else clause
- `CW_BRANCH(cond)` – Indirect branching with obfuscation
- `CW_FLATTEN(func, ...)` – Flattens control flow via state machine
- `CW_JUNK()` – Insert junk computation
- `CW_JUNK_FLOW()` – Insert junk with fake control flow

### Function Protection

- `CW_CALL(func)` – Obfuscates function pointer with multi-layer encryption
- `CW_SPOOF_CALL(func)` – Call with spoofed return address

### Import Hiding

- `CW_IMPORT(mod, func)` – Resolve function without import table
- `cloakwork::imports::getModuleBase(hash)` – Get module base by hash
- `cloakwork::imports::getProcAddress(mod, hash)` – Get function by hash

### Direct Syscalls

- `CW_SYSCALL_NUMBER(func)` – Get syscall number for ntdll function
- `cloakwork::syscall::getSyscallNumber(hash)` – Get syscall by function hash

### Anti-Debugging

- `CW_ANTI_DEBUG()` – Crashes if debugger detected
- `CW_CHECK_ANALYSIS()` – Advanced anti-analysis check
- `CW_INLINE_CHECK()` – Inline anti-debug check
- `cloakwork::anti_debug::is_debugger_present()` – Basic debugger detection
- `cloakwork::anti_debug::comprehensive_check()` – Multi-layer detection

### Anti-VM/Sandbox

- `CW_ANTI_VM()` – Crashes if VM/sandbox detected
- `CW_CHECK_VM()` – Returns true if VM/sandbox detected
- `cloakwork::anti_debug::anti_vm::comprehensive_check()` – Full VM/sandbox detection
- `cloakwork::anti_debug::anti_vm::is_hypervisor_present()` – Hypervisor detection
- `cloakwork::anti_debug::anti_vm::detect_vm_vendor()` – VM vendor detection
- `cloakwork::anti_debug::anti_vm::detect_sandbox_dlls()` – Sandbox DLL detection

### Integrity Verification

- `CW_DETECT_HOOK(func)` – Check if function is hooked
- `CW_INTEGRITY_CHECK(func, size)` – Wrap function with integrity checking
- `cloakwork::integrity::computeHash(data, size)` – Compute hash of memory
- `cloakwork::integrity::detectHook(func)` – Check for hook patterns
- `cloakwork::integrity::verifyFunctions(...)` – Verify multiple functions

### Random Number Generation

- `CW_RANDOM_CT()` – Compile-time random value (unique per build)
- `CW_RAND_CT(min, max)` – Compile-time random in range
- `CW_RANDOM_RT()` – Runtime random value (unique per execution)
- `CW_RAND_RT(min, max)` – Runtime random in range

### Template Classes

- `cloakwork::obfuscated_value<T>` – Generic value obfuscation
- `cloakwork::mba_obfuscated<T>` – MBA-based obfuscation
- `cloakwork::bool_obfuscation::obfuscated_bool` – Multi-byte boolean storage
- `cloakwork::data_hiding::scattered_value<T, Chunks>` – Data scattering
- `cloakwork::data_hiding::polymorphic_value<T>` – Polymorphic value
- `cloakwork::obfuscated_call<Func>` – Function pointer obfuscation
- `cloakwork::metamorphic::metamorphic_function<Func>` – Metamorphic wrapper
- `cloakwork::constants::runtime_constant<T>` – Runtime-keyed constant
- `cloakwork::integrity::integrity_checked<Func>` – Integrity-checked function

***

## Advanced Integration

All features are **header-only** and are **Windows-focused** (with advanced anti-debug using Win32 APIs). C++20 or above required.

- Deep integration possible with scatter/polymorphic wrappers for sensitive data structures.
- Metamorphic function patterns confuse code flow analysis.
- Import hiding removes sensitive APIs from import table, resolving at runtime via PEB walking.
- Direct syscalls bypass usermode hooks entirely.
- Anti-debug techniques include:
  - PEB inspection (BeingDebugged flag)
  - Hardware breakpoint detection via debug registers
  - Timing analysis (RDTSC vs QueryPerformanceCounter)
  - Parent process analysis
  - Debugger window class detection
  - Anti-anti-debug plugin detection (ScyllaHide, TitanHide, HyperHide)
  - Kernel debugger detection
  - Memory breakpoint (PAGE_GUARD) detection
- Anti-VM techniques include:
  - Hypervisor bit detection via CPUID
  - VM vendor string matching
  - Low resource detection (CPU count, RAM, disk size)
  - VM-specific registry keys
  - VM MAC address prefix detection
  - Sandbox DLL detection
- Control flow flattening uses runtime-keyed state machines to frustrate static analysis.
- String encryption uses multi-layer XOR with position-dependent keys and optional polymorphic re-encryption.

***

## Credits

- Inspired by legendary tools: obfusheader.h, nimrodhide.h, and the anti-re tools of unknowncheats.
- Created by helz.dev/Helzky / Discord: `helz.dev`
- Open for contributions and issues!

***

## License

MIT License – do what you want, no warranty.

***

**Cloakwork: Ultra-obfuscated, ultra-useful... Happy hiding!**

---
