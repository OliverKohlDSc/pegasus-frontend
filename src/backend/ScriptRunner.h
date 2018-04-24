// Pegasus Frontend
// Copyright (C) 2017  Mátyás Mustoha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include <QString>
#include <QVector>


/// A utility class for finding and running external scripts
class ScriptRunner {
public:
    enum class EventType : unsigned char {
        QUIT,
        REBOOT,
        SHUTDOWN,
        CONFIG_CHANGED,
        SETTINGS_CHANGED,
        CONTROLS_CHANGED,
        PROCESS_STARTED,
        PROCESS_FINISHED,
    };

    static void findAndRunScripts(EventType);

    static QVector<QString> findScripts(const QString& dirname);
    static QVector<QString> findScripts(EventType);

    static void runScripts(const QVector<QString>& paths);
};