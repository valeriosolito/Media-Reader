#include "Json.h"
#include "visitors/JsonVisitor.h"

namespace Json{

    json::json(Reader& reader): reader(reader) {}

    Reader& json::getReader() const {
    return reader;
    }

    QJsonObject json::fromObject(const Item::AbsItem& item) const{
    JsonVisitor jVisit;
    item.acceptconst(jVisit);
    return jVisit.getObject();
    }

    Item::AbsItem* json::toObject(const QJsonObject& json) const {
    return reader.read(json);
    }

}
