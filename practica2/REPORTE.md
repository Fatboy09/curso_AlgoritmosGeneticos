# Reporte Práctica 2

Alumno: Jonatan Zuriel Ruiz Beltrán

### Introducción

Las capacidades para procesamiento de datos de las técnicas de computación evolutiva dentro de una amplia gama de dominios han sido reconocidas en los últimos años y han recibido mucha atención por parte de cientı́ficos que trabajan en diversas disciplinas. Dentro de estas técnicas evolutivas, quizás la más popular sea el algoritmo genético (AG). Siendo una técnica heurı́stica estocástica, el algoritmo genético no necesita información especı́fica para guiar la búsqueda. Su estructura presenta analogı́as con la teorı́a biológica de la evolución, y se basa en el principio de la supervivencia del más apto. Por lo tanto, el AG puede verse como una “caja negra” que puede conectarse a cualquier aplicación en particular. En general, se necesitan los cinco componentes básicos siguientes para implementar un AG que resuelva un problema cualquiera:

1. Una representación de soluciones potenciales al problema.
2. Una forma de crear una población inicial de soluciones potenciales (esto se efectúa normalmente de manera aleatoria, pero también pueden usarse métodos determinı́sticos).
3. Una función de evaluación que juega el papel del ambiente, calificando a las soluciones producidas en términos de su “aptitud”.
4. Operadores genéticos que alteran la composición de los descendientes (normalmente se usan la cruza y la mutación).
5. Valores para los diversos parámetros utilizados por el algoritmo genético (tamaño de la población, probabilidad de cruza y mutación, número máximo de generaciones, etc.)

La representación tradicional usada para codificar un conjunto de soluciones es el esquema binario en el cual un cromosoma es una cadena de la forma \[b0,b1,...,bn\] donde b0, b1, ..., bn se denominan alelos. (ya sean ceros o unos). 

__Códigos GRAY__

Un problema que fue notado desde los inicios de la investigación en AGs fue que el uso de la representación binaria no mapea adecuadamente el espacio de búsqueda con el espacio de representación. Por ejemplo, si codificamos en binario los enteros 5 y 6, los cuales están adyacentes en el espacio de búsqueda, sus equivalentes en binario serán el 101 y el 110, los cuales difieren en 2 bits (el primero y el segundo de derecha a izquierda) en el espacio de representación. A este fenómeno se le conoce como el risco de Hamming, y ha conducido a los investigadores a proponer una representaci ón alternativa en la que la propiedad de adyacencia existente en el espacio de búsqueda pueda preservarse en el espacio de representación. La codificación de Gray es parte de una familia de representaciones que caen dentro de esta categorı́a.

Podemos convertir cualquier número binario a un código de Gray haciendo XOR a sus bits consecutivos de derecha a izquierda, dejando el bit más significativo con el mismo valor.

__Codificando números Reales__

El uso de números reales en una cadena cromosómica ha sido común en otras técnicas de computación evolutiva tales como las estrategias evolutivas y la programación evolutiva, donde la mutación es el operador principal. Sin embargo, los teóricos de los AGs han criticado fuertemente el uso de valores reales en los genes de un cromosoma, principalmente porque esta representación de cardinalidad más alta tiende a hacer que el comportamiento del AG sea más errático y difı́cil de predecir, por lo que el uso de AGs con codificación real sigue siendo una elección que se deja al usuario.

**Codificación en números enteros**

Es una alternativa utilizar números enteros para representar números Reales, pero los operadores tendrı́an que redefinirse de la misma manera que al usar números reales. El uso de este esquema de representación como una alternativa a los AGs con codificación real parece, sin embargo, un tanto improbable, ya que se tendrı́an que hacer sacrificios notables en la representación, y los únicos ahorros importantes que se lograrı́an serı́an en términos de memoria (el almacenamiento de enteros toma menos memoria que el de números reales).


### Capturas de pantalla

![Capt01](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p2_capt01.png)
![Capt02](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p2_capt02.png)
![Capt03](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p2_capt03.png)
![Capt04](https://github.com/Fatboy09/curso_AlgoritmosGeneticos/blob/assets/practica1/p2_capt04.png)


### Conclusión

En conclusión, el objetivo de esta práctica fue el conocer los tipos de representaciones de soluciones a un problema que podemos utilizar para poder desarrollar nuestro algoritmo genético, estás representaciones pueden ser cadenas binarias que es la representación clásica de un cromosoma donde el valor de cada posición de la cadena se denomina alelo. También existe una representación en código GRAY que se podría decir que es una mejora de la cadena binaria para poder evitar problemas de mapear el espacio, otras son la representación en números Reales y de números enteros, ésta última es una forma más de interpretar a un número real, ya que en la práctica un número entero ocupa menos espacio que un número real o flotante. 
