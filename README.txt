Projekt "Aplikace typu Pac-Man"

Implementace:
Výsledkem je hra vytvořená pomocí prostředí Qt v C++
Uživatel používá GUI k interakci s hrou.

Funkčnost:
1) Při spuštění aplikace budete vyzváni k výběru mapy. Poté je možné vybrat mapu pomocí tlačítka Game -> 'Load',
nebo spuštěním stejné mapy pomocí 'Restart' po skončení hry
2) Stav hry lze uložit pomocí tlačítka Game -> 'Save'. Poté se načte jako běžná mapa
3) Po skončení hry lze gameplay uložit pomocí tlačítka 'Save this gameplay' a poté ji znovu přehrát pomocí tlačítka Game -> 'Replay'

Omezení implementace:
1) Pohyby Pac-Mana se ovládají pouze pomocí WASD, šipky nefungují
2) Byl implementován pouze jeden mód přehrávání – postupné krokování

Známé chyby:
1) Okenko 'Save this gameplay' se objeví tolikrát, kolikrát jste klikli na 'Restart'
