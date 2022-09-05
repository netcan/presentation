/*************************************************************************
    > File Name: html.cpp
    > Author: Netcan
    > Blog: https://netcan.github.io/
    > Mail: netcan1996@gmail.com
    > Created Time: 2022-09-05 22:38
************************************************************************/
#include <string_view>
#include <iostream>
#include <ostream>
#include <vector>
#include <variant>

struct LiTag {
    std::string_view content;
};

struct UlTag {
    template<typename... Args>
    UlTag(Args... arg) {
        (liTag_.emplace_back(arg), ...);
    }
    std::vector<LiTag> liTag_;
};

struct OlTag {
    template<typename... Args>
    OlTag(Args... arg) {
        (liTag_.emplace_back(arg), ...);
    }
    std::vector<LiTag> liTag_;
};


struct HtmlTag {
    template<typename... Es>
    HtmlTag(Es... es) {
        (elems_.emplace_back(es), ...);
    }
    using Elem = std::variant<UlTag, OlTag>;
    std::vector<Elem> elems_;
};


template<typename... E>
auto html(E... e) {
    return HtmlTag { e... };
}

template<typename... LI>
auto ul(LI... li) {
    return UlTag { li... };
}

template<typename... LI>
auto ol(LI... li) {
    return UlTag { li... };
}

auto li(std::string_view vs) {
    return LiTag { vs };
}

struct HtmlDumpper {
    void operator()(const LiTag& li) const {
        os << "<li>" << li.content << "</li>\n";
    }

    void operator()(const UlTag& ul) const {
        os << "<ul>\n";
        for (const auto& li: ul.liTag_)
            (*this)(li);
        os << "</ul>\n";
    }

    void operator()(const OlTag& ol) const {
        os << "<li>\n";
        for (const auto& li: ol.liTag_)
            (*this)(li);
        os << "</li>\n";
    }

    void operator()(const HtmlTag& html) const {
        os << "<html>\n";
        for (const auto& es: html.elems_)
            std::visit(*this, es);
        os << "</html>\n";
    }

    std::ostream& os;
};

int main(int argc, char** argv) {
    auto v = html(ul( li("Coffee")
                    , li("Tea")
                    , li("Milk")),
                  ol( li("hello"),
                      li("world")));

    HtmlDumpper{std::cout}(v);

    return 0;
}
