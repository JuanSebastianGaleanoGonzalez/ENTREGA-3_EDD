Vertice::Vertice() {
    this->indice = -1;
    this->nx = 0;
    this->ny = 0;
    this->nz = 0;
}

void Vertice::copiar(Vertice verticeCopiar) {
    this->indice = verticeCopiar.obtenerIndice();
    this->nx = verticeCopiar.obtenerNx();
    this->ny = verticeCopiar.obtenerNy();
    this->nz = verticeCopiar.obtenerNz();
}
void Vertice::asignarIndice(int indice_asignar) {
    indice = indice_asignar;
}

void Vertice::asignarNx(float nx_asignar) {
    nx = nx_asignar;
}

void Vertice::asignarNy(float ny_asignar) {
    ny = ny_asignar;
}

void Vertice::asignarNz(float nz_asignar) {
    nz = nz_asignar;
}

int Vertice::obtenerIndice() {
    return indice;
}

float Vertice::obtenerNx() {
    return nx;
}

float Vertice::obtenerNy() {
    return ny;
}

float Vertice::obtenerNz() {
    return nz;
}