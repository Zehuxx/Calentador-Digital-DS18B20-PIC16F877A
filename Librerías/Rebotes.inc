;=========Eliminar rebote en botón siguiente================================
ReboteSiguiente
;================Eliminacion de rebote==========================
		call Retardo_20ms
		call Retardo_10ms	;realizamos un retardo de 30 ms
apreta		
		btfsc PORTB,0		;comprueba si todavia esta presionado en boton
		goto yasalto		;si lo solto pues va al siguiente paso
		goto apreta		;salta a la etiqeuta apreta2
yasalto
		call Retardo_20ms	;
		call Retardo_10ms	;realiza un retardo de 30 ms
;================Fin eliminacion de rebote=======================
return

;=========Eliminar rebote en botón incrementar======================================
ReboteIncrementar
;================Eliminacion de rebote===========================
		call Retardo_20ms
		call Retardo_10ms	;realizamos un retardo de 30 ms
apreta2		
		btfsc PORTB,1		;comprueba si todavia esta presionado en boton
		goto yasalto2		;si lo solto pues va al siguiente paso
		goto apreta2		;salta a la etiqeuta apreta2
yasalto2
		call Retardo_20ms	;
		call Retardo_10ms	;realiza un retardo de 30 ms
;================Fin eliminacion de rebote======================
return

;=========Eliminar rebote en botón decrementar======================================
ReboteDecrementar
;================Eliminacion de rebote===========================
		call Retardo_20ms
		call Retardo_10ms	;realizamos un retardo de 30 ms
apreta3		
		btfsc PORTB,2		;comprueba si todavia esta presionado en boton
		goto yasalto3		;si lo solto pues va al siguiente paso
		goto apreta3		;salta a la etiqeuta apreta2
yasalto3
		call Retardo_20ms	;
		call Retardo_10ms	;realiza un retardo de 30 ms
;================Fin eliminacion de rebote======================
return
