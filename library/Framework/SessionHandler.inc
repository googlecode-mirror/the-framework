<?php
/**
 * SessionHandler.inc
 * 
 * This file contains the Framework_SessionHandler class.
 * 
 * PHP Version 4 and 5
 * 
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  SVN: 1
 */
/**
* This class serves as a helper to deal with user data at a session level.
*
* @category   Framework
* @package    Framework
* @author     Tiago Seixas <tiagoafseixas@gmail.com>
* @license    GPLv3 http://www.gnu.org/licenses/gpl.html
* @version    Release: 1
*/
class Framework_SessionHandler
{
    private $_role_nm;
    private $_start_date;
    private $_user_id;
    private $_acl;

    private function __construct()
    {

    }

    public function setRole($role_nm)
    {
        $this->_role_nm = $role_nm;
    }

    public function getRole()
    {
        return $this->_role_nm;
    }
}