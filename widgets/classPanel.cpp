#include "widgets/classPanel.h"
#include <QPushButton>
#include <QVBoxLayout>

ClassPanel::ClassPanel(QWidget *parent) : QWidget(parent) {

    auto layout = new QHBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    btnFumetto = new QPushButton("Fumetto", this);
    btnFilm = new QPushButton("Film", this);
    btnAlbum = new QPushButton("Album", this);
    btnAll = new QPushButton("All", this);

    btnFumetto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnAlbum->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnAll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(btnFumetto);
    layout->addWidget(btnFilm);
    layout->addWidget(btnAlbum);
    layout->addWidget(btnAll);
    layout->addStretch();

    connect(btnFumetto, &QPushButton::clicked, this, &ClassPanel::onClassClick);
    connect(btnFilm, &QPushButton::clicked, this, &ClassPanel::onClassClick);
    connect(btnAlbum, &QPushButton::clicked, this, &ClassPanel::onClassClick);
    connect(btnAll, &QPushButton::clicked, this, &ClassPanel::onClassClick);
}

void ClassPanel::onClassClick() {

    QPushButton* sendBtn = qobject_cast<QPushButton*>(sender());
    if(sendBtn) {
        emit selectedType(sendBtn->text());
    }

}
