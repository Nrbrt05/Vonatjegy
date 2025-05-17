/**
 *
 * \file string5.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C++ nem OO eszközeinek felhasználásával készített String-kezelő
 * függvényke neveit.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a string5.h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetőknek kell lenniük)
 * *
 * A teszteléskor ne felejtse el beállítani a string5.h állományban az ELKESZULT makrót.
 *
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez
#include <iomanip>

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterből (createString)
String::String(const char ch) {
  len = 1;
  this->pData = new char[len+1];
  this->pData[0] = ch;
  this->pData[1] = '\0';
}
///                egy nullával lezárt char sorozatból (createString)
String::String(const char *p) {
  len = strlen(p);
  pData = new char[len+1];
  strcpy(pData, p);
}

/// Másoló konstruktor: String-ből készít (createString)
String::String(const String& str) {
    if(str.pData == NULL) {
        pData = NULL;
        len = 0;
        return;
    }
    len = str.size();
    pData = new char[len+1];
    strcpy(pData , str.pData);
    pData[len] = '\0';
}

/// Destruktor (disposeString)
    String::~String()  {
        delete[] this->pData;
    }

/// operator=
    String& String::operator=(const String& str){
        if (pData == str.pData)
            return *this;
        if (str.pData == NULL)
            return *this;
        delete[] pData;
        len = str.size();
        pData = new char[len+1];
        strcpy(pData , str.pData);
        pData[len] = '\0';
        return *this;
    }
/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!
    char& String::operator[](unsigned int idx) {
        if (idx > this->len - 1 || idx < 0)
            throw "R89TY7";
        return this->pData[idx];
    }
/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
///                 String-hez String-et ad (addString)
    String String::operator+(const String& str)const{
    String res;
    res.len = this->len + str.size();
    res.pData = new char[res.len + 1];
    strcpy(res.pData , this->pData);
    strcat(res.pData , str.c_str());
    return res;
    }
    String String::operator+(const char ch) const {
    String res;
    res.len = this->len + 1;
    res.pData = new char[res.len + 1];

    if (this->pData != nullptr)
        strcpy(res.pData , this->pData);
    else
        res.pData[0] = '\0';

    res.pData[res.len - 1] = ch;
    res.pData[res.len] = '\0';
    return res;
    }

    bool String::operator!=(const String s){
        if(len == s.len && strcmp(s.c_str() , this->c_str()) == 0)
           return false;
        return true;
    }

    bool String::operator==(const String s) {
        if(len == s.len && strcmp(s.c_str() , this->c_str()) == 0)
            return true;
        return false;
    }

/// << operator, ami kiír az ostream-re
std::ostream& operator<<(std::ostream& os , const String& str){
    return os << str.c_str();
}

/// >> operátor, ami beolvas az istream-ről egy szót
std::istream& operator>>(std::istream& is, String& str) {
    str = String();       // kiürítjük a sztringet
    is >> std::ws;        // kihagyjuk a szóközöket

    char ch;
    while (is.get(ch) && !std::isspace(static_cast<unsigned char>(ch))) {
        str = str + ch;   // minden karakterrel új String-et hozunk létre
    }

    // Ha a whitespace-t olvastunk, visszarakjuk
    if (!is.eof())
        is.unget();

    return is;
}
