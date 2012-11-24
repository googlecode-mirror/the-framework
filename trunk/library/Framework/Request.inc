<?php
/**
 * Request.inc
 *
 * This file contains the Framework_Request class.
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
 * This class is used to relay request related information to
 * the application controllers.
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 */
class Framework_Request
{
    private $_request_type;
    private $_params;
    private $_controller;
    private $_action;

    /**
     * The constructor for the Framework_Request object
     *
     * @param string $controller the name of the controller
     * @param string $action     the name of the action
     *
     * @access public
     * @return Framework_Request
     */
    public function __construct($controller, $action)
    {
        $this->_controller = $controller;
        $this->_action = $action;
        $this->_params = array_merge($_GET, $_POST);
    }

    /**
     * Returns the action
     * 
     * @access public
     * @return string
     */
    public function getAction()
    {
        return $this->_action;
    }

    /**
     * Sets the action
     * 
     * @param string $action the name of the action
     * 
     * @access public
     * @return string
     */
    public function setAction($action)
    {
        $this->_action = $action;
    }

    /**
     * Returns the controller
     * 
     * @access public
     * @return string
     */
    public function getController()
    {
        return $this->_controller;
    }
    
    /**
     * Sets the controller
     * 
     * @param string $controller the controller name
     * 
     * @access public
     * @return void
     */
    public function setController($controller)
    {
        $this->_controller = $controller;
    }

    /**
     * Returns the complete array of parameters
     *
     * @access public
     * @return array
     */
    public function getParams()
    {
        return $this->_params;
    }
    
     /* Override the complete array of parameters
     *
     * @access public
     */
    public function setParams($params)
    {
        $this->_params = $params;
    }

    /**
     * Returns a parameter
     *
     * @param string $key The parameter name
     * 
     * @access public
     * @return mixed
     */
    public function getParam($key)
    {
        if (isset($this->_params[$key])) {
            return $this->_params[$key];
        }
    }

    /**
     * If the request was submited via GET or POST
     *
     * @access public
     * @return boolean
     */
    public function isPost()
    {
        return ('POST' === $_SERVER['REQUEST_METHOD']);
    }
    /**
     * Was the request received via an AJAX call or not.
     *
     * @access public
     * @return bool
     */
    public function isXmlHttpRequest()
    {
        return (isset($_SERVER['HTTP_X_REQUESTED_WITH']) &&
        $_SERVER['HTTP_X_REQUESTED_WITH'] === 'XMLHttpRequest');
    }
}