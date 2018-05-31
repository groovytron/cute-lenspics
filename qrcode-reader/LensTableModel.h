#ifndef LENS_TABLE_MODEL_H
#define LENS_TABLE_MODEL_H

#include "lens.h"

#include <QObject>
#include <QAbstractTableModel>

class LensTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    LensTableModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool addLens(Lens lens);
    QList<Lens> getLenses();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<Lens>* lenses;
};

#endif // LENS_TABLE_MODEL_H
