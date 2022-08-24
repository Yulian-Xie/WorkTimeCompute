#include "inputtimeui.h"

InputTimeUi::InputTimeUi(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant InputTimeUi::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex InputTimeUi::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex InputTimeUi::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int InputTimeUi::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int InputTimeUi::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant InputTimeUi::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
