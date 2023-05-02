# Accionador-Manipulador-Electrico-Valvula-Bola-8-16v

El Archivo Aspersores.ino está pensado para operar aspersores de agua para pasto (sacate, y no se que otros nombres tenga).
Solo quería 2 minutos de riego pero ahi están los comentarios para modificarlos para más.
Quería poder manipularlo desde el cel tambien y por eso el uso del enchufe inteligente y cierta lógica adicional pensando en esto.
También quería poder cerrar la valvula sin tener que usar el pin que la propia valvula trae y por ese se ve lógica adicional apoyandonos de la EPROM.

- Casos de uso

1. Caso de uso normal.
Los aspersores riegan el pasto por 2 minutos, tan tas veces como queramos en el día.

Instrucciones
El enchufe inteligente, usando la aplicación de Sonoff y del que hayan comporado, se programa con la opción de pulsos para que automaticamente se apague a los 3 minutos.
El enchufe inteligente se agenda para que se prenda en los horarios que queramos. Por efecto de la configuración de pulsos solito se va a pagar. O si su enchufe no suporta esto, entonces agendar el apagado tambien.
Sin cambios, Arduino estaría programado para 25s de apertura de valvula + 120s de rigo + 25s de cerrado de valvula, Arduido toma entre 1-3s en iniciar el programa. Eso es un total de 2:53s. Por lo que podemos agendar nuestro apagador inteligente para apagarse a los 3 minutos.

2. Caso de uso especial cerrado de valvula.
Cerrar la valvula inmediatamente que empieza a abrirse.
Este caso de uso es normalmente cuando estamos físicamente ahi en la valvula, prendemos nuestro enchufe inteligente el cual a su vez prende arduino y empieza a abrise la valvula pero de pronto queremos que se cierre.
Lo único que hay que hacer es apagar el enchufe inteligente y volverlo a prender.
También, en dado caso que se tenga fácil acceso al botón de reinicio del arduino, también tendrá el mismo efecto.

3. Caso de uso especial apertura de valvula.
Aperturar la valvula inmediatamente que empieza a cerrarse.
El metodo es el mismo, básicamente Arduino cambia de modo entre abrir y cerrar cada vez que se reinicia dentro de los 2 minutos pre programados de riego.



- Posibles mejoras
a) El cálculo de tiempo para que sin importar el tiempo de 25s que se le da a la apertura, sean en total exactamente el tiempo destinado al riego.
b) ???
