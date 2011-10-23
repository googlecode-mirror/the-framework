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
    $acl->addRole('admin', 'user');
    
    // Actions
    $acl->addAction('index', 'index');
    $acl->addAction('index', 'contact');
    $acl->addAction('index', 'help');

    $acl->addAction('authentication', 'index');
    $acl->addAction('authentication', 'login');
    $acl->addAction('authentication', 'logout');
    $acl->addAction('authentication', 'recover');
    
    $acl->addAction('user', 'register');
    $acl->addAction('user', 'update');

    $acl->addAction('classifieds', 'search');
    $acl->addAction('classifieds', 'user');

    $acl->addAction('classified', 'add');
    $acl->addAction('classified', 'view');
    $acl->addAction('classified', 'comment');

    $acl->addAction('municipality', 'findByDistrictId');

    $acl->addAction('forum', '');
    // Authorization
    $acl->authorize('guest', 'index', 'index');
    $acl->authorize('guest', 'index', 'contact');
    $acl->authorize('guest', 'index', 'help');

    $acl->authorize('guest', 'user', 'register');
    $acl->authorize('user', 'user', 'update');

    $acl->authorize('guest', 'authentication', 'login');
    $acl->authorize('user', 'authentication', 'logout');
    $acl->authorize('guest', 'authentication', 'recover');

    $acl->authorize('guest', 'classifieds', 'search');
    $acl->authorize('user', 'classifieds', 'user');

    $acl->authorize('guest', 'classified', 'view');
    $acl->authorize('guest', 'classified', 'add');
    $acl->authorize('guest', 'classified', 'comment');

    $acl->authorize('guest', 'municipality', 'findByDistrictId');
    
    $acl->authorize('guest', 'forum', '');
    
    // denials
    $acl->deny('user', 'authentication', 'login');
    $acl->deny('user', 'authentication', 'recover');
    $acl->deny('user', 'user', 'register');

    $_SESSION['acl'] = serialize($acl);
} else {
    write_info_msg("Build ACL", "Retrieving from Session");
    $acl = unserialize($_SESSION['acl']);
}

Framework_Registry::set('acl', $acl);