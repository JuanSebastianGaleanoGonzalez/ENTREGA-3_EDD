Arista::Arista() {
}

void Arista::asignarP1(Vertice p1_asignar) {
    p1 = p1_asignar;
}

void Arista::asignarP2(Vertice p2_asignar) {
    p2 = p2_asignar;
}

Vertice Arista::obtenerP1() {
    return p1;
}

Vertice Arista::obtenerP2() {
    return p2;
}