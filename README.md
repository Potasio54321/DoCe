# 🃏 DoCe 

**DoCe** es un juego de cartas simple pero adictivo desarrollado en C, donde un jugador humano compite contra la computadora para alcanzar 12 puntos antes que su oponente.
Se trata de un juego dinámico, basado en estrategia y azar, que además permite registrar los resultados en un servidor remoto mediante una API para futuras mejoras en la inteligencia artificial. 
Fue desarrollado para formar parte de un sistema de entretenimiento de un festival, con el objetivo de ofrecer una experiencia competitiva y divertida para los asistentes.

## 🎮 Instrucciones del juego
Al iniciar, se presenta un menú interactivo. Las opciones disponibles son:

- **A) Jugar:** Se le pedirá al jugador que ingrese su nombre y seleccione el nivel de dificultad. A continuación comenzará la partida.
- **B) Ver ranking:** Se mostrará por pantalla el nombre y la cantidad de partidas ganadas de cada jugador.
- **C) Salir:** Termina el juego.


## 📜 Reglas del Juego
- El jugador y la máquina comienzan con 0 puntos y una mano de 3 cartas cada uno.
- Ningún jugador puede tener puntos negativos.
- Las cartas tienen diferentes efectos, entre ellos:
	- **+2 o +1 puntos** para quien la juega.
 	- **Sacar puntos** al rival (-1 o -2).
  	- **Repetir turno** inmediatamente.
  	- **Carta Espejo**: permite anular un efecto negativo recibido y devolverlo.
- En cada turno:
	- El jugador elige una carta de su mano y la juega.
	- Roba una nueva carta del mazo al finalizar su jugada.
- Gana el primero que llegue a 12 puntos.

## 🧠 Inteligencia Artificial
La IA de la computadora cuenta con 3 niveles de dificultad:
- **Fácil**: juega cartas al azar.
- **Medio**: evita jugadas inefectivas:
	- No usa una carta de "sacar puntos" si el oponente tiene 0 puntos.
 	- Prioriza cartas que suman puntos si está cerca de ganar (8 o más puntos).   
- **Difícil**: elige la mejor jugada disponible según el estado actual del juego.
	- Si el jugador está cerca de ganar, prioriza cartas de “repetir turno” o “sacar puntos”.
 	- Usa carta espejo en caso de recibir una carta negativa del oponente.
  	- Prefiere repetir turno si tiene al menos una carta buena en mano.
  
## 🧪 Pruebas
Ver el archivo `pruebas.md` para conocer distintos casos de prueba realizados con descripción, salida esperada y salida obtenida.

## 🧱 Estructura y estrategia
Ver el archivo `estrategia.md` para conocer las estructuras de datos y estrategias utilizadas en el juego.
  	  
## ⚙️ Configuraciones
### Configuraciones del juego
Si deseás modificar alguna de las configuraciones del juego, podés hacerlo editando manualmente el archivo "Config.txt", respetando el siguiente formato:
```
UrlApi|Codigo identificador grupo
```
### Configuraciones de libcurl y Codeblocks
Este proyecto necesita de la instalación de curl para conectarse con la api, si no lo tiene instalado siga las siguientes instrucciones:
1. Descargar la última versión de curl desde la pagina oficial de [curl](https://curl.se/windows/).
2. Descomprimir el zip y pasar esa carpeta a una ubicación que no la vayan a borrar.
3. Agregar dentro de PATH (como variable de entorno) la ubicación a la carpeta “bin”.
4. En Codeblocks: Settings > Compiler > Linker Settings: agregar ubicación a “lib\libcurl.dll.a”.
5. En Codeblocks: Settings > Compiler > Search directories > Compiler y Resource compiler: agregar ubicación a “include”.
6. En Codeblocks: Settings > Compiler > Search directories > Linker: agregar ubicación a “lib”.

## 👥 Créditos
Este proyecto fue desarrollado por estudiantes del grupo **Vector** de Ingeniería Informática para la materia **Algoritmos y Estructuras de Datos**.
**Integrante del grupo:**
- Delgado Mailen
- Mamani Lucas
- Lopez Manuel
