#include "visitors/JsonVisitor.h"
namespace Json{

    JsonVisitor::JsonVisitor() {}

    QJsonObject JsonVisitor::getObject() const{
        return object;
    }

    void JsonVisitor::visit(const Item::Album& album){
    QJsonObject alb;

    alb.insert("tipo",QJsonValue::fromVariant("album"));
    alb.insert("id",QJsonValue::fromVariant(album.getId()));
    alb.insert("nome",QJsonValue::fromVariant(QString::fromStdString(album.getNome())));
    alb.insert("descrizione",QJsonValue::fromVariant(QString::fromStdString(album.getDescrizione())));
    alb.insert("imgpath",QJsonValue::fromVariant(QString::fromStdString(album.getImgpath())));
    alb.insert("anno",QJsonValue::fromVariant(album.getAnno()));
    alb.insert("artista",QJsonValue::fromVariant(QString::fromStdString(album.getArtista())));
    alb.insert("label",QJsonValue::fromVariant(QString::fromStdString(album.getLabel())));
    alb.insert("durata",QJsonValue::fromVariant(album.getDurata()));
    alb.insert("tracce",QJsonValue::fromVariant(album.getTracce()));
    

    object = alb;
    }

    void JsonVisitor::visit(const Item::Film& film){
        QJsonObject fil;

        fil.insert("tipo",QJsonValue::fromVariant("film"));
        fil.insert("id",QJsonValue::fromVariant(film.getId()));
        fil.insert("nome",QJsonValue::fromVariant(QString::fromStdString(film.getNome())));
        fil.insert("descrizione",QJsonValue::fromVariant(QString::fromStdString(film.getDescrizione())));
        fil.insert("imgpath",QJsonValue::fromVariant(QString::fromStdString(film.getImgpath())));
        fil.insert("anno",QJsonValue::fromVariant(film.getAnno()));
        fil.insert("regista",QJsonValue::fromVariant(QString::fromStdString(film.getRegista())));
        fil.insert("produttore",QJsonValue::fromVariant(QString::fromStdString(film.getProduttore())));
        fil.insert("durata",QJsonValue::fromVariant(film.getDurata()));


        object = fil;
    }

    void JsonVisitor::visit(const Item::Fumetto& fumetto){
        
        QJsonObject fum;

        fum.insert("tipo",QJsonValue::fromVariant("fumetto"));
        fum.insert("id",QJsonValue::fromVariant(fumetto.getId()));
        fum.insert("nome",QJsonValue::fromVariant(QString::fromStdString(fumetto.getNome())));
        fum.insert("descrizione",QJsonValue::fromVariant(QString::fromStdString(fumetto.getDescrizione())));
        fum.insert("imgpath",QJsonValue::fromVariant(QString::fromStdString(fumetto.getImgpath())));
        fum.insert("anno",QJsonValue::fromVariant(fumetto.getAnno()));
        fum.insert("autore",QJsonValue::fromVariant(QString::fromStdString(fumetto.getAutore())));
        fum.insert("disegnatore",QJsonValue::fromVariant(QString::fromStdString(fumetto.getDisegnatore())));
        fum.insert("pagine",QJsonValue::fromVariant(fumetto.getPagine()));
        fum.insert("disegnatore",QJsonValue::fromVariant(QString::fromStdString(fumetto.getEditore())));


        object = fum;
    }


}
