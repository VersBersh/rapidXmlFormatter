#include <cstring>
#include <iterator>
#include <sstream>
#include <string>

#include "lib/rapidxml.hpp"
#include "lib/rapidxml_print.hpp"


#if defined(_WIN32)
    #define EXPORT __declspec(dllexport)
    #define CALL_CONV __cdecl
#else
    #define EXPORT __attribute__((visibility("default")))
    #define CALL_CONV
#endif

#define RAPIDXML_NO_EXCEPTIONS


extern "C"
{
    EXPORT
    char*
    CALL_CONV
    FormatXml(const char* str, unsigned int length)
    {
        char *pChar = new char[length + 1];
        std::strncpy(pChar, str, length + 1);
        pChar[length] = 0;

        rapidxml::xml_document<> doc;
        doc.parse<0>(pChar);

        std::ostringstream result;
        std::ostream_iterator<char> it{result};
        rapidxml::print(it, doc, 0);

        auto final = result.str();
        auto sz = final.size();
        char* pBuff = new char[sz + 1];
        final.copy(pBuff, sz);
        pBuff[sz] = 0;

        delete[] pChar;

        return pBuff;
    }

    EXPORT
    void
    CALL_CONV
    Release(char* pChar)
    {
        if (pChar != nullptr)
            delete[] pChar;
        return;
    }
}

#if !defined(NDEBUG)
int main()
{
    auto s = "<w:x><w:s>yyy</w:s><w:t xml:space=\"preserve\">  </w:t></w:x>";
    auto ln = strnlen_s(s, 100);
    char *p = new char[ln+1];
    std::strncpy(p, s, ln + 1);
    p[ln] = 0;

    rapidxml::xml_document<> doc;
    doc.parse<0>(p);

    delete[] s;

}
#endif