@ECHO  OFF
REM  Compila todos os testes

cls

del ..\produto\*.err
del ..\objetos\*.obj

pushd  .
nmake /F..\composicao\TesteGrafoControleEsp.make 
popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err