#ifndef JSONFILE_H
#define JSONFILE_H

#include <string>
#include <vector>
#include "header/AbsItem.h"
#include "Json.h"

namespace Json {

    class JsonFile{
        private:
        std::string path;
        json& converter;

        public:

        JsonFile(const std::string& path, json& converter);
        static JsonFile fromPath(const std::string& path);
        const std::string& getPath() const;
        JsonFile& setPath(const std::string& path);
        const json& getConverter() const;
        JsonFile& store(const std::vector<const Item::AbsItem*>& items);
        std::vector<Item::AbsItem*> load();
    };

}

#endif // JSONFILE_H
