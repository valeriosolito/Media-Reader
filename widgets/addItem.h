#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class AddItemDialog : public QDialog{
    Q_OBJECT

public:
    enum ItemType {Album, Film, Fumetto};

    AddItemDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Scegli il tipo di articolo");
        setModal(true);

        QVBoxLayout *layout = new QVBoxLayout(this);
        QPushButton *fumBtn = new QPushButton("Aggiungi Fumetto", this);
        QPushButton *filmBtn = new QPushButton("Aggiungi Film", this);
        QPushButton *albumBtn = new QPushButton("Aggiungi Album", this);

        layout->addWidget(fumBtn);
        layout->addWidget(filmBtn);
        layout->addWidget(albumBtn);

        connect(fumBtn, &QPushButton::clicked, this, [this]() { selected = Fumetto; accept(); });
        connect(filmBtn, &QPushButton::clicked, this, [this]() { selected = Film; accept(); });
        connect(albumBtn, &QPushButton::clicked, this, [this]() { selected = Album; accept(); });
    }

    ItemType selectedType() const { return selected; }

private:
    ItemType selected;
};

#endif
