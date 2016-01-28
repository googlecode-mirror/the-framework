# How it Works: Autoloading #
A utilização de autoload permite que o php verifique que quando tentas instanciar uma classe ele verifique se existe ou não e caso não exista, vai invocar a função que se encontra no ficheiro autoload.inc e pequisa nas pastas ai definidas o ficheiro apropriado para fazer include.

De modo a optimizar a utilização deste recurso os ficheiros mais utilizados pela framework são carregados directamente à cabeça do bootstrap.inc.