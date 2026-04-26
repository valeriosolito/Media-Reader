#include "ItemReader.h"
#include "header/Album.h"
#include "header/Film.h"
#include "header/Fumetto.h"
#include <QJsonValue>

namespace Json{
    Reader::Reader(){}

    Reader& Reader::clear(){
    cache.clear();
    return *this;
    }

    Item::AbsItem* Reader::read(const QJsonObject &obj){
        try{
            QJsonValue tipo = obj.value("tipo");

            if(tipo.isUndefined()){
                throw std::invalid_argument("tipo inesistente");
            }
            const unsigned int id = obj.value("Id").toInt();

            if(cache.count(id) > 0){
                return cache[id];
            }
            else if (tipo.toString().compare("fumetto")==0){
                cache[id] = readFumetto(obj);
            }
            else if (tipo.toString().compare("film")==0){
                cache[id] = readFilm(obj);
            }
            else if (tipo.toString().compare("album")==0){
                cache[id] = readAlbum(obj);
            }
            else {
                throw std::invalid_argument("Tipo non riconosciuto");
            }
            return cache[id];
        }
        catch(const std::exception& err){
            qDebug() <<"Errore Reader" << err.what();
            return nullptr;
        }
    }

    const std::map<unsigned int, Item::AbsItem*>& Reader::getCache() const{
        return cache;
    }
    
    Item::AbsItem* Reader::readAlbum(const QJsonObject &obj) const{
        if (!obj.contains("id") || !obj.contains("nome") || !obj.contains("descrizione") ||
            !obj.contains("imgpath") || !obj.contains("anno") || !obj.contains("artista") ||
            !obj.contains("label") || !obj.contains("durata") || !obj.contains("tracce")) {
            throw std::invalid_argument("Album JSON missing required fields");
        }
        return new Item::Album(
            obj.value("id").toInt(),
            obj.value("nome").toString().toStdString(),
            obj.value("descrizione").toString().toStdString(),
            obj.value("imgpath").toString().toStdString(),
            obj.value("anno").toInt(),
            obj.value("artista").toString().toStdString(),
            obj.value("label").toString().toStdString(),
            obj.value("durata").toInt(),
            obj.value("tracce").toInt()
            );
    }

    Item::AbsItem* Reader::readFilm(const QJsonObject &obj) const{
        if (!obj.contains("id") || !obj.contains("nome") || !obj.contains("descrizione") ||
            !obj.contains("imgpath") || !obj.contains("anno") || !obj.contains("regista") ||
            !obj.contains("produttore") || !obj.contains("durata")) {
            throw std::invalid_argument("Film JSON missing required fields");
        }
        return new Item::Film(
            obj.value("id").toInt(),
            obj.value("nome").toString().toStdString(),
            obj.value("descrizione").toString().toStdString(),
            obj.value("imgpath").toString().toStdString(),
            obj.value("anno").toInt(),
            obj.value("regista").toString().toStdString(),
            obj.value("produttore").toString().toStdString(),
            obj.value("durata").toInt()
            );
    }

    Item::AbsItem* Reader::readFumetto(const QJsonObject &obj) const{
        if (!obj.contains("id") || !obj.contains("nome") || !obj.contains("descrizione") ||
            !obj.contains("imgpath") || !obj.contains("anno") || !obj.contains("autore") ||
            !obj.contains("disegnatore") || !obj.contains("pagine") || !obj.contains("editore")) {
            throw std::invalid_argument("Fumetto JSON missing required fields");
        }
        return new Item::Fumetto(
            obj.value("id").toInt(),
            obj.value("nome").toString().toStdString(),
            obj.value("descrizione").toString().toStdString(),
            obj.value("imgpath").toString().toStdString(),
            obj.value("anno").toInt(),
            obj.value("autore").toString().toStdString(),
            obj.value("disegnatore").toString().toStdString(),
            obj.value("pagine").toInt(),
            obj.value("editore").toString().toStdString()
            );
    }

}
