#ifndef ITEMDETAIL_H
#define ITEMDETAIL_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include "header/AbsItem.h"
#include "visitors/visitor.h"
#include <QTextEdit>

class ItemDetail : public QWidget{
    Q_OBJECT

private:
    QLabel* cover;
    QLineEdit* nomeEdit;
    QTextEdit* descrizioneEdit;
    QSpinBox* annoEdit;
    QLineEdit* artistaEdit;
    QLineEdit* labelEdit;
    QSpinBox* durataEdit;
    QSpinBox* tracceEdit;
    QPushButton* editButton;
    QPushButton* saveButton;
    QPushButton* deleteButton;
    QVBoxLayout* layout;
    QWidget* contentWidget;
    QScrollArea* scrollArea;
    QPushButton* changeCoverButton;
    QString selectedCoverPath;
    QLabel* artistaLabel;
    QLabel* labelLabel;
    QLabel* durataLabel;
    QLabel* tracceLabel;
    QLineEdit* autoreEdit;
    QLabel* autoreLabel;
    QLineEdit* disegnatoreEdit;
    QLabel* disegnatoreLabel;
    QLabel* editoreLabel;
    QLineEdit* editoreEdit;
    QLabel* pagineLabel;
    QSpinBox* pagineEdit;
    QLabel* registaLabel;
    QLineEdit* registaEdit;
    QLabel* produttoreLabel;
    QLineEdit* produttoreEdit;


    const Item::AbsItem* currentItem = nullptr;

    void setupUI();
    void setEditMode(bool);
    void applyChanges();

public:
    const Item::AbsItem* getCurrentItem() const;

    ItemDetail(QWidget* parent = nullptr);
    void setItem(const Item::AbsItem* prod);
    void clearDetail();
    void setDeleteButtonVisible(bool visible);



signals:
    void deleteRequest(const Item::AbsItem* item);
    void itemEdited(Item::AbsItem* newItem);
};



#endif
