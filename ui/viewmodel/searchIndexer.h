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
#include <QString>

#include "searchBoxHandler.h"

class SearchIndexer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* fieldId             READ getFieldId       WRITE setFieldId      /*NOTIFY showFieldId*/)
    Q_PROPERTY(QString text                 READ getText          WRITE setText         CONSTANT/*NOTIFY showFieldName*/)
    Q_PROPERTY(SearchBoxHandler* handler    READ getHandler       WRITE setHandler      /*NOTIFY showHandler*/)

public:

    SearchIndexer() = default;
    ~SearchIndexer();

    [[nodiscard]] QObject* getFieldId() const;
    void setFieldId(QObject* fieldId);
    
    [[nodiscard]] QString getText() const;
    void setText(QString text);

    [[nodiscard]] SearchBoxHandler* getHandler() const;
    void setHandler(SearchBoxHandler* handler);

    Q_INVOKABLE void addIndexToHandler();

signals:

private:
    QObject* _fieldId;
    QString _text;
    SearchBoxHandler* _handler;
};
