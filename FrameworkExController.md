# Example: Create the Controller #

Criar o controller é relativamente simples. Na pasta application/Controller criar um ficheiro com o nome Hello.inc e definir a classe do controller da seguinte forma:

```
<?php
class Controller_Hello extends Framework_Controller
{
    // Método Abstracto da classe Framework_Controller
    public function init() {}

    public function action1()
    {
        //code goes here
    }
}
```