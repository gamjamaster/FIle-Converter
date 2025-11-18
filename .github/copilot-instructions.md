# GitHub Copilot Instructions

## Language Preference
- All responses from GitHub Copilot should be provided in **Korean (ÇÑ±¹¾î)**.
- Code comments should be in Korean when explaining functionality.
- Error messages and explanations should be in Korean.
- Documentation and README files should be in Korean.

## Project-Specific Guidelines
- This is a C++ project using C++14 standard
- Uses wxWidgets for GUI
- Embeds Python 3.13 for PowerPoint to PDF conversion
- Always check for null pointers when using Python C API
- Always use proper reference counting with `Py_INCREF` and `Py_DECREF`
- Follow RAII principles where possible

## Coding Standards
- Use clear variable names in English (code itself)
- Add Korean comments for complex logic
- Always handle errors gracefully
- Memory management is critical - no leaks allowed
