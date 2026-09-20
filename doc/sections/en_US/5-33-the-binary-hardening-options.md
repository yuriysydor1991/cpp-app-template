## The binary hardening options

The template hardens every binary it produces, so nothing has to be enabled for that. The options follow the [Compiler Options Hardening Guide for C and C++](https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html) of the OpenSSF and live in the [meson/template-project-hardening/meson.build](/meson/template-project-hardening/meson.build) module, which hands them over to the `add_project_arguments` and the `add_project_link_arguments` commands, so every target of the project takes them.

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

The [GCC instrumentation options](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html) documentation describes the options themselves in detail.

### The GCC and the clang link time options

| Option | What it does |
| --- | --- |
| `-Wl,-z,relro` | the relocations become read only once the dynamic linker has resolved them |
| `-Wl,-z,now` | every symbol is resolved at the start up, which the option above needs to cover the global offset table too (the full RELRO) |
| `-Wl,-z,noexecstack` | marks the stack memory as a non executable one |
| `-Wl,-z,separate-code` | the code and the data never share a memory page, so a data page holds no executable leftovers |

The position independent executable comes from the `b_pie` base option the `project()` call of the [meson.build](/meson.build) keeps at `true`: Meson gives the `-fPIE` and the `-pie` of it to the executables and keeps the `-fPIC` of the libraries, so the address space layout randomization moves the code of the binary itself. The [GNU ld options](https://sourceware.org/binutils/docs/ld/Options.html) documentation describes the rest of them.

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

The module takes them when the `cpp.get_argument_syntax()` reports the `msvc` one. The [MSVC compiler options](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170) and the [MSVC linker options](https://learn.microsoft.com/en-us/cpp/build/reference/linker-options?view=msvc-170) documentation describes them in detail.

### The unsupported options are dropped

The hardening options are the compiler version, the linker and the target CPU specific ones: the `-fcf-protection=full` belongs to the x86 CPUs, the `-mbranch-protection=standard` to the AArch64 ones, and the `-Wl,-z,*` family to the ELF linkers. So the module passes every option of the tables above through the `cpp.get_supported_arguments()` and the `cpp.get_supported_link_arguments()` probes, and the rejected one is dropped instead of breaking the build. A `meson setup` run reports each one:

```
Compiler for C++ supports arguments -fcf-protection=full: YES
Compiler for C++ supports arguments -mbranch-protection=standard: NO
Compiler for C++ supports link arguments -Wl,-z,noexecstack: YES
```

### The debug build keeps its diagnostics

The `-D_FORTIFY_SOURCE` and the `-ftrivial-auto-var-init=zero` options are given to the `1`, the `2`, the `3` and the `s` optimization levels only, which the `release`, the `debugoptimized` and the `minsize` build types take. The C library ignores the first one without an optimization anyway, while the second one would hide the uninitialized reads from the valgrind and the sanitizers the debug build runs.

The level 3 of the `_FORTIFY_SOURCE` needs the dynamic object size builtins of the GCC 12 / clang 9, so the module probes it by a compile and drops to the level 2 with an older compiler:

```
Checking if "the _FORTIFY_SOURCE level 3" compiles: YES
```

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
