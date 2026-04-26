#include "JsonFile.h"
#include "ItemReader.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

namespace Json{

    JsonFile::JsonFile(const std::string& path, json& converter): path(path), converter(converter){}

    JsonFile JsonFile::fromPath(const std::string& path){
        Reader reader;
        json converter(reader);
        JsonFile datamap(path,converter);
        return datamap;
    } 

    const std::string& JsonFile::getPath() const{
        return path;
    }

    const json& JsonFile::getConverter() const{
        return converter;
    }

    JsonFile& JsonFile::setPath(const std::string& path){
        this->path = path;
        return *this;
    }

    JsonFile& JsonFile::store(const std::vector<const Item::AbsItem*>& items){
        QJsonArray jItems;

        for(auto cit=items.begin(); cit!=items.end(); cit++){
            jItems.push_back(converter.fromObject(**cit));
        }
        QJsonObject root;
        root.insert("items", jItems);
        QJsonDocument document(root);
        QFile jsonFile(QString::fromStdString(path));
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(document.toJson(QJsonDocument::Indented));
        jsonFile.close();
        return *this;

    }

}
