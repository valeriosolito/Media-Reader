#ifndef JSON_H
#define JSON_H

#include <QJsonObject>
#include "ItemReader.h"
#include "header/AbsItem.h"

namespace Json{
    class json{
        private:
        Reader& reader;
        public:
        json(Reader& reader);
        Reader& getReader() const;
        QJsonObject fromObject(const Item::AbsItem& item) const;
        Item::AbsItem* toObject(const QJsonObject& json) const;

};
}
#endif
