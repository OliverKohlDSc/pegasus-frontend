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


#include "Model.h"

#include <QDebug>
#include <QFileInfo>


namespace Model {

GameAssets::GameAssets(QObject* parent)
    : QObject(parent)
{}

void GameAssets::setSingle(Assets::Type key, QString value)
{
    Q_ASSERT(Assets::singleTypes.contains(key));
    m_single_assets[key] = value;
}

void GameAssets::appendMulti(Assets::Type key, QString value)
{
    Q_ASSERT(Assets::multiTypes.contains(key));
    m_multi_assets[key].append(value);
}

Game::Game(QString path, QObject* parent)
    : QObject(parent)
    , m_rom_path(path)
    , m_rom_basename(QFileInfo(m_rom_path).completeBaseName())
    , m_title(m_rom_basename)
    , m_players(1)
    , m_rating(0)
    , m_year(0)
    , m_month(0)
    , m_day(0)
    , m_playcount(0)
    , m_assets(new GameAssets(this))
{}

Platform::Platform(QString name, QString rom_dir_path,
                   QStringList rom_filters, QString launch_cmd,
                   QObject* parent)
    : QObject(parent)
    , m_short_name(name)
    , m_rom_dir_path(rom_dir_path)
    , m_rom_filters(rom_filters)
    , m_launch_cmd(launch_cmd)
    , m_current_game_idx(-1)
    , m_current_game(nullptr)
{
    Q_ASSERT(!m_short_name.isEmpty());
    Q_ASSERT(!m_rom_dir_path.isEmpty());
    Q_ASSERT(!m_rom_filters.isEmpty());
    Q_ASSERT(!m_launch_cmd.isEmpty());
}

void Platform::setCurrentGameIndex(int idx)
{
    if (idx == -1) {
        resetGameIndex();
        return;
    }

    const bool valid_idx = (0 <= idx && idx < m_games.count());
    if (!valid_idx) {
        qWarning() << tr("Invalid game index #%1").arg(idx);
        return;
    }

    Model::Game* new_game = m_games.at(idx);
    if (m_current_game == new_game)
        return;

    m_current_game_idx = idx;
    m_current_game = new_game;
    Q_ASSERT(m_current_game);

    emit currentGameIndexChanged();
    emit currentGameChanged();
}

void Platform::resetGameIndex()
{
    // these values are always in pair
    Q_ASSERT((m_current_game_idx == -1) == (m_current_game == nullptr));
    if (!m_current_game) // already reset
        return;

    m_current_game_idx = -1;
    m_current_game = nullptr;

    emit currentGameIndexChanged();
    emit currentGameChanged();
}

QQmlListProperty<Model::Game> Platform::getGamesProp()
{
    return QQmlListProperty<Model::Game>(this, m_games);
}

} // namespace Model
