#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>
#include <vector>

class Language {
public:
    /* Constructor. Takes path to .json */
    Language(std::string keyPath);

    /* Checks entities,
       Returns whether all entities are found
     */
    bool checkEntities(std::string text, std::vector<std::string> entities);
    
private:
    std::string credentialPath;
};

#endif