# DoCe
Doce un juego de cartas por turnos, que simula una
batalla entre un jugador humano y una computadora. El objetivo es alcanzar 12
puntos antes que el oponente, utilizando cartas con distintos efectos. 
##Reglas del Juego
• El jugador y la máquina comienzan con 0 puntos y una mano de 3 cartas
cada uno.
• Ningún jugador puede tener puntos negativos
• Las cartas tienen diferentes efectos, entre ellos:
o +2 o +1 puntos para quien la juega.
o Sacar puntos al rival (-1 o -2).
o Repetir turno inmediatamente.
o Carta Espejo: permite anular un efecto negativo recibido y devolverlo.
• En cada turno:
o El jugador elige una carta de su mano y la juega.
o Roba una nueva carta del mazo al finalizar su jugada.
• Gana el primero que llegue a 12 puntos.
• La máquina puede jugar con distintos niveles de dificultad:
o Fácil: juega cartas al azar.
o Medio: evita jugadas inefectivas:
▪ No usa una carta de "sacar puntos" si el oponente tiene 0
puntos.
▪ Prioriza cartas que suman puntos si está cerca de ganar (por
ejemplo, si tiene 8 o 9 puntos).
o Difícil: elige la mejor jugada disponible según el estado actual del
juego.
▪ Si el jugador está cerca de ganar, prioriza cartas de “repetir
turno” o “sacar puntos”.
▪ Usa carta espejo en caso de recibir una carta negativa del
oponente
▪ Prefiere repetir turno solo si tiene más de una carta buena
en mano
