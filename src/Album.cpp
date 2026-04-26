#include "header/Album.h"

namespace Item{
    
    Album::Album(unsigned int id, string nome, string descrizione, string imgpath, unsigned int anno, string artista, string label, unsigned int durata, unsigned int tracce ):
    AbsItem(id, nome, descrizione, imgpath, anno), Artista(artista), Label(label), Durata(durata), Tracce(tracce){}

    const string& Album::getArtista() const {
        return Artista;
    }

    const string& Album::getLabel() const {
        return Label;
    }

    unsigned int Album::getDurata() const {
        return Durata;
    }

    unsigned int Album::getTracce() const {
        return Tracce;
    }

    Album& Album::setArtista(const string& artista){
        this->Artista = artista;
        return *this;
    }

    Album& Album::setLabel(const string& label){
        this->Label=label;
        return *this;
    }

    Album& Album::setDurata(unsigned int durata){
        this->Durata=durata;
        return *this;
    }

    Album& Album::setTracce(unsigned int tracce){
        this->Tracce=tracce;
        return *this;
    }

    void Album::accept(Visitor::IVisitor& visitor){
        visitor.visit(*this);
    }

    void Album::acceptconst(Visitor::IConstVisitor& constvisitor) const {
        constvisitor.visit(*this);
    }

}
