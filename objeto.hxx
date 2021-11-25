Objeto::Objeto() {
}

string Objeto::obtenerNombre() {
    return this->nombre;
}

void Objeto::asignarNombre(string nombre_asignar) {
    this->nombre = nombre_asignar;
}

void Objeto::asignarNumVert(int numero_vertices) {
    this->numVert = numero_vertices;
}

int Objeto::obtenerNumVert() {
    return this->numVert;
}

vector<Cara>* Objeto::obtenerCaras() {
    return &caras;
}

vector<Vertice>* Objeto::obtenerVertices() {
    return &vertices;
}

int Objeto::obtenerNumAristas() {
    return this->numAristas;
}

void Objeto::asignarNumAristas(int numAristas_asignar) {
    this->numAristas = numAristas_asignar;
}

void Objeto::asignarCaras(vector<Cara>* caras_asignar) {
    this->caras = *caras_asignar;
}

void Objeto::imprimirObjeto() {
    cout << this->nombre << " contiene " << this->numVert << " vertices, " << this->numAristas << " aristas y " << this->caras.size() << " caras." << endl;
}

void Objeto::asignarVertices(vector<Vertice>* vertices_asignar) {
    this->vertices = *vertices_asignar;
}