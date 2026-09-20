## The binary hardening options

The template hardens every binary it produces, so nothing has to be enabled for that. The options follow the [Compiler Options Hardening Guide for C and C++](https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html) of the OpenSSF and live in the modules of the [cmake/compile-options/hardening](/cmake/compile-options/hardening) directory, which append them to the `EXTRA_COMPILE_OPTIONS` and the `EXTRA_LINK_OPTIONS` variables the [src/CMakeLists.txt](/src/CMakeLists.txt) hands over to the `add_compile_options` and the `add_link_options` commands. Both variables are printed by a configure run, so the options the build has taken need no digging through its command lines:

```
-- COMPILE OPTIONS: -Wall;-Wextra;...;-fstack-protector-all;...
-- LINK OPTIONS: -Wl,-z,relro;-Wl,-z,now;-Wl,-z,noexecstack;...
```

### The GCC and the clang compile time options

| Option | What it does |
| --- | --- |
| `-fstack-protector-all` | places a canary into the frame of every function, not of the ones holding an array only, so a stack buffer overflow is caught before the overwritten return address is used |
| `-fstack-clash-protection` | every stack allocation touches its guard page, so a huge local variable can not jump over it into another mapping |
| `-fcf-protection=full` | the indirect branch tracking and the shadow stack of the x86 control flow enforcement technology |
| `-mbranch-protection=standard` | the AArch64 counterpart: the branch target identification and the return address signing |
| `-fzero-call-used-regs=used-gpr` | wipes the used general purpose registers on return, which shortens the gadgets a return oriented attack chains |
| `-fstrict-flex-arrays=3` | only a trailing `[]` member is a flexible array, so the `[0]` and the `[1]` ones keep their size known to the bounds checks |
| `-fno-delete-null-pointer-checks` | the null pointer checks of the code survive the optimization |
| `-fno-strict-overflow` | the signed overflow wraps instead of being an undefined behaviour the optimizer exploits by dropping the overflow checks |
| `-fno-common` | a variable defined twice becomes a link time error instead of a silently shared memory |
| `-D_GLIBCXX_ASSERTIONS` | turns on the precondition checks of the libstdc++ containers and iterators, the `operator[]` bounds among them |
| `-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3` | the buffer overflow checks of the C library calls; the undefinition goes first, since a distribution which fortifies by default would report a macro redefinition |
| `-ftrivial-auto-var-init=zero` | the automatic variables start zeroed, so a missed initialization reads no leftover of an old stack content |

The `-fPIE` and the `-fPIC` compile time counterparts of the `-pie` linker option below come from the `CMAKE_POSITION_INDEPENDENT_CODE` variable of the [template-project-compile-options](/cmake/compile-options/template-project-compile-options.cmake) module. The [GCC instrumentation options](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html) documentation describes the options themselves in detail.

### The GCC and the clang link time options

| Option | What it does |
| --- | --- |
| `-Wl,-z,relro` | the relocations become read only once the dynamic linker has resolved them |
| `-Wl,-z,now` | every symbol is resolved at the start up, which the option above needs to cover the global offset table too (the full RELRO) |
| `-Wl,-z,noexecstack` | marks the stack memory as a non executable one |
| `-Wl,-z,separate-code` | the code and the data never share a memory page, so a data page holds no executable leftovers |
| `-pie` | a position independent executable, which lets the address space layout randomization move the code of the binary itself |

The `-pie` one is given to the executables only, because the linker rejects it together with the `-shared` of a shared library. The [GNU ld options](https://sourceware.org/binutils/docs/ld/Options.html) documentation describes the rest of them.

### The MS Windows (MSVC) options

| Option | What it does |
| --- | --- |
| `/GS` | the buffer security check: a cookie guards the return address of a function holding a buffer |
| `/guard:cf` | the control flow guard: an indirect call is checked against the table of the valid targets |
| `/Qspectre` | the mitigation of the CVE-2017-5753 class of the speculative execution attacks |
| `/GUARD:CF` | the linker counterpart of the `/guard:cf` one |
| `/DYNAMICBASE` | the image is relocatable, so the address space layout randomization moves it |
| `/NXCOMPAT` | the data execution prevention is on |
| `/HIGHENTROPYVA` | the 64 bit address space randomization of the image |
| `/CETCOMPAT` | marks the image as a shadow stack compatible one |

The [MSVC compiler options](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170) and the [MSVC linker options](https://learn.microsoft.com/en-us/cpp/build/reference/linker-options?view=msvc-170) documentation describes them in detail. The MSVC toolchain only warns about an option it does not know (the `D9002` and the `LNK4044` warnings), so an older or a non x86 toolchain drops what it misses instead of failing the build.

### The unsupported options are dropped

The GCC and the clang toolchains reject an option they do not know, and the hardening ones are the compiler version, the linker and the target CPU specific ones: the `-fcf-protection=full` belongs to the x86 CPUs, the `-mbranch-protection=standard` to the AArch64 ones, and the `-Wl,-z,*` family to the ELF linkers. So every option of the tables above is probed by a compile and link of a tiny source before the use, and the rejected one is dropped instead of breaking the build. The `template_project_check_supported_options` and the `template_project_append_supported_option` functions of the [cmake/tools/template-project-supported-options-function.cmake](/cmake/tools/template-project-supported-options-function.cmake) module perform the probe, and a configure run reports each one:

```
-- Performing Test TEMPLATE_PROJECT_ACCEPTS__fcf_protection_full - Success
-- Performing Test TEMPLATE_PROJECT_ACCEPTS__mbranch_protection_standard - Failed
```

### The debug build keeps its diagnostics

The `-D_FORTIFY_SOURCE` and the `-ftrivial-auto-var-init=zero` options are given to the `Release`, the `RelWithDebInfo` and the `MinSizeRel` configurations only. The C library ignores the first one without an optimization anyway, while the second one would hide the uninitialized reads from the valgrind and the sanitizers the debug build runs.

The sanitizers build lowers the control flow protection and turns the stack clash one off on purpose, so the `-fcf-protection=full` and the `-fstack-clash-protection` options stay away from it and its code generation choices remain its own.

### Examining the result

The `readelf` of the binutils tells what the produced binary has got. With the `BINARY` variable holding its path (`build/src/CppAppTemplate` of a default build tree):

```
# a position independent executable: Type: DYN
readelf -hW "$BINARY" | grep Type

# the full RELRO: both the GNU_RELRO segment and the BIND_NOW flag
readelf -lW "$BINARY" | grep GNU_RELRO
readelf -dW "$BINARY" | grep BIND_NOW

# the non executable stack: the RW and not the RWE flags of the GNU_STACK
readelf -lW "$BINARY" | grep -A1 GNU_STACK

# the control flow enforcement: the IBT and the SHSTK x86 features
readelf -nW "$BINARY" | grep "x86 feature"
```
