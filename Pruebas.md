# Casos de Prueba  

<table>
  <tr>
    <th>Descripción</th>
    <th>Salida esperada</th>
    <th>Salida Obtenida</th>
  </tr>
  <tr>
    <td>Se quiere probar qué es lo que pasaría si la máquina juga una carta en dificultad fácil.</td>
    <td>Se espera que la máquina juegue una carta al azar.</td>
    <td>La salida obtenida fue que la máquina jugó una carta al azar.</td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: center;">
      <img src="imagenes/Prueba Facil.png" alt="Facil">
    </td>
  </tr> 
  <tr>
    <td>Se quiere probar qué es lo que pasaría si el jugador tiene 0 puntos y la máquina juega una carta en dificultad media.</td>
    <td>Se espera que la máquina intente jugar una carta que no sea de sacar puntos.</td>
    <td>La salida obtenida fue que la máquina jugó una carta que no era de sacar puntos. </td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: center;">
      <img src="imagenes/Prueba Normal 0.png" alt="Normal0">
    </td>
  </tr> 
  <tr>
    <td>Se quiere probar qué es lo que pasaría si la máquina tiene 8 o más puntos y tiene cartas de +2 o +1 en dificultad media.</td>
    <td>Se espera que la máquina juegue una carta +2 o +1.</td>
    <td>La salida obtenida fue que la máquina jugó una carta +2 o +1 que tenía disponible.</td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: center;">
      <img src="imagenes/Prueba Normal 8.png" alt="Normal8">
    </td>
  </tr> 
  <tr>
    <td>Se quiere probar qué es lo que pararía si la máquina tiene la posibilidad de ganar con una de las cartas que tiene disponible en dificultad difícil.</td>
    <td>Se espera que la máquina juegue la carta que le permita ganar.</td>
    <td>La salida obtenida fue que la máquina jugó la carta que le permitió ganar.</td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: center;">
      <img src="imagenes/PruebaDificil1.png" alt="Capura1">
    </td>
  </tr> 
  <tr>
    <td>Se quiere probar qué es lo que pasaría si el jugador está cerca de ganar (8 o más puntos) y la máquina juega una carta en dificultad difícil.</td>
    <td>Se espera que la máquina intente jugar una carta en este orden de prioridad: -2, -1, REPITE (si tengo al menos 2 cartas buenas).</td>
    <td>La salida obtenida fue que la maquina jugó la carta que tenía disponible de mayor prioridad.</td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: center;">
      <img src="imagenes/PruebaDificil2.png" alt="Capura1">
    </td>
  </tr> 
  <tr>
    <td>Se quiere probar qué es lo que pasaría si el jugador le tira una carta negativa a la máquina y la maquina tiene la carta ESPEJO en dificultad difícil.</td>
    <td>Se espera que la maquina juegue la carta ESPEJO. </td>
    <td>La salida obtenida fue que la máquina jugó la carta ESPEJO.</td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: center;">
      <img src="imagenes/PruebaDificil3.png" alt="Capura1">
    </td>
  </tr> 
  <tr>
    <td>Se quiere probar qué es lo que pasaría si se elige la opción B) Ver ranking</td>
    <td>Se espera que se muestre por pantalla el nombre y la cantidad de partidas ganadas de cada jugador.</td>
    <td>La salida obtenida fue que se mostró por pantalla el nombre y la cantidad de partidas ganadas de cada jugador.</td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: center;">
      <img src="imagenes/Prueba Ranking.png" alt="Ranking">
    </td>
  </tr>
  <tr>
    <td>Se quiere probar qué el mazo de descartes tenga 35 elementos</td>
    <td>Se espera que diga que hay 35 elementos en descartes, y 40 cartas en total. Porque 35(Descartadas)+5(Por Jugarse)</td>
    <td>La salida obtenida fue hay 35 cartas en el mazo descarte, 5 en los jugadores y 40 en total</td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: center;">
      <img src="imagenes/Prueba Cartas.png" alt="Cartas">
    </td>
  </tr> 
  </table>
  
 
