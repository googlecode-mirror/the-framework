<?php
/**
 * dispatch.inc
 * 
 * File that creates the controller and invokes the action.
 *
 * PHP Version 4 and 5
 *
 * @category Application
 * @package  Bootstrap
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 *
 */
if (false === $request instanceof Framework_Request) {
    write_error_msg("Dispatch", "Request object not instantiated.");
}

if (false === $acl->exists($request->getController(), $request->getAction())) {
    $request->setController('error');
    $request->setAction('notFound');
}

if (false === $is_authorized) {
    $request->setController('error');
    $request->setAction('prohibited');
}

$controller_nm = ucwords($request->getController());
$action_nm = $request->getAction();

$controller_path = BASE_PATH . "/application/Controller/{$controller_nm}.inc";

require_once $controller_path;
require_once 'smarty3/Smarty.class.php';
require_once 'smarty3/plugins/block.t.php';

$view = new Smarty();

$controller_class_nm = "Controller_{$controller_nm}";
$response = new Framework_Response();

try {
    $controller = new  $controller_class_nm($request, $response, $view);        
    $controller->init();
    $controller->$action_nm();
} catch (Exception $e) {
    write_error_msg("Dispatch", $e);
    $request->setController('error');
    $request->setAction('application');
    $action_nm = 'application';
}