#include "searchBoxHandler.h"
#include <QDebug>

SearchBoxHandler::~SearchBoxHandler()
{
    delete(_viewId);
    qDeleteAll(_indexes);
}

QObject* SearchBoxHandler::getViewId() const
{
    return _viewId;
}

void SearchBoxHandler::setViewId(QObject* viewId)
{
    _viewId = viewId;
}

SearchBoxHandler* SearchBoxHandler::getHandler()
{
    return this;
}

void SearchBoxHandler::addIndex(QString& key, QObject* value)
{
    _indexes.insert(key, value);
    qDebug() << "keu"<< key;
    qDebug() << value;
}
