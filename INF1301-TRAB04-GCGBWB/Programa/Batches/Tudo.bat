@ECHO  OFF
REM  Gera, Compila e testa todos os exemplos simples 

if exist TestaTudo.bat goto faz
rem >>> esta' no diretorio ilegal
goto sai

:faz

cls

Call  Limpatudo
Call  Geratudo
Call  Compilatudo
Call  TestaTudo

:sai