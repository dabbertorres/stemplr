#include <algorithm>
#include <sstream>

namespace stemplr
{
    // 2 consecutive instances of these signifies the start/end of a substitution
    constexpr char SUBST_START_CHAR = '{';
    constexpr char SUBST_END_CHAR = '}';

    // cheater mode
    template<typename Elem>
    std::vector<Elem>& operator<<(const Elem& el, std::vector<Elem>& vec)
    {
        vec.push_back(el);
        return vec;
    }

    template<typename Ch>
    Template<Ch>::Template(View_t templateStr)
    {
        preprocess(templateStr);
    }

    template<typename Ch>
    typename Template<Ch>::String_t Template<Ch>::run(const SubMap_t& map) const
    {
        Stream_t ss;
        run(map, ss, value);
        return ss.str();
    }

    template<typename Ch>
    Template<Ch> Template<Ch>::partial(const SubMap_t& map) const
    {
        std::vector<String_t> newParts;
        run(map, newParts, valueSkipMissing);
        return { newParts };
    }

    template<typename Ch>
    Template<Ch>::Template(std::vector<String_t> parts)
        : parts{ parts }
    {}

    template<typename Ch>
    template<typename Out>
    void Template<Ch>::run(const SubMap_t& map, Out& out, View_t(*valueFunc)(View_t, const SubMap_t&)) const
    {
        for (const auto& p : parts)
            out << valueFunc(p, map);
    }

    template<typename Ch>
    void Template<Ch>::preprocess(View_t str)
    {
        auto front = str.begin();
        for (auto it = str.begin(); it != str.end(); ++it)
        {
            if (*it == SUBST_START_CHAR && *(it + 1) == SUBST_START_CHAR)
            {
                // store (not empty) non-variable
                if (it - front > 0)
                {
                    parts.emplace_back(front, it);

                    // front of variable
                    front = it;
                }

                // find end of variable
                do
                {
                    ++it;
                }
                while (*it != SUBST_END_CHAR || *(it + 1) != SUBST_END_CHAR);

                // it now points to 2nd SUBST_END_CHAR
                ++it;

                // store variable (we want to include the 2nd SUBST_END_CHAR
                parts.emplace_back(front, it + 1);

                // new front
                front = it + 1;
            }
        }
    }

    template<typename Ch>
    bool Template<Ch>::isVar(View_t str)
    {
        return str.length() >= 2 && str[0] == SUBST_START_CHAR && str[1] == SUBST_START_CHAR;
    }

    template<typename Ch>
    typename Template<Ch>::View_t Template<Ch>::key(View_t str)
    {
        return str.substr(2, str.length() - 4);
    }

    template<typename Ch>
    typename Template<Ch>::View_t Template<Ch>::value(View_t str, const SubMap_t& map)
    {
        if (isVar(str))
            return map.at(key(str));
        else
            return str;
    }

    template<typename Ch>
    typename Template<Ch>::View_t Template<Ch>::valueSkipMissing(View_t str, const SubMap_t& map)
    {
        if (isVar(str))
        {
            auto it = map.find(key(str));
            return it != map.end() ? it->second : str;
        }
        else
            return str;
    }
}
