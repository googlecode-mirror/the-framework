# How it Works: Bootstraping #
# Description #
Bootstraping requires the [mod\_rewrite](http://httpd.apache.org/docs/current/mod/mod_rewrite.html) enabled in your apache configuration and a .htaccess file in the root of your server root - usually the **public** folder.

This file is configured in such a way that the requests for static elements - images, css, js, etc. - are proceed as they usually do, but the request for a dynamic page redirected to the index.php page and the bootstraping process.

```
# Desactivar ETags
FileETag none
# Expire images header
<FilesMatch "\.(ico|pdf|flv|jpe?g|png|gif|js|css|swf)$">
    ExpiresActive On
    ExpiresDefault "access plus 1 year"
</FilesMatch>
# Regras de reencaminhamento


RewriteEngine on
RewriteCond %{REQUEST_FILENAME} !-f
RewriteCond %{REQUEST_FILENAME} !-d
RewriteRule !\.(js|ico|gif|jpe?g|png|css|pdf)$ index.php
```

These requests follow this URL pattern: `server/controller/action`. They are then processed by some other files in the bootstraping process that handle: permissions, routing, view rendering, etc.

## Bootstraping Files ##
  * bootstrap.php
  * autoload.inc
  * initconfig.inc
  * buildacl.inc
  * route.inc
  * accesscheck.inc
  * dispatch.inc
  * renderview.inc