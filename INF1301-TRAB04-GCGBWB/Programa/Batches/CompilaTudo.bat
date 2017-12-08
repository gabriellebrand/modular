@ECHO  OFF
REM  Compila todos os testes

cls

del ..\produto\*.err
del ..\objetos\*.obj

pushd  .
nmake /F..\composicao\TesteGrafo.make 
popd

pushd  .
nmake /F..\composicao\TesteGrafoControleEsp.make 
popd

pushd  .
nmake /F..\composicao\TestePerfil.make 
popd

pushd  .
nmake /F..\composicao\TesteMensagem.make 
popd

pushd  .
nmake /F..\composicao\TesteControlador.make 
popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err