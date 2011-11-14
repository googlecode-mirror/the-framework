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
require 'functions.inc';
require '../library/Framework/ACL.inc';
require '../library/Framework/ACL/Role.inc';
require '../library/Framework/Controller.inc';
require '../library/Framework/Form.inc';
require '../library/Framework/LogFactory.inc';
require '../library/Framework/Model.inc';
require '../library/Framework/Navigation.inc';
require '../library/Framework/Navigation/Item.inc';
require '../library/Framework/Registry.inc';
require '../library/Framework/Request.inc';
require '../library/Framework/Response.inc';

define('DEBUG_ENABLED', false && can_debug());

require 'Bootstrap/autoload.inc';
require 'Bootstrap/initconfig.inc';

write_info_msg("Bootstraping", "start");

require 'Bootstrap/buildacl.inc';
require 'Bootstrap/route.inc';
require 'Bootstrap/accesscheck.inc';

require '../library/Smarty-3.1.4/libs/Smarty.class.php';
require '../library/Smarty-3.1.4/libs/plugins/block.t.php';

require 'Bootstrap/dispatch.inc';
require 'Bootstrap/renderview.inc';

write_info_msg("Bootstraping", "done");
session_write_close();