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
#ifndef MC_MASS_LOG_H_
#define MC_MASS_LOG_H_

#include <cstdarg>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**
 * \brief Logging class.
 */
class Log
{
public:

    /**
     * \brief The verbose level enum
     */
    enum class VerboseLevel
    {
        Error   = 0x0,      ///< critical error
        Warning = 0x1,      ///< warning
        Info    = 0x2,      ///< information
        Debug   = 0x3       ///< debug output
    };

    /**
     * \brief Prints error log message.
     * \param format message format
     */
    inline static void error(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        print(VerboseLevel::Error, format, args);
        va_end(args);
    }

    /**
     * \brief Prints warning log message.
     * \param format message format
     */
    inline static void warning(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        print(VerboseLevel::Warning, format, args);
        va_end(args);
    }

    /**
     * \brief Prints info log message.
     * \param format message format
     */
    inline static void info(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        print(VerboseLevel::Info, format, args);
        va_end(args);
    }

    /**
     * \brief Prints debug log message.
     * \param format message format
     */
    inline static void debug(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        print(VerboseLevel::Debug, format, args);
        va_end(args);
    }

    /**
     * \brief Gets output stream.
     * If output stream is not set std::cout is returned.
     * \return output stream
     */
    inline static std::ostream& out()
    {
        return _out_stream == nullptr ? std::cout : *_out_stream;
    }

    /**
     * \brief Sets output stream.
     * \param outputStream output stream
     */
    inline static void setOutStream(std::ostream* out_stream)
    {
        _out_stream = out_stream;
    }

    /**
     * \brief Sets verbose level.
     * \param verboseLevel verbose level
     */
    inline static void setVerbLevel(VerboseLevel verb_level)
    {
        _verb_level = verb_level;
    }

private:

    static std::ostream* _out_stream;   ///< output stream (default std::cout)
    static VerboseLevel  _verb_level;   ///< verbose level (default Info)

    /**
     * \brief Prints log message.
     * \param level verbose level
     * \param format message format
     */
    static void print(VerboseLevel level, const char* format, va_list args);
};

#endif // MC_MASS_LOG_H_
