#ifndef ITEMCARD_H
#define ITEMCARD_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "header/AbsItem.h"

class ItemCard : public QWidget{
    Q_OBJECT

private:
    QLabel *imageLabel;
    QLabel *titleLabel;
    const Item::AbsItem* cItem;


public:
    explicit ItemCard(const Item::AbsItem &prod, QWidget *parent = nullptr);

signals:
    void cardClicked(const Item::AbsItem* prod);
    void deleteRequested(unsigned int id);

protected:
    void mousePressEvent(QMouseEvent* event) override{
        Q_UNUSED(event);
        emit cardClicked(cItem);
    }



};

#endif
