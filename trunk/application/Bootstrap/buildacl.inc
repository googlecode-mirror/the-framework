<?php
/**
 * buildacl.inc
 * 
 * File that builds the Access Control List
 *
 * PHP Version 4 and 5
 *
 * @category Application
 * @package  Bootstrap
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 *
 */
if (false === isset($_SESSION['acl'])) {
    $acl = new Framework_ACL();

    // Roles
    $acl->addRole('guest');
    $acl->addRole('user', 'guest');
    
    // Actions
    $acl->addAction('index', 'index');
    // Authorization
    $acl->authorize('guest', 'index', 'index');

    $_SESSION['acl'] = serialize($acl);
} else {
    write_info_msg("Build ACL", "Retrieving from Session");
    $acl = unserialize($_SESSION['acl']);
}

Framework_Registry::set('acl', $acl);