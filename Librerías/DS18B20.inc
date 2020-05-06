;ZONA DE DATOS

CBLOCK
     DS18B20_TemperaturaSigno
     DS18B20_TemperaturaByte1			; Primer byte leído del termómetro DS18B20
     DS18B20_TemperaturaByte2			; Segundo byte leído del termómetro DS18B20
     DS18B20_Temperatura
     DS18B20_TemperaturaDecimal		; Parte decimal de la temperatura medida.
ENDC

DS18B20_Skip_ROM_Command	EQU	0xCC	; Comandos del DS18B20.
DS18B20_Read_Scratchpad_Command	EQU	0xBE
DS18B20_Convert_T_Command	EQU	0x44
;
; Subrutina "DS1820_Inicializa" ---------------------------------------------------------
;
; Inicializa el DS18B20 para que comience la conversión de temperatura.
;
DS18B20_Inicializa
	call	Bus1Linea_Reset		; Primero los pulsos de Reset y Presence.
	movlw	DS18B20_Skip_ROM_Command ; Salta los comandos de ROM ya que hay
	call	Bus1Linea_EscribeByte	; conectado un único dispositivo al bus.
	movlw	DS18B20_Convert_T_Command ; Para que comience la conversiÃ³n de temperatura.
	call	Bus1Linea_EscribeByte
	return
	
; Subrutina "DS1820_LeeTemperatura" -----------------------------------------------------

DS18B20_LeeTemperatura
	call	Bus1Linea_Reset		; Primero los pulsos de "Reset" y "Presence".
	movlw	DS18B20_Skip_ROM_Command ; Salta los comandos de ROM ya que hay
	call	Bus1Linea_EscribeByte	; conectado un Ãºnico dispositivo al bus.
	movlw	DS18B20_Read_Scratchpad_Command ; Va a leer la primera posiciÃ³n de memoria,
	call	Bus1Linea_EscribeByte	; donde se localiza el valor de la temperatura.
	call	Bus1Linea_LeeByte		; Lee la temperatura en 
	movwf	DS18B20_TemperaturaByte1	; complemento a 2.
	call	Bus1Linea_LeeByte		; Ahora lee el segundo byte que indica el signo
	movwf	DS18B20_TemperaturaByte2	; de la temperatura.
	call	Bus1Linea_Reset		; Y para terminar, resetea el dispositivo.
;
; Ahora deduce si la temperatura es positiva o negativa y halla su valor absoluto.
;	
	clrf 	DS18B20_TemperaturaSigno
	btfss	DS18B20_TemperaturaByte2,7	; Si cualquier bit es "1": temperatura negativa.
	goto 	DS18B20_TemperaturaDecimalSelecionar	; La temperatura es positiva y salta.
DS18B20_TemperaturaSignoNegativo
	movlw 	b'11111111'
	movwf 	DS18B20_TemperaturaSigno
DS18B20_TemperaturaDecimalSelecionar
	movlw	.0
	btfsc 	DS18B20_TemperaturaByte1, 3
	movlw 	.50
	movwf 	DS18B20_TemperaturaDecimal
DS18B20_TemperaturaCompleta
	bcf	STATUS,C			; Para no corromper luego el MSB.
	movf 	DS18B20_TemperaturaByte1, W
	andlw 	b'11110000'
	movwf	DS18B20_TemperaturaByte1
	rrf	DS18B20_TemperaturaByte1,F	; Obtiene el valor absoluto de la temperatura.
	rrf	DS18B20_TemperaturaByte1,F	; Obtiene el valor absoluto de la temperatura.
	rrf	DS18B20_TemperaturaByte1,F	; Obtiene el valor absoluto de la temperatura.
	rrf	DS18B20_TemperaturaByte1,F	; Obtiene el valor absoluto de la temperatura.
	
	movf 	DS18B20_TemperaturaByte2, W
	andlw 	b'00001111'
	movwf	DS18B20_TemperaturaByte2
	rlf 	DS18B20_TemperaturaByte2, F
	rlf 	DS18B20_TemperaturaByte2, F
	rlf 	DS18B20_TemperaturaByte2, F
	rlf 	DS18B20_TemperaturaByte2, F

	movf 	DS18B20_TemperaturaByte2, W
	xorwf 	DS18B20_TemperaturaByte1, W
	movwf 	DS18B20_Temperatura
DS18B20_TemperaturaAbsoluta
	btfss 	DS18B20_TemperaturaSigno, 0
	goto 	DS18B20_FinLeeTemperatura
	movf 	DS18B20_Temperatura, W ; Saca el valor absoluto de la temperatura bajo cero
	sublw 	0x00
	movwf 	DS18B20_Temperatura
	btfss	DS18B20_TemperaturaDecimal, 1
	goto	DS18B20_FinLeeTemperatura
	decf 	DS18B20_Temperatura
DS18B20_FinLeeTemperatura
	movf 	DS18B20_Temperatura, W
	return