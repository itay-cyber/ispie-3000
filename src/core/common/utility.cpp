/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/common/utility.h>

namespace ISpieCore
{
    namespace Common
    {
#ifdef _WIN32
        std::string wstring_to_string(const std::basic_string<TCHAR> &input)
        {
#ifdef _UNICODE
            // Unicode build: input is std::wstring (wide), convert to UTF-8 std::string
            if (input.empty())
                return {};

            int sizeNeeded = WideCharToMultiByte(
                CP_UTF8,
                0,
                input.c_str(),
                -1,
                nullptr,
                0,
                nullptr,
                nullptr);

            std::string result(sizeNeeded - 1, '\0');

            WideCharToMultiByte(
                CP_UTF8,
                0,
                input.c_str(),
                -1,
                result.data(),
                sizeNeeded,
                nullptr,
                nullptr);

            return result;
#else
            // ANSI build: input is already std::string (narrow), no conversion needed
            return std::string(input.begin(), input.end());
#endif
        }
#endif

    }
}