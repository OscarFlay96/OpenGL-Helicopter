**Gráficos por Computador**

**Práctica 4 –Modelo HELICÓPTERO**

Hemos decido implementar una escena dinámica. En particular, hemos implementado una aplicación que muestra el modelo helicóptero mostrado en la Figura 1. y en la Figura 2.

![](RackMultipart20200910-4-1b8o67h_html_a6c5d04e6753e386.jpg)

Figura 1. Helicóptero estático.

![](RackMultipart20200910-4-1b8o67h_html_e655fd6c2e4c4e40.gif)

Figura 2. Helicóptero sobrevolando la escena.

1. Modelo de proyección y ubicación de la cámara

-Proyección en perspectiva con fovy variando entre 10 y 90, plano near = 0.1 y plano far = 25 y viewport con tamaño 600x600 en origen.

-Cámara ubicada en el punto (x,y,z) mirando hacia el helicóptero, vector up = (0,1,0) y vector look at = (desX, desY, desZ).

2. Suelo sobre el que se visualiza el helicóptero

-La superficie ocupada por dicho suelo, situado en y= 0 es de 4X4 unidades en el plano XZ y su textura es &#39;baldosas&#39;, se muestra mediante la función &#39;drawSuelo()&#39;.

-Adicionalmente, se ha añadido un helipuerto, cuyo tamaño es 0.5x0.5, con textura &#39;helipuerto&#39;, se muestra mediante la función &#39;drawHelipuerto()&#39;.

3. Descripción de los elementos que componen el helicóptero

- **Cabina** : Elipsoide de diámetro menor = 0.055 y diámetro mayor = 0.075 con textura &#39;helicoptero&#39;, se muestra mediante la función &#39;drawCabina()&#39;.

- **Cristal** : Esfera de diámetro = 0.075 con transparencia &#39;silver&#39;, se muestra mediante la función &#39;drawCristal()&#39;.

- **Articulación Cabina** : Cilindro de longitud = 0.1 y diámetro = 0.05 con material &#39;gold&#39;, se muestra mediante la función &#39;drawSoporte()&#39;.

- **Hélice Cabina** : Formada por dos aspas, conos de altura = 0.15 y diámetro menor = 0.010 y diámetro mayor = 0.05, con material &#39;brass&#39;, se muestra mediante la función &#39;drawAspasSuperiores()&#39;.

- **Cola** : Cono de altura =0.15 y diámetro = 0.06 con material &#39;cromado&#39;, se muestra mediante la función &#39;drawCola()&#39;.

- **Cilindro Inferior** : Cilindro de longitud = 0.05, diámetro menor = 0.04 y diámetro mayor = 0.1 con material &#39;cromado&#39;, se muestra mediante la función &#39;drawCilindro()&#39;.

- **Articulación Inferior** : Esfera de diámetro = 0.02, con material &#39;ruby&#39;, se muestra mediante la función &#39;drawArticulacion()&#39;.

- **Hélice Cola** : Formada por cuatro aspas, conos de altura = 0.06, diámetro menor = 0.02 y diámetro mayor = 0.08, con material &#39;brass&#39;, las aspas se pintan en la escena gracias a la función &#39;drawAspaCola()&#39; y la hélice formada a partir de ellas se muestra mediante la función &#39;drawHeliceCola()&#39;.

- **Patas helicóptero** : Formadas por dos cilindros, cilindro vertical de longitud = 0.05 y diámetro 0.02 = y cilindro horizontal de longitud = 0.3 y diámetro = 0.03, ambos con material &#39;cromado&#39;, se muestra mediante la función &#39;drawPatas()&#39;.

-Los anteriores componentes se encuentran encapsulados en la función &#39;drawHelicoptero()&#39; a través de la cual obtenemos el modelo Helicóptero.

4. Modularidad y diseño del código

Hemos encapsulado las funciones que dibujan los componentes de la siguiente manera:

-Las funciones correspondientes a Cristal y Cabina son independientes para poder aplicar la trasparencia y la textura solo a dichos componentes.

-El método para para pintar la Cola del helicóptero contiene al método para pintar el Cilindro, que es el nexo para unir Cola con Articulación y Hélice Cola en ambos lados.

-La función para dibujar el Cilindro contiene las Hélice Cola, que a su veces contiene las Aspas Cola, y la Articulación.

-El método para dibujar el Aspa Superior de la Cabina, tiene encapsulado el pintado de las dos Aspas Superiores así como el Soporte que las une a la Cabina.

-Las Patas del helicóptero contiene el par de Cilindros que conforman ambas patas.

5. Uso de texturas

Se usan texturas en las caras anteriores y posteriores tanto de las baldosas del suelo como de los fondos que componen el skyline. En las partes posteriores no se refleja la luz y se han añadido las texturas de &#39;suelo&#39;, &#39;helipuerto&#39;, &#39;edifico&#39; y &#39;skyline&#39;.

6. Uso de transparencias

Se ha decidido usar transparencias para simular el cristal que compone la cabina, transparencia &#39;silver&#39;. De esta manera, a través de la cabina quedaría visible la textura que conforma la cabina del helicóptero.

7. Movimiento e interacción con los objetos

Los objetos que recrean movimiento dentro del helicóptero son:

-Hélices Cola: Movimiento rotatorio de 3 radianes cada 20 milisegundos de manera automática.

-Hélice Superior: Movimiento rotatorio de 5 radianes cada 20 milisegundos de manera que pueda ser controlado por el usuario a través de la tecla &#39;f&#39;, puede pararse o reanudarse.

-El helicóptero se mueve a lo largo de los tres ejes y rota sobre sí mismo.

8. Movimiento e interacción con la cámara

Se ha mantenido el modelo de esfera para el movimiento del ratón con la cámara en la semiesfera pero se ha cambiado el vector look at para que apunte siempre al modelo helicóptero.

9. Movimiento e interacción con las luces

-Luz focal: Trata de simular la luz de un rascacielos, posicionada en la esquina del edifico con dirección variable hacia la posición del modelo helicóptero.

-Luz direccional: Se ubica cerca del edificio para aportar luz a los fondos y se direcciona hacia abajo. Esta luz puede controlarse en su intensidad con las teclas flecha arriba y flecha abajo del teclado.

-Luz posicional: Se ubica dentro del helicóptero y se mueve con él para simular el foco de un helicóptero.

10. Habilitar o deshabilitar funcionalidades

Se ha creado un sistema de arranque en el helicóptero que se acciona con la tecla &#39;f&#39; habilitando o deshabilitando la rotación de la hélice superior y la luz posicional del helicóptero.

11. Otros elementos destacables

-Se ha recreado con el mayor realismo posible todos los movimientos de un helicóptero, de forma que cuando realiza movimientos en los ejes tiene una rotación correspondiente a las físicas reales.

-Se ha añadido una función extra para restablecer la posición del helicóptero al origen de coordenadas, mediante la tecla &#39;o&#39;.

12. Tabla de instrucciones

| **Tecla** | **Acción** |
| --- | --- |
| ↑ ↓ | Sube y baja la intensidad de la luz direccional. |
| o | Restablecer la posición del helicóptero al origen de coordenadas. |
| f | Arranque y parada del helicóptero (Hélice Superior y Luz Posicional). |
| a d | Rotación del helicóptero en torno al eje Y, rotando sobre sí mismo. |
| z x | Desplazamiento del helicóptero en el eje Z y rotación en el eje X, moviéndose hacia izquierda y derecha. |
| e q | Desplazamiento del helicóptero en el eje Y, subiendo y bajando el vuelo del helicóptero. |
| w s | Desplazamiento del helicóptero en el eje X y rotación en el eje Z, avanzando y retrocediendo. |
