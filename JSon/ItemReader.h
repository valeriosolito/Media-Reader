#ifndef ITEMREADER_H
#define ITEMREADER_H

#include <QJsonObject>
#include <header/AbsItem.h>
#include <map>

namespace Json{
    class Reader{
        private:
        std::map<unsigned int, Item::AbsItem*> cache;
        Item::AbsItem* readAlbum(const QJsonObject &obj) const;
        Item::AbsItem* readFilm(const QJsonObject &obj) const;
        Item::AbsItem* readFumetto(const QJsonObject &obj) const;


        public:
        Reader();
        Reader& clear();
        Item::AbsItem* read(const QJsonObject &obj);
        const std::map<unsigned int, Item::AbsItem*>& getCache() const;

    };
}
#endif
