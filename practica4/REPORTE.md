# Reporte Práctica 4

Alumno: Jonatan Zuriel Ruiz Beltrán

### Introducción

Una parte fundamental del funcionamiento de un algoritmo genético es, sin lugar a dudas, el proceso de selección de candidatos a reproducirse. En el algoritmo genético este proceso de selección suele realizarse de forma probabilı́stica, lo cual quiere decir, que los individuos menos aptos tienen oportunidad de sobrevivir, a diferencia de las estrategias evolutivas en donde la selección es __extintiva__(los menos aptos tienen una probabilidad de cero de sobrevivir).

Existen técnicas de selección que son utilizadas en los algoritmos genéticos y pueden clasificarse en tres grandes grupos:
1. Selección proporcional
2. Selección mediante torneo
3. Selección de estado uniforme

En este reporte se platicará sobre la primera técnica, debido a que esta práctica tuvo como objetivo aplicar y desarrollar esta técnica de selección implementando el algoritmo de la ruleta.

### Selección mediante torneo
La selección mediante torneo es similar a la de jerarquı́as en términos de la presión de selección, pero es computacionalmente más adecuada para implementarse en paralelo. 
Esta técnica fue propuesta por Wetzel y estudiada en la tesis doctoral de Brindle. La idea básica del método es seleccionar con base en comparaciones directas de los individuos. Hay 2 versiones de la selección mediante torneo:

* Determinı́stica
* Probabilı́stica

El algoritmo de la versión determinı́stica es el siguiente:
* Barajar los individuos de la población.
* Escoger un número p de individuos (tı́picamente 2).
* Compararlos con base en su aptitud.
* El ganador del “torneo” es el individuo más apto.
* Debe barajarse la población un total de p veces para seleccionar N padres (donde N es el tamaño de la población).

El algoritmo de la versión probabilı́stica es idéntico al anterior, excepto por el paso en que se escoge al ganador. En vez de seleccionar siempre al individuo con aptitud más alta, se aplica flip(p) y si el resultado es cierto, se selecciona al más apto. De lo contrario, se selecciona al menos apto.
El valor de p permanece fijo a lo largo de todo el proceso evolutivo y se escoge en un rango mayor a 0.5 pero menor o igual a 1.

### Capturas de pantalla
10 Generaciones:


![Capt01](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p4_capt01.png)


30 Generaciones:


![Capt02](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p4_capt02.png)


50 Generaciones:


![Capt03](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p4_capt03.png)


100 Generaciones:


![Capt04](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p4_capt04.png)


salida de pantalla del programa:


![Capt05](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p4_capt05.png)
![Capt06](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p4_capt06.png)
![Capt07](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p4_capt07.png)

### Conclusión

En conclusión, el objetivo de esta práctica fue el implementar una técnica de selección de candidatos para poder reproducirse, para ello se realizó el algoritmo de seleccion por torneo, un algoritmo que fue desarrollado por Wetzel. Este algoritmo nos garantiza que en su versión determinística el mejor individuo será seleccionado p veces y su complejidad es de O(n), donde resulta ser las "n" competencias que se necesita para completar una generación. Es una técnica de selección eficiente y de implementación sencilla. 
