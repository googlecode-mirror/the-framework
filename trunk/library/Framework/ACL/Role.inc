<?php
/**
 * Role.inc
 *
 * This file contains the Framework_ACL_Role class.
 *
 * PHP versions 4 and 5
 * 
 * @category   Framework
 * @package    Framework
 * @subpackage ACL
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    SVN: 1
 */
/**
 * This class describes an Action in the application.
 * 
 * @category   Framework
 * @package    Framework
 * @subpackage ACL
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    Release: 1
 */
class Framework_ACL_Role
{
    private $_parent;
    private $_a_authorized;
    private $_a_denied;
    
    /**
     * Constructor for the Framework_ACL_Role
     *
     * @param string $parent the name of the parent
     *
     * @access public
     * @return Framework_Role
     */
    public function __construct($parent = null)
    {
        $this->_parent = $parent;
        $this->_a_denied = array();
        $this->_a_authorized = array();
    }
    /**
     * Verifies if this role has authorization to execute an action.
     *
     * @param string $controller_nm the controller name
     * @param string $action_nm     the action name
     *
     * @æccess public
     * @return void
     */
    public function isAuthorized($controller_nm, $action_nm)
    {
        return true  === isset($this->_a_authorized[$controller_nm][$action_nm]);
    }

    /**
     * Verifies if this role has an action denied to himself.
     *
     * @param string $controller_nm the controller name
     * @param string $action_nm     the action name
     *
     * @æccess public
     * @return void
     */
    public function isDenied($controller_nm, $action_nm)
    {
        return true === isset($this->_a_denied[$controller_nm][$action_nm]);
    }
    /**
     * Adds an action to the allowed actions array
     * 
     * @param string $controller_nm The name of the controller
     * @param string $action_nm     The name of the action
     * 
     * @access public
     * @return void
     */
    public function authorize($controller_nm, $action_nm)
    {
        if (false === isset($this->_a_authorized[$controller_nm])) {
            $this->_a_authorized[$controller_nm] = array();
        }

        $this->_a_authorized[$controller_nm][$action_nm] = true;
    }
    /**
     * Adds an action to the denied actions array
     * 
     * @param string $controller_nm The name of the controller
     * @param string $action_nm     The name of the action
     * 
     * @access public
     * @return void
     */
    public function deny($controller_nm, $action_nm)
    {
        if (false === isset($this->_a_denied[$controller_nm])) {
            $this->_a_denied[$controller_nm] = array();
        }

        $this->_a_denied[$controller_nm][$action_nm] = true;
    }

    /**
     * Returns the parent's name.
     *
     * @access public
     * @return string
     */
    public function getParent()
    {
        return $this->_parent;
    }
}