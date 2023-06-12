#pragma once
#include "D:\Utils\Utils\plog\Record.h"
#include "D:\Utils\Utils\plog\Util.h"

namespace plog
{
    class PLOG_LINKAGE IAppender
    {
    public:
        virtual ~IAppender()
        {
        }

        virtual void write(const Record& record) = 0;
    };
}
