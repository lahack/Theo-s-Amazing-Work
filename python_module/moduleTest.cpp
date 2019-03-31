#include <string>
#include <vector>
#include <iostream>

#include "Language.h"

using namespace std;

int main() {
    string text = "GOOGLE, headquartered in Mountain View, unveiled the new Android phone at the Consumer Electronic Show.  Sundar Pichai said in his keynote that users love their new Android phones.";
    vector<string> vec;

    // Pushes to vec
    vec.push_back("GOOGLE");
    vec.push_back("Mountain View");

    Language lang("/Users/lihanzhu/Desktop/lahacks/Cloud/service-account.json");

    cout << lang.checkEntities(text, vec) << endl;;

    return 0;
}