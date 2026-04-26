#ifndef CLASSPANEL_H
#define CLASSPANEL_H

#include <QWidget>

class QPushButton;

class ClassPanel : public QWidget
{
    Q_OBJECT

private:
    QPushButton *btnAll;
    QPushButton *btnFumetto;
    QPushButton *btnFilm;
    QPushButton *btnAlbum;


public:
    ClassPanel(QWidget *parent = nullptr);

signals:
    void selectedType(const QString &category);

private slots:
    void onClassClick();
};

#endif
