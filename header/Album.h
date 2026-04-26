#ifndef ALBUM_H
#define ALBUM_H

#include "AbsItem.h"
#include <string>
using std::string;
namespace Item{
    class Album: public AbsItem{
        private:
        string Artista;
        string Label;
        unsigned int Durata;
        unsigned int Tracce;

        public:
        Album(unsigned int id, string nome, string descrizione, string imgpath, unsigned int anno, string artista, string label, unsigned int durata, unsigned int tracce);
        
        const string& getArtista() const;
        const string& getLabel() const;
        unsigned int getDurata() const;
        unsigned int getTracce() const;

        Album& setArtista(const string& artista);
        Album& setLabel(const string& label);
        Album& setDurata(unsigned int durata);
        Album& setTracce(unsigned int tracce);

        virtual void accept(Visitor::IVisitor& visitor) final;
        virtual void acceptconst(Visitor::IConstVisitor& constvisitor) const final;


    };
}
#endif