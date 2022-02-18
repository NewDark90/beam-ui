#include "searchBoxHandler.h"

SearchBoxHandler::~SearchBoxHandler()
{
    delete(_viewId);
    //qDeleteAll(_indexes);
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
    _indexes.push_back(qMakePair(key.toLower(), value));
}

QVector<QObject*> SearchBoxHandler::search(const QString& str)
{
    QVector<QObject*> searchResult;
    foreach(auto pair, _indexes)
    {
        if(!pair.first.isEmpty() && pair.first.contains(str.toLower()))
        {
            searchResult.push_back(pair.second);
        }
    }
    return searchResult;
}
