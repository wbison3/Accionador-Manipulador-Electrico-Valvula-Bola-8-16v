# Accionador-Manipulador-Electrico-Valvula-Bola-8-16v

* Código Arduino, revisar el archivo Aspersores.ino
* Lista de Materiales, revisar el archivo BoM

Demo: https://youtu.be/fxEmD51HoMo

El Archivo Aspersores.ino está pensado para operar aspersores de agua para pasto (sacate, y no se que otros nombres tenga).  
* Solo quería 2 minutos de riego pero ahi están los comentarios para modificarlos para más.  
* Quería poder manipularlo desde el cel tambien y por eso el uso del enchufe inteligente y cierta lógica adicional pensando en esto.  
* También quería poder cerrar la valvula sin tener que usar el pin que la propia valvula trae y por ese se ve lógica adicional apoyandonos de la EPROM.  
  
Armado
=======
1. Ambos ejes de rotación deben quedar lo mejor alineados posible. Esto es alinear el eje de rotación de la manivela del manipulador eléctrico al eje de rotación de la válvula a manipular y que tenga poco juego. Ni nada, ni mucho, poco juego. Esta es probablemente la parte más dificil o la más fácil dependiendo si te sirve el soporte tal cual. Dejo fotos y video de cómo adaptamos nosotros para llave de 1 pulgada, ya que con el soporte que viene no fue posible sin modificaciones.  <br><img width="250" src="https://github.com/wbison3/Accionador-Manipulador-Electrico-Valvula-Bola-8-16v/blob/main/Soporte%20y%20alineaci%C3%B3n%20de%20ejes%20de%20rotaci%C3%B3n.jpg">  
2. El Manipulador Eléctrico debe estar lo más firme posible, lo suficiente para contra restar la fuerza necesaria para abrir la valvula.  
3. Es recomendable estañar las puntas de los cables para que su agarre sea más firme al atornillarlos en los conectores. Solo es calentar la punta del cable con un cautín hasta que la soldadura se derrita y fluya por la punta 1 o 2 segundos.  
4. Es probable que ocupes algún extensor de Wi-Fi para que se conecte corretamente el enchufe inteligente.  
5. El código esta pensado para que FORWARD abra y BACKWARD cierre. Por lo que la polaridad de M1 debe ser negro,rojo como se muestra  
6. Es posible usar 1 solo eliminador, o un eliminador más pequeño para Arduino. Como compro de a varios estos eliminadores, por eso use uno de 12v2a para arduino también y quería un diseño más robusto al usar fuentes de poder independientes. No olvides desconectar el jumper de poder del shield para no dañar el arduino en caso que decidas tener fuente de alimentación independiente también.  
7. Conseguir algún tipo de caja que proteja de polvo y contaminación la tarjeta de arduino.  

  
Casos de uso  
============
  
1. Caso de uso normal.  
Los aspersores riegan el pasto por 2 minutos, tan tas veces como queramos en el día.  
Instrucciones  
- El enchufe inteligente, usando la aplicación de Sonoff o del que hayan comporado, se programa con la opción de pulsos para que automaticamente se apague a los 3 minutos.  
- El enchufe inteligente se agenda para que se prenda en los horarios que queramos. Por efecto de la configuración de pulsos solito se va a pagar. O si su enchufe no suporta esto, entonces agendar el apagado tambien.  
Sin cambios, Arduino estaría programado para 25s de apertura de valvula + 120s de riego + 25s de cerrado de valvula, Arduido toma entre 1-3s en iniciar el programa. Eso es un total de 2min 53s. Por lo que podemos agendar nuestro apagador inteligente para apagarse a los 3 minutos.  
  
2. Caso de uso especial cerrado de valvula.  
Cerrar la valvula inmediatamente que empieza a abrirse.  
Este caso de uso es normalmente cuando estamos físicamente ahi en la valvula, prendemos nuestro enchufe inteligente el cual a su vez prende arduino y empieza a abrise la valvula pero de pronto queremos que se cierre.  
Lo único que hay que hacer es apagar el enchufe inteligente y volverlo a prender.  
También, en dado caso que se tenga fácil acceso al botón de reinicio del arduino, también tendrá el mismo efecto.  
  
3. Caso de uso especial apertura de valvula.  
Aperturar la valvula inmediatamente que empieza a cerrarse.  
El metodo es el mismo, básicamente Arduino cambia de modo entre abrir y cerrar cada vez que se reinicia dentro de los 2 minutos pre programados de riego.  
  
  
Posibles mejoras
================

a) El cálculo de tiempo para que sin importar el tiempo de apertura, sean en total exactamente el tiempo destinado al riego.  
b) ???  

