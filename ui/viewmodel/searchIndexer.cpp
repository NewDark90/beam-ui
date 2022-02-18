#include "searchIndexer.h"

SearchIndexer::~SearchIndexer()
{
    delete(_fieldId);
    delete(_handler);
}

QObject* SearchIndexer::getFieldId() const
{
    return _fieldId;
}
void SearchIndexer::setFieldId(QObject* fieldId)
{
    _fieldId = fieldId;
}

QString SearchIndexer::getText() const
{
    return _text;
}
void SearchIndexer::setText(QString text)
{
    _text = text;
}

SearchBoxHandler* SearchIndexer::getHandler() const
{
    return _handler;
}
void SearchIndexer::setHandler(SearchBoxHandler* handler)
{
    _handler = handler;
}

void SearchIndexer::addIndexToHandler()
{
    //if (!_handler && !_fieldId && !_text.isEmpty())
    //{
        _handler->addIndex(_text, _fieldId);
    //}
}
