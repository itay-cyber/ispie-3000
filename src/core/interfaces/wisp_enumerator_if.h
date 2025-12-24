#pragma once
/*****************************
┓ ┏• ┓   ┳┳┓    ┓ •  ┓    ┏┓
┃┃┃┓╋┣┓  ┃┃┃┓┏  ┃ ┓╋╋┃┏┓  ┣ ┓┏┏┓
┗┻┛┗┗┛┗  ┛ ┗┗┫  ┗┛┗┗┗┗┗   ┗┛┗┫┗
             ┛               ┛


Written by Itay G - 2025
******************************/
#include <string>
#include <core/interfaces/wisp_snapshot_if.h>

namespace ISpieCore
{
    namespace Interfaces
    {
        class IWispEnumerator
        {
        public:
            virtual ~IWispEnumerator() = default;
            virtual std::shared_ptr<IWispSnapshot> get_wisp_snapshot() = 0;
            virtual IWispSnapshot &get_previous_wisp_snapshot() const = 0;
        };
    }
}