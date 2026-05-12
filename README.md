# Grafika
**Beadandó bemutató – Programozott 3D szoba**

# Programozott 3D Szoba – Grafika Beadandó

Ez a projekt egy háromdimenziós belső teret valósít meg C nyelven, OpenGL használatával.  
A program egy bejárható szobát jelenít meg, amelyben a felhasználó szabadon mozoghat, módosíthatja a fényerőt, valamint megfigyelhet egy animált, térbeli objektumot a jelenet közepén.

## Funkciók és jellemzők

* **Interaktív 3D kamerakezelés:** Szabad mozgás a térben vízszintes irányban.
* **Dinamikus világítás:** A felhasználó valós időben módosíthatja a szoba fényerejét.
* **Animált objektum:** A szoba közepén egy térbeli kocka található, amely folyamatosan forog.
* **Minimális objektumkövetelmény teljesítése:** A középen elhelyezett kocka egy önálló 3D objektum, így megfelel a beadandó minimális objektumkritériumának.
* **On-screen help (HUD):** Bármikor előhívható 2D-s segítség az irányításhoz.

## Irányítás

| Billentyű | Funkció |
| :--- | :--- |
| **W, S** | Mozgás előre / hátra |
| **A, D** | Mozgás balra / jobbra |
| **U, J** | Fényerő növelése / csökkentése |
| **F1** | Súgó ablak ki/bekapcsolása |

## Technikai megvalósítás

### 1. Térbeli objektum és animáció
A jelenet közepén egy kocka helyezkedik el, amely a program futása közben folyamatosan forog a függőleges tengely körül.  
Ez a kocka biztosítja a beadandó minimális objektumkövetelményének teljesítését, mivel egy jól látható, önálló térbeli objektum jelenik meg a szobában.

Az animáció megvalósítása időalapú frissítéssel történik: a program minden képkockában növeli a kocka forgási szögét, majd ezt az értéket a kirajzolás során `glRotatef` segítségével alkalmazza.  
Ennek eredményeként a kocka egyenletesen, folyamatosan mozog, tehát az animációs / mozgatási követelmény is teljesül.

### 2. Transzformációk
A kocka megjelenítéséhez a program geometriai transzformációkat használ.  
Kirajzolás előtt a modellt a megfelelő helyre pozicionálja, majd elforgatja, végül felskálázza, hogy jól látható legyen a térben.

A megjelenítés során alkalmazott transzformációk sorrendje:
* eltolás a jelenet közepére,
* forgatás az aktuális szög alapján,
* méretezés a kívánt méretre.

Ez a megközelítés jól bemutatja az OpenGL-ben használt modelltranszformációk alapjait.

### 3. Világítási modell
A projekt a **Blinn–Phong megvilágítási modellt** használja.  
A felhasználó interaktív módon, az `U` és `J` billentyűk segítségével módosíthatja a fényforrás erejét. A program ilyenkor valós időben frissíti a fény környezeti (ambient) és szórt (diffuse) komponenseit.

### 4. Kamera és irányítás
A program egy belső nézetű kamerarendszert használ.  
A kamera pozícióját és nézési irányát a felhasználói bemenetek alapján frissíti. A 3D látványt a `gluLookAt` függvény állítja elő minden képkockában az aktuális kamerapozíció és nézeti irány felhasználásával.

### 5. 2D felhasználói felület
Az `F1` billentyűvel előhívható súgóablak ortografikus vetítéssel készül.  
Megjelenítéskor a program ideiglenesen átvált 2D-s megjelenítésre, így a súgó a képernyőre rajzolható, függetlenül attól, hogy a kamera éppen merre néz a 3D térben.

## Felhasznált technológiák

* **Programozási nyelv:** C
* **Grafikus könyvtár:** OpenGL
* **Ablakkezelés / input:** SDL2
* **Képbetöltés:** stb_image.h
* **Fordító:** GCC (MinGW)

## Fordítás és futtatás

A projekt lefordításához és futtatásához használd a mellékelt `Makefile`-t terminálból:

```bash
make
./Beadando.exe
```

## Összegzés

A program egy bejárható, megvilágított 3D szobát valósít meg, amelyben megjelenik egy központi, forgó kocka.  
Ez a kocka egyszerre szolgál önálló térbeli objektumként és animált elemként, így a beadandó minimális elvárásai közül teljesíti az objektum és a mozgás / animáció követelményét.