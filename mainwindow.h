#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QLineEdit>
#include "header/ItemRepo.h"

class ClassPanel;
class ItemGrid;
class ItemDetail;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refreshUi(const Item::AbsItem* editedItem);

private:

    void createTestData();
    void connectSignals();
    void setupUI();

    ItemDetail *itemDetail;
    ClassPanel *classPanel;
    ItemGrid *itemGrid;
    QSplitter *mainSplitter;
    QLineEdit *searchBar;
    MainWindow* ui;


    Repo::ItemRepo storage;

private slots:
    void onNewFile();
    void onLoadFile();
    void onSaveFile();
    void onAddItem();
    void onDeleteItem(const Item::AbsItem* item);
    void onSearchTextChanged(const QString &text);
    void onItemSelected(const Item::AbsItem* item);

};
#endif // MAINWINDOW_H
