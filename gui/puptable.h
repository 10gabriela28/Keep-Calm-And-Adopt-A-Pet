
#pragma once
#include <QAbstractTableModel>
#include "service.h"

class PupTable : public QAbstractTableModel {
private:
    Service* service;
public:
    PupTable(Service* s) : service(s) {}

    int rowCount(const QModelIndex& = QModelIndex()) const override { 
        return service->getAdoptionService()->getSize(); 
    }
    
    int columnCount(const QModelIndex& = QModelIndex()) const override { 
        return 3; 
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole || !index.isValid()) return QVariant{};
        
        Dog dog = service->getAdoptionService()->getDogS(index.row());
        if (index.column() == 0) return QString::fromStdString(dog.getName());
        if (index.column() == 1) return QString::fromStdString(dog.getBreed());
        if (index.column() == 2) return dog.getAge();
        return QVariant{};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant{};
        if (section == 0) return "Name";
        if (section == 1) return "Breed";
        if (section == 2) return "Age";
        return QVariant{};
    }

    void refresh() { emit layoutChanged(); }
};