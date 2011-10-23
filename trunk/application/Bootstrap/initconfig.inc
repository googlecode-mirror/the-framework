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
// Common Includes
require 'Log.php';

//Ini Files
if (false === isset($_SESSION['DB_CONFIGS'])) {
    write_info_msg("Init Config", "Loading DB Configs");
    $init_conf_path = BASE_PATH . '/application/Config/';
    
    $db_confs  = parse_ini_file($init_conf_path . 'db.ini', true);
    $app_confs = parse_ini_file($init_conf_path . 'application.ini', true);

    $_SESSION['DB_CONFIGS']  = $db_confs['pdo'];
    $_SESSION['APP_CONFIGS'] = $app_confs;
}

Framework_Registry::set('db_configs', $_SESSION['DB_CONFIGS']);

$app_configs = $_SESSION['APP_CONFIGS'];
foreach ($app_configs['application'] as $key => $value) {
    Framework_Registry::set($key, $value);
}
foreach ($app_configs['i18n'] as $key => $value) {
    Framework_Registry::set($key, $value);
}

Framework_Registry::set('LOG_MASK', Log::MASK(PEAR_LOG_DEBUG));

// Locale Configuration
//@todo: inicializar a variavel $language com os valores recebidos do lado do cliente
$locale_folder = Framework_Registry::get('LOCALE_PATH');
$language = Framework_Registry::get('DEFAULT_LANGUAGE');
$domain = Framework_Registry::get('DEFAULT_DOMAIN');

$language .= ".utf8";
putenv("LANG={$language}");
setlocale(LC_ALL, $language);
bindtextdomain($domain, $locale_folder);
bind_textdomain_codeset($domain, Framework_Registry::get('DEFAULT_CODESET'));
textdomain($domain);
// End locale Configuration