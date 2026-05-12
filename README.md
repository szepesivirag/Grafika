# Grafika
**Beadandó Bemutató – Programozott 3D Szoba**  

# Programozott 3D Szoba – Grafika Beadandó

Ez a projekt egy háromdimenziós belső teret valósít meg C nyelven, az OpenGL 

## Funkciók és Jellemzők

* **Interaktív 3D Kamerakezelés:** Szabad mozgás a térben vízszintes irányban.
* **Dinamikus Világítás:** A felhasználó valós időben módosíthatja a szoba fényerejét.
* **Animált Objektumok:** A kocka folyamatos mozgást végez.
* **Hierarchikus Modellezés:** Külső `.obj` modell betöltése és transzformálása (skálázás, eltolás).
* **On-screen Help (HUD):** Bármikor előhívható 2D-s segítség az irányításhoz.

## Irányítás

| Billentyű | Funkció |
| :--- | :--- |
| **W, S** | Mozgás előre / hátra |
| **A, D** | Mozgás balra / jobbra |
| **U, J** | Fényerő növelése / csökkentése |
| **F1** | Súgó ablak ki/bekapcsolása |

## Technikai Megvalósítás

### 1. Animáció és Transzformációk
A szoba közepén található kockaforma folyamatos mozgást végez. 

### 2. Világítási Modell
A projekt a **Blinn-Phong megvilágítási modellt** használja. A felhasználó interaktív módon, az `U` és `J` billentyűk segítségével módosíthatja a fényforrás erejét. A program ilyenkor valós időben frissíti a fény környezeti (ambient) és szórt (diffuse) komponenseit.

### 3. Kamera és Irányítás
A program egy belső nézetű (FPS) kamerarendszert használ. A kamera pozícióját és nézési irányát a felhasználói bemenetek (egér és billentyűzet) alapján frissítjük. A 3D-s látványt a `gluLookAt` függvény generálja minden képkockánál a kamera aktuális adatai alapján.

### 4. 2D Felhasználói Felület 
Az `F1` billentyűvel előhívható súgó ablak ortografikus vetítéssel készül. Megjelenítéskor a program ideiglenesen átvált 2D-s síkba, így a súgó képe "rávetül" a képernyőre, függetlenül attól, hogy a kamera éppen merre néz a 3D-s térben. 


## Felhasznált Technológiák

* **Programozási nyelv:** C
* **Grafikus könyvtár:** OpenGL 
* **Képbetöltés:** stb_image.h (modern, fejléc-alapú könyvtár)
* **Fordító:** GCC (MinGW)

## Fordítás és Futtatás

A projekt lefordításához és futtatásához használd a mellékelt `Makefile`-t a terminálban:

```bash
make
./Beadando.exe
