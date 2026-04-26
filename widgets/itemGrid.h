#ifndef ITEMGRID_H
#define ITEMGRID_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QVBoxLayout>
#include "header/ItemRepo.h"
#include "widgets/itemDetail.h"

class ItemGrid: public QWidget {
    Q_OBJECT

private:
    QScrollArea *scrollArea;
    QWidget *gridWidget;
    QGridLayout *gridLayout;
    Repo::ItemRepo *storage;
    ItemDetail* detailView;
    const Item::AbsItem* selectedItem = nullptr;
    void clearGrid();
    void addItemCard(const Item::AbsItem *product);

public:
    explicit ItemGrid(QWidget *parent = nullptr);
    void setStorage(Repo::ItemRepo *storage);
    void setDetailView(ItemDetail* detailView);
    void showProductsByClass(const QString &className);
    void filterByNome(const QString& text);
    const Item::AbsItem* getSelectedItem() const;

signals:
    void itemSelected(const Item::AbsItem* product);
};

#endif
