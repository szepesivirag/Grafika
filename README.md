# Grafika
**Beadandó Bemutató – Programozott 3D Szoba**  

# Programozott 3D Szoba – Grafika Beadandó

Ez a projekt egy interaktív, háromdimenziós belső teret valósít meg C nyelven, az OpenGL és a FreeGLUT grafikus könyvtárak segítségével. A jelenet központi eleme egy szürreális, lebegő asztal, amely egy textúrázott szoba belsejében helyezkedik el.

## Funkciók és Jellemzők

* **Interaktív 3D Kamerakezelés:** Szabad mozgás a térben vízszintes és függőleges irányban is.
* **Dinamikus Világítás:** A felhasználó valós időben módosíthatja a szoba fényerejét.
* **Animált Objektumok:** Az asztal folyamatos, szinuszos lebegő mozgást végez.
* **Hierarchikus Modellezés:** Külső `.obj` modell betöltése és transzformálása (skálázás, eltolás).
* **On-screen Help (HUD):** Bármikor előhívható 2D-s segítség az irányításhoz.

## Irányítás

| Billentyű | Funkció |
| :--- | :--- |
| **W, S** | Mozgás előre / hátra |
| **A, D** | Mozgás balra / jobbra |
| **T, G** | Kamera emelése / süllyesztése |
| **U, J** | Fényerő növelése / csökkentése |
| **F1** | Súgó ablak ki/bekapcsolása |

### Technikai Megvalósítás

### 1. Animáció és Transzformációk
Az asztal lebegését a `draw.c` modulban egy időfüggő szinuszos függvény vezérli. A program az eltelt idő alapján kiszámít egy eltolási értéket, amelyet a `glTranslatef()` függvény Y-paramétereként alkalmazunk. Ez biztosítja a folyamatos, zökkenőmentes vertikális oszcillációt.

### 2. Világítási Modell
A projekt a **Blinn-Phong megvilágítási modellt** használja. Az `U` és `J` billentyűk a globális fényforrás diffúz és ambient komponenseit módosítják a `glLightfv()` hívásokon keresztül, lehetővé téve a jelenet sötétítését és világosítását.

### 3. Kamera és Nézet
A kamera pozícióját és nézési irányát egy struktúra tárolja, amely a felhasználói bemenetek alapján frissül. A 3D-s látványt a `gluLookAt()` függvény generálja minden egyes képkocka rajzolásakor, a modell-nézet mátrix frissítésével.

### 4. 2D UI (HUD) megvalósítása
Az F1 billentyűvel előhívható súgó ablak ortografikus vetítéssel készül. A program ideiglenesen átvált `GL_PROJECTION` módból 2D-s síkba, hogy a szöveges információkat fixen a képernyőre rajzolja, függetlenül a kamera pozíciójától.

## Felhasznált Technológiák

* **Programozási nyelv:** C
* **Grafikus könyvtár:** Modern OpenGL (GL, GLU)
* **Ablakkezelés:** FreeGLUT
* **Képbetöltés:** SOIL (Simple OpenGL Image Library)
* **Fejlesztői környezet:** GCC / Makefile alapú fordítás

```bash
make
./Beadando.exe
