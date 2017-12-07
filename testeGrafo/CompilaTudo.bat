@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TesteGrafo.exe

del *.obj
nmake /FTesteGrafo.make 

copy  *.err  tudo.err

notepad tudo.err

popd
