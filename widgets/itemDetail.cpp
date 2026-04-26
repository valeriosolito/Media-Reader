#include "itemDetail.h"
#include <QPixmap>
#include <QDebug>
#include "header/Film.h"
#include "header/Fumetto.h"
#include "header/Album.h"
#include <QFileDialog>
#include "itemGrid.h"
#include <QTextEdit>
#include <QTextCursor>
#include <QScrollBar>

void ItemDetail::setDeleteButtonVisible(bool visible) {
    if (deleteButton)
        deleteButton->setVisible(visible);
}

void ItemDetail::setupUI(){
    setMinimumWidth(300);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    contentWidget = new QWidget();
    layout = new QVBoxLayout(contentWidget);

    cover = new QLabel(contentWidget);
    cover->setAlignment(Qt::AlignCenter);
    cover->setMinimumHeight(200);
    cover->setStyleSheet("border: 1px double #808080; background-color: black;");
    layout->addWidget(cover);
    changeCoverButton = new QPushButton("Cambia Copertina", contentWidget);
    layout->addWidget(changeCoverButton);
    changeCoverButton->hide();

    connect(changeCoverButton, &QPushButton::clicked, this, [this]() {
        QString file = QFileDialog::getOpenFileName(this, "Seleziona cover", "", "Images (*.png *.jpg *.jpeg)");
        if (!file.isEmpty()) {
            selectedCoverPath = file;
            QPixmap pix(file);
            if (!pix.isNull()) {
                cover->setPixmap(pix.scaled(200, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));

            }
        }
    });

    QLabel* nomeLabel = new QLabel("Nome:", contentWidget);
    layout->addWidget(nomeLabel);
    nomeEdit = new QLineEdit(contentWidget);
    layout->addWidget(nomeEdit);

    QLabel* descrizioneLabel = new QLabel("Descrizione:", contentWidget);
    layout->addWidget(descrizioneLabel);
    descrizioneEdit = new QTextEdit(contentWidget);
    descrizioneEdit->setReadOnly(true);
    descrizioneEdit->setFixedHeight(70);
    layout->addWidget(descrizioneEdit);

    QLabel* annoLabel = new QLabel("Anno:", contentWidget);
    layout->addWidget(annoLabel);
    annoEdit = new QSpinBox(contentWidget);
    annoEdit->setRange(1800, 2100);
    layout->addWidget(annoEdit);

    artistaLabel = new QLabel("Artista:", contentWidget);
    layout->addWidget(artistaLabel);
    artistaEdit = new QLineEdit(contentWidget);
    layout->addWidget(artistaEdit);

    labelLabel = new QLabel("Label:", contentWidget);
    layout->addWidget(labelLabel);
    labelEdit = new QLineEdit(contentWidget);
    layout->addWidget(labelEdit);

    durataLabel = new QLabel("Durata (minuti):", contentWidget);
    layout->addWidget(durataLabel);
    durataEdit = new QSpinBox(contentWidget);
    durataEdit->setRange(0, 1000);
    layout->addWidget(durataEdit);

    tracceLabel = new QLabel("Numero tracce:", contentWidget);
    layout->addWidget(tracceLabel);
    tracceEdit = new QSpinBox(contentWidget);
    tracceEdit->setRange(0, 100);
    layout->addWidget(tracceEdit);

    autoreLabel = new QLabel("Autore:", contentWidget);
    layout->addWidget(autoreLabel);
    autoreEdit = new QLineEdit(contentWidget);
    layout->addWidget(autoreEdit);

    disegnatoreLabel = new QLabel("Disegnatore:", contentWidget);
    layout->addWidget(disegnatoreLabel);
    disegnatoreEdit = new QLineEdit(contentWidget);
    layout->addWidget(disegnatoreEdit);

    editoreLabel = new QLabel("Editore:", contentWidget);
    layout->addWidget(editoreLabel);
    editoreEdit = new QLineEdit(contentWidget);
    layout->addWidget(editoreEdit);

    pagineLabel = new QLabel("Pagine:", contentWidget);
    layout->addWidget(pagineLabel);
    pagineEdit = new QSpinBox(contentWidget);
    pagineEdit->setRange(1, 5000);
    layout->addWidget(pagineEdit);

    registaLabel = new QLabel("Regista:", contentWidget);
    layout->addWidget(registaLabel);
    registaEdit = new QLineEdit(contentWidget);
    layout->addWidget(registaEdit);

    produttoreLabel = new QLabel("Produttore:", contentWidget);
    layout->addWidget(produttoreLabel);
    produttoreEdit = new QLineEdit(contentWidget);
    layout->addWidget(produttoreEdit);

    editButton = new QPushButton("Modifica", contentWidget);
    layout->addWidget(editButton);

    saveButton = new QPushButton("Salva", contentWidget);
    saveButton->hide();
    layout->addWidget(saveButton);

    deleteButton = new QPushButton("Elimina", contentWidget);
    layout->addWidget(deleteButton);

    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea);

    connect(editButton, &QPushButton::clicked, this, [this]() {
        setEditMode(true);
    });
    connect(saveButton, &QPushButton::clicked, this, [this]() {
        applyChanges();
        setEditMode(false);
    });
    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        if (currentItem)
            emit deleteRequest(currentItem);
    });
    setEditMode(false);

}

ItemDetail::ItemDetail(QWidget *parent) : QWidget(parent) {
    setupUI();
}

const Item::AbsItem* ItemDetail::getCurrentItem() const {
    return currentItem;
}

void ItemDetail::setItem(const AbsItem *prod) {
    currentItem = prod;
    selectedCoverPath.clear();
    if (!prod){
        clearDetail();
        setDeleteButtonVisible(false);
        return;
    }

    nomeEdit->setText(QString::fromStdString(prod->getNome()));
    descrizioneEdit->setPlainText(QString::fromStdString(prod->getDescrizione()));
    descrizioneEdit->moveCursor(QTextCursor::Start);
    descrizioneEdit->verticalScrollBar()->setValue(0);
    annoEdit->setValue(prod->getAnno());

    QString imgPath = QString::fromStdString(prod->getImgpath());
    QPixmap pix(imgPath);
    if (!pix.isNull()) {
        cover->setPixmap(pix.scaled(200, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        cover->setText("Nessuna immagine disponibile");
    }

    artistaLabel->setVisible(false);
    artistaEdit->setVisible(false);
    labelLabel->setVisible(false);
    labelEdit->setVisible(false);
    durataLabel->setVisible(false);
    durataEdit->setVisible(false);
    tracceLabel->setVisible(false);
    tracceEdit->setVisible(false);
    autoreLabel->setVisible(false);
    autoreEdit->setVisible(false);
    disegnatoreLabel->setVisible(false);
    disegnatoreEdit->setVisible(false);
    editoreLabel->setVisible(false);
    editoreEdit->setVisible(false);
    pagineLabel->setVisible(false);
    pagineEdit->setVisible(false);
    registaLabel->setVisible(false);
    registaEdit->setVisible(false);
    produttoreLabel->setVisible(false);
    produttoreEdit->setVisible(false);
    setDeleteButtonVisible(true);

    if ( auto album = dynamic_cast<const Item::Album*>(prod)) {

        artistaLabel->setVisible(true);
        artistaEdit->setVisible(true);
        labelLabel->setVisible(true);
        labelEdit->setVisible(true);
        durataLabel->setVisible(true);
        durataEdit->setVisible(true);
        tracceLabel->setVisible(true);
        tracceEdit->setVisible(true);

        artistaEdit->setText(QString::fromStdString(album->getArtista()));
        labelEdit->setText(QString::fromStdString(album->getLabel()));
        durataEdit->setValue(album->getDurata());
        tracceEdit->setValue(album->getTracce());
    }

    else if ( auto fumetto = dynamic_cast<const Item::Fumetto*>(prod)) {

        autoreLabel->setVisible(true);
        autoreEdit->setVisible(true);
        disegnatoreLabel->setVisible(true);
        disegnatoreEdit->setVisible(true);
        editoreLabel->setVisible(true);
        editoreEdit->setVisible(true);
        pagineLabel->setVisible(true);
        pagineEdit->setVisible(true);

        autoreEdit->setText(QString::fromStdString(fumetto->getAutore()));
        disegnatoreEdit->setText(QString::fromStdString(fumetto->getDisegnatore()));
        editoreEdit->setText(QString::fromStdString(fumetto->getEditore()));
        pagineEdit->setValue(fumetto->getPagine());

    } else if (auto film = dynamic_cast<const Item::Film*>(prod)) {

        durataLabel->setVisible(true);
        durataEdit->setVisible(true);
        registaLabel->setVisible(true);
        registaEdit->setVisible(true);
        produttoreLabel->setVisible(true);
        produttoreEdit->setVisible(true);

        durataEdit->setValue(film->getDurata());
        registaEdit->setText(QString::fromStdString(film->getRegista()));
        produttoreEdit->setText(QString::fromStdString(film->getProduttore()));

        artistaLabel->setVisible(false);
        artistaEdit->setVisible(false);
        labelLabel->setVisible(false);
        labelEdit->setVisible(false);
        autoreLabel->setVisible(false);
        autoreEdit->setVisible(false);
        disegnatoreLabel->setVisible(false);
        disegnatoreEdit->setVisible(false);
        editoreLabel->setVisible(false);
        editoreEdit->setVisible(false);
        pagineLabel->setVisible(false);
        pagineEdit->setVisible(false);
        tracceLabel->setVisible(false);
        tracceEdit->setVisible(false);

    }
    setEditMode(false);
}

void ItemDetail::applyChanges() {

    if(!currentItem) return;

    auto* mod = const_cast<Item::AbsItem*>(currentItem);
    mod->setNome(nomeEdit->text().toStdString());
    mod->setDescrizione(descrizioneEdit->toPlainText().toStdString());
    mod->setAnno(annoEdit->value());
    if (!selectedCoverPath.isEmpty()) {
        mod->setImgPath(selectedCoverPath.toStdString());

    }
    if (auto album = dynamic_cast<Item::Album*>(mod)) {
        album->setArtista(artistaEdit->text().toStdString());
        album->setLabel(labelEdit->text().toStdString());
        album->setDurata(durataEdit->value());
        album->setTracce(tracceEdit->value());

    }
    else if ( auto fumetto = dynamic_cast<Item::Fumetto*>(mod)) {
        fumetto->setAutore(autoreEdit->text().toStdString());
        fumetto->setDisegnatore(disegnatoreEdit->text().toStdString());
        fumetto->setEditore(editoreEdit->text().toStdString());
        fumetto->setPagine(pagineEdit->value());
    }
    else if (auto film = dynamic_cast<Item::Film*>(mod)) {
        film->setRegista(registaEdit->text().toStdString());
        film->setProduttore(produttoreEdit->text().toStdString());
        film->setDurata(durataEdit->value());

    }

    emit itemEdited(mod);

}

void ItemDetail::clearDetail() {
    currentItem = nullptr;
    selectedCoverPath.clear();

    cover->clear();
    cover->setText("Scegli un articolo per vedere dettagli");
    cover->setStyleSheet("border: 1px solid #ddd; border-radius: 5px; background-color: #f9f9f9; color: #888; font-style: italic;");

    nomeEdit->clear();
    descrizioneEdit->clear();
    autoreEdit->clear();
    registaEdit->clear();
    artistaEdit->clear();
    disegnatoreEdit->clear();
    editoreEdit->clear();
    labelEdit->clear();
    produttoreEdit->clear();

    annoEdit->setValue(2000);
    pagineEdit->setValue(0);
    durataEdit->setValue(0);
    tracceEdit->setValue(0);
    setEditMode(false);
    editButton->hide();
    deleteButton->hide();
}

void ItemDetail::setEditMode(bool editing){
    nomeEdit->setReadOnly(!editing);
    descrizioneEdit->setReadOnly(!editing);
    artistaEdit->setReadOnly(!editing);
    autoreEdit->setReadOnly(!editing);
    labelEdit->setReadOnly(!editing);
    disegnatoreEdit->setReadOnly(!editing);
    produttoreEdit->setReadOnly(!editing);
    editoreEdit->setReadOnly(!editing);
    annoEdit->setEnabled(editing);
    durataEdit->setEnabled(editing);
    tracceEdit->setEnabled(editing);
    pagineEdit->setEnabled(editing);
    registaEdit->setReadOnly(!editing);
    produttoreEdit->setReadOnly(!editing);
    changeCoverButton->setVisible(editing);
    editButton->setVisible(!editing);
    saveButton->setVisible(editing);
}
