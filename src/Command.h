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
#ifndef MC_MASS_COMMAND_H_
#define MC_MASS_COMMAND_H_

/**
 * \brief Abstract base class for commands.
 *
 * This class defines the interface for commands that can be executed and undone.
 */
class Command
{
public:

    // LCOV_EXCL_START
    Command() = default;
    Command(const Command&) = default;
    Command(Command&&) = default;
    virtual ~Command() = default;
    Command& operator=(const Command&) = default;
    Command& operator=(Command&&) = default;
    // LCOV_EXCL_STOP

    /**
     * \brief Executes the command.
     */
    virtual void execute() = 0;

    /**
     * \brief Undoes the command.
     */
    virtual void undo() = 0;

    /**
     * \brief Sets the command's saved state.
     */
    void setSaved(bool saved)
    {
        _is_saved = saved;
    }

    /**
     * \brief Checks if the command is saved.
     * \return true if the command is saved, false otherwise.
     */
    bool isSaved() const
    {
        return _is_saved;
    }

private:

    bool _is_saved = false; ///< flag indicating if the command is saved.
};

#endif // MC_MASS_COMMAND_H_
