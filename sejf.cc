#include "sejf.h"

Sejf::Sejf(const std::string_view &napis, unsigned liczbaDostepow):
    napis__(napis),
    liczbaDostepow__(liczbaDostepow)
{
}


int16_t Sejf::operator[](const size_t index)
{
    if (index >= napis__.length())
        return -1;
    if (liczbaDostepow__ == 0) {
        wlamanie__ = true;
        return -1;
    }
    --liczbaDostepow__;
    return static_cast<unsigned char>(napis__[index]);
}


Sejf & Sejf::operator*=(const unsigned int mnoznik)
{
    decltype(liczbaDostepow__) tmp = mnoznik * liczbaDostepow__;
    if (tmp >= liczbaDostepow__)
        zmanipuluj_(tmp);
    return *this;
}


Sejf & Sejf::operator+=(const unsigned int delta)
{
    decltype(liczbaDostepow__) tmp = delta + liczbaDostepow__;
    if (tmp >= liczbaDostepow__)
        zmanipuluj_(tmp);
    return *this;
}


Sejf & Sejf::operator-=(const unsigned int delta)
{
    if (delta <= liczbaDostepow__)
        zmanipuluj_(liczbaDostepow__ - delta);
    return *this;
}



Kontroler::Kontroler(const class Sejf &sejf):
        sejf__(sejf)
{
}


Kontroler::operator bool() const
{
    return sejf__.liczbaDostepow__ > 0;
}


std::ostream &operator<<(std::ostream &stream, const Kontroler &kontroler)
{
    if (kontroler.sejf__.wlamanie__)
        stream << "ALARM: WLAMANIE\n";
    if (kontroler.sejf__.zmanipulowany__)
        stream << "ALARM: ZMANIPULOWANY\n";
    if (!kontroler.sejf__.zmanipulowany__ && !kontroler.sejf__.wlamanie__)
        stream << "OK\n";
    return stream;
}

