# Reporte Práctica 3

Alumno: Jonatan Zuriel Ruiz Beltrán

### Introducción

Una parte fundamental del funcionamiento de un algoritmo genético es, sin lugar a dudas, el proceso de selección de candidatos a reproducirse. En el algoritmo genético este proceso de selección suele realizarse de forma probabilı́stica, lo cual quiere decir, que los individuos menos aptos tienen oportunidad de sobrevivir, a diferencia de las estrategias evolutivas en donde la selección es __extintiva__(los menos aptos tienen una probabilidad de cero de sobrevivir).

Existen técnicas de selección que son utilizadas en los algoritmos genéticos y pueden clasificarse en tres grandes grupos:
1. Selección proporcional
2. Selección mediante torneo
3. Selección de estado uniforme

En este reporte se platicará sobre la primera técnica, debido a que esta práctica tuvo como objetivo aplicar y desarrollar esta técnica de selección implementando el algoritmo de la ruleta.

### Selección Proporcional

Este nombre describe a un grupo de esquemas de selección originalmente propuestos por Holland en los cuales se eligen individuos de acuerdo a su contribución de aptitud con respecto al total de la población.

Se consideran cuatro grupos de esquemas que pertenecen a esta técnia, las cuales son las siguientes:
1. La ruleta
2. Sobrante Estocástico
3. Universal Estocástica
4. Muestreo Determinístico

## La ruleta
Fue propuesta por DeJong, y ha sido el método más comúnmente usado desde los orı́genes de los algoritmos genéticos. El algoritmo es simple, pero ineficiente debido a que su complejidad es O(n²). Asimismo, presenta el problema de que el individuo menos apto puede ser seleccionado más de una vez.

El algoritmo de la Ruleta es el siguiente:
* Calcular la suma de valores esperados T
* Repetir N veces (N es el tamaño de la población):
    * Generar un número aleatorio r entre 0.0 y T
    * Ciclar a través de los individuos de la población sumando los valores esperados hasta que la suma sea mayor o igual a r.
    * El individuo que haga que esta suma exceda el lı́mite es el seleccionado.

### Capturas de pantalla

![Capt01](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p3_capt01.png)
![Capt02](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p3_capt02.png)
![Capt03](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p3_capt03.png)
![Capt04](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p3_capt04.png)


### Conclusión

En conclusión, el objetivo de esta práctica fue el implementar una técnica de selección de candidatos para poder reproducirse, para ello se realizó el algoritmo de la Ruleta, un algoritmo que fue desarrollado por DeJong y que resulta un algoritmo simple pero poco eficiente ya que la complejidad de este es O(n²) y resulta que los individuos menos óptimos pueden ser seleccionados varias veces. La selección lo hace generando un número aleatorio *r* entre 0.0 y T, donde T es la suma total de los valores esperados de cada individuo, repetir n veces, donde n es el tamaño de la población, y ciclar a través de los individuos de la población sumando sus valores esperados hasta que la suma sea mayor o igual a _r_. Si el individuo excede esta suma, es seleccionado.
