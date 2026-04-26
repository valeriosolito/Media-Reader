#include "itemGrid.h"
#include "itemCard.h"
#include "header/Album.h"
#include "header/Film.h"
#include "header/Fumetto.h"
#include "header/ItemRepo.h"
#include <QDebug>

ItemGrid::ItemGrid(QWidget *parent) : QWidget(parent), storage(nullptr) {
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    gridWidget = new QWidget();
    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setAlignment(Qt::AlignTop);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(20, 20, 20, 20);

    gridWidget->setLayout(gridLayout);
    scrollArea->setWidget(gridWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

}

void ItemGrid::setStorage(Repo::ItemRepo *storage) {
    this->storage = storage;
}

void ItemGrid::clearGrid() {
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
}

void ItemGrid::showProductsByClass(const QString &className) {
    clearGrid();

    if (!storage)
        return;

    for (const auto &product : *storage) {
        if (className == "All" ||
            (className == "Fumetto" && dynamic_cast<const Item::Fumetto*>(product)) ||
            (className == "Film" && dynamic_cast<const Item::Film*>(product)) ||
            (className == "Album" && dynamic_cast<const Item::Album*>(product))) {
            addItemCard(product);
        }
    }
}


void ItemGrid::addItemCard(const Item::AbsItem *product) {
    ItemCard* card = new ItemCard(*product);
    int count = gridLayout->count();
    int row = count / 3;
    if(window()->isMaximized()){
        row = count/6;
    }
    int col = count%3;
    if(window()->isMaximized()){
        col = count % 6;
    }

    gridLayout->addWidget(card, row, col);
    connect(card, &ItemCard::cardClicked, this, [this](const Item::AbsItem* item){
        selectedItem = item;
        if (detailView)
            detailView->setItem(item);
    });
}

void ItemGrid::filterByNome(const QString &text){
    clearGrid();

    if(!storage) return;

    if(detailView){
        detailView->clearDetail();
        detailView->setDeleteButtonVisible(false);
        }

    for (const auto &item : *storage){
        QString nome = QString::fromStdString(item->getNome());
        if(nome.contains(text,Qt::CaseInsensitive)) {
            addItemCard(item);
        }
    }
}

void ItemGrid::setDetailView(ItemDetail *detailView){
    this->detailView = detailView;
}

const Item::AbsItem* ItemGrid::getSelectedItem() const{
    return selectedItem;
}
