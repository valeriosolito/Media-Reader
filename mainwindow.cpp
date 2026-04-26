#include "mainwindow.h"
#include "qapplication.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
#include "qlabel.h"
#include "qstatusbar.h"
#include "widgets/classPanel.h"
#include "widgets/itemDetail.h"
#include "widgets/itemGrid.h"
#include "widgets/addItem.h"
#include "header/Album.h"
#include "header/Film.h"
#include "header/Fumetto.h"
#include "JSon/JsonFile.h"
#include "JSon/Json.h"
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <QToolBar>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setupUI();
    connectSignals();
    itemGrid->showProductsByClass("All");
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {

    setWindowTitle("Medias");
    resize(1100, 800);

    QToolBar* toolbar = addToolBar("Main Toolbar");
    toolbar->setMovable(false);

    QAction* loadFileAction = toolbar->addAction(QIcon(":/icons/interface/load.png"), "Load File");
    QAction* saveFileAction = toolbar->addAction(QIcon(":/icons/interface/save.png"), "Save File");
    QAction* newFileAction = toolbar->addAction(QIcon(":/icons/interface/new.png"), "New File");

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolbar->addWidget(spacer);


    QAction* addItemAction = toolbar->addAction(QIcon(":/icons/interface/add.png"),"Add item");
    QAction* infoAction = toolbar->addAction(QIcon(":/icons/interface/shortcuts.png"), "Help");
    QAction* quitAction = new QAction("Quit", this);
    toolbar->addAction(quitAction);
    toolbar->setStyleSheet("QToolBar { border-bottom:1px solid gray;}");

    addToolBarBreak();

    QToolBar* toolbar2 = addToolBar("Search Toolbar");
    toolbar2->setMovable(false);

    QLabel* searchLabel = new QLabel("Cerca: ", this);
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca per nome");
    searchBar->setClearButtonEnabled(true);
    searchBar->setMaximumWidth(400);

    toolbar2->addWidget(searchLabel);
    toolbar2->addWidget(searchBar);

    connect(infoAction, &QAction::triggered, this, [this]() {
        QString shortcutsText =
            "Shortcut da Tastiera:\n"
            "Ctrl+O - Apri File\n"
            "Ctrl+S - Salva con Nome\n"
            "Ctrl+I - Crea nuovo articolo\n"
            "Ctrl+N - Nuovo File\n"
            "Ctrl+X - Chiudi programma\n"
            "Ctrl+H - Informazioni\n";
        QMessageBox::information(this, "Shortcuts", shortcutsText);
    });

        connect(newFileAction, &QAction::triggered, this, &MainWindow::onNewFile);
        connect(loadFileAction, &QAction::triggered, this, &MainWindow::onLoadFile);
        connect(saveFileAction, &QAction::triggered, this, &MainWindow::onSaveFile);
        connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
        connect(addItemAction, &QAction::triggered, this, &MainWindow::onAddItem);
        saveFileAction->setShortcut(QKeySequence("Ctrl+S"));
        loadFileAction->setShortcut(QKeySequence("Ctrl+O"));
        infoAction->setShortcut(QKeySequence("Ctrl+H"));
        newFileAction->setShortcut(QKeySequence("Ctrl+N"));
        quitAction->setShortcut(QKeySequence("Ctrl+X"));
        addItemAction->setShortcut(QKeySequence("Ctrl+I"));

        addAction(quitAction);

        QWidget* central = new QWidget(this);
        QVBoxLayout* mainLayout = new QVBoxLayout(central);
        mainLayout->setSpacing(0);
        mainLayout->setContentsMargins(0, 0, 0, 0);

        classPanel = new ClassPanel(this);
        classPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        mainLayout->addWidget(classPanel);

        mainSplitter = new QSplitter(Qt::Horizontal, this);
        mainSplitter->setChildrenCollapsible(false);

        itemGrid = new ItemGrid(mainSplitter);
        itemGrid->setStorage(&storage);

        itemDetail = new ItemDetail(mainSplitter);
        itemDetail->setMaximumWidth(350);
        itemDetail->setMinimumWidth(300);
        itemGrid->setDetailView(itemDetail);

        mainSplitter->addWidget(itemGrid);
        mainSplitter->addWidget(itemDetail);

        mainSplitter->setStretchFactor(0, 3);
        mainSplitter->setStretchFactor(1, 1);

        mainLayout->addWidget(mainSplitter);

        setCentralWidget(central);

        setStyleSheet(R"(
        QMainWindow {
            background-color: #000000;
        }

        QWidget {
            background-color: #000000;
            color: #007acc;
            font-family: 'afta serif', serif , sans-serif;
            font-size: 14px;
        }

        QPushButton {
            background-color: #000000;
            border: 1px solid #007acc;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: 500;
        }

        QToolBar {
        border: 1px solid #808080;
        border-radius: 4px;
        background-color: #000000;
        spacing: 5px;
        padding: 4px;
        }


        QPushButton:hover {
            background-color: #1a1a1a;
            border-color: 1px solid #007acc;
        }

        QPushButton:pressed {
            background-color: #007acc;
        }

        QLabel {
            color: #007acc;
            border: 1px solid #808080;
            border-radius: 4px;
            padding: 4px;
            background-color: #1a1a1a;
        }

        QLineEdit {
            background-color: #1a1a1a;
            border: 1px solid #808080;
            border-radius: 4px;
            padding: 6px;
            color: #ffffff;
            selection-background-color: #007acc;
        }

        QLineEdit:focus {
            border: 2px solid #007acc;
        }

        QScrollArea {
            background-color: #1a1a1a;
            border: 1px solid #808080;
            border-radius: 8px;
        }

        QSplitter::handle {
            background-color: #808080;
            width: 2px;
            height: 2px;
        }

        QSplitter::handle:hover {
            background-color: #808080;
        }

        QGroupBox {
            border: 1px solid #808080;
            border-radius: 6px;
            margin-top: 1ex;
            padding-top: 10px;
            background-color: #1a1a1a;
            color: #007acc;
            font-weight: bold;
        }

        QSpinBox {
            background-color: #1e1e1e;
            color: white;
            border: 1px solid #555;
            padding-right: 20px; /* spazio per le freccette */
        }

        QSpinBox::up-button {
            subcontrol-origin: border;
            subcontrol-position: top right;
            width: 16px;
            background-color: #444;
            border-left: 1px solid #555;
            border-bottom: 1px solid #555;
        }

        QSpinBox::down-button {
            subcontrol-origin: border;
            subcontrol-position: bottom right;
            width: 16px;
            background-color: #444;
            border-left: 1px solid #555;
            border-top: 1px solid #555;
        }

        QSpinBox::up-arrow, QSpinBox::down-arrow {
            image: none;
            width: 7px;
            height: 7px;
        }

        QSpinBox::up-arrow {
            border: solid white;
            border-width: 0 2px 2px 0;
            margin: 4px;
        }

        QSpinBox::down-arrow {
            border: solid white;
            border-width: 2px 0 0 2px;
            margin: 4px;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top center;
            padding: 0 5px;
            background-color: #000000;
        }

        QTextEdit {
            background-color: #1a1a1a;
            border: 1px solid #808080;
            border-radius: 4px;
            padding: 6px;
            color: #ffffff;
        }

    )");

}

void MainWindow::connectSignals() {
    connect (classPanel, &ClassPanel::selectedType, itemGrid, &ItemGrid::showProductsByClass);
    connect (searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect (itemGrid, &ItemGrid::itemSelected, this, &MainWindow::onItemSelected);
}

void MainWindow::onSearchTextChanged(const QString& text) {
    if (text.isEmpty()) {
        itemGrid->showProductsByClass("All");
    } else {
        itemGrid->filterByNome(text);
    }
}

void MainWindow::onItemSelected(const AbsItem *item) {
    if(item) {
        qDebug() << "Item selezionato:" << QString::fromStdString(item->getNome());
    }
}

void MainWindow::refreshUi(const AbsItem *editedItem) {
    if(!editedItem) return;

    itemGrid->showProductsByClass("All");

    if(itemDetail->getCurrentItem() &&
       itemDetail->getCurrentItem()->getId() == editedItem->getId()) {
        itemDetail->setItem(editedItem);
    }
}

void MainWindow::onLoadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Apri file JSON", "" , "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Errore", "Impossibile aprire file.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        QMessageBox::warning(this, "Errore Parsing", error.errorString());
        return;
    }

    storage.clear();
    QJsonObject root = doc.object();
    QJsonArray items = root["items"].toArray();

    for (const auto& val : items) {
        QJsonObject obj = val.toObject();
        std::string tipo = obj["tipo"].toString().toStdString();

        unsigned int id = obj["id"].toInt();
        std::string nome = obj["nome"].toString().toStdString();
        std::string descrizione = obj["descrizione"].toString().toStdString();
        std::string imgpath = obj["imgpath"].toString().toStdString();
        unsigned int anno = obj["anno"].toInt();

        Item::AbsItem* prodotto = nullptr;

        try {
            if (tipo == "fumetto") {
                std::string autore = obj["autore"].toString().toStdString();
                std::string disegnatore = obj["disegnatore"].toString().toStdString();
                unsigned int pagine = obj["pagine"].toInt();
                std::string editore = obj["editore"].toString().toStdString();

                prodotto = new Item::Fumetto(id, nome, descrizione, imgpath, anno, autore, disegnatore, pagine, editore);

            } else if (tipo == "film") {
                std::string regista = obj["regista"].toString().toStdString();
                std::string produttore = obj["produttore"].toString().toStdString();
                unsigned int durata = obj["durata"].toInt();

                prodotto = new Item::Film(id, nome, descrizione, imgpath, anno, regista, produttore, durata);

            } else if (tipo == "album") {
                std::string artista = obj["artista"].toString().toStdString();
                std::string label = obj["label"].toString().toStdString();
                unsigned int durata = obj["durata"].toInt();
                unsigned int tracce = obj["tracce"].toInt();

                prodotto = new Item::Album(id, nome, descrizione, imgpath, anno, artista, label, durata, tracce);

            }
        } catch (const std::invalid_argument& e) {
            qWarning() << "Articolo invalido:" << QString::fromStdString(e.what());
            delete prodotto;
            continue;
        }

        if (prodotto) {
            storage.add(prodotto);
        }
    }
    itemGrid->showProductsByClass("All");
}

void MainWindow::onNewFile() {
    QMessageBox::StandardButton risposta = QMessageBox::question(
        this,
        "Nuovo File",
        "Sei sicuro di voler creare un nuovo file?\nTutte le modifiche non salvate andranno perse.",
        QMessageBox::Yes | QMessageBox::No
        );

    if (risposta == QMessageBox::No)
        return;
    storage.clear();
    searchBar->clear();
    itemDetail->clearDetail();
    itemGrid->showProductsByClass("All");
    itemDetail->setDeleteButtonVisible(false);
}

void MainWindow::onSaveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Salva file JSON", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;

    std::string path = fileName.toStdString();

    static Json::Reader reader;
    static Json::json converter(reader);
    Json::JsonFile Jfile(path, converter);
    try {
        Jfile.store(storage.getAll());
        statusBar()->showMessage("File salvato correttamente", 2000);
        qDebug() << "Saved to:" << fileName;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Errore", QString("Errore salvataggio: %1").arg(e.what()));
    }
}

void MainWindow::onDeleteItem(const AbsItem *item) {
    if(!item) return;

    const unsigned int id = item->getId();
    QString name = QString::fromStdString(item->getNome());

    auto ask = QMessageBox::question(this, "Conferma eliminazione",
                                     QString("Eliminare '%1'?").arg(name),
                                     QMessageBox::Yes | QMessageBox::No);
    if (ask == QMessageBox::Yes) {
        storage.remove(id);
        itemDetail->setItem(nullptr);
        itemGrid->showProductsByClass("All");
        itemDetail->clearDetail();
        itemDetail->setDeleteButtonVisible(false);
        statusBar()->showMessage("Articolo eliminato", 2000);
    }

}

void MainWindow::onAddItem() {
    AddItemDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted) return;

    AddItemDialog::ItemType type = dialog.selectedType();
    Item::AbsItem* newItem = nullptr;

    unsigned int id;
    do {
        id = static_cast<unsigned int>(QRandomGenerator::global()->bounded(1, 999));
    } while (storage.findId(id)); 

    switch (type) {
    case AddItemDialog::Fumetto:
        newItem = new Item::Fumetto(id, "Untitled", "Descrizione Vuota" ,"/icons/interface/qmark.png", 2025 , "Inserisci Autore", "Inserisci Disegnatore", 150 , "Inserisci Editore");
        break;
    case AddItemDialog::Film:
        newItem = new Item::Film(id, "Untitled", "Descrizione Vuota" ,"/icons/interface/qmark.png", 2025 , "Inserisci Regista", "Inserisci Produttore", 120);
        break;
    case AddItemDialog::Album:
        newItem = new Item::Album(id, "Untitled", "Descrizione Vuota" ,"/icons/interface/qmark.png", 2025 , "Inserisci Artista","Inserisci Label", 60 , 10);
        break;
    default:
        return;
    }

    if (newItem) {
        storage.add(newItem);
        itemGrid->showProductsByClass("All");
        itemDetail->setItem(newItem);
        itemDetail->setDeleteButtonVisible(true);
    }
}

