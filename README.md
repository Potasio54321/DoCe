# 🃏 DoCe 

**DoCe** es un juego de cartas simple pero adictivo desarrollado en C, donde un jugador humano compite contra la computadora para alcanzar 12 puntos antes que su oponente.
Se trata de un juego dinámico, basado en estrategia y azar, que además permite registrar los resultados en un servidor remoto mediante una API para futuras mejoras en la inteligencia artificial. 
Fue desarrollado como parte de un sistema de entrenimiento para un festival, con el objetivo de ofrecer una experiencia competitiva y divertida para los asistentes.

## Instrucciones del juego
Al iniciar, se presenta un menú interactivo. Las opciones disponibles son:

- **A) Jugar:** Se le pedirá al jugador que ingrese su nombre y seleccione el nivel de dificultad. A continuación comenzara la partida.
- **B) Ver ranking:** Se mostrara por pantalla el nombre y la cantidad de partidas ganadas de cada jugador.
- **C) Salir:** Termina el juego.


## 🎮 Reglas del Juego
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
  	  
## ⚙️ Configuraciones
