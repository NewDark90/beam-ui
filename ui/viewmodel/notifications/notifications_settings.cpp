// Copyright 2020 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "notifications_settings.h"

NotificationsSettings::NotificationsSettings(WalletSettings& walletSettings)
    : m_storage(walletSettings)
{
    loadFromStorage();
}

bool NotificationsSettings::isExcRatesActive()
{
    return m_isExcRatesActive;
}

bool NotificationsSettings::isNewVersionActive()
{
    return m_isNewVersionActive;
}

bool NotificationsSettings::isBeamNewsActive()
{
    return m_isBeamNewsActive;
}

bool NotificationsSettings::isTxStatusActive()
{
    return m_isTxStatusActive;
}

void NotificationsSettings::setNewVersionActive(bool isActive)
{
    if (isActive != m_isNewVersionActive)
    {
        m_isNewVersionActive = isActive;
        m_storage.setNewVersionActive(m_isNewVersionActive);
        emit newVersionActiveChanged();
    }
}

void NotificationsSettings::setExcRatesActive(bool isActive)
{
    if (isActive != m_isExcRatesActive)
    {
        m_isExcRatesActive = isActive;
        m_storage.setExcRatesActive(m_isExcRatesActive);
        emit excRatesActiveChanged();
    }
}

void NotificationsSettings::setBeamNewsActive(bool isActive)
{
    if (isActive != m_isBeamNewsActive)
    {
        m_isBeamNewsActive = isActive;
        // m_storage.setBeamNewsActive
        emit beamNewsActiveChanged();
    }
}

void NotificationsSettings::setTxStatusActive(bool isActive)
{
    if (isActive != m_isTxStatusActive)
    {
        m_isTxStatusActive = isActive;
        // m_storage.setTxStatusActive
        emit txStatusActiveChanged();
    }
}

void NotificationsSettings::loadFromStorage()
{
    m_isNewVersionActive = m_storage.isNewVersionActive();
    m_isExcRatesActive = m_storage.isExcRatesActive();
    emit excRatesActiveChanged();
    emit newVersionActiveChanged();
}
