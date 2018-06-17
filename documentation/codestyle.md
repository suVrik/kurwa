# Line length
Write your code to fit within 120 columns of text. 80 is not enough for good looking code, 120 is good for 2 side by side editors on Full HD monitor.

# Whitespace
No tabs. No whitespace at the end of a line.

Unix-style linebreaks ('\n'), not Windows-style ('\r\n').

Four spaces per logic level.

# Control structures
Use [K&R bracing style](https://en.wikipedia.org/wiki/Indentation_style#K&R): left brace at end of first line, 'cuddled' else on both sides.

Always brace controlled statements, even a single-line consequent of if else else. This is redundant, typically, but it avoids dangling else bugs, so it's safer at scale than fine-tuning.

```
int32 foo(int32 boo) {
    if (boo == 0) {
        return 1;
    }
    return 0;
}
```

# Line breaking
Each statement should get its own line.

```
x++;
y++;
if (condition) {
    doIt();
}
```

# Naming

[Snake case](https://ru.wikipedia.org/wiki/Snake_case) for variables, functions and namespaces.

```
int32 my_variable;
String another_variable;
```

[Camel case](https://ru.wikipedia.org/wiki/CamelCase) with an initial capital letter for classes, enums, unions and structures.

```
namespace kw {

class MyClass {
    public:
        int32 member_variable;
    private:
        String m_private_member;
};

struct MyStructure {
    int32 variable;
}

} // namespace kw
```

Macroses, constexpr variables, static const variables, enum and enum class values must use all uppercase names with words separated by underscores.

```
constexpr int32 STYLES_COUNT = 16;

enum class Player {
    RED,
    GREEN,
    BLUE,
    BLACK
};
```

Private members must have prefix `m_`.

```
class MyClass {
    private:
        int32 m_capacity;
        float m_weight;
}
```

Use full words, except in the rare case where an abbreviation would be more canonical and easier to understand.

```
size_t characterSize;
size_t length;
int64 tabIndex; // more canonical than 'tabulation'
```

Precede boolean values and getters with words like `is_` and `did_`.

```
bool is_valid;
bool did_send_data;
bool is_initialized() const;
```

Precede setters with the word `set_` and getters with the word `get_`.

```
void set_width(float width);
int32 get_size() const;
int16 get_port() const;
```

Use descriptive verbs in function names.

```
bool convertToASCII(int16*, size_t);
```

Prefer enums to bools on function parameters if callers are likely to be passing constants, since named constants are easier to read at the call site. An exception to this rule is a setter function, where the name of the function already makes clear what the boolean is.

```
do_something(something, ALLOW_FOO_BAR);
paint_text_with_shadows(context, ..., textStrokeWidth > 0, is_horizontal());
set_resizable(false);
```

Use `#pragma once` instead of `#define` and `#ifdef` for header guards.

```
#pragma once

int8 whatever_you_want();
```

# Other Punctuation

Constructors for C++ classes should initialize all of their members using C++ initializer syntax. Each member (and superclass) should be indented on a separate line, with the colon or comma preceding the member on that line.

```
namespace kw {

MyClass::MyClass(Document* document)
    : MySuperClass()
    , m_my_member(0)
    , m_document(document) {
}

MyOtherClass::MyOtherClass()
    : MySuperClass() {
}

} // namespace kw
```

Prefer range-based loops to indices or iterators.

```
for (auto& it : m_windows) {
    it->update();
}
```

# Pointers and References

Both pointer types and reference types should be written with no space between the type name and the `*` or `&`.

```
const char* name = "Jhonny";
const int16& ref = original;
```

An out argument of a function should be passed by reference except rare cases where it is optional in which case it should be passed by pointer.

```

```

# C++ namespaces
Write all the engine related stuff in `kw` namespace. Some details might be written in nested namespaces with postfix `_details`. Namespace's contents are written without an indent. The closing brace must have a comment that identifies a namespace it's related to.

```
namespace kw {

class MyClass {
    public:
        int32 member_variable;
    private:
        String m_private_member;
};

struct MyStructure {
    int32 variable;
}

} // namespace kw
```

# C++ classes
Access modifiers must be indented.
```
namespace kw {

class MyClass : public A {
    ...
}

class MyClass : public X, public Y {
    public:

        // Special member functions, like constructors, that have default bodies
        // should use '= default' annotation instead.
        MyClass() = default;

        // Unless it's a copy or move constructor or you have a specific reason to allow
        // implicit conversions, mark all single-argument constructors explicit.
        explicit MyClass(OtherClass arg);

        // This constructor can also take a single argument, so it also needs to be marked explicit.
        // Always split definition and declaration. Never put definition and declaration in the same file.
        explicit MyClass(OtherClass arg, AnotherClass arg2 = AnotherClass());
    protected:
    private:
        int m_variable;
}

} // namespace kw

#include "my_class_impl.h"
```
Define classes using the style given above.

Class names and structure names should be capitalized and use camelCase

# Comments:
Documentation is written like this:
```
/**
 * Commentary
 */
```
Do not write any `\returns`, `\arg` and other doxygen stuff, because it simply takes a lot of time to make it look consistent and most of time it is completely unnecessary. Write documentation for all the public classes, methods and variables.

Comments in private scope, *.cpp or *_impl.h files is written like this:
```
// Commentary
```

Task that need to be done is written with "TODO:" prefix and, optionally, an issue number postfix:
```
// TODO: task that must be done in the future (#1337)
```

Same idea for bugs/potential bugs that need to be fixed:
```
// FIXME: something bad happens here (#1489)
```

# Includes

Includes follow this order:

1) Project/Module related includes first.
2) Thirdparties and system libraries at the end.

Sorted alphabetically in each block.

```
#include "kw/core/vector.h"
#include "kw/render/texture.h"

#include <SDL_events.h>
#include <imgui.h>
```

# nullptr and comparison with 0

Use nullptr instead of 0 or NULL for pointers. When comparing pointer types with nullptr, always show it explicitly.

```
int* a = nullptr;
// ...
KW_ASSERT(a == nullptr);
```

The same rule applies to numbers, show you're comparing a number with zero explicitly.

```
int a = 0;
// ...
if (a == 0) {
    a++;
}
```

You can omit the comparison for boolean type.

```
bool a = 0;
// ...
if (a) {
    trace("Hello, world!");
}
```

# Floating-point numbers

Always write postfix for floating-point numbers to prevent errors.

```
float a = 10.f;
double b = 15.0;
```

# C++17

Try to use raw pointers as less as possible. Use UniquePtr and SharedPtr instead. 

```
UniquePtr<Game> game;
```

To receive or return objects that might be not initialized use Optional.

```
Optional<String> get_name();
```

If function returns multiple results, do not put them as arguments, use tuple or pair instead and receive them by structured binding declarations.

```
auto [is_succeed, exit_code] = get_result();
```

