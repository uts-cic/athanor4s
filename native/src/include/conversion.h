
/*
*  Athanor: Le langage des Alpages m�de � Grenoble
*
*  Copyright (C) 2017: ATHANOR Language
* This file can only be used with the ATHANOR library or the executable
* it should not and cannot be used otherwise.
*/
/* --- CONTENTS ---
Project    : ATHANOR
Version    : ATANOR 0.26
filename   : conversion.h
Date       : 2017/04/01
Purpose    : 
Programmer : Claude ROUX
Reviewer   :
*/

#ifndef conversion_h
#define conversion_h

#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <map>

#include "binmap.h"

using std::stringstream;
using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::list;
using std::ios;
using std::ostream;
using std::istream;
using std::fstream;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ostringstream;

#if defined(WIN32) || defined(MAVERICK)
#include <unordered_map>
#define hmap unordered_map
using std::unordered_map;
#else
#include <tr1/unordered_map>
#define hmap std::tr1::unordered_map
#endif

#ifdef WIN32
#define Endl "\r\n"
#else
#define Endl "\n"
#endif

#define uchar unsigned char
#define STR(x) (char*)x.c_str()
#define USTR(x) (uchar*)x.c_str()
#define WSTR(x) (wchar_t*)x.c_str()


#ifndef Exporting
#if defined(WIN32)
#ifdef ATANORSTATIC
#define Exporting
#define Exchanging
#else
#define Exporting __declspec(dllexport)
#ifdef ATANORDLL
#define Exchanging __declspec(dllimport)
#else
#define Exchanging __declspec(dllexport)
#endif
#endif
#else
#define Exporting
#define Exchanging
#endif
#endif

#define BULONG unsigned long long
#define BLONG long long

const short token_comma = 1;
const short token_separator = 2;
const short token_period = 4;
const short token_keepwithdigit = 8;
const short token_keeprc = 16;

using std::wstring;

union bulongchar {
	BULONG val;
	unsigned char ustr[8];
	char str[8];
	bulongchar() {
		memset(str, 0, 8);
	}
	void clear() {
		memset(str, 0, 8);
	}
};

//--------------------- Main Initialization, to be launched before using any of the following methods...
Exporting void inittableutf8();

//--------------------- Code Indention
void IndentCode(string& codestr, string& codeindente, int blancs, const char* kifelse = "else", const char* kifelif = "elif", const char* kifif = "if");
Exporting void IndentationCode(string& codeindente, vector<string>& code, vector <int>& blancs, int mxbase, bool construit, const char* kifelse = "else", const char* kifelif = "elif", const char* kifif = "if");
int VirtualIndentation(string& codestr, const char* kifelse, const char* kifelif, const char* kifif);

//--------------------- Carriage Return normalisation
void cr_normalise(string& code);

//--------------------- Trimming strings
Exporting string& Trim(string& chaine);
Exporting string& Trimleft(string& chaine);
Exporting string& Trimright(string& chaine);

Exporting wstring& Trim(wstring& chaine);
Exporting wstring& Trimleft(wstring& chaine);
Exporting wstring& Trimright(wstring& chaine);

//--------------------- Digits conversion

Exporting BLONG conversionintegerhexa(char* number);
Exporting double conversionfloat(char* s);
Exporting double convertfloat(char* s);
Exporting double convertfloat(wstring value);
Exporting long convertinteger(wstring value);
Exporting double convertfloat(string value);
Exporting long convertinteger(string value);

Exporting double convertdouble(wstring value);
Exporting long convertlong(wstring value);
Exporting double convertdouble(string value);
Exporting long convertlong(string value);

//--------------------- Conversions
Exporting bool valid_latin_table(int table);

void s_EvaluateMetaCharacters(string& s);

Exporting bool s_is_utf8(unsigned char* contenu, int longueur);

Exporting char s_is_pure_utf8(unsigned char* contenu, int longueur);
Exporting char c_detect_utf8(unsigned char* utf);
Exporting char c_test_utf8(unsigned char* utf);

Exporting string c_unicode_to_utf8(wchar_t code);

Exporting string s_unicode_to_utf8(BULONG code);
Exporting string s_utf8_to_dos(unsigned char* contenu);
Exporting string s_dos_to_utf8(unsigned char* contenu);
Exporting string s_utf8_to_dos(const char* contenu);
Exporting string s_dos_to_utf8(const char* contenu);

Exporting void s_unicode_to_utf8(string& s, wchar_t* str);
Exporting void s_unicode_to_utf8(string& s, wstring& str);
Exporting void s_unicode_to_utf8(BULONG code, char* utf);
Exporting void s_utf8_to_unicode(wstring& s, char* str);
Exporting void s_doubleutf8_to_unicode(wstring& s, wchar_t* str);
Exporting void c_latin_to_utf8(unsigned char code, unsigned char* utf);

Exporting BULONG c_latin_table_to_unicode(int table, BULONG c);
Exporting BULONG c_unicode_to_latin(BULONG u);

//--------------------- Conversion with the recipient string cleared
Exporting void sc_unicode_to_utf8(string& s, wstring& str);
Exporting void sc_utf8_to_unicode(wstring& s, char* str);

//--------------------- Character conversion
Exporting void c_HTMLcode(string& s, BULONG code);
Exporting void c_XMLcode(string& s, BULONG code);
Exporting bool c_utf8_to_latin(unsigned char* utf, unsigned char& code);
Exporting int c_utf8_to_unicode(unsigned char* utf, BULONG& code);
Exporting int c_unicode_to_utf8(BULONG code, unsigned char* utf);
Exporting int c_lookforUTF8(unsigned char* contenu, int longueur);

//--------------------- String conversion
Exporting unsigned char conversion_utf8_to_latin(short);
Exporting string conversion_utf8_to_latin(string contenu);
Exporting string conversion_latin_to_utf8(string contenu);
Exporting string conversion_latin_to_utf8(unsigned char* contenu);
Exporting string conversion_utf8_to_latin(unsigned char* contenu);

Exporting string conversion_latin_table_to_utf8(int, unsigned char* contenu);
Exporting wstring conversion_latin_table_to_unicode(int table, unsigned char* contenu);

Exporting int conversion_utf8_to_fat(unsigned char* contenu, vector<string>& l);

Exporting char* s_utf8_to_latin(char* str);
Exporting void s_latin_to_utf8(string& res, unsigned char* contenu);

//---------------------Korean Manipulation
bool s_is_hangul(wstring& w);
bool s_is_jamo(wstring& w);
wstring s_split_jamo(wstring& w);
wstring s_combine_jamo(wstring& w);
bool c_is_hangul(wchar_t c);
bool c_is_hangul(unsigned char* m, int& i);
wstring s_hangul_normalize(wstring& w);
string c_translate(wchar_t c);
string c_translate(unsigned char* m, int& i);
//--------------------- UNICODE Manipulation
Exporting bool b_alpha(BULONG c);

Exporting bool c_is_space(BULONG c);
Exporting bool c_is_punctuation(BULONG c);
Exporting bool c_is_digit(BULONG code);
Exporting bool c_is_lower(BULONG code);
Exporting bool c_is_upper(BULONG code);

Exporting char c_is_alpha(BULONG c);

Exporting BULONG c_to_lower(BULONG c);
Exporting BULONG c_to_upper(BULONG c);

Exporting bool c_is_emoji(BLONG c);
Exporting string Emoji(BLONG c);
Exporting string Emoji(string&);
Exporting string Emoji(wstring& s);
Exporting bool s_is_emoji(string s);
Exporting bool s_is_emoji(wstring& s);
Exporting void l_emojis(map<BLONG, string>& dico);

//--------------------- Character manipulation
Exporting void c_to_lower(string&, unsigned char* s, int lg);
Exporting void c_to_upper(string&, unsigned char* s, int lg);

Exporting char c_is_alpha(unsigned char* m, int& i);

Exporting string c_latin_utf8(int c);

//--------------------- String manipulation
Exporting bool s_is_upper(string s);
Exporting bool s_is_alpha(string s);
Exporting bool s_is_lower(string s);
Exporting bool s_is_digit(string& str);
Exporting bool s_is_punctuation(string& str);
Exporting bool s_is_space(string& str);


Exporting bool s_is_punctuation(wstring& str);
Exporting bool s_is_alpha(wstring& s);
Exporting bool s_is_upper(wstring& s);
Exporting bool s_is_lower(wstring& s);
Exporting bool s_is_vowel(wstring& s);
Exporting bool s_is_consonant(wstring& s);
Exporting bool s_is_digit(wstring& str);

Exporting bool s_is_consonant(unsigned char* s);
Exporting bool s_is_vowel(unsigned char* s);

Exporting string s_to_lower(string s);
Exporting string s_to_upper(string s);
Exporting string s_deaccentuate(unsigned char* s);

Exporting wstring s_to_upper(wstring& s);
Exporting wstring s_to_lower(wstring& s);
Exporting wstring s_deaccentuate(wstring& s);

Exporting char s_is_number(unsigned char* str, char decimal, long& l, double& f);
Exporting void s_binary(unsigned char* s, int mx, int lg, BULONG* codes);

//--------------------- Finding or replacing
Exporting char* strrstr(char* str, char* sub, long sz, long szsub);
Exporting wchar_t* wcsrstr(wchar_t* str, wchar_t* sub, long sz, long szsub);
Exporting void s_findall(string& s, string& substr, vector<long>& v);
Exporting void s_findall(wstring& s, wstring& substr, vector<long>& v);
Exporting void s_findall(char* s, char* substr, vector<long>& v);

Exporting long s_findbyte(string& s, string& substr, long i);
Exporting long s_rfindbyte(string& s, string& substr, long i);
Exporting int s_find(unsigned char* s, string fd, int pos);
Exporting int s_find(string& s, string fd, int pos);
Exporting int s_rfind(unsigned char* s, string fd, int pos);
Exporting int s_rfind(string& s, string fd, int pos);
Exporting int s_find(wstring& s, wstring substr, int i);
Exporting int s_rfind(wstring& s, wstring substr, int pos);

//--------------------- Extracting substring
Exporting string s_left(string& s, int nb);
Exporting string s_right(string& s, int nb);
Exporting string s_middle(string& s, int g, int nb);

Exporting string s_replacestring(string& s, string& r, string& rep);
Exporting string s_replacestrings(string& s, string r, string rep);

Exporting string s_insert_sep(string s, string sep);
Exporting string s_insert_sep_byte(string& s, string sep);
Exporting string s_char_reverse(string& s, int& length);
Exporting string s_revert(string& s);

Exporting wstring s_left(wstring& s, int nb);
Exporting wstring s_right(wstring& s, int nb);
Exporting wstring s_middle(wstring& s, int l, int nb);
Exporting wstring s_replacestring(wstring& str, wstring reg, wstring rep);

Exporting wstring s_revert(wstring& s);


Exporting int size_c(string& s);
Exporting int size_c(const char* s);

Exporting void s_split(string& s, string& splitter, vector<string>& strs, bool keepblanks = false);
Exporting void s_split(wstring& s, wstring& splitter, vector<wstring>& strs, bool keepblanks = false);
Exporting void v_split(string& thestr, string thesplitter, vector<string>& v);
Exporting void v_split_indent(string& thestr, vector<string>& v);

//--------------------- Character extraction from potential UTF8 string-----------------
Exporting short c_char_get_wide(unsigned char* m, int& i);

Exporting unsigned char c_utf8_latin(string s);

Exporting int c_code_get(unsigned char* m, int& i, BULONG& code);
Exporting int c_chartobyteposition(unsigned char* contenu, int charpos);
Exporting int c_bytetocharposition(unsigned char* contenu, int charpos);
Exporting int c_chartobytepositionidx(unsigned char* contenu, int charpos, int& nb, int& i);
Exporting int c_bytetocharpositionidx(unsigned char* contenu, int charpos, int& nb, int& i);
Exporting int c_char_next(unsigned char* m, int& i);

Exporting string c_char_index(string& s, size_t i);
Exporting string c_char_index_remove(string& s, size_t i);

Exporting bool c_char_index_assign(string& s, string c, int i);
Exporting bool c_char_index_insert(string& s, string c, size_t i);

Exporting BULONG c_char_index_code(string& s, size_t i);

Exporting void c_get_utf8_char(short t, string&);
Exporting void c_char_index_code_all(string& s, vector<int>& vect);
Exporting void c_char_index_code_all_long(string& s, vector<long>& vect);
Exporting void c_char_index_code_all_long(string& s, vector<BLONG>& vect);

Exporting string c_to_utf8(unsigned char* m);
Exporting string c_char_get(unsigned char* m, int& i);
Exporting string c_char_get_next(unsigned char* m, size_t& i);

//--------------------- Tokenization
Exporting bool s_threedigits(wstring& s, int i);


void vw_tokenize(vector<wstring>& vect, wstring& thestr, short flag);
void s_tokenize(vector<wstring>& vect, wstring& thestr, map<wstring, bool>&);
void v_tokenize(vector<string>& vect, string& thestr, short flag);
void s_tokenize(vector<string>& vect, string& thestr, map<string, bool>&);

//--------------------- agnostring implementation

class agnostring : public string {
public:
	size_t bytepos;
	size_t charpos;

	agnostring() : string() {}
	agnostring(agnostring& s) : string(s.c_str()) { bytepos = 0; charpos = 0; }

	agnostring(const char* s) : string(s) { bytepos = 0; charpos = 0; }
	agnostring(const unsigned char* s) : string((const char*)s) { bytepos = 0; charpos = 0; }

	agnostring(char* s) : string(s) { bytepos = 0; charpos = 0; }
	agnostring(unsigned char* s) : string((char*)s) { bytepos = 0; charpos = 0; }

	agnostring(string s) : string(s) { bytepos = 0; charpos = 0; }
	agnostring(wstring s) { s_unicode_to_utf8(*this, s);  bytepos = 0; charpos = 0; }

	agnostring(BULONG b) : string(s_unicode_to_utf8(b)) { bytepos = 0; charpos = 0; }

	BULONG tonumber() {
		return conversionintegerhexa((char*)c_str());
	}

	string tolower() {
		return s_to_lower(*this);
	}

	string toupper() {
		return s_to_upper(*this);
	}

	bool isupper() {
		return s_is_upper(*this);
	}

	string emoji() {
		return Emoji(*this);
	}

	bool isemoji() {
		return s_is_emoji(*this);
	}

	bool isalpha() {
		return s_is_alpha(*this);
	}

	bool islower() {
		return s_is_lower(*this);
	}

	bool isconsonant() {
		return s_is_consonant((unsigned char*)c_str());
	}

	bool isvowel() {
		return s_is_vowel((unsigned char*)c_str());
	}

	bool ispunctuation() {
		return s_is_punctuation(*this);
	}

	bool isspace() {
		return s_is_space(*this);
	}

	string deaccentuate() {
		return s_deaccentuate((unsigned char*)c_str());
	}

	bool isdigit() {
		return s_is_digit(*this);
	}

	char isnumber(char decimal, long& l, double& f) {
		return s_is_number((unsigned char*)c_str(), decimal, l, f);
	}

	bool isutf8() {
		return s_is_utf8((unsigned char*)c_str(), (int)size());
	}

	char ispureutf8() {
		return s_is_pure_utf8((unsigned char*)c_str(), (int)size());
	}

	string utf8tolatin() {
		return conversion_utf8_to_latin((unsigned char*)c_str());
	}

	wstring utf8tounicode() {
		wstring ws;
		s_utf8_to_unicode(ws, (char*)c_str());
		return ws;
	}

	wstring latintounicode() {
		wstring ws;
		s_utf8_to_unicode(ws, (char*)c_str());
		return ws;
	}

	string latintoutf8() {
		return conversion_latin_to_utf8((unsigned char*)c_str());
	}

	string latintoutf8(int table) {
		return conversion_latin_table_to_utf8(table, (unsigned char*)c_str());
	}

	wstring latintounicode(int table) {
		return conversion_latin_table_to_unicode(table, (unsigned char*)c_str());
	}

	string dostoutf8() {
		return s_dos_to_utf8((unsigned char*)c_str());
	}

	string utf8todos() {
		return s_utf8_to_dos((unsigned char*)c_str());
	}

	void begin() {
		bytepos = 0;
		charpos = 0;
	}

	bool end() {
		if (bytepos >= size())
			return true;
		return false;
	}

	size_t getbytepos() {
		return bytepos;
	}

	void setbytepos(size_t i) {
		bytepos = i;
		charpos = c_bytetocharposition((unsigned char*)c_str(), (int)bytepos);
	}

	size_t getcharpos() {
		return charpos;
	}

	void setcharpos(int i) {
		charpos = i;
		bytepos = c_chartobyteposition((unsigned char*)c_str(), (int)charpos);
	}

	void setpos(int b, int c) {
		bytepos = b;
		charpos = c;
	}

	string next() {
		charpos++;
		return c_char_get_next((unsigned char*)c_str(), bytepos);
	}

	BULONG nextcode() {
		charpos++;
		BULONG v;
		bytepos += 1 + c_utf8_to_unicode((unsigned char*)c_str() + bytepos, v);
		return v;
	}

	void following() {
		charpos++;
		bytepos += 1 + c_test_utf8((unsigned char*)c_str() + bytepos);
	}

	string current() {
		size_t i = bytepos;
		return c_char_get_next((unsigned char*)c_str(), i);
	}

	wstring wcurrent() {
		size_t i = bytepos;
		string s = c_char_get_next((unsigned char*)c_str(), i);
		wstring ws;
		s_utf8_to_unicode(ws, STR(s));
		return ws;
	}

	string next(size_t& i) {
		return c_char_get_next((unsigned char*)c_str(), i);
	}

	BULONG nextcode(int& i) {
		BULONG v;
		i += 1 + c_utf8_to_unicode((unsigned char*)c_str() + i, v);
		return v;
	}

	void following(int& i) {
		i += 1 + c_test_utf8((unsigned char*)c_str() + i);
	}

	char getbyte(int i) {
		string& s = *this;
		return s[i];
	}

	string operator [](int i) {
		return c_char_index(*this, i);
	}

	string trim() {
		return Trim(*this);
	}

	string trimleft() {
		return Trimleft(*this);
	}

	string trimright() {
		return Trimright(*this);
	}

	string replace(string r, string rep) {
		return s_replacestring(*this, r, rep);
	}

	bool insert(string c, size_t i) {
		return c_char_index_insert(*this, c, i);
	}

	int find(string fd, int pos) {
		return s_find((unsigned char*)c_str(), fd, pos);
	}

	int rfind(string fd, int pos) {
		return s_rfind((unsigned char*)c_str(), fd, pos);
	}

	void findall(string fd, vector<long>& v) {
		s_findall(*this, fd, v);
	}

	string extract(int g, int nb) {
		return s_middle(*this, g, nb);
	}

	string left(int nb) {
		return s_left(*this, nb);
	}

	string right(int nb) {
		return s_right(*this, nb);
	}

	int chartobyteposition(int pos) {
		return c_chartobyteposition((unsigned char*)c_str(), pos);
	}

	int bytetocharposition(int pos) {
		return c_bytetocharposition((unsigned char*)c_str(), pos);
	}

	void tokenize(vector<string>& vect, bool comma, bool separator, bool keepwithdigit) {
		short flags = token_period;
		if (comma)
			flags |= token_comma;
		if (separator)
			flags |= token_separator;
		if (keepwithdigit)
			flags |= token_keepwithdigit;
		v_tokenize(vect, *this, flags);
	}

	void tokenize(vector<string>& vect, short flag) {
		v_tokenize(vect, *this, flag);
	}

	void stokenize(vector<string>& vect, map<string, bool>& keeps) {
		s_tokenize(vect, *this, keeps);
	}

	void tokenize(vector<wstring>& vect, bool comma, bool separator, bool keepwithdigit) {
		short flags = token_period;
		if (comma)
			flags |= token_comma;
		if (separator)
			flags |= token_separator;
		if (keepwithdigit)
			flags |= token_keepwithdigit;

		wstring ws;
		s_utf8_to_unicode(ws, (char*)c_str());
		vw_tokenize(vect, ws, flags);
	}


	void tokenize(vector<wstring>& vect, short flag) {
		wstring ws;
		s_utf8_to_unicode(ws, (char*)c_str());
		vw_tokenize(vect, ws, flag);
	}

	void stokenize(vector<wstring>& vect, map<wstring, bool>& keeps) {
		wstring ws;
		s_utf8_to_unicode(ws, (char*)c_str());
		s_tokenize(vect, ws, keeps);
	}

	void split(string thesplitter, vector<string>& v) {
		v_split(*this, thesplitter, v);
	}

	void unicodes(vector<int>& vect) {
		c_char_index_code_all(*this, vect);
	}

	void unicodes(vector<long>& vect) {
		c_char_index_code_all_long(*this, vect);
	}

	size_t sizec() {
		return size_c(c_str());
	}

	string revert() {
		return s_revert(*this);
	}

	Exporting string insertseparator(string sep) {
		return s_insert_sep(*this, sep);
	}

	BULONG code(size_t i) {
		return c_char_index_code(*this, i);
	}

	int count(string x) {
		int cp = 0;
		int ps = 0;
		while ((ps = find(x, ps)) != string::npos) {
			cp++;
			ps++;
		}
		return cp;
	}

	int count(BULONG b) {
		int cp = 0;
		begin();
		while (!end()) {
			if (b == nextcode())
				cp++;
		}
		return cp;
	}
};

#endif







