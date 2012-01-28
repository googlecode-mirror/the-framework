<?php
/**
 * accesscheck.inc
 * 
 * File that verifies the user's permissions to perform the current requested action.
 *
 * PHP Version 4 and 5
 *
 * @category Application
 * @package  Bootstrap
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 *
 */
if (true === isset($acl) && true === $acl instanceof Framework_ACL 
    && true === isset($request) && true === $request instanceof Framework_Request
) {
    
    $role = "guest";
    if (true === isset($_SESSION["session_role"])) {
        $role = $_SESSION["session_role"];
    }

    Framework_Registry::set("role", $role);

    $is_authorized = $acl->isAuthorized(
        $role,
        $request->getController(),
        $request->getAction()
    );
    
    write_info_msg("Access Check", "Authorization is ${is_authorized}");
} else {
    $request->setController("error");
    $request->setAction("application");
}