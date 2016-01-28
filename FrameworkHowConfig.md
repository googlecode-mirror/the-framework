# Ficheiros de Configuração #
Existem três ficheiros de configuração:
  * application.ini
  * db.ini
  * navigation.xml

## application.ini ##
Contém a configuração do Log e de Locale.
```
[application]
LOG_HANDLER=file
LOG_PATH=../logs/default.log
HTTP_STATIC_CONTEXT=/
[i18n]
LOCALE_PATH=ROOT_PATH'/i18n'
DEFAULT_LANGUAGE=pt_PT
DEFAULT_CODESET=UTF-8
DEFAULT_DOMAIN=messages
```
## db.ini ##
Contém a configuração de acesso à base de dados:
```
[pdo]
pdo_driver=mysql
mysql_host=localhost
mysql_dbname=<schema name>
mysql_user=user
mysql_password=password
```
## navigation.xml ##
Ao contrário dos outros este ficheiro é opcional e deve ser utilizado caso seja a framework a gerir o menu da plataforma. Não esquecer que o resultado deste ficheiro irá depender da configuração da ACL.
```
<?xml version="1.0" encoding="ISO-8859-1"?>
<nav>
  <item>
    <id>login</id>
    <label>login</label>
    <controller>authentication</controller>
    <action>login</action>
    <auth>authentication:login</auth>
    <nav_path>authentication:login</nav_path>
  </item>
</nav>
```