# 🧠 Estrategia de Desarrollo del Juego
Para desarrollar este juego utilizamos estructuras de datos vistas en la materia, seleccionadas en función de su comportamiento y de las necesidades específicas de cada parte del sistema:

## Estructura tJugador🧍‍♂️ :
Cada jugador tiene su nombre, su puntaje y un vector mazo[4] de cartas. Las tres primeras posiciones representan las cartas en mano, y la cuarta posición almacena la última carta jugada. Esto permite verificar qué carta jugó previamente el oponente, especialmente útil cuando se juega una carta "Espejo". Por último, la estructura de jugador contiene también "Efecto Recibido", esto es para que al momento de que se use la carta espejo, los puntos que se le devuelvan sean sólo los restados y no puntos demás. Por ejemplo, en el caso de que el jugador tenga 0 puntos, y la IA juegue -1, al aplicar el efecto este sigue teniendo 0 puntos, por lo tanto su "efecto Recibido" es 0, pero la última carta jugada por la IA es -1, por lo que al momento de que el jugador utilice Espejo, no se le sumarán puntos a él, pero a la IA si se le restará 1 punto.

## Dos pilas estáticas🃏:
Una pila representa el mazo principal de cartas, y la otra, el mazo de descartadas. Para simular el mazo, usamos un vector de char que contiene las cartas representadas por letras:
- `'a'`: +2 puntos
- `'b'`: +1 punto
- `'c'`: -1 punto
- `'d'`: -2 puntos
- `'e'`: Repite turno
- `'f'`: Espejo

Éstas se van cargando de forma aleatoria a la **pila del mazo**. Mientras se juega, las cartas se van guardando en una **pila de descartadas**, y cuando ya no hay más cartas en la pila del mazo, las cartas de la pila de descartadas se copian a un nuevo vector char y se vuelven a cargar aleatoriamente en la pila del mazo.
#### Motivo de la elección🧩
Elegimos pilas estáticas porque el número total de cartas es fijo (40), lo que permite manejar la memoria de forma eficiente, y porque su comportamiento (sacar desde el tope) replica el funcionamiento real de un mazo.


## Lista circular para las rondas1️⃣📝🔁:
Implementamos una lista circular con dos nodos, representando a cada jugador. Esta estructura permite alternar los turnos de manera cíclica. Cada nodo almacena al jugador, su oponente, la pila del mazo, la pila de descartadas y una función decisión, que corresponde a la acción que tomará el jugador (por ejemplo, elegirCarta() en el caso del jugador humano, o una función IA si se trata de la computadora).
Esta estructura permite que cuando un jugador juega una carta especial como "Repite", no se cambie de nodo, manteniendo así el flujo lógico del juego.
🔍Además el hecho de que cada nodo tenga acceso también al oponente permite restar puntos rápidamente en caso de que el jugador elija un **"-1"** o **"-2"** o **"Espejo"**.

## Lista circular para registrar los turnos2️⃣📝🔁:
Creamos una segunda lista circular para guardar lo sucedido en cada turno. Esta solución nos resultó más eficiente que una cola tradicional, ya que permite insertar los nuevos turnos y al final recorrerla desde la misma posición (siempre desde el segundo nodo), evitando así recorridos innecesarios al generar 🧾 el informe final de la partida.

## Lista simplemente enlazada para la API (Ranking)➡️📝:
Usamos una lista simple para almacenar los datos recibidos desde la API (nombre del jugador y cantidad de partidas ganadas). Luego, esta lista se ordena y se muestra como ranking.
✅Elegimos esta estructura por su simplicidad y porque se adapta bien al comportamiento esperado: inserciones dinámicas y recorrido ordenado para visualización.

📌Además, antes de implementar el código, diagramamos el flujo del juego en Draw.io, lo que nos ayudó a visualizar mejor la lógica y nos ayudó a pensar qué estructuras de datos eran mejores para cada funcionalidad.
