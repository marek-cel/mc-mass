/****************************************************************************//*
 *  Copyright (C) 2025 Marek M. Cel
 *
 *  This file is part of MC-Mass.
 *
 *  MC-Mass is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MC-Mass is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <Log.h>

std::ostream* Log::_out_stream = &std::cout;
Log::VerboseLevel  Log::_verb_level = Log::VerboseLevel::Info;

void Log::print(VerboseLevel level, const char* format, va_list args)
{
    if ( level <= _verb_level )
    {
        char* buf = nullptr;

        va_list args2;
        va_copy(args2, args);
        size_t size = vsnprintf(nullptr, 0, format, args);
        va_end(args);

        if (size > 0)
        {
            buf = new char[size+1];
            vsnprintf(buf, size+1, format, args2);
        }

        va_end(args2);

        std::string level_tag;
        switch (level)
        {
            case VerboseLevel::Error   : level_tag = "ERROR";   break;
            case VerboseLevel::Warning : level_tag = "WARNING"; break;
            case VerboseLevel::Info    : level_tag = "INFO";    break;
            case VerboseLevel::Debug   : level_tag = "DEBUG";   break;
        }

        if (level <= _verb_level)
        {
            std::stringstream ss;
            ss << "[" << level_tag << "]";
            ss << " " << buf << "\n";
            std::string msg = ss.str();

            std::ostream* out = _out_stream == nullptr ? &std::cout : _out_stream;
            *out << msg;
            out->flush();
        }

        if ( buf ) { delete [] buf; } buf = nullptr;
    }
}
