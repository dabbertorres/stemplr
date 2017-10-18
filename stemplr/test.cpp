#include <iostream>

#include "stemplr.hpp"

int main()
{
    stemplr::Template<> t{ "{{pronoun}} name is {{name}}" };

    stemplr::Template<>::SubMap_t subs = { {"name", "Alec"}, {"pronoun", "My"} };

    std::cout << t.run(subs) << '\n';

    subs["name"] = "C++";
    subs["pronoun"] = "Its";
    std::cout << t.run(subs) << '\n';

    subs["name"] = "programmer";
    subs["pronoun"] = "Her";
    std::cout << t.run(subs) << '\n';

    subs["name"] = "sad";
    subs["pronoun"] = "His";
    std::cout << t.run(subs) << '\n';

    subs["name"] = "Harambe";
    subs["pronoun"] = "The gorilla's";
    std::cout << t.run(subs) << '\n';

    subs["name"] = "Codey McCodeface";
    subs["pronoun"] = "My hero's";
    std::cout << t.run(subs) << '\n';

    return 0;
}
