// Copyright 2022 The Beam Team
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
#include <QPair>
#include <QVector>

class SearchBoxHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* viewId              READ getViewId       WRITE setViewId      /*NOTIFY showViewdId*/)
    Q_PROPERTY(SearchBoxHandler* handler    READ getHandler)

public:
    using Ptr = std::shared_ptr<SearchBoxHandler>;

    SearchBoxHandler() = default;
    ~SearchBoxHandler();

    [[nodiscard]] QObject* getViewId() const;
    void setViewId(QObject* fieldId);

    [[nodiscard]] SearchBoxHandler* getHandler();

    void addIndex(QString& key, QObject* value);

    Q_INVOKABLE QVector<QObject*> search(const QString& str);

signals:

private:
    QObject* _viewId;
    QVector<QPair<QString, QObject*>> _indexes;
};
