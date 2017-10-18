#pragma once

#include <string>
#include <string_view>
#include <map>
#include <vector>

namespace stemplr
{
    template<typename Ch = char>
    class Template
    {
    public:
        using String_t = std::basic_string<Ch>;
        using View_t = std::basic_string_view<Ch>;
        using SubMap_t = std::map<View_t, String_t>;

        Template(View_t templateStr);

        Template(const Template&) = default;
        Template(Template&&) = default;

        Template& operator=(const Template&) = default;
        Template& operator=(Template&&) = default;

        ~Template() = default;

        String_t run(const SubMap_t& map) const;
        Template<Ch> partial(const SubMap_t& map) const;

    private:
        using Stream_t = std::basic_ostringstream<Ch>;

        Template(std::vector<String_t> parts);

        template<typename Out>
        void run(const SubMap_t& map, Out& out, View_t (*valueFunc)(View_t, const SubMap_t&)) const;

        void preprocess(View_t templateStr);

        std::vector<String_t> parts;

        static bool isVar(View_t str);
        static View_t key(View_t str);
        static View_t value(View_t str, const SubMap_t& map);
        static View_t valueSkipMissing(View_t str, const SubMap_t& map);
    };
}

#include "stemplr.tpp"
