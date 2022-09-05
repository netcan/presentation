/*************************************************************************
    > File Name: html.cpp
    > Author: Netcan
    > Blog: https://netcan.github.io/
    > Mail: netcan1996@gmail.com
    > Created Time: 2022-09-05 22:38
************************************************************************/
#include <iostream>
#include <ostream>
#include <algorithm>

template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }

    char value[N];
};

template<typename... LI>
struct UlTag { };

template<typename... UI>
struct OlTag { };

template<typename... Es>
struct HtmlTag { };

template<StringLiteral content>
struct LiTag { };


template<typename... E>
constexpr auto html(E...) {
    return HtmlTag<E...> {};
}

template<typename... LI>
constexpr auto ul(LI...) {
    return UlTag<LI...>{};
}

template<typename... LI>
constexpr auto ol(LI...) {
    return OlTag<LI...>{};
}

template<StringLiteral content>
constexpr auto li = LiTag<content>{};

template<StringLiteral content>
void htmlDumpper(LiTag<content>) {
    printf("<li>%s</li>\n", content.value);
}

template<typename... LI>
void htmlDumpper(UlTag<LI...>) {
    puts("<ul>");
    (htmlDumpper(LI{}), ...);
    puts("</ul>");
}

template<typename... LI>
void htmlDumpper(OlTag<LI...> ol) {
    puts("<li>");
    (htmlDumpper(LI{}), ...);
    puts("</li>");
}

template<typename... E>
void htmlDumpper(HtmlTag<E...>) {
    puts("<html>");
    (htmlDumpper(E{}), ...);
    puts("</html>");
}

int main(int argc, char** argv) {
    constexpr auto v = html(ul( li<"Coffee">
                              , li<"Tea">
                              , li<"Milk">),
                            ol( li<"hello">,
                                li<"world">));
    htmlDumpper(v);

    return 0;
}
