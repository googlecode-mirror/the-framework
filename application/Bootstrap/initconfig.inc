<?php
/**
 * initconfig.inc
 *
 * This loads the files in the Config path and puts their content into session
 * and into the Registry.
 *
 * PHP Version 4 and 5
 *
 * @category Application
 * @package  Bootstrap
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 */
// ==================================================================================
// Parse the ini files if they are not already in session
// ==================================================================================
if (false === isset($_SESSION['DB_CONFIGS'])) {
    $init_conf_path = BASE_PATH . '/application/Config/';
    
    $db_confs  = parse_ini_file($init_conf_path . 'db.ini', true);

    $_SESSION['DB_CONFIGS']  = $db_confs['pdo'];
    $_SESSION['APP_CONFIGS'] = parse_ini_file(
        $init_conf_path . 'application.ini',
        true
    );
}
// ==================================================================================
// Pass the values in session to the registry
// ==================================================================================
Framework_Registry::set('db_configs', $_SESSION['DB_CONFIGS']);
$app_configs = $_SESSION['APP_CONFIGS'];
foreach ($app_configs as $k => $arr) {
    foreach($arr as $key => $value) {
        Framework_Registry::set($key, $value);
    }
}
// ==================================================================================
// Log level
// ==================================================================================
define('DEFAULT_LOG_LEVEL', LOG_ERR);

// ==================================================================================
// Locale configuration. We get the default values from the registry
// ==================================================================================
//@todo: inicializar a variavel $language com os valores recebidos do lado do cliente
$locale_folder = Framework_Registry::get('LOCALE_PATH');
$language      = Framework_Registry::get('DEFAULT_LANGUAGE');
$domain        = Framework_Registry::get('DEFAULT_DOMAIN');

$language .= ".utf8";
putenv("LANG={$language}");
setlocale(LC_ALL, $language);
bindtextdomain($domain, $locale_folder);
bind_textdomain_codeset($domain, Framework_Registry::get('DEFAULT_CODESET'));
textdomain($domain);
// ==================================================================================
// End Locale configuration.
// ==================================================================================