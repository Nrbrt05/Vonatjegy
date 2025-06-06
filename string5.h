#ifndef STRING_H
#define STRING_H
/**
 * \file string5.h
 *
 * Ez a fájl tartalmazza a
 *   - String osztály deklarációját
 *   - az inline függvényeket. Ha valamit inline-ként akar megvalósítani,
 *     akkor azt ebbe a fájlba írja! Tipikusan a rövid kódokat szokás
 *     inline-két megvalósítani (pl: c_str).
 *     Más függvényeket ill. definíciókat ne írjon a .h fájlba!
 *
 * A C nyelven megvalósított String adatszerkezetet (string1) a 2. laboron a
 * C++ nyelv nem OO eszközeivel átalakítottuk (string2_cpp).
 *
 * Most továbblépünk és a String adatszerkezetet igazi osztállyá alakítjuk:
 * Az adatokon műveletet végző függvényeket összezárjuk az adatokkal,
 * így ezek a függvények tagfüggvényekké válnak és
 *   formálisan eltűnik az első paraméterük (s0) (ezt this-ként azért megkapják).
 * A nevük is megváltozik, mert most már az összetartozást, és a
 *   paraméterek típusára való utalást már nem a név hordozza, hanem az osztály.
 * A createString... alakú függvényekből konstruktorok keletkeznek.
 * A disposeString destruktorrá alakul át.
 * Egyes műveletvégző függvényekből pedig operátor függvény lesz.
 */

/**
 * Az Ön feladata ebben fájlban bővíteni a megkezdett deklarációt, és string5.cpp
 * fájlban pedig megvalósítani (definiálni) az osztály egyes függvényeit úgy,
 * hogy az a lenti követelményeknek eleget tegyen.
 *
 * Ahogyan halad a megvalósítással egyre több tesztesetet kell lefuttatni,
 * ezért az ELKESZULT makró értéket folyamatosan növelje a feladatsorszámoknak
 * megfelelően!
 *
 * Tanulságos a megvalósítás előtt már a megnövelt értékkel is lefordítani
 * a programot, és elemezni a kapott hibajelzést.
 *
 */

/**
 * Az ELKESZULT makró értékét a lenti feladatoknak megfelelően állítsa be,
 * azaz, sorban haladva ahol tart a feladatok megoldásában!
 * Ne hagyjon ki feladatot!
 */


/**
 * \section fel Feladat:
 * A 2. laborgyakorlaton létrehoztunk egy dinamikus sztring (String) adatszerkezet
 * és a rajta műveleteket végző függvényeket
 * A tanultakat felhasználva a string5.h és a string5.cpp állományokban definiáljon ill.
 * implementáljon egy olyan sztring (String) osztályt C++ nyelven, ami dinamikusan tárol
 * és rendelkezik az alábbi tulajdonságokkal:
 *
 *ELKESZULT értéke - feladatok:
 *  1  A paraméter nélkül hívható konstruktora üres sztringet hozzon létre!
 *     Van olyan tagfüggvénye ( size() ), ami visszaadja a sztring hosszát.
 *  2. Van olyan tagfüggvénye ( c_str() ), ami C-sztringgel, azaz nullával lezárt
 *     karaktersorozatra mutató pointerrel (const char *) tér vissza.
 *  3. Van olyan konstruktora, ami karakterből hoz létre sztringet.
 *  4. Van olyan konstruktora, ami C-sztringből (const char*) hoz létre sztringet.
 *  5. Az osztályból létrehozott objektum legyen átadható értékparaméterként!
 *  6. Támogassa a többszörös értékadást (b = a = a)!
 *  7. Legyenek olyan operátorai (operator+), amivel a sztring végéhez sztringet
 *     és karaktert is lehet fűzni!
 *  8. Lehessen karakterhez is sztringet fűzni a + operátorral!
 *  9. A tárolt a karakterek legyenek elérhetőek a szokásos módon indexeléssel!
 *     Az indexeléssel elért elem legyen használható balértékként is!
 *     A konstans objektumok is legyenek indexelhetők.
 *     Az indexelési hiba esetén dobjon const char * kivételt!
 * 10. Készítsen olyan << operátort, amivel egy sztring kiírható egy ostream típusú
 *     objektumra!
 *
 * Szorgalmi feladatok:
 * 11. Készítsen olyan fűzhető >> operátort, amivel be tud olvasni egy szót egy sztring-be!
 *     A beolvasó működjön úgy, mint a scanf %s, azaz a szó végét white space határolja!
 *     A szó eleji white space karaktereket pedig el kell dobni.
 *    *Megj: az istream wshite space kezelése a flags() tagfüggvénnyel szabályozható.
 * 12. Próbálja ki ékezetes szövegekkel is az elkészített String osztályt!
 *     Segítségül elkészítettünk egy egyszerű kódrészletet ami szavakat olvas be,
 *     majd qsort() függvénnyel rendezi azokat.
 *     Az ékezetes karakterek kódolásával kapcsolatban korábban már volt egy egyszerű
 *     szorgalmi feladat feladat. Most a rendezésen van a hangsúly.
 *     Értse meg a rendez.cpp fájlban levő kód működését és futtassa a programot!
 * 13. A setlocale függvényhívás beállítja a karakterek és sztringek összehasonlításához
 *     szükséges nyelvi környezetet (LC_COLLATE) próbálja ki! Változott a rendezési
 *     sorrend?
 */

#include <iostream>
#include <iomanip>
#include "memtrace.h"

/**
 * A String osztály.
 * A 'pData'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
 * A hosszba nem számít bele a lezáró nulla.
 *
 * Korábban a len adattag unsigned int típusú volt. Most helyette a size_t típust használjuk.
 * Ezzel a típussal tér vissza a sizeof operator is, később több helyen ezt használjuk
 * mérettípusként.

 */
class String {
    char *pData;        ///< pointer az adatra
    size_t len;         ///< hossz lezáró nulla nélkül
public:
/// Kiírunk egy Stringet (debug célokra)
/// Ezt a tagfüggvényt elkészítettük, hogy használja a hibák felderítéséhez.
/// Igény szerint módosítható
/// @param txt - nullával lezárt szövegre mutató pointer.
///              Ezt a szöveget írjuk ki a debug információ előtt.
    void printDbg(const char *txt = "") const {
        std::cout << txt << "[" << len << "], "
                  << (pData ? pData : "(NULL)") << '|' << std::endl;
    }

/// Az első két feladatot előre megoldottuk, de lehet, hogy nem jól.
/// Az üres sztring reprezentációja nem szerencsés, mert így NULL pointerré
/// konvertál a c_str(), ami külön kezelést igényel a későbbiekben.
/// Ezt a teszt program sem fogadja el.
/// Gondolja végig, és változtassa meg!
/// Két lehetőség van:
///     a) nem NULL pointert tárol, hanem ténylegesen üres sztringet.
///     b) NULL-t tárol, de a c_str() üres sztringet ad vissza helyette
///        Ebben az esetben ügyelnie kell a másolásokra (másoló kostruktor op=) is,
///        nehogy NULL pointert kapjon az strcpy!
/// Bármelyik megoldás jó, mert ez az osztály belügye.

////////////////////////////////////////////////////////////////////////////////////////
///EKLKESZULT 1-2  A paraméter nélkül hívható konstruktora üres sztringet hozzon létre!///
/// Van olyan tagfüggvénye ( size() ), ami visszaadja a sztring hosszát.             ///
    /// Paraméter nélküli konstruktor:                                               ///
    String() :pData(0), len(0) {}                                                    ///
                                                                                     ///
    /// @return sztring tényleges hossza (lezáró nulla nélkül).                      ///
    size_t size() const { return len; }                                              ///
///                                                                                  ///
/// C-sztringet ad vissza                                                            ///
/// @return pointer a tárolt, vagy azzal azonos tartalmú nullával lezárt sztring-re. ///
    const char* c_str() const {                                                      ///
        if (pData == 0) return "";                                                   ///
        return pData;                                                                ///
    }                                                                                ///
////////////////////////////////////////////////////////////////////////////////////////


/// Itt folytassa a tagfüggvények deklarációit a feladatoknak megfelelően.

/////////////////////////////////////////////////////////////////////////////////////////////
///EKLKESZULT 3-4  Van olyan konstruktora, ami karakterből hoz létre sztringet.             ///
    String(const char ch);                                                   ///
    String(const char *p);                                                   ///
    ~String();
///5. Az osztályból létrehozott objektum legyen átadható értékparaméterként!
    String(const String& str);
/// *  6. Támogassa a többszörös értékadást (b = a = a)!
    String& operator=(const String& str);
/// ELKESZULT 7-8
    String operator+(const String& str) const;
    String operator+(const char ch) const;

/// ELKESZULT 9
    char& operator[](unsigned int idx);

    bool operator!=(const String s);
    bool operator==(const String s);
}; /// Itt az osztály deklarációjának vége

/// Ide kerülnek a globális operátorok deklarációi.
std::ostream& operator<<(std::ostream& os , const String& str);

std::istream& operator>>(std::istream& is, String& str);



#endif
