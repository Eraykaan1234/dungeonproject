**Dungeon Game: Volledig Gedocumenteerd Project**
Welkom bij de Dungeon Game!

Dit project is een text-based dungeon crawler in C, compleet met:

* gevechten,
* willekeurig gegenereerde kamers,
* items,
* save/load functionaliteit,
* en kleurrijke terminal-output met animaties.

---
## 🔧 Compilatie-instructies (Ubuntu / VSCode)

1. Zorg dat je `gcc` en `make` hebt geïnstalleerd:
```bash
sudo apt update && sudo apt install build-essential
```

2. Compileer met:
```bash
gcc main.c dungeon.c combat.c player.c save.c utils.c -o dungeon_game.exe
```

3. Start het spel met een nieuw aantal kamers (bijv. 10):

```bash
./dungeon_game.exe 10
```
Of laad een opgeslagen spel:

```bash
./dungeon_game.exe load
```
--

## 📁 Bestandsstructuur en Functies

### `main.c`

* **Main game loop**
* Handelt input van speler af
* Roept `enter_room`, `print_doors`, `fight`, en `save/load_game`
* Toont `Victory` of `Game Over` met animatie

### `combat.c`

* `fight(Player*, Room*)`: regelt het volledige gevecht
* `print_hp_bar`: toont kleurrijke healthbar (groen/geel/rood)
* Maakt gebruik van animatie, ascii-boxen, vertraging (`usleep`) en kleur

### `dungeon.c`

* `generate_dungeon()`: maakt random kamers + connecties
* `create_room()`, `connect_rooms()` enz.
* `enter_room()`: toont kamer-info, loot, triggers gevechten
* `print_doors()`: toont mogelijke uitgangen
* `free_dungeon()`: geheugen opruimen

### `player.c`

* `init_player()`: stelt begingezondheid en schade in
* Struct definitie voor `Player`

### `save.c`

* `save_game(...)` en `load_game(...)` lezen/schrijven speldata naar `save.txt`
* Maakt gebruik van eenvoudige bestand-IO (`fprintf`, `fscanf`)

### `utils.c`

* Kleine hulpmethoden zoals `random_getal_tussen(min, max)`

### `item.h`

* Enum voor items: HEAL en DAMAGE
* `Item` struct met type + waarde

### `dungeon.h`, `player.h`, `combat.h`, `item.h`, `utils.h`, `save.h`

* Header files met struct- en functie-declaraties

---

## 📌 Extra Features

* 🎨 Kleurrijke ASCII-boxen
* 🎉 Victory-scherm met confetti animatie
* 💚 Healing-items en 💥 Damage boosters
* 💀 Doodscherm met rode melding
* ✅ Save/load via `save.txt`

---

## ✅ Aanbevolen instellingen (VSCode)

* Installeer extensie: `C/C++` van Microsoft
* Gebruik `gcc` als default compiler
* Gebruik `Terminal > Run Task...` of eigen `Makefile`

Gemaakt met ❤️ door mij (Eray)