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
define('START_TIME', microtime(true));

// Most Common Includes Go Here
include 'functions.inc';
include '../library/Framework/ACL.inc';
include '../library/Framework/ACL/Role.inc';
include '../library/Framework/Controller.inc';
include '../library/Framework/Form.inc';
include '../library/Framework/Model.inc';
include '../library/Framework/Navigation.inc';
include '../library/Framework/Navigation/Item.inc';
include '../library/Framework/Registry.inc';
include '../library/Framework/Request.inc';
include '../library/Framework/Response.inc';

define('DEBUG_ENABLED', true && can_debug());

include 'Bootstrap/autoload.inc';
include 'Bootstrap/initconfig.inc';

write_info_msg("Bootstraping", "start");

include 'Bootstrap/buildacl.inc';
include 'Bootstrap/route.inc';
include 'Bootstrap/accesscheck.inc';

include '../library/Smarty-3.1.4/libs/Smarty.class.php';
include '../library/Smarty-3.1.4/libs/plugins/block.t.php';

include 'Bootstrap/dispatch.inc';
include 'Bootstrap/renderview.inc';

write_info_msg("Bootstraping", "done");
session_write_close();
