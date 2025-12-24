#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <memory>
#include <string>
#include <unordered_map>
#include <core/interfaces/wisp_if.h>

namespace ISpieCore
{
    namespace Interfaces
    {
        class IWispSnapshot
        {
        public:
            virtual ~IWispSnapshot() = default;

            // functions to fetch wisps by specifiers
            virtual IWisp &get_wisp_by_image_name(const std::string &w_name) const = 0;
            virtual IWisp &get_wisp_by_pid(const unsigned int pid) const = 0;

            virtual const std::unordered_map<unsigned int, std::shared_ptr<IWisp>> &get_all_wisps() const = 0;
            virtual void add_wisp(Common::WispInfo wisp) = 0;
        };
    }
}