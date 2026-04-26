#ifndef AbsItem_H
#define AbsItem_H

#include <string>
#include "visitors/visitor.h"


using std::string;
namespace Item{
    class AbsItem{
        private:
        unsigned int Id;
        string Nome;
        string Descrizione;
        string Imgpath;
        unsigned int Anno;
        
        public:
        AbsItem(unsigned int id, string nome, string descrizione, string imgpath, unsigned int anno);
        virtual ~AbsItem() = default ;

        unsigned int getId() const;
        const string& getNome() const;
        const string& getDescrizione() const;
        const string& getImgpath() const;
        unsigned int getAnno() const;

        AbsItem& setId(unsigned int id);
        AbsItem& setNome(const string& nome);
        AbsItem& setDescrizione(const string& descrizione);
        AbsItem& setImgPath(const string& imgpath);
        AbsItem& setAnno(unsigned int anno);

        virtual void accept(Visitor::IVisitor& visitor) = 0;
        virtual void acceptconst(Visitor::IConstVisitor& constvisitor) const = 0;
    };
}
#endif
