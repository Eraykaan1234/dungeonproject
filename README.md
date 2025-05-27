# dungeonproject
# Dungeon Game - README

Welkom bij het Dungeon Game project! Dit is een text-based avonturenspel geschreven in C, waarin je door kamers navigeert, monsters bevecht en probeert de schat te vinden.

## 🔧 Vereisten

Om dit project te compileren en uit te voeren, heb je het volgende nodig:

* **GCC compiler** (voor Linux zoals Ubuntu)
* Of **Visual Studio Code** met een C/C++ compiler en terminal

## 🧪 Bestandenstructuur

```bash
📁 dungeon_game/
├── main.c           # Het hoofdprogramma (startpunt)
├── dungeon.c        # Dungeongeneratie, kamers en deuren
├── dungeon.h        # Header voor dungeon.c
├── combat.c         # Gevechtslogica (monsters, animaties)
├── combat.h         # Header voor combat.c
├── player.c         # Spelerstruct en initialisatie
├── player.h         # Header voor player.c
├── save.c           # Opslaan en laden van speldata
├── save.h           # Header voor save.c
├── utils.c          # Algemene hulpfuncties
├── utils.h          # Header voor utils.c
└── item.h           # Structs voor items
```

## 🚀 Compileren en Spelen

### Voor Ubuntu:

Open je terminal in de map van het project en voer in:

```bash
gcc main.c dungeon.c combat.c player.c save.c utils.c -o dungeon_game.exe
./dungeon_game.exe 10
```

### Voor Visual Studio Code:

1. Installeer de extensie: **C/C++** van Microsoft.
2. Open een terminal in VSCode.
3. Gebruik dezelfde compileerregel:

```bash
gcc main.c dungeon.c combat.c player.c save.c utils.c -o dungeon_game.exe
./dungeon_game.exe 10
```

## 💡 Spelregels

* Navigeer door kamers met getallen (deurnummers).
* Vind items om te healen of je schade te verhogen.
* Vecht tegen goblins of orcs met een binair aanvallogica.
* Vind de kamer met de schat om te winnen.

## 💬 Spel starten

```bash
./dungeon_game.exe 10   # start een spel met 10 kamers
./dungeon_game.exe load # laadt je opgeslagen spel
```

## 📌 Opmerkingen

* Het spel slaat automatisch je voortgang op na elke kamer.
* De gevechten zijn willekeurig bepaald met een "aanval volgorde".
* Als je HP nul is, verlies je. Als het monster verslagen is, ga je verder.

## 📚 Code uitleg

Elke `.c` en `.h` bestand bevat commentaarregels die uitleg geven over wat de functie of structuur doet. Hier zijn voorbeelden:

### Voorbeeld - `combat.c`

```c
// Tekent een gekleurde health bar voor speler of monster
void print_hp_bar(const char* label, int hp, int max_hp) { ... }

// Regelt het hele gevecht tussen speler en monster
void fight(Player* player, Room* room) { ... }
```

### Voorbeeld - `dungeon.c`

```c
// Genereert een kamer met lege inhoud
Room *create_room(int id) { ... }

// Verbindt twee kamers met elkaar
void connect_rooms(Room **rooms, int from, int to) { ... }
```

## ✨ Credits

Project gebouwd door Eray kaan Koç met hulp van ChatGPT als copiloot.
Veel plezier met je dungeon avontuur! 🐉🏆
