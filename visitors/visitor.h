#ifndef VISITOR_H
#define VISITOR_H

namespace Item{
    class Film;
    class Fumetto;
    class Album;
}

namespace Visitor{
    class IVisitor{
        public:
        virtual ~IVisitor() = default;
        virtual void visit(Item::Film& film) = 0;
        virtual void visit(Item::Fumetto& fumetto) = 0;
        virtual void visit(Item::Album& album) = 0;
        
    };

    class IConstVisitor{
        public:
        virtual ~IConstVisitor() = default;
        virtual void visit(const Item::Film& film) = 0 ;
        virtual void visit(const Item::Fumetto& fumetto) = 0;
        virtual void visit(const Item::Album& album) = 0;
    };
   
} 
#endif