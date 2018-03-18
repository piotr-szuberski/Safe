#ifndef JNP1_ZADANIE3_SEJF_H
#define JNP1_ZADANIE3_SEJF_H

#include <string_view>
#include <string>
#include <cinttypes>
#include <iostream>



/**
 * @brief Służy do sprawdzania stanu sejfu
 */
class Kontroler
{
    friend class Sejf;
    friend std::ostream &operator<<(std::ostream &stream,
                                    const Kontroler &kontroler);

    /// Sejf, z którym związany jest ten kontroler
    const class Sejf &sejf__;

protected:

    /**
     * @brief Tworzy kontrolera przywiązanego do zadanego sejfa.
     *
     * Żeby kontroler był poprawny, sejf nie może zostać usunięty.
     * @param sejf sejf, do którego przywiązany jest kontroler
     */
    explicit Kontroler(const class Sejf &sejf);

public:
    Kontroler() = delete;

    Kontroler(const Kontroler &other) = delete;

    Kontroler(Kontroler &&other) = default;


    /**
     * @brief Sprawdza, czy sejf ma jeszcze dostępne odczyty
     * @return <c>true</c> wtedy i tylko wtedy, gdy sejf ma jeszcze dostępne
     * odczyty.
     */
    explicit operator bool() const;
};



/**
 * @brief Klasa przechowuje podany napis z ograniczoną liczbą dostępów.
 */
class Sejf
{
    friend class Kontroler;
    friend std::ostream &operator<<(std::ostream &stream,
                                    const Kontroler &kontroler);

    /// Napis przechowywany w sejfie
    std::string napis__;

    /// Pozostała liczba dostępów do sejfu
    unsigned liczbaDostepow__;


    /// Ustawiane na <c>true</c>, gdy nastąpiła próba odczytu po wyczerpaniu
    /// dostępów
    bool wlamanie__ = false;

    /// Ustawiane na <c>true</c>, gdy z sukcesem użyto któregoś z operatorów
    /// manipulacji liczbą dostępow
    bool zmanipulowany__ = false;


protected:

    /**
     * @brief Ustawia nową wartość <c>liczbaDostepow__</c> i utrzymuje
     * zmienną <c>zmanipulowany__</c>
     * Jeżeli nowa wartość różni się od starej
     * @param nowaLiczbaDostepow
     */
    inline void zmanipuluj_(unsigned int nowaLiczbaDostepow) {
        zmanipulowany__ = true;
        liczbaDostepow__ = nowaLiczbaDostepow;
    }


public:
    /**
     * @brief Inicjalizuje sejf przechowujący podany napis.
     *
     * Sejf pozwoli na podaną parametrem <c>liczba_dostepow</c> liczbę dostępów
     * do napisu.
     * @param napis napis przechowywany w sejfie
     * @param liczbaDostepow liczba dostępow, na które pozwala sejf
     */
    explicit Sejf(const std::string_view &napis, unsigned liczbaDostepow = 42);

    Sejf(const Sejf &other) = delete;

    Sejf(Sejf &&rval) = default;

    Sejf &operator= (Sejf &&rval) = default;

    /**
     * @brief Dostęp do zawartosci sejfu.
     *
     * Pozwala na dostęp do znakow napisu przechowywanego w sejfie. O ile
     * podany <c>index</c> nie wychodzi poza zakres oraz pozostały jeszcze
     * jakieś dostępy do sejfu, zwraca znak o podanym indeksie zrzutowany na
     * <c>unsigned char</c> i zmniejsza liczbę pozostałych dostępów.
     * W przeciwnym wypadku zwraca <c>-1</c>.
     * @param index indeks znaku, który ma być zwrócony
     * @return <c>(unsigned char)c</c> (gdzie <c>c</c> -- znak o zadanym
     * indeksie) lub <c>-1</c> w przypadku braku dostępów lub niepoprawnego
     * indeksu
     */
    int16_t operator[] (size_t index);

    /**
     * @brief Mnoży pozostałą liczbę dostępów, przy czym nie może ona zmaleć.
     *
     * W przypadku, gdyby wykonanie tej operacji spowodowałoby zmniejszenie
     * pozostałej liczby dostępów, operacja nie jest wykonywana.
     *
     * Jeżeli liczba dostępnych odczytów została zmieniona, sejf uważa się za
     * zmanipulowany (i tylko wtedy).
     *
     * @param mnoznik liczba, przez którą mnożymy liczbę pozostałych operacji
     * @return referencję do zmodyfikowanego obiektu
     */
    Sejf &operator*= (unsigned int mnoznik);

    /**
     * @brief Zwiększa liczbę pozostałych dostępów
     *
     * W wyniku <em>zwiększania</em> liczba dostępów nie może się zmniejszyć.
     * Jeżeli dodanie podanej wartości spowodowałoby zmniejszenie się liczby
     * pozostałych dostępów, operacja nie jest wykonywana.
     *
     * Jeżeli liczba dostępnych odczytów została zmieniona, sejf uważa się za
     * zmanipulowany (i tylko wtedy).
     *
     * @param delta liczba, którą dodajemy do liczby pozostałych dostepów
     * @return referencję do zmodyfikowanego obiektu
     */
    Sejf &operator+= (unsigned int delta);

    /**
     * @brief Zmniejsza liczbę pozostałych dostępów
     *
     * W wyniku <em>zmniejszenia</em> liczba dostępów nie może się zmniejszyć.
     * Jeżeli dodanie podanej wartości spowodowałoby zmniejszenie się liczby
     * pozostałych dostępów, operacja nie jest wykonywana. Jeżeli
     * spowodowałoby ustawienie liczby posostałych operacji na liczbę ujemną, to
     * zostaje ona ustawiona na <c>0</c>.
     *
     * Jeżeli liczba dostępnych odczytów została zmieniona, sejf uważa się za
     * zmanipulowany (i tylko wtedy).
     *
     * @param delta liczba, którą odejmujemy od liczby pozostałych dostepów
     * @return referencję do zmodyfikowanego obiektu
     */
    Sejf &operator-= (unsigned int delta);

    /**
     * @brief Zwraca kontrolera sejfu
     * Nie ma gwarancji, że kontroler będzie jeden na obiekt.
     * @return kontrolera dla sejfu
     */
    Kontroler kontroler() const {
        return Kontroler(*this);
    }
};


#endif //JNP1_ZADANIE3_SEJF_H
