#include "itemCard.h"
#include "header/Album.h"
#include "header/Film.h"
#include "header/Fumetto.h"
#include <QPixmap>


ItemCard::ItemCard(const Item::AbsItem &prod, QWidget *parent) :
    QWidget(parent) , cItem(&prod){
        setFixedSize(150,200);
        setStyleSheet("ItemCard { border: 1px solid #ddd; border-radius: 5px; background-color: white; }"
                      "ItemCard:hover { border: 2px solid #007acc; background-color: #f0f8ff; }");
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(10, 10, 10, 10);
        layout->setSpacing(10);

        imageLabel = new QLabel(this);
        imageLabel->setAlignment(Qt::AlignCenter);
        QString imagePath = (prod.getImgpath()).empty() ?
                                "" :
                                QString::fromStdString(prod.getImgpath());
        QPixmap pixmap(imagePath);
        if (pixmap.isNull()){
            pixmap.load(":/icons/interface/qmark.png");
        }
        imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        titleLabel = new QLabel(QString::fromStdString(prod.getNome()), this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-weight: normal; font-size: 13px;");
        titleLabel->setWordWrap(true);

        layout->addWidget(imageLabel);
        layout->addWidget(titleLabel);
        setLayout(layout);


        setCursor(Qt::PointingHandCursor);

}

