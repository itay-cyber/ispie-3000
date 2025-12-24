#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <core/common/types.h>

namespace ISpieCore
{
    namespace Interfaces
    {
        class IWisp
        {
        public:
            virtual ~IWisp() = default;

            virtual const Common::WispInfo get_wisp_info() const = 0;
            virtual const unsigned int get_pid() const = 0;
            virtual const std::string &get_image_name() const = 0;
        };
    }
}