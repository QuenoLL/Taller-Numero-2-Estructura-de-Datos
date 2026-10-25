Integrantes:

1.- Matías Núñez González / Rut: 22.256.666-5 / Usuario: Manugooo / Carrera: ICCI / Paralelo: (completar)

2.- Eugenio Cortés Egaña / Rut: 22.405.687-7 / Usuario: QuenoLL / Carrera: ICCI / Paralelo: (completar)

Este código está hecho en C++ y es la continuación del Taller 1. Sirve para gestionar los pacientes del hospital Marmaja: se leen desde un archivo, esperan en una cola, un árbol de decisión elige a qué servicio van y después se guardan en el árbol AVL de ese servicio. La cola, la lista, el árbol de decisión y los AVL están hechos a mano, sin usar la STL.

Compilación y ejecución

Desde una terminal ubicada en la carpeta Logic:

```
g++ Main.cpp SystemImpl.cpp ../Dominio/*.cpp -o Main && ./Main
```

(Windows: `g++ Main.cpp SystemImpl.cpp ../Dominio/*.cpp -o Main && .\Main`)

Probado en Codespace. Los pacientes se leen de `txts/Pacientes Marmaja.txt`.

Cómo funciona

Al iniciar se leen los pacientes del archivo y entran a la cola según el orden de llegada. Cuando se atiende, se saca al primero de la cola, se pasa por el árbol de decisión (que muestra la ruta que siguió), se obtiene su servicio y se inserta en el AVL de ese departamento usando el ID como clave. Los AVL se balancean solos con rotaciones simples y dobles al insertar y al eliminar.

Cada línea del archivo va separada por `;` en este orden:

ID;Nombre;Edad;Temperatura;PresionArterial;Dolor;TipoDolor;Trauma;SintomasNeurologicos;RequiereCirugia;DiasHospitalizacion`

El menú tiene: atender pacientes, ver departamentos (con recorridos, altura y factor de balance), buscar paciente por ID o nombre, eliminar paciente, ver el árbol de decisión y salir.

Árbol de decisión

Las preguntas se hacen en este orden, y si un paciente cumple varias, gana la primera (así se resuelven los empates):

1. Edad menor a 14: Pediatría, porque los niños van a pediatría sin importar el motivo.
2. Trauma: si requiere cirugía va a Cirugía, si no a Traumatología.
3. Síntomas neurológicos: Neurología, porque pesan más que el dolor o la fiebre.
4. Dolor de pecho: Cardiología, porque primero se descarta algo del corazón.
5. Temperatura mayor a 38.5: Urgencias, por fiebre alta.
6. Dolor 8 o más: Urgencias, por dolor fuerte.
7. Presión arterial 180 o más: Urgencias, por presión muy alta.
8. Requiere cirugía (sin trauma): Cirugía.
9. Días de hospitalización 2 o más: Hospitalización.
10. Si no cumple nada de lo anterior: Medicina General.

Usa 9 atributos del paciente y hay camino hacia los 8 servicios.

Datos inválidos

Si una línea del archivo está mal, se muestra un mensaje y se salta, el programa sigue funcionando. Se rechaza cuando:

- no tiene los 11 campos
- el ID no es un número mayor a 0 o está repetido
- la edad no está entre 0 y 120, la temperatura entre 30 y 45, la presión entre 40 y 300 o el dolor entre 0 y 10
- el tipo de dolor no es pecho, cabeza, abdomen, extremidad u otro
- trauma, síntomas neurológicos o requiere cirugía no son 0 o 1
- los días de hospitalización no están entre 0 y 365

Si el archivo no existe, avisa con un error y sigue sin pacientes.

Memoria

Todas las estructuras tienen su destructor para liberar la memoria dinámica (cola, lista, árbol de decisión y AVL con sus pacientes). Se revisó con AddressSanitizer y no hubo fugas.
