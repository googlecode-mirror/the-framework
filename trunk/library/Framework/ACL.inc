<?php
/**
 * ACL.inc
 *
 * This file contains the Framework_ACL class.
 *
 * PHP versions 4 and 5
 * 
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  SVN: 1
 */
/**
 * This class holds the permission data for the application
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 */
class Framework_ACL
{
    private $_actions;
    private $_roles;
    private $_permissions;
    private $_denials;
    
    /**
     * Class constructor
     *
     * @access public
     * @return Framework_ACL
     */
    public function __construct()
    {

    }
    
    /**
     * Adds an action to the ACL.
     *
     * @param string $controller_nm the controller name
     * @param string $action_nm     the action name
     *
     * @access public
     * @return void
     */
    public function addAction($controller_nm, $action_nm)
    {
        if (false === isset($this->_actions[$controller_nm])) {
            $this->_actions[$controller_nm] = array();
        }

        $this->_actions[$controller_nm][$action_nm] = true;

        write_info_msg("ACL", "Added action {$controller_nm}->{$action_nm}");
    }
    
    /**
     * Adds a role to the ACL.
     *
     * @param string $role_nm   the name of the role
     * @param string $parent_nm the parent role name
     *
     * @access public
     * @return void
     */
    public function addRole($role_nm, $parent_nm = null)
    {
        if ($parent_nm !== null && false === isset($this->_roles[$parent_nm])) {
            write_error_msg(
                "ACL", 
                "Error defining Role {$role_nm}. Parent {$parent_nm} is not defined"
            );
            return false;
        }

        $this->_roles[$role_nm] = new Framework_ACL_Role($parent_nm);
    }

    /**
     * Authorizes an action for a role.
     *
     * @param string $role_nm       the name of the role
     * @param string $controller_nm the name of the controller
     * @param string $action_nm     the name of the action
     *
     * @access public
     * @return boolean
     */
    public function authorize($role_nm, $controller_nm, $action_nm)
    {
        if (false === isset($this->_roles[$role_nm])) {
            write_error_msg(
                "ACL",
                "Error authorizing action for Role $role_nm. Role does not exist."
            );
            return false;
        }

        if (false === isset($this->_actions[$controller_nm])
            || false === isset($this->_actions[$controller_nm][$action_nm])
        ) {
            write_error_msg(
                "ACL",
                "Error authorizing action for Role $role_nm. Action does not exit."
            );
            return false;
        }

        $this->_roles[$role_nm]->authorize($controller_nm, $action_nm);
        write_info_msg(
            "ACL", 
            "Authorized Action {$controller_nm}->{$action_nm} to {$role_nm}"
        );
    }

    /**
     * Denies an action for a user.
     *
     * @param string $role_nm       the name of the role
     * @param string $controller_nm the name of the controller
     * @param string $action_nm     the name of the action
     *
     * @access public
     * @return void
     */
    public function deny($role_nm, $controller_nm, $action_nm)
    {
        if (false === isset($this->_roles[$role_nm])) {
            write_error_msg(
                "ACL",
                "Error denying action for Role $role_nm. Role does not exist."
            );
            return false;
        }

        if (false === isset($this->_actions[$controller_nm])
            || false === isset($this->_actions[$controller_nm][$action_nm])
        ) {
            write_error_msg(
                "ACL",
                "Error denying action for Role $role_nm. Action does not exit."
            );
            return false;
        }

        $this->_roles[$role_nm]->deny($controller_nm, $action_nm);
        write_info_msg(
            "ACL",
            "Denied Action {$controller_nm}->{$action_nm} to {$role_nm}"
        );
    }

    /**
     * Verifies if a user has permissions to execute an action
     *
     * @param string $role_nm       the name of the role
     * @param string $controller_nm the name of the controller
     * @param string $action_nm     the name of the action
     *
     * @access public
     * @return boolean
     */
    public function isAuthorized($role_nm, $controller_nm, $action_nm)
    {
        if (false === isset($this->_roles[$role_nm])) {
            write_error_msg(
                "ACL",
                "Error checking Action {$controller_nm}->{$action_nm}".
                " for Role $role_nm. Role does not exist."
            );
            return false;
        }

        if (false === isset($this->_actions[$controller_nm][$action_nm])
        ) {
            write_error_msg(
                "ACL",
                "Error checking Action {$controller_nm}->{$action_nm} " .
                "for Role $role_nm. Action does not exit."
            );
            return false;
        }

        $role = $this->_roles[$role_nm];
        
        if ($role !== null && $role->getParent() !== null) {
            write_info_msg(
                "ACL",
                "Checking Role {$role_nm} and Parent authorization".
                " for {$controller_nm}->{$action_nm}"
            );
            $is_denied = $this->_roles[$role_nm]->isDenied(
                $controller_nm,
                $action_nm
            );
            $is_parent_denied = $this->_roles[$role->getParent()]->isDenied(
                $controller_nm,
                $action_nm
            );
            if (true === $is_denied || true === $is_parent_denied) {
                return false;
            }

            $is_authorized = $this->_roles[$role_nm]->isAuthorized(
                $controller_nm,
                $action_nm
            );

            $is_parent_authorized = $this->isAuthorized(
                $role->getParent(),
                $controller_nm,
                $action_nm
            );

            return true === $is_authorized || true === $is_parent_authorized;
        } else {
            write_info_msg(
                "ACL",
                "Checking Role {$role_nm} authorization".
                " for {$controller_nm}->{$action_nm}"
            );
            return true === $this->_roles[$role_nm]->isAuthorized(
                $controller_nm,
                $action_nm
            );
        }
    }

    /**
     * Checks the existence of an action.
     *
     * @param string $controller_nm the name of the controller
     * @param string $action_nm     the name of the action
     *
     * @access public
     * @return boolean
     */
    public function exists($controller_nm, $action_nm)
    {
        return isset($this->_actions[$controller_nm][$action_nm]);
    }
}