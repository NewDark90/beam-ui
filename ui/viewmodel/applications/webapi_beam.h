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

#include "model/app_model.h"
#include "shaders_manager.h"
#include "wallet/api/i_wallet_api.h"

namespace beamui::applications
{
    class WebAPI_Beam
        : public QObject
        , public beam::wallet::IWalletApiHandler
    {
        Q_OBJECT
    public:
        explicit WebAPI_Beam(const std::string& version, const std::string& appid);
        ~WebAPI_Beam() override;

    //
    // Slots below are called by web in context of the UI thread
    //
    public slots:
       int test();
       void callWalletApi(const QString& request);

    //
    // Signals are received by web
    //
    signals:
        void callWalletApiResult(const QString& result);

    private:
        // This callback is called in the reactor thread
        void sendAPIResponse(const beam::wallet::json& result) override;

        // This should be called only in context of the reactor thread
        void callWalletApiImp(const std::string& request);

        // API should be accessed only in context of the reactor thread
        beam::wallet::IWalletApi::Ptr _walletAPI;
    };

    class WebAPICreator: public QObject
    {
        Q_OBJECT
    public:
        explicit WebAPICreator(QObject *parent = nullptr);
        ~WebAPICreator() override;

        Q_INVOKABLE void createApi(const QString& version, const QString& appName, const QString& appUrl);

    signals:
        void apiCreated(QObject* api, const QString& appAddress);
        void apiFailed(const QString& error);

    private:
        std::unique_ptr<WebAPI_Beam> _api;
        std::shared_ptr<bool> _guard = std::make_shared<bool>(true);
    };
}
