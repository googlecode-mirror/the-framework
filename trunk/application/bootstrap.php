<?php
/**
 * bootstrap.php
 * 
 * Entry point for the application.
 *
 * PHP Version 4 and 5
 *
 * @category Application
 * @package  Bootstrap
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 *
 */
session_start();
define('BASE_PATH', dirname(dirname(__FILE__)));
// Most Common Includes Go Here
require 'functions.inc';
require '../library/Framework/Registry.inc';
require '../library/Framework/ACL.inc';
require '../library/Framework/ACL/Role.inc';
require '../library/Framework/Request.inc';
require '../library/Framework/Response.inc';
require '../library/Framework/Controller.inc';
require '../library/Framework/Model.inc';
require '../library/Framework/Navigation.inc';

global $debug;
$debug = false && canDebug();

global $start_time;
$start_time = microtime(true);

write_info_msg("Bootstraping", "start");

require 'Bootstrap/autoload.inc';
require 'Bootstrap/initconfig.inc';
require 'Bootstrap/buildacl.inc';
require 'Bootstrap/route.inc';
require 'Bootstrap/accesscheck.inc';
require 'Bootstrap/dispatch.inc';
require 'Bootstrap/renderview.inc';

write_info_msg("Bootstraping", "done");
$mem = round((memory_get_usage(TRUE) / 1048576), 2);
write_info_msg("Bootstraping", "used $mem MB");
session_write_close();