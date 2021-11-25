Cara::Cara() {
}
vector<Vertice>* Cara::obtenerVertices() {
    return &vertices;
}

int Cara::obtenerTam() {
    return tam;
}
void Cara::asignarTam(int tam_asignar) {
    this->tam = tam_asignar;
}

vector<Arista>* Cara::obtenerAristas() {
    return &aristas;
}

void Cara::asignarVertices(vector<Vertice> vertices_asignar) {
    this->vertices = vertices_asignar;
}

void Cara::asignarAristas(vector<Arista> aristas_asignar) {
    this->aristas = aristas_asignar;
}