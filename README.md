# DoCe

**DoCe** es un juego de cartas simple pero adictivo desarrollado en C, donde un jugador humano compite contra la computadora para alcanzar 12 puntos antes que su oponente.
Se trara de un juego dinámico, basado en estrategia y azar, que además permite registrar los resultados para futuras mejoras en la inteligencia artificial. 
Fue desarrollado como parte de un sistema de entrenimiento para un festival, con el objetivo de ofrecer una experiencia competitiva y divertida para los asistentes.


## Reglas del Juego
El jugador y la máquina comienzan con 0 puntos y una mano de 3 cartas
cada uno.<br />
•	Ningún jugador puede tener puntos negativos<br />
• Las cartas tienen diferentes efectos, entre ellos:<br />
	o +2 o +1 puntos para quien la juega.<br />
  o Sacar puntos al rival (-1 o -2).<br />
  o Repetir turno inmediatamente.<br />
  o Carta Espejo: permite anular un efecto negativo recibido y devolverlo.<br />
• En cada turno:<br />
  o El jugador elige una carta de su mano y la juega.<br />
  o Roba una nueva carta del mazo al finalizar su jugada.<br />
• Gana el primero que llegue a 12 puntos.<br />
• La máquina puede jugar con distintos niveles de dificultad:<br />
	o Fácil: juega cartas al azar.<br />
	o Medio: evita jugadas inefectivas:<br />
		▪ No usa una carta de "sacar puntos" si el oponente tiene 0
		puntos.<br />
		▪ Prioriza cartas que suman puntos si está cerca de ganar (por
		ejemplo, si tiene 8 o 9 puntos).<br />
	o Difícil: elige la mejor jugada disponible según el estado actual del
	juego.<br />
		▪ Si el jugador está cerca de ganar, prioriza cartas de “repetir
			turno” o “sacar puntos”.<br />
		▪ Usa carta espejo en caso de recibir una carta negativa del
			oponente<br />
		▪ Prefiere repetir turno solo si tiene más de una carta buena
			en mano<br />
## Cambiar Configuraciones
