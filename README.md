# FlapyBird

/* SIMA ANA-MARIA - 333CB */

Tema1.h:

class Obstacle{} - folosita pentru a construi dreptunghiurile verticale din cadrul obstacolelor

Tema1.cpp:

void Restart() - reseteaza ecranul

void print() - pentru printarea scorului in consola

In Update(float):
- construiesc pasarea;
- pentru obstacole: intra maxim 4 obstacole in ecran; de fiecare data cand un obstacol a ajuns la sfarsitul ecranului(x = 0), intra unul nou din partea opusa(resolution.x);
- pentru coliziuni, am incadrat pasarea intr-un dreptunghi de dimensiuni maxPoint si heightBird;
- scorul se incrementeaza la fiecare obstacol iesit din scena;

Object2D.h:

Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill = false);

Mesh* CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill);

Mesh* CreateCircle(std::string name, glm::vec3 leftBottomCorner, float r, glm::vec3 color, bool fill);

Object2D.cpp:

- implementare functii pentru construire dreptunghi, cerc, triunghi.
