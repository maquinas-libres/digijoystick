En digikeyboard no existe un modo de sostener una tecla por un buen rato, asi que tube que modificar la libreria para 
que haga eso.

~~~
DigiKeyboard.sendKeyStroke(KEY_Q); // presiona la tecla
DigiKeyboard.delay(1000); // la presiona un segundo
DigiKeyboard.sendKeyStroke(0); // la libera
~~~
