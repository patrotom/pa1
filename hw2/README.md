# SETI #

Úkolem je vytvořit program, který bude analyzovat vysílání mimozemských civilizací.

Radioastronomům se podařilo zachytit zprávy mimozemských civilizací. Konečně. Zprávy přicházejí od hvězd, které mají podobné charakteristiky, jako Slunce. Není pochyb.

Problém je zprávy dekódovat. Překvapivě, kódování všech zpráv je stejné (mimozemský UNICODE), navíc, od jedné hvězdy přichází ta samá zpráva stále dokola. Jednou z otázek je, zda se zprávy někdy sesynchronizují, tedy, zda v nějakém okamžiku budeme přijímat všechny zprávy od jejich začátku.

Vstupem programu jsou dvě nebo více zpráv. Každá zpráva je zadaná na jedné řádce jako posloupnost písmen malé abecedy. Každé písmeno určuje délku zachyceného pulzu: a=1, b=2, c=4, d=8, e=16, ... Dále je na vstupu znak |, který určuje začátek zprávy. Tedy vstup v podobě:

ea|babab

představuje zprávu s pulzy délky 16, 1, 2, 1, 2, 1 a 2. Celková délka zprávy je 16 + 1 + 2 + 1 + 2 + 1 + 2=25 časových jednotek. Zpráva je zaznamenaná tak, že do jejího konce zbývá ještě 16+1=17 časových jednotek.

Program takto dostane na svém vstupu několik zpráv, každá zpráva může mít různou délku a aktuální pozice v každé zprávě také může být jiná. Program určí, zda dojde k synchronizaci ve všech zprávách a kdy k tomu dojde. Například pro vstup:

ea|babab

d|abaca

dojde k synchronizaci za 42 jednotek času:

ea|  bababea|          = 42

d|   abacad|abacad|    = 42

Vstupem programu jsou přijímané zprávy ve formátu popsaném výše. Zprávy jsou nejméně dvě. Pro základní testy jsou na vstupu pouze dvě zprávy, bonusové testy zadávají více zpráv na vstupu.

Výstupem programu je vypočtená informace, kdy se vstupní zprávy sesynchronizují. Pro některé vstupy se může stát, že se zprávy nikdy nesesynchronizují, v této situaci je zobrazena jiná odpověď (viz ukázky).

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

* méně než dvě vstupní zprávy,
* zpráva nemá správný formát (nesmí být prázdná, musí obsahovat pouze písmena malé abecedy a právě jeden znak kolmítko).

## Ukázka práce programu: ##

Zpravy:

ea|babab

d|abaca

Synchronizace za: 42

---

Zpravy:

acacbbaaa|

cbbcabcbbaa|

Synchronizace za: 0

---

Zpravy:

|acabbaaa

|dcbabaaaa

Synchronizace za: 0

---

Zpravy:

acacbbaa|baa

bcaabaa|baaa

Synchronizace za: 216

---

Zpravy:

cbbcbaa|aaaa

aadaaaabaaa|abaa

Nelze dosahnout.

---

Zpravy:

dbdccdccbbbbaa|aaaa

bebbaedbcabbaa|ccbaa

Synchronizace za: 276

---

Zpravy:

jfddiaggfdffaagfacafcfbbbgdcddbfaedfeaacfeadcbabbaaa|hdccdfdbfadcdbbcbbaa

bhfdigdbggfadfdddacceaedbefeacbacaacbbbaa|cdcgebfichfbgcbjbhdfadgheifheceeehiceeedfbgcgaggfdaadacbdeccbaadbbabaa

Synchronizace za: 5046543

---

Zpravy:

acacbb|aaa

cbbcabcbbaa

Nespravny vstup.

---

Zpravy:

acacbb|aaa

cbbc abcb|baa

Nespravny vstup.

## Poznámky: ##

* Znak odřádkování (\n) je i za poslední řádkou výstupu (i za případným chybovým hlášením).
* Úlohu lze vyřešit bez použití funkcí. Pokud ale správně použijete funkce, bude program přehlednější a bude se snáze ladit.
* Není potřeba alokovat pole. Práce s polem úlohu zbytečně zkomplikuje. Vstupy lze načítat průběžně a ukládat si pouze agregované hodnoty.
* Pro načítání vstupu se hodí funkce scanf s formátem %c nebo funkce fgetc.
* Hodnocení připouští různě dokonalá řešení, podle úrovně řešení budou přidělené body navíc:
    * první bonus získá řešení, které dokáže pracovat s více než dvojicí zpráv na vstupu,
    * druhý bonus získá řešení, které použije efektivní algoritmus výpočtu, a dokáže rychle pracovat i pro dlouhé zprávy,
    * třetí bonus získá řešení, které použije efektivní algoritmus výpočtu, a dokáže rychle pracovat i pro velmi dlouhé zprávy.
* Pro výpočty v základních testech stačí datový typ int. Pro zvládnutí druhého a třetího bonusu je potřeba pracovat s velkými čísly, která překračují rozsah typu int. Doporučený je datový typ long int nebo long long int. Pro zvládnutí třetího bonusu (a s některými algoritmy i pro druhý bonus) budete dokonce muset ukládat mezivýsledky v typu __int128_t (tento typ je nestandardní, má rozsah 128 bitů, neexistuje pro něj standardní vstupní a výstupní konverze, ale lze jej použít v aritmetických operacích).
* Datový typ long long int není standardním typem v C89. Jeho použití je oznámeno varováním kompilátoru. Toto varování lze potlačit přepínačem -Wno-long-long. Kompilátor Progtestu tento přepínač používá, tedy správné použití typu long long int nepovede k varování při překladu a ani k bodové penalizaci.
* Pro zobrazení hodnot typu long long int použijte formát %lld.
* Slovní popis struktury platných vstupních dat není zcela exaktní. Proto na výtky některých studentů přikládáme i popis vstupního jazyka v EBNF:

input      ::= message '\n' message '\n' { message '\n' }

message    ::= { pulse } separator { pulse }

separator  ::= ( pulse '|' ) | ( '|' pulse )

pulse      ::= 'a' | 'b' | 'c' | ... | 'z'
