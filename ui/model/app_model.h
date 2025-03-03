// Copyright 2018 The Beam Team
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
#pragma once

#include "wallet_model.h"
#include "swap_coin_client_model.h"
#include "swap_eth_client_model.h"
#include "settings.h"
#include "messages.h"
#include "node_model.h"
#include "helpers.h"
#include "wallet/core/secstring.h"
#include "wallet/core/private_key_keeper.h"
#include "wallet/transactions/swaps/bridges/bitcoin/bridge_holder.h"
#include "wallet/transactions/swaps/swap_transaction.h"
#include "assets_manager.h"
#include "exchange_rates_manager.h"
#include "assets_list.h"
#include <memory>
#include <QSharedMemory>
#include <QSystemSemaphore>

#if defined(BEAM_HW_WALLET)
namespace beam::wallet
{
    class HWWallet;
}
#endif

class AppModel final: public QObject
{
    Q_OBJECT
public:
    static AppModel& getInstance();
    static std::string getMyName();
    static const std::string& getMyVersion();

    explicit AppModel(WalletSettings& settings);
    ~AppModel() override;

    bool createWallet(const beam::SecString& seed, const beam::SecString& pass, const std::string& rawSeed = "");

#if defined(BEAM_HW_WALLET)
    bool createTrezorWallet(const beam::SecString& pass, beam::wallet::IPrivateKeyKeeper2::Ptr keyKeeper);
    std::shared_ptr<beam::wallet::HWWallet> getHardwareWalletClient() const;
    beam::io::Reactor::Ptr getWalletReactor() const;
#endif

    void openWalletThrow(const beam::SecString& pass, beam::wallet::IPrivateKeyKeeper2::Ptr keyKeeper = {});
    [[nodiscard]] bool checkWalletPassword(const beam::SecString& pass) const;
    void changeWalletPassword(const std::string& pass);

    void applyNodeChanges();

    #ifdef BEAM_IPFS_SUPPORT
    void applyIPFSChanges();
    #endif

    void nodeSettingsChanged();
    void resetWallet();
    bool exportData();
    bool importData();
    bool isSeedValidationMode() const;
    void setSeedValidationMode(bool value);
    bool isSeedValidationTriggeredFromSetting() const;
    void setSeedValidationTriggeredFromSetting(bool value);
    bool isOnlyOneInstanceStarted() const;

    [[nodiscard]] WalletSettings& getSettings() const;
    [[nodiscard]] WalletModel::Ptr getWalletModel() const;
    [[nodiscard]] WalletModel::Ptr getWalletModelUnsafe() const;
    [[nodiscard]] AssetsManager::Ptr getAssets() const;
    [[nodiscard]] ExchangeRatesManager::Ptr getRates() const;
    [[nodiscard]] AssetsList::Ptr getMyAssets() const;

    MessageManager& getMessages();

    // Please, be very careful with this
    // wallet db can be destroyed internally
    [[nodiscard]] beam::wallet::IWalletDB::Ptr getWalletDB() const;

    NodeModel& getNode();
    [[nodiscard]] SwapCoinClientModel::Ptr getSwapCoinClient(beam::wallet::AtomicSwapCoin swapCoin) const;
    [[nodiscard]] SwapEthClientModel::Ptr getSwapEthClient() const;
public slots:
    void onStartedNode();
    void onFailedToStartNode(beam::wallet::ErrorType errorCode);
    void onResetWallet();

signals:
    void walletReset();
    void walletResetCompleted();

private:
    void start();
    void startNode();
    void startWallet();
    void initSwapClients();
    template<typename CoreBridge, typename ElectrumBridge, typename SettingsProvider>
    void initSwapClient(beam::wallet::AtomicSwapCoin swapCoin);
    void initEthClient();
    void resetSwapClients();
    void onWalledOpened(const beam::SecString& pass);
    void backupDB(const std::string& dbFilePath);
    void restoreDBFromBackup(const std::string& dbFilePath);

    template<typename BridgeSide, typename Bridge, typename SettingsProvider>
    void registerSwapFactory(beam::wallet::AtomicSwapCoin swapCoin, beam::wallet::AtomicSwapTransaction::Creator& swapTxCreator);

private:
    bool isAnotherRunning();
    bool tryLock();
    void release();
    // SwapCoinClientModels must be destroyed after WalletModel
    std::map<beam::wallet::AtomicSwapCoin, SwapCoinClientModel::Ptr> m_swapClients;
    std::map<beam::wallet::AtomicSwapCoin, beam::bitcoin::IBridgeHolder::Ptr> m_swapBridgeHolders;
    SwapEthClientModel::Ptr m_swapEthClient;
    beam::ethereum::IBridgeHolder::Ptr m_swapEthBridgeHolder;

    WalletModel::Ptr m_wallet;
    NodeModel m_nodeModel;
    WalletSettings& m_settings;
    ExchangeRatesManager::Ptr m_rates;
    AssetsManager::Ptr m_assets;
    AssetsList::Ptr m_myAssets; // assets in the wallet + BEAM even if 0
    MessageManager m_messages;
    ECC::NoLeak<ECC::uintBig> m_passwordHash;
    beam::io::Reactor::Ptr m_walletReactor;
    beam::wallet::IWalletDB::Ptr m_db;
    Connections m_nsc; // [n]ode [s]tarting [c]onnections
    Connections m_walletConnections;
    static AppModel* s_instance;
    std::string m_walletDBBackupPath;

    bool m_isSeedValidationMode = false;
    bool m_isSeedValidationTriggeredFromSettings = false;

    bool m_isOnlyOneInstanceStarted = false;
    QString m_key;
    QString m_memKey;
    QSystemSemaphore m_memLock;
    QSharedMemory m_memAppGuard;

#if defined(BEAM_HW_WALLET)
    mutable std::shared_ptr<beam::wallet::HWWallet> m_hwWallet;
#endif
};

inline WalletSettings& AppSettings()
{
    return AppModel::getInstance().getSettings();
}
