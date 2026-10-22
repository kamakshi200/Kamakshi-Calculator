# Kamakshi Joshi — All-in-One Smart Calculator

A single-window C++17 / Qt 6 Widgets desktop calculator. The main scientific calculator stays visible beside the feature tabs. The interface uses a vivid purple-blue-cyan theme and includes no puzzle feature.

## Features
- Scientific arithmetic: +, -, *, /, powers, parentheses, sqrt, sin/cos/tan (degrees), log, ln, pi and Ans
- Information storage-unit conversion: bit, byte, decimal KB/MB/GB/TB and binary KiB/MiB/GiB
- Bits / Nats / Decits information calculator: calculate per-event information content I(p) = -log_b(p) in bits, nats and decits. This tab does not calculate Shannon entropy.
- Binary, octal, decimal and hexadecimal conversion
- Efficiency percentage calculator
- Formula lab: rectangle, circle, triangle, simple interest, distance, BMI, Pythagorean theorem
- Currency converter for INR, USD, EUR, GBP, JPY, CAD and AUD with editable example rates (not live rates)

## Build
Requires CMake 3.21+, Qt 6 Widgets, and a C++17 compiler.
Open `CMakeLists.txt` in Qt Creator, select a compatible Qt kit, then Configure, Build, Run.

Or in a terminal configured for the matching compiler:
```bash
cmake -S . -B build
cmake --build build
```
On Windows, a missing `nmake` means the terminal doesn't have the MSVC build environment. Use Qt Creator with a configured kit or Developer PowerShell for Visual Studio. Don't mix MSVC and MinGW Qt kits.

## Notes
Currency rates are editable examples and are not live exchange rates. Trigonometric functions use degrees.
