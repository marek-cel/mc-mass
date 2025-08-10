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
#ifndef MC_MASS_COMMANDSMANAGER_H_
#define MC_MASS_COMMANDSMANAGER_H_

#include <memory>
#include <vector>

#include <Command.h>

/**
 * \brief Commands history manager.
 *
 * This class manages a history of commands, allowing for undo and redo operations.
 */
class CommandsManager
{
public:

    /**
     * \brief Constructor.
     * \param max_size Maximum number of commands to keep in history.
     */
    CommandsManager(size_t max_size = 1000)
        : _max_size(max_size)
    {}

    /**
     * \brief Executes a command and adds it to the history.
     * \param command The command to execute.
     */
    void execute(std::unique_ptr<Command> command)
    {
        if ( command )
        {
            if ( canRedo() )
            {
                _commands.erase(_commands.begin() + _current_index + 1, _commands.end());
            }

            command->execute();
            _commands.push_back(std::move(command));

            if ( _commands.size() > _max_size )
            {
                _commands.erase(_commands.begin());
            }

            _current_index = static_cast<int>(_commands.size()) - 1;
        }
    }

    /**
     * \brief If the current command can be undone, it undoes it and decrements
     * current command index.
     */
    void undo()
    {
        if ( canUndo() )
        {
            _commands[_current_index]->undo();
            --_current_index;
        }
    }

    /**
     * \brief If the current command can be redone, it redoes it and increments
     * current command index.
     */
    void redo()
    {
        if ( canRedo() )
        {
            ++_current_index;
            _commands[_current_index]->execute();
        }
    }

    /**
     * \brief Checks if the command history is empty.
     * \return true if the command history is empty, false otherwise.
     */
    bool isEmpty() const
    {
        return _commands.empty();
    }

    /**
     * \brief Checks if the current command can be undone.
     * \return true if the command can be undone, false otherwise.
     */
    bool canUndo() const
    {
        return _current_index >= 0;
    }

    /**
     * \brief Checks if the current command can be redone.
     * \return true if the command can be redone, false otherwise.
     */
    bool canRedo() const
    {
        return _current_index < static_cast<int>(_commands.size()) - 1;
    }

    /**
     * \brief Clears commands history.
     */
    void reset()
    {
        _commands.clear();
        _current_index = -1;
    }

    /**
     * \brief Sets current command as saved and all other commands as unsaved.
     */
    void setCurrentSaved()
    {
        for ( auto& command : _commands )
        {
            command->setSaved(false);
        }

        if ( _current_index >= 0 )
        {
            _commands[_current_index]->setSaved(true);
        }
    }

    /**
     * \brief Returns current command saved state.
     * \return true if the command is saved, false otherwise
     */
    bool isCurrentSaved() const
    {
        if ( _current_index >= 0 )
        {
            return _commands[_current_index]->isSaved();
        }
        return false;
    }

private:

    const size_t _max_size; ///< Maximum number of commands to keep in history

    std::vector<std::unique_ptr<Command>> _commands; ///< command history
    int _current_index = -1;    ///< index of the current command in the history
};

#endif // MC_MASS_COMMANDSMANAGER_H_
