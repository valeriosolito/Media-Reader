#ifndef JSONVISITOR_H
#define JSONVISITOR_H
#include "visitor.h"
#include "header/Album.h"
#include "header/Film.h"
#include "header/Fumetto.h"
#include <QJsonObject>

namespace Json{
    class JsonVisitor : public Visitor::IConstVisitor{
        private:
        QJsonObject object;

        public:
        JsonVisitor();
        QJsonObject getObject() const;
        void visit(const Item::Album& album);
        void visit(const Item::Film& film);
        void visit(const Item::Fumetto& fumetto);


    };
}
#endif
