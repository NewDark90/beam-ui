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

#include <QObject>
#include <QSettings>
#include <QQmlListProperty>

#include "model/settings.h"
#include "wallet/transactions/swaps/bridges/bitcoin/client.h"
#include "wallet/transactions/swaps/bridges/bitcoin/settings.h"
#include "viewmodel/notifications/notifications_settings.h"
#include "viewmodel/atomic_swap/swap_eth_settings_item.h"

class SettingsViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString      nodeAddress                     READ getNodeAddress                 WRITE setNodeAddress    NOTIFY nodeAddressChanged)
    Q_PROPERTY(QString      version                         READ getVersion                     CONSTANT)
    Q_PROPERTY(bool         localNodeRun                    READ getLocalNodeRun                WRITE setLocalNodeRun   NOTIFY localNodeRunChanged)
    Q_PROPERTY(unsigned int localNodePort                   READ getLocalNodePort               WRITE setLocalNodePort  NOTIFY localNodePortChanged)
    Q_PROPERTY(QString      remoteNodePort                  READ getRemoteNodePort              WRITE setRemoteNodePort NOTIFY remoteNodePortChanged)
    Q_PROPERTY(bool         isNodeChanged                   READ isNodeChanged                  NOTIFY nodeSettingsChanged)
    Q_PROPERTY(QStringList  localNodePeers                  READ getLocalNodePeers              NOTIFY localNodePeersChanged)
    Q_PROPERTY(int          lockTimeout                     READ getLockTimeout                 WRITE  setLockTimeout NOTIFY lockTimeoutChanged)
    Q_PROPERTY(QString      walletLocation                  READ getWalletLocation              CONSTANT)
    Q_PROPERTY(bool         isLocalNodeRunning              READ isLocalNodeRunning             NOTIFY localNodeRunningChanged)
    Q_PROPERTY(bool         isPasswordReqiredToSpendMoney   READ isPasswordReqiredToSpendMoney  WRITE   setPasswordReqiredToSpendMoney NOTIFY passwordReqiredToSpendMoneyChanged)
    Q_PROPERTY(bool         isAllowedBeamMWLinks            READ isAllowedBeamMWLinks           WRITE   allowBeamMWLinks NOTIFY beamMWLinksPermissionChanged)
    Q_PROPERTY(QStringList  supportedLanguages              READ getSupportedLanguages          NOTIFY  currentLanguageIndexChanged)
    Q_PROPERTY(int          currentLanguageIndex            READ getCurrentLanguageIndex        NOTIFY  currentLanguageIndexChanged)
    Q_PROPERTY(QString      currentLanguage                 READ getCurrentLanguage             WRITE   setCurrentLanguage)
    Q_PROPERTY(bool         isValidNodeAddress              READ isValidNodeAddress             NOTIFY  validNodeAddressChanged)
    Q_PROPERTY(QString      secondCurrency                  READ getSecondCurrency              WRITE   setSecondCurrency NOTIFY secondCurrencyChanged)
    Q_PROPERTY(QString      publicAddress                   READ getPublicAddress               NOTIFY  publicAddressChanged)
    Q_PROPERTY(QString      explorerUrl                     READ getExplorerUrl                 CONSTANT)
    Q_PROPERTY(QString      faucetUrl                       READ getFaucetUrl                   CONSTANT)
    Q_PROPERTY(int          minConfirmations                READ getMinConfirmations            WRITE  setMinConfirmations NOTIFY minConfirmationsChanged)
    Q_PROPERTY(bool         dappsAllowed                    READ getDAppsAllowed                WRITE  setDAppsAllowed NOTIFY dappsAllowedChanged)
    Q_PROPERTY(int          appsServerPort                  READ getAppsPort                    WRITE  setAppsPort     NOTIFY appsPortChanged)

    Q_PROPERTY(bool ipfsSupported READ getIPFSSupported CONSTANT)

    #ifdef BEAM_IPFS_SUPPORT
    Q_PROPERTY(unsigned int ipfsSwarmPort READ getIPFSSwarmPort WRITE setIPFSSwarmPort  NOTIFY IPFSSettingsChanged)
    Q_PROPERTY(QString ipfsNodeStart READ getIPFSNodeStart WRITE setIPFSNodeStart  NOTIFY IPFSNodeStartChanged)
    Q_PROPERTY(bool ipfsChanged READ getIPFSChanged NOTIFY IPFSSettingsChanged)
    Q_PROPERTY(QString ipfsLocation READ getIPFSLocation CONSTANT)
    #endif

    Q_PROPERTY(QList<QObject*> swapCoinSettingsList READ getSwapCoinSettings    CONSTANT)
    Q_PROPERTY(QObject* notificationsSettings   READ getNotificationsSettings   CONSTANT)
    Q_PROPERTY(int maxPrivacyAnonymitySet  READ geMaxPrivacyAnonymitySet   WRITE setMaxPrivacyAnonymitySet NOTIFY maxPrivacyAnonymitySetChanged)
    Q_PROPERTY(int maxPrivacyLockTimeLimit READ getMaxPrivacyLockTimeLimit WRITE setMaxPrivacyLockTimeLimit NOTIFY maxPrivacyLockTimeLimitChanged)
    Q_PROPERTY(QObject* ethSettings   READ getEthSettings   CONSTANT)
    Q_PROPERTY(QString currentHeight READ getCurrentHeight NOTIFY stateChanged)

public:

    SettingsViewModel();
    ~SettingsViewModel() override;

    QString getNodeAddress() const;
    void setNodeAddress(const QString& value);
    QString getVersion() const;
    bool getLocalNodeRun() const;
    void setLocalNodeRun(bool value);

    [[nodiscard]] unsigned int getLocalNodePort() const;
    void setLocalNodePort(unsigned int value);

    [[nodiscard]] bool getIPFSSupported() const;

    #ifdef BEAM_IPFS_SUPPORT
    [[nodiscard]] unsigned int getIPFSSwarmPort() const;
    void setIPFSSwarmPort(unsigned int value);
    [[nodiscard]] bool getIPFSChanged() const;
    [[nodiscard]] QString getIPFSLocation() const;
    [[nodiscard]] QString getIPFSNodeStart() const;
    void setIPFSNodeStart(const QString&);
    #endif

    QString getRemoteNodePort() const;
    void setRemoteNodePort(const QString& value);
    int getLockTimeout() const;
    void setLockTimeout(int value);
    bool isPasswordReqiredToSpendMoney() const;
    void setPasswordReqiredToSpendMoney(bool value);
    bool isAllowedBeamMWLinks();
    void allowBeamMWLinks(bool value);
    QStringList getSupportedLanguages() const;
    int getCurrentLanguageIndex() const;
    void setCurrentLanguageIndex(int value);
    QString getCurrentLanguage() const;
    void setCurrentLanguage(QString value);
    QString getExplorerUrl() const;
    QString getFaucetUrl() const;
    // Amount in second currency
    QString getSecondCurrency() const;
    void setSecondCurrency(const QString&);

    const QString& getPublicAddress() const;

    QStringList getLocalNodePeers() const;
    void setLocalNodePeers(const QStringList& localNodePeers);
    QString getWalletLocation() const;
    bool isLocalNodeRunning() const;
    bool isValidNodeAddress() const;

    bool isNodeChanged() const;

    const QList<QObject*>& getSwapCoinSettings();
    QObject* getNotificationsSettings();
    QObject* getEthSettings();

    int geMaxPrivacyAnonymitySet() const;
    void setMaxPrivacyAnonymitySet(int mpAnonymitySetIndex);

    int getMaxPrivacyLockTimeLimit() const;
    void setMaxPrivacyLockTimeLimit(int limit);

    int getMinConfirmations() const;
    void setMinConfirmations(int value);

    bool getDAppsAllowed () const;
    void setDAppsAllowed (bool val);
    int getAppsPort() const;
    void setAppsPort(int port);

    QString getCurrentHeight() const;

    Q_INVOKABLE uint coreAmount() const;
    Q_INVOKABLE void addLocalNodePeer(const QString& localNodePeer);
    Q_INVOKABLE void deleteLocalNodePeer(int index);
    Q_INVOKABLE void openUrl(const QString& url);
    Q_INVOKABLE void refreshWallet();
    Q_INVOKABLE void openFolder(const QString& path);
    Q_INVOKABLE bool checkWalletPassword(const QString& password) const;
    Q_INVOKABLE QString getOwnerKey(const QString& password) const;
    Q_INVOKABLE bool exportData() const;
    Q_INVOKABLE bool importData() const;
    Q_INVOKABLE bool hasPeer(const QString& peer) const;
    Q_INVOKABLE void reportProblem();
    Q_INVOKABLE void changeWalletPassword(const QString& pass);

public slots:
    void applyNodeChanges();

    #ifdef BEAM_IPFS_SUPPORT
    void applyIPFSChanges();
    #endif

    void undoChanges();
    void onNodeStarted();
    void onNodeStopped();
    void onAddressChecked(const QString& addr, bool isValid);
    void onPublicAddressChanged(const QString& publicAddr);

signals:
    void nodeAddressChanged();
    void localNodeRunChanged();
    void localNodePortChanged();
    void remoteNodePortChanged();
    void localNodePeersChanged();
    void nodeSettingsChanged();
    void lockTimeoutChanged();
    void localNodeRunningChanged();
    void passwordReqiredToSpendMoneyChanged();
    void validNodeAddressChanged();
    void currentLanguageIndexChanged();
    void secondCurrencyChanged();
    void beamMWLinksPermissionChanged();
    void publicAddressChanged();
    void maxPrivacyAnonymitySetChanged();
    void maxPrivacyLockTimeLimitChanged();
    void minConfirmationsChanged();
    void dappsAllowedChanged();
    void stateChanged();
    void appsPortChanged();

    #ifdef BEAM_IPFS_SUPPORT
    void IPFSSwarmPortChanged();
    void IPFSNodeStartChanged();
    void IPFSSettingsChanged();
    #endif

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    WalletSettings& m_settings;
    QList<QObject*> m_swapSettings;
    NotificationsSettings m_notificationsSettings;
    SwapEthSettingsItem m_ethSettings;

    QString m_nodeAddress;
    bool m_localNodeRun;
    unsigned int m_localNodePort = 0;
    QString m_remoteNodePort; // TODO:change to unsigned int like localNodePort

    #ifdef BEAM_IPFS_SUPPORT
    unsigned int m_IPFSSwarmPort = 0;
    QString m_IPFSNodeStart;
    #endif

    QStringList m_localNodePeers;
    int m_lockTimeout;
    bool m_isPasswordReqiredToSpendMoney;
    bool m_isAllowedBeamMWLinks;
    bool m_isValidNodeAddress;
    bool m_isNeedToCheckAddress;
    bool m_isNeedToApplyChanges;
    QStringList m_supportedLanguages;
    int m_currentLanguageIndex;
    beam::wallet::Currency m_rateCurrency;
    int m_timerId;
    QString m_publicAddress;
    mutable int m_mpAnonymitySetIndex = 0;
    mutable int m_mpLockTimeLimitIndex = 1;
    WalletModel::Ptr m_walletModel;
    const int CHECK_INTERVAL = 1000;
};
